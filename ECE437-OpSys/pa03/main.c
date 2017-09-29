/*******************************************************************
 
 ECE 437: Operating Systems PA03
 Professor: Dr. Shu
 Created by: Panayioti Kitsos, Ryan Vacek
 Date: 9/28/17

 Makefile:
  make all - comiles and links files into executable myfib
  make test1 - runs the executable myfib (./mylib -F n -S 6)
  make test2 - runs the executable myfib (./mylib -F 6 -S 3)
  make clean - clean up files

*******************************************************************/
#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h> 
#include <sys/stat.h> 

int fib_seq(int x);

int main(int argc, char **argv)  
{
    // Definitions
    int x=0, fib=0;
    int c, n, m, i;
    int Fflag, Sflag; 
    pid_t pid; 

    // interprocess communication
    const int size=4096; 
    char *shared_memory; 

    int segment_id=shmget(IPC_PRIVATE, size, S_IRUSR|S_IWUSR);
    shared_memory= (char *)shmat(segment_id, NULL, 0); 

    // command line options using getopt for -F and -S
    while ((c=getopt(argc, argv, "F:S:")) != -1) 
        switch(c) 
        {
            case 'F':
                Fflag = 1;
                //printf("test\n");
                n= atoi(optarg);
                break;
            case 'S':
                Sflag = 1;
                m= atoi(optarg);
                printf("\nn = %d\nm = %d\n", n, m);
                break;
            default:
                abort();
        }

    //begin fibonacci sequence
    for(i=0; i<=n; i+=1) {

        fib = fib_seq(x);
        x+=1;

        // fork child to compute next Fib numbers recursively
        //if((((x-1)>m)&&((x-2)>m))) {
        if((x-1)>m) {
            pid=fork();
            if (pid < 0) {
                fprintf(stderr, "Fork failed");
                return 1;
            }
            if (pid == 0) {
                printf("\nChild computing next Fib number...\n");
                fib = fib_seq(x); 
                printf("Child process complete\n");
            }
            else {
              printf("\nParent waiting for child to finish...\n");
              wait(NULL);
            }
            return 0;
        }
        // compute next fib numbers recursively
        //else if((((x-1)<=m)&&((x-2)<=m))) {
        else if((x-1)<=m) {
            printf("\nComputing without child...");
            fib = fib_seq(x-1);
        }
        printf("\nFibonacci sequence of %d is %d\n", x-1, fib);
    }
    return 0;
}
