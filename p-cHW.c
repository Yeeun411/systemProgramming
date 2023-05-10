//
//  p-cHW.c
//  studyForSPMidterm
//
//  Created by 강예은 on 2023/05/02.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "linkedlist.h"

void *producer(void*);
void *consumer(void*);

#define MAX_BUF 100

// Shared variables
struct LinkedList int_buffer_queue;
int count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t buffer_has_space = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_has_data = PTHREAD_COND_INITIALIZER;

int main(void){
    int i;
    pthread_t threads[2];

    ListInit(&int_buffer_queue);//make linkedlist

    pthread_create (&threads[0], NULL, producer, NULL);//create thread[0]
    pthread_create (&threads[1], NULL, consumer, NULL);//create thread[1]
    for (i=0; i< 2; i++)
        pthread_join(threads[i], NULL);//wait until threads end

    freeAllNode(&int_buffer_queue);//make all linkedlist nodes free
    return 0;
}

void *producer (void *v){
    int i = 0;
    while(1){
        pthread_mutex_lock(&mutex);//mutex locked
        if (isFull(&int_buffer_queue)) // if linkedlist is full,
            pthread_cond_wait(&buffer_has_space, &mutex);//wait
        
        int data = i;
        i += 1;
        insertItem(&int_buffer_queue, data);//insert an item at head
        printf("@@producer = %d\n",data);
        count++;

        pthread_cond_signal(&buffer_has_data);//signal
        pthread_mutex_unlock(&mutex);//mutex unlocked

        usleep(200*1000); // Sleep for some amount of time
    }
}

void *consumer (void *v){
    int data;
    while(1){
        pthread_mutex_lock(&mutex);//mutex locked
        if (isEmpty(&int_buffer_queue)) // if linkedlist is empty,
            pthread_cond_wait(&buffer_has_data, &mutex);//wait

        data = getItem(&int_buffer_queue);//get an item at tail
        printf("consumer = %d@@\n", data);//print getItem
        count--;

        pthread_cond_signal(&buffer_has_space);//signal
        pthread_mutex_unlock(&mutex);//mutex unlocked


        usleep(1000*1000); // Sleep for some amount of time
    }
}
