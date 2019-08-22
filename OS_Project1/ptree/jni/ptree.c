//Print the process tree ine the shell.
#include "ptree.h"


#define MAX 200

struct prinfo *levelStack[MAX];
int level = 0;

void level_push(struct prinfo *v)
{
	levelStack[level++] = v;
}


int stack_pop_indent(int parent_pid)
{
         int i;
	 for (i=level; i >0; i--) {
	   if (levelStack[i-1]->pid == parent_pid) 	break;
	 }

	level = i;
	return level;
}


int main(int argc, char **argv)
{
  int nr;
  if(argc >= 2)  nr = atoi(argv[1]);
  else  nr = MAX;

	int i,j;
	struct prinfo *p = malloc(nr * sizeof(struct prinfo));
	int ret = syscall(356, &p[0], &nr);

	if (ret < 0) {
		perror("error");
		return -1;
	}
	for ( i = 0; i < nr; i++) {
	  for ( j = 0; j < stack_pop_indent(p[i].parent_pid); j++)  printf("\t");
	  
	  level_push(&p[i]);
	  printf("%s,%d,%ld,%d,%d,%d,%ld\n", p[i].comm, p[i].pid,
		 p[i].state, p[i].parent_pid,
		 p[i].first_child_pid,
		 p[i].next_sibling_pid, p[i].uid);
	}
  
	return 0;
}


