//
//  prod-cons.c
//  studyForSPMidterm
//
//  Created by 강예은 on 2023/05/10.
//

#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_BSIZE 10
int cnt=0;
int buf[MAX_BSIZE];
static sem_t hsem, num_buff, num_data;
void *Producer(void *arg){ // producer
    int i, tmp = 0;
    for(;;) {
        sleep(1);//test3
        sem_wait(&num_buff);
        sem_wait(&hsem); //access
        buf[cnt] = tmp;
        tmp = tmp +3;
        printf("prod cnt: %d buf[%d] = %d\n", cnt, cnt, tmp);
        cnt++; //use buffer
        //sleep(1);//test1
        sem_post(&hsem);
        sem_post(&num_data); //wait
        //sleep(1);//test2
    }
    printf("Producer Ends\n");
    return NULL;
}
void *Consumer(void *arg){ // consumer
    int i, tmp;
    for(;;) {
        sem_wait(&num_data);
        sem_wait(&hsem);
        cnt--; //get data
        tmp = buf[cnt];
        printf("cons cnt: %d buf[%d] = %d\n", cnt, cnt, tmp);
        sleep(1);//test1, test3
        sem_post(&hsem);
        sem_post(&num_buff);
        //sleep(1);//test2
    }
    printf("Consumer Ends\n");
    return NULL;
}
int main(int argc, char *argv[]){
    pthread_t thread1;
    pthread_t thread2;
    if (sem_init(&hsem, 0, 1) < 0){
        fprintf(stderr, "Semaphore Initialization Error\n");
        return 1;
    }
    if (sem_init(&num_buff, 0, MAX_BSIZE) < 0){
        fprintf(stderr, "Semaphore Initialization Error\n");
        return 1;
    }
    if (sem_init(&num_data, 0, 0) < 0){
        fprintf(stderr, "Semaphore Initialization Error\n");
        return 1;
    }
    pthread_create(&thread1, NULL, Producer, NULL);
    pthread_create(&thread2, NULL, Consumer, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("%d\n", cnt);
    sem_destroy(&hsem);
    return 0;
}
