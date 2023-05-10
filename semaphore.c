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

int cnt = 0;
static sem_t hsem;

void *Thread1(void *arg){
   int i, tmp;
   for(i=0; i<1000; i++){
      tmp = cnt;
      printf("Thread1, cnt = %d\n", cnt);
      usleep(1000);
      cnt=tmp+1;
      if(cnt >= 1000)
         sem_post(&hsem);
   }
   printf("Thread1 End\n");
   return NULL;
}

void *Thread2(void *arg){
   int i, tmp;
   for(i=0; i<1000; i++){
      if(cnt < 1000)
         sem_wait(&hsem);
      tmp=cnt;
      printf("Thread2, cnt = %d\n", cnt);
      usleep(1000);
      cnt=tmp+1;
   }
   printf("Thread2 End\n");
   return NULL;
}

int main(int argc, char *argv[]){
   pthread_t thread1;
   pthread_t thread2;
   if (sem_init(&hsem, 0, 1) < 0){
      fprintf(stderr, "Semaphore Initilization Error\n");
      return 1;
   }
   pthread_create(&thread1, NULL, Thread1, NULL);
   pthread_create(&thread2, NULL, Thread2, NULL);
   pthread_join(thread1, NULL);
   pthread_join(thread2, NULL);
   printf("%d\n", cnt);
   sem_destroy(&hsem);

   return 0;
}
