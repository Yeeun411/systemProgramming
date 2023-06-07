#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/types.h> 
#include <stdlib.h>
#include <sys/stat.h> 
#define SIZE 128 
#define FIFO "fifo"
#define FIFO_1 "fifo_1"
#define FIFO_2 "fifo_2"
void *receiver(void *value){
	int fd, cmd, pid;
	char buffer[SIZE];
	if((fd=open(FIFO_1, O_RDWR))==-1){
		perror("open failed");
	}
	
	while(1){
		memset(buffer, 0, SIZE);
		if(read(fd, buffer, SIZE) == -1){
			perror("read failed");
			exit(1);
		}
		printf("\n[SERVER] %s", buffer);
		printf("\n[CLIENT]");
		fflush(stdout);
		
	}

}
main(int argc, char *argv[]) {
	int fd,i;
	char buffer[SIZE];
	
	pthread_t t_receiver;
	
	if((fd=open(FIFO_2,O_RDWR)) == -1) { 
		perror("open failed");
		exit(1);
		}
		
	pthread_create(&t_receiver, NULL, receiver, NULL);
	
	printf("\n[SERVER]");
	fflush(stdout);
	
	while(1){
		fgets(buffer, SIZE, stdin);
		write(fd, buffer, SIZE);
		if(!strcpy(buffer, "quit"))
			exit(0);
	}
}
