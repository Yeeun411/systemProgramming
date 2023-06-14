#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

#define TIMEOUT 3 // login time limit = 3 sec. After alarm, ring a bell.
#define MAXTRIES 5 // retry login five times when timeout
#define LINESIZE 100 // login name/passwd buffer size
#define CTRL_G '\007' // bell
#define TRUE 1
#define FALSE 0

volatile int timed_out; // set when an alarm occurs
char myline [LINESIZE]; // character buffer
void sig_catch(int); // alarm signal handler
char *quickreply(char *prompt);

int main()
{
	quickreply("login-name:");
}

char *quickreply(char *prompt) {
	void (*was)(int);
	int ntries, i;
	char *answer;
	
	was = signal(SIGALRM, sig_catch);
	siginterrupt(SIGALRM, TRUE);
	
	// set error return when a signal occurs
	for (ntries = 0; ntries <MAXTRIES; ntries++) { // retry loop
	
		timed_out = FALSE;
		printf("\n%s > ",prompt);
		fflush(stdout);
		
		alarm(TIMEOUT);
		for (i = 0; i < LINESIZE; i++) {
			if ((myline[i] = getchar()) < 0)
				break; // error return by alarm
			if (myline[i] == '\n') {
				myline[i] = 0;
				break; // end of line input
			}
		}
		// normal case or alarm case here
		alarm(0); // reset the alarm
		if (!timed_out) { // normal case
			printf("%s",myline);
			break;
		} // end of retry loop
		// normal or fail 5 times
		answer = myline;
		signal(SIGALRM,was);
		return(ntries == MAXTRIES ? ((char *) 0) : answer);
	}
}
