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
	int myPriority; 

	printf("Please input the Scheduling method (0-normal,1-FIFO,2-RR): ");
	scanf("%d",&myScheduler); 
	switch(myScheduler)
	{
		case 0 : printf("Current scheduling method is SCHED_NORMAL\n");break;
		case 1 : printf("Current scheduling method is SCHED_FIFO\n");break;
		case 2 : printf("Current scheduling method is SCHED_RR\n");break;
		default: printf("Invalid input.\n"); return -1;break;
	}


	int i = 0;
	int processpid[50];

	while(1)
	{
		printf("Please input the id of the testprocess (quit by -1) : ");
		scanf("%d",&processpid[i]);
		if (processpid[i]==-1)
		{
			break;
		}
		i ++ ;
	}

	// set Priority
	if (myScheduler == 0) //  sched_get_priority_max(0) only can be zero
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

	switch(sched_getscheduler(processpid[0]) ){
	case 0: printf("SCHED_NORMAL\n");
	  break;
	case 1:printf("SCHED_FIFO\n");
	  break;
	case 2:printf("SCHED_RR\n");
	  break;
	default:
	  printf("unknown");
	}

	param.sched_priority = myPriority;
	for (i = i - 1; i >= 0; --i) //exclude the -1
	{
		if (sched_setscheduler(processpid[i], myScheduler, &param) == -1) //设置优先级
		{ 
	        perror("sched_setscheduler() failed"); 
	        return -1;
		} 
	}
	
	printf("cur scheduler : ");

		switch(sched_getscheduler(processpid[0]) ){
	case 0: printf("SCHED_NORMAL\n");
	  break;
	case 1:printf("SCHED_FIFO\n");
	  break;
	case 2:printf("SCHED_RR\n");
	  break;
	default:
	  printf("unknown");
	}


	return 0;
}
