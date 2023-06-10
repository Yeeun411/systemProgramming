#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX 1024
#define PORT 30000
#define BACKLOG 5

int main(int argc, char *argv[]){
    int sd, nsd, pid, bytes, cliaddrsize;
    struct sockaddr_in cliaddr, servaddr;
    char data[MAX];
    printf("create socket...\n");
    if((sd = socket(PF_INET, SOCK_DGRAM, 0))<0){
        fprintf(stderr, "can't open socket.\n");
        exit(1);
    }
    bzero((char*) &servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    
    printf("bind socket...\n");
    if (bind(sd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0){
        fprintf(stderr, "can't bind to socket.\n");
        exit(1);
    }
    listen(sd, BACKLOG);
    
    while(1){
        bytes = recvfrom(sd, data, MAX, 0, (struct sockaddr *)&cliaddr, &cliaddrsize);
        
        printf("[receive data] %s", data);
        printf("[resend to the client]\n");
        
        sendto(sd, data, bytes, 0, (struct sockaddr *)&cliaddr, cliaddrsize);
    }
}
