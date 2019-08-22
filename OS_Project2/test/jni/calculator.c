#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>  // for gettimeofday()

//calculate n!
void function(int n)
{
  int i = 0;
  volatile   long long  result = 1;
	for(i = n; i > 0; i--){
		result = result*n;
	}
	//	printf("Result:%lld\n", result);
}


int main()
{
	struct timeval tpstart,tpend;
	float timeuse;
	int n = 0;
	int  getinput = 0;

	while(1){
	  
	  printf("Please input one number, it will calculate n^n and show you the running time (-1 to quit):\n");
	  if(getinput == 0)  scanf("%d",&n);
	  
	  if(n == -1) break;
	  
	  if(n >= 1){
	        getinput = 1;
		gettimeofday(&tpstart,0);
		function(n);
		gettimeofday(&tpend,0);
		timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+ tpend.tv_usec-tpstart.tv_usec;
		timeuse/=1000;
		printf("used time: %f ms\n",timeuse);
		//exit(0);
	    }
	    
	    n = 0;
	    getinput = 0;
	}

	return 0;
}
