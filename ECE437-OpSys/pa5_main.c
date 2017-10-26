/*=========================================================*/ 
/*  race.c --- for playing with ECE437                     */ 
/*=========================================================*/ 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h>  
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>

sem_t mutex; // semaphore global variable

struct Bank {
    int balance[2];
};

struct Bank *bank;

// routine for thread execution
void* MakeTransactions() { 
    int i, j, tmp1, tmp2, rint;
    double dummy;

    // wait on semaphore
    //sem_wait(&mutex);
    for (i=0; i < 100; i++) {  
        rint = (rand()%30)-15; 
        if (((tmp1=bank->balance[0])+rint) >=0 &&
                ((tmp2=bank->balance[1])-rint)>=0) { 
            sem_wait(&mutex);
            bank->balance[0] = tmp1 + rint;
            sem_post(&mutex); 
            for (j=0; j < rint*100; j++) {
                dummy=2.345*8.765/1.234; // spend time on purpose
            }
            sem_wait(&mutex);
            bank->balance[1] = tmp2 - rint;
            sem_post(&mutex); 
        }  
    } 
    // increment value of semaphore
    //sem_post(&mutex);
    return NULL; 
} 

int main(int argc, char **argv) { 

    int i;
    void* voidptr = NULL;
    
    // initialize semaphore
    sem_init(&mutex, 0, 1);

    // shared memory
    bank = mmap(NULL, sizeof(struct Bank), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    
    //check if bank is not NULL
    bank->balance[0] = 100;
    bank->balance[1] = 100;

    pid_t pid;
    srand(getpid()); 

    printf("\nInit balances A:%d + B:%d ==> %d!", 
            bank->balance[0],bank->balance[1],bank->balance[0]+bank->balance[1]); 

    pid=fork();
    if (pid < 0) {
        fprintf(stderr, "Fork failed");
        return 1;
    }
    if (pid == 0) {
        printf("\nChild computing ...");
        MakeTransactions();
        printf("\nChild process complete");
        printf("\nLet's check the balances A:%d + B:%d ==> %d ?= 200",
            bank->balance[0],bank->balance[1],bank->balance[0]+bank->balance[1]);
        return 0;
    }
    else {
        printf("\nParent computing...\n");
        MakeTransactions();
        wait(NULL);
        printf("\nParent process complete\n");
        printf("Let's check the balances A:%d + B:%d ==> %d ?= 200\n\n",
            bank->balance[0],bank->balance[1],bank->balance[0]+bank->balance[1]);
        return 0;
    }
    sem_destroy(&mutex);
    munmap(bank, sizeof(struct Bank));
    return 0; 
}
