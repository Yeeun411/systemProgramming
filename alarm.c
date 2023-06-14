#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static void sig_catcher(int);

int alarmed = 0;
int main(){
	int pid;
	signal(SIGALRM, sig_catcher);
	alarm(3);

	while(alarmed == 0){
		printf("waiting alarm...\n");
		sleep(1);
	}
	printf("after alarm in main\n");
}

void sig_catcher(int signo){
	//alarmed = 1;
	printf("alarm\n");
	alarm(3);
}
