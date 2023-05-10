//
//  pause.c
//  studyForSPMidterm
//
//  Created by 강예은 on 2023/05/10.
//

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void sig_catch(int sig_no){
    printf("sig No(%d) : sig_catch is called\n", sig_no);
}

int main(){
    int pid;
    int status;
    signal(SIGUSR1, sig_catch);
    if ((pid = fork()) == 0) { // child
    // this pause may block forever: why?
        sleep(2);//test1,test2
        pause();
        printf("Child wake up\n");
        exit(0);
    } else { // parent
        sleep(1);//test1
        //sleep(3);//test2
        kill (pid, SIGUSR1); // send SIGUSR1 to the child process
        wait(&status);
    }
}
