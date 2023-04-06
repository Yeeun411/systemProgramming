#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
    int i = 10000;

    // fork()\ub85c child create
    if ((pid = fork()) < 0) {
        perror("fork error");
    } else if (pid == 0) { // child process
        printf("Child: pid=%d\n", getpid());

        // \ubb34\ud55c \ub8e8\ud504: i \uac12\uc744 \ucd9c\ub825\ud558\uace0 1 \uc99d\uac00\uc2dc\ud0b4
        while (1) {
            printf("c(%d)\n", i);
            i++;
            sleep(1); // 1\ucd08 \ub300\uae30
        }
    } else { // parent process
        printf("Parent: pid=%d\n", getpid());
        printf("Parent: Child pid=%d\n", pid);
        
        sleep(1); // 1\ucd08 \ub300\uae30

        printf("Parent : exit\n");
        exit(0); // parent process \uc885\ub8cc
    }
}
