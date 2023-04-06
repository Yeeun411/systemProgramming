#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include <sys/wait.h>
#include <fcntl.h>

#define BUFFER_SIZE 10

int main() {
    pid_t pid1, pid2;//pid 2개
    int pipe1[2], pipe2[2];//pipe를 위한 descripters
    char buffer[BUFFER_SIZE];//buffer
    ssize_t n;
    int status;
    
    pipe(pipe1);//pipe1[0] for reading, pipe1[1] for writing
    pipe(pipe2);//pipe2[0] for reading, pipe2[1] for writing

    // Open input and output files
    int input = open("input-file", O_RDONLY);
    int output = open("outputfile", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    
    //input에 있는 text값을 pipe1[1]에 적는 과정
    while ((n = read(input, buffer, BUFFER_SIZE)) != 0) {// until EOF
        write(pipe1[1], buffer, BUFFER_SIZE);//pipe1 write에 buffer에 있는 값 저장
    }
    close(pipe1[1]);//pipe1[1] write 닫기
    close(input);
    
    pid1 = fork();// Fork child 1
    if (pid1 == 0) {
        // Child 1 process
        //pipe1[0] read에서 값을 읽어 대문자로 바꾼 뒤 그 값을 pipe2[1]에 적는 과정
        while ((n = read(pipe1[0], buffer, BUFFER_SIZE)) != 0){ // until EOF
            for (int i = 0; i < BUFFER_SIZE; i++) {
                buffer[i] = toupper(buffer[i]);//buffer에 있는 값을 대문자로 바꾸는 과정
            }
            write(pipe2[1], buffer, BUFFER_SIZE);//pipe2에 대문자 값 적는 과정
        }
        close(pipe2[1]);//pipe2[1] write 닫기
        return 0;//child 1 exit
    }
    else {
        pid2 = fork();// Fork child2
        if (pid2 == 0) {
            // Child 2 process
            //pipe2[0] read에서 값을 읽어 outputfile에 적는 과정
            while ((n = read(pipe2[0], buffer, BUFFER_SIZE)) != 0) {// until EOF
                write(output, buffer, BUFFER_SIZE);//buffer에 있는 값을 파일에 적는 과정
            }
            close(output);//파일 닫기
            return 0;//child2 exit
        }
        else {
            // Parent process
            waitpid(pid1, &status, 0);//waiting child1
            waitpid(pid2, &status, 0);//waiting child2
        }
    }
    return 0;
}
