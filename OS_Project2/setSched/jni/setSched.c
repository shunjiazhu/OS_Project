#include <sched.h>
#include <stdio.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/unistd.h>

int main(int argc, char const *argv[])
{
	struct sched_param param;
	int myScheduler;
	printf("Please input the Choice of Scheduling algorithms (0-normal,1-FIFO,2-RR): ");

	scanf("%d",&myScheduler); 
	switch(myScheduler)
	{
		case 0 : printf("Current scheduling algorithm is SCHED_NORMAL\n");break;
		case 1 : printf("Current scheduling algorithm is SCHED_FIFO\n");break;
		case 2 : printf("Current scheduling algorithm is SCHED_RR\n");break;
		default: printf("Invalid input.\n"); return -1;break;
	}

	int myPriority; 
	int processpid;

	//set the process id
	printf("Please input the id of the testprocess : ");
	scanf("%d",&processpid);

	//set the priority
	if (myScheduler == 0)
	{
		myPriority = 0;
	}
	else
	{
		printf("Set Process's priority (1-99): ");

		scanf("%d", &myPriority);

		if (myPriority < 1 || myPriority > 99)
		{
			perror("Priority level doesn't exist.");
			return -1;
		}
	}
	printf("current scheduler's priority is : ");
	printf("%d\n",myPriority);

	printf("pre scheduler : ");

	switch(sched_getscheduler(processpid) ){
	case 0: printf("SCHED_NORMAL\n");
	  break;
	case 1:printf("SCHED_FIFO\n");
	  break;
	case 2:printf("SCHED_RR\n");
	  break;
	default:
	  printf("unknown");
	}
	
	//	printf("%d\n", sched_getscheduler(processpid));
	param.sched_priority = myPriority;

	if (sched_setscheduler(processpid, myScheduler, &param) == -1) //设置优先级
	{ 
	        perror("sched_setscheduler() failed"); 
	        return -1;
	} 
	printf("cur scheduler : ");

	switch(sched_getscheduler(processpid) ){
	case 0: printf("SCHED_NORMAL\n");
	  break;
	case 1:printf("SCHED_FIFO\n");
	  break;
	case 2:printf("SCHED_RR\n");
	  break;
	default:
	  printf("unknown");
	}
	//printf("%d\n", sched_getscheduler(processpid));
	return 0;
}

