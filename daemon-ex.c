//
//  daemon-ex.c
//  hw3
//
//  Created by 강예은 on 2023/04/05.
//

#include <stdio.h>
 #include <stdlib.h>
 #include <sys/types.h>
 #include <unistd.h>
 int main(void)
 {
     pid_t   pid;
     int i = 10000;
     
     if ((pid = fork()) < 0) {
         perror("fork error");
     }
     else if (pid == 0) { /* child process \uf0e0 daemon */
         printf("Child: pid=%d\n",getpid());
    close(0);
    close(1);
    close(2);
    setsid(); //terminal close, create new session and process group
    while(1) {
        printf("c(%d)\n",i);
        i++;
        sleep(1);
        printf("Child process : pid = %d, ppid = %d, pgrp = %d, pgid = %d\n", getpid(), getppid(), getpgrp(), getpgid(getpid()));//
         }
      }
      else { /* parent process */
          printf("Parent: pid=%d\n",getpid());
          printf("Parent: Child pid=%d\n",pid);
    sleep(1);
        printf("Parent : exit\n");
        printf("Parent process : pid = %d, ppid = %d, pgrp = %d, pgid = %d\n", getpid(), getppid(), getpgrp(), getpgid(getpid()));
    exit(0);
    }
}
