#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    pid_t child;
    
    if((child = fork()) == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if(child == 0)                 //子进程中
    {
        printf("5140219105child: %d\n",getpid());
	if(execl("/data/OsPrj5140219105/ptreeARM","./ptreeARM",(char *)0 ) == -1 )  
	  {  
	    perror("execl");  
	    exit(EXIT_FAILURE);  
	  }  
        exit(EXIT_SUCCESS);
    }
    else
    { 
        printf("5140219105parent: %d\n",getpid());
	sleep(2);
    }
    exit(EXIT_SUCCESS);
}
