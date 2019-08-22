#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

#define MAX 300
#define RACKDEAULT 10

sem_t order;// rack, order;//r, rackMax;
sem_t rackmutex,burgerOnRack,cashFree,custWaiting;

int run = 0;
int rackNum = 0;
int rackMax = 0;
//int custNum = 0;
int custRest = 0;

void* customers(void* param);
void* cooks(void* param);
void* cashiers(void* param);

int main(int argc, const char * argv[]) {
    // insert code here...
    //std::cout << "Hello, World!\n";
    int cookT = 0,cashierT = 0,customerT = 0,rackT = 0;
    
    if(argc > 4)
    {
        cookT=atoi(argv[1]);
        cashierT=atoi(argv[2]);
        customerT=atoi(argv[3]);
        rackT = atoi(argv[4]);
        if(cookT > 300 || cashierT > 300 || customerT > 300){
            perror("\too many people!\n");
            exit(0);
        }
    }
    if(argc <= 4)
    {
        perror("illegal arguments!\n");
        exit(0);
    }
    
    
    rackMax = rackT;
    custRest = customerT;
    
    int index[MAX]; //the *th of the people
    int i;
    int ret;
    for (i=0; i < MAX; i++) index[i] = i+1;
    
    
    pthread_t *Cook = (pthread_t *) malloc(cookT * sizeof(pthread_t));
    pthread_t *Cashier = (pthread_t *) malloc(cashierT * sizeof(pthread_t));
    pthread_t *Customer = (pthread_t *) malloc(customerT * sizeof(pthread_t));
    
    
    //sem_init(&mutex1, 0, 1);
    //sem_init(&mutex2, 0, 1);
    sem_init(&rackmutex, 0, 1);
    //sem_init(&cashier, 0, 1);
    sem_init(&burgerOnRack, 0, 0);
    sem_init(&cashFree,0, cashierT);
    sem_init(&custWaiting,0,0);
    sem_init(&order, 0,  0);
    //    sem_init(&rack, 0, 0);
    

    
    printf("Cooks [%d], Cashiers [%d], Customers [%d]\n",cookT,cashierT,customerT);
    printf("Begin run\n");
    
    
    for( i = 0; i < cookT; ++i){
        ret = pthread_create(&Cook[i], NULL, cooks, &index[i]);
        if(ret != 0){
            printf("Create pthread error!(class: cook id : %d)\n", i);
            exit(1);
        }
    }
    for( i = 0; i < customerT; ++i){
        ret = pthread_create(&Customer[i], NULL, customers, &index[i]);
        if(ret != 0){
            printf("Create pthread error!(class: customer id : %d)\n", i);
            exit(1);
        }
    }
    
    for( i = 0; i < cashierT; ++i){
        ret = pthread_create(&Cashier[i], NULL, cashiers, &index[i]);
        if(ret != 0){
            printf("Create pthread error!(class: cashier id : %d)\n", i);
            exit(1);
        }
    }
  
 
   for(i = 0; i < cookT; i++)   pthread_join(Cook[i],NULL); 
    for(i = 0; i < cashierT; i++)    pthread_join(Cashier[i],NULL); 
  for(i = 0; i < customerT; i++)  pthread_join(Customer[i],NULL); 

  
    
  
    sem_destroy(&rackmutex);
    //sem_init(&cashier, 0, 1);
    sem_destroy(&burgerOnRack);
    sem_destroy(&cashFree);
    sem_destroy(&custWaiting);
    sem_destroy(&order);
    //    sem_init(&rack, 0, 0);

    free(Cook);
    free(Cashier);
    free(Customer);

    return 0;
}


void* cooks(void* param){
    int index = *(int*)(param);
    if(!index)  pthread_exit(0);

    while(1){
      if(custRest <= 0){ sem_post(&rackmutex); pthread_exit(0);}
  
       sem_wait(&rackmutex);
      if(custRest <= 0){ sem_post(&rackmutex); pthread_exit(0);}
       
      if(rackNum <= rackMax ){
            printf("Cook[%d] makes a burger\n", index);
            rackNum++;
        }

        sem_post(&rackmutex);
        usleep(100);
    }
    pthread_exit(0);
}

void* customers(void* param){
    int index = *(int*)(param);
    
    // printf("cccccc\n");
    usleep(rand()%1000);
    printf("Customer[%d] come\n", index);
    sem_post(&custWaiting);
    sem_wait(&cashFree);
    
    //ordering a hamburger
    
    sem_post(&order);
    //    printf("ffffff");
    sem_wait(&burgerOnRack);

    //sem_post(&customer);
    pthread_exit(0);
}

void* cashiers(void* param){
    int index = *(int*)(param);
    if(!index)  pthread_exit(0);

    // printf("mmmmmmmm\n");
    
    while(1) {
      if(custRest <= 0) {
	sem_post(&custWaiting);
	sem_post(&order);
	sem_post(&rackmutex);
	sem_post(&burgerOnRack);
	pthread_exit(0);
      }
            
        sem_post(&cashFree);

        sem_wait(&custWaiting);
	if(custRest <= 0){sem_post(&custWaiting); pthread_exit(0);}

        sem_wait(&order);
	if(custRest <= 0){sem_post(&order); pthread_exit(0);}

        printf("Casher[%d] accepts an order\n", index);
        
        while(!rackNum) ;//waiting for rack;
        sem_wait(&rackmutex);
	if(custRest <= 0){sem_post(&rackmutex); pthread_exit(0);}

        --rackNum;
        printf("Casher[%d] take a burger to customer\n", index);
        --custRest;
        sem_post(&burgerOnRack);
        sem_post(&rackmutex);

        usleep(100);
    }
    
    pthread_exit(0);
}
