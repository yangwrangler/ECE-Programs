/*******************************************************************
 
 ECE 437: Operating Systems PA03
 Professor: Dr. Shu
 Created by: Panayioti Kitsos, Ryan Vacek
 Date: 9/28/17

 Makefile:
  main all - comiles and links files into executable myfib
  main test - runs the executable myfib (./mylib -F n -S m)
  main clean - clean up files

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
    int x=0;
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
                printf("n=%d\nm=%d\n", n, m);
                break;
            default:
                abort ();
        }

    //begin fibonacci sequence
    for(i=0; i<=n; i+=1){

        fib_seq(x);
        x+=1;

        // fork child to compute next Fib numbers recursively
        if (((x-1)>m)||((x-2)>m)){

            //printf("Child computing next Fib number...\n");
            pid=fork();
            if (pid < 0) {
                fprintf(stderr, "Fork failed");
                return 1;
            }
            if (pid == 0) {
                printf("Child computing next Fib number...\n");
                fib_seq(x); 
                x+=1; 
                printf("Child process complete\n");
                return 1;
            }
            else {
              printf("\nParent waiting for child to finish...\n");
            }
        }
        // compute next fib numbers recursively
        else if(((x-1)<=m)||((x-2)<=m)) {
            printf("Computing without child...\n");
            fib_seq(x-1);
        }
    }
    return 0;
}
