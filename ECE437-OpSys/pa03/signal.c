/***************************************************************

 ECE 437: Operating Systems PA03 Problem 2
 Professor: Dr. Shu
 Created by: Ryan Vacek and Panayioti Kitsos
 Date: 9/28/17
 
 Signal Handlers:
    Ctrl-c: stops child process and then main process
    Ctrl-z: pauses/resumes child process

 Makefile:
    make signals: compiles program and creates executable for prob2
    make test3: runs executable for prob2
    make clean: cleans files

**************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>

#define PATH "/usr/bin/yes"

static pid_t pid = 0;
static int resume = 1;
static int running = 1;

void cHandler(int sig) {
    char c;
    resume = 1;
    printf("\n*** WARNING ***\nCaught ctrl-c: all processes stopped\n");
    kill(pid, SIGINT);
    running = 0;
}

void zHandler(int sig) {
    if(resume) {
        printf("\n*** WARNING ***\nCaught ctrl-z: child processes paused.\nRepeat command to resume...\n");
        kill(pid, SIGSTOP);
        resume = 0;
    }
    else {
        kill(pid, SIGCONT);
        resume = 1;
    }
}

int main() {
    pid = fork();
    if(pid < 0)
        perror("*** WARNING: Fork failed! ***");
    if(pid == 0) {
        execl(PATH, "yes", NULL);    
    }
    else {
        signal(SIGINT, cHandler);
        signal(SIGTSTP, zHandler);
        while(running) {
        }
        return 0;
    }
    return 0;
}
