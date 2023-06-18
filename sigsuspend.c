#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

void sig_catch (int sig_no)
{
printf("sig_catch, %d\n",sig_no);
}
int main()
{
	int pid;
	sigset_t mysigset, oldsigset;
	
	// empty the set
	sigemptyset(&mysigset);// empty the set
	
	// add SIGUSR1 to the set
	sigaddset(&mysigset, SIGUSR1);
	
	// set a user-defined signal handler
	signal(SIGUSR1, sig_catch);
	
	// block SIGUSR1
	sigprocmask(SIG_BLOCK, &mysigset, &oldsigset);
	
	if ((pid = fork()) == 0) { // child
	// to prevent the early handling before pause()
		sigsuspend(&oldsigset); // unblock and pause!
		printf("Child wake up\n");
		//while(1);
		exit(0);
	} else { // parent
		sleep(1);
		kill (pid, SIGUSR1); // send the SIGUSR1 to the child
		wait(NULL);
	}
} 
