#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/unistd.h>
#include <linux/syscalls.h>
#include <linux/slab.h>
#include <linux/uaccess.h>


MODULE_LICENSE("Dual BSD/GPL");

#define __NR_ptreecall 356

struct prinfo{
  pid_t parent_pid;
  pid_t pid;
  pid_t first_child_pid;
  pid_t next_sibling_pid;
  long state;
  long uid;
  char comm[64];
};

void copy_from_task_to_prinfo(struct prinfo *process_info, struct task_struct *task){
  //get information from task
  //get pid, parent,state,uid and comm
  process_info->pid = task->pid;  // according to the Internet, threads are treated as LWP, so different threads belonging to the same process has different pid.
  process_info->parent_pid = task->parent->pid;
  process_info->state = task->state;
  process_info->uid = task->cred->uid;
  strcpy(process_info->comm, task->comm);
  
  //get the first_child
  // parents's children is siblings of one child.
  if (!list_empty(&task->children))
    process_info->first_child_pid = list_entry(task->children.next, struct task_struct, sibling)->pid;
  else
    process_info->first_child_pid = 0;

  //get the next_sibling
  if (task->parent == task) //Process 'swapper' whose pid = 0 and parent is itself has no siblings
      process_info->next_sibling_pid = 0;
  else if (!list_is_last(&task->sibling, &task->parent->children)) //we should not use the function list_empty(&task->sibling), because sibling is a cycle.
            process_info->next_sibling_pid = list_entry(task->sibling.next, struct task_struct, sibling)->pid;
          else   process_info->next_sibling_pid = 0;
 
}

int tasks_dfs_copy(struct task_struct *task, struct prinfo *process_info, int nr)
{
	struct task_struct *cur = task;
	int ret = 0; // the number of process being recorded
	//bool flag = true;

	while (true) {
	  if (thread_group_leader(cur)) {// this 'if' may make sense, but it just guarantees that I get the process( the first thread ) itself instead of one of its other threads. 
	    if (ret < nr) {
	      copy_from_task_to_prinfo(process_info, cur);
	      ++process_info;                                                   //next process_info
	    }
	    if( ++ret == nr) return ret;  // max num
	  }
	  //else {printk("hhhhhh");}

	  //search the first child first
	  if (!list_empty(&cur->children)) {
	    cur = list_entry(cur->children.next, struct task_struct, sibling);
	    continue;
	  }

	  //search the next_sibling 
 	  if (!list_is_last(&cur->sibling, &cur->parent->children)) {
	    cur = list_entry(cur->sibling.next, struct task_struct, sibling);
	    continue;
	  }
	  
	  //to find some process that has not been searched
	  while (cur->parent->parent != cur->parent  && list_is_last(&cur->parent->sibling, &cur->parent->parent->children) ) {// to find one process that not be searched.
	    cur = cur->parent;
	  }
	  
	  if (cur->parent->parent == cur->parent)  return ret; //return Process 'swapper', it means that it finds the second child of 'swapper'.
	  else cur = list_entry(cur->parent->sibling.next, struct task_struct, sibling);
	
	}

	return ret;
}



static int (*oldcall)(void);

static int sys_ptreecall(struct prinfo *buf, int *nr){
  // printk("this is my system first call!\n the uid = %ld\n str:%s\n",n,str);

  unsigned long bufsize;
  struct prinfo *process_info,*process_info_head;
  int pnr,ret = 0;

  struct task_struct *task;
  //  struct prinfo abc;

  read_lock(&tasklist_lock);
  task = &init_task;
  while (task->parent != task)//get the Process 0.
    task = task->parent;
  read_unlock(&tasklist_lock);
  
  if (!buf || nr < 1) // illegal value
    return -EINVAL;

  if (copy_from_user(&pnr, nr, sizeof(int))) // does not get the sound parameter
    return -EFAULT; //errno: 14

  bufsize = pnr * sizeof(struct prinfo);
  process_info = kmalloc(bufsize, GFP_KERNEL);
  
  // if (copy_from_user(process_info, buf, bufsize))
  // return -EFAULT;
  
  process_info_head = process_info;

  read_lock(&tasklist_lock);
  ret = tasks_dfs_copy(task, process_info, pnr);
  read_unlock(&tasklist_lock);
  
  if (copy_to_user(buf, process_info_head, bufsize))
    return -EFAULT;
  if (ret < pnr)
  if (copy_to_user(nr, &ret, sizeof(int)))
    return -EFAULT;
  kfree(process_info);

  return ret;
}

static int addsyscall_init(void){
  long *syscall = (long*)0xc000d8c4;
  oldcall = (int(*)(void))(syscall[__NR_ptreecall]);
  syscall[__NR_ptreecall] = (unsigned long) sys_ptreecall;
  printk(KERN_INFO "module load!\n");
  return 0;
}

static int addsyscall_exit(void){
  long *syscall = (long*)0xc000d8c4;
  syscall[__NR_ptreecall] = (unsigned long) oldcall;
  printk(KERN_INFO "module exit!\n");
}

module_init(addsyscall_init);
module_exit(addsyscall_exit);


