#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define ARRAY_SIZE 100000
#define MALLOC_SIZE 100000
#define SHM_SIZE 100000
char array[ARRAY_SIZE]; /* uninitialized data = bss */
int main(void)
{
	int shmid;
	char *ptr, *shmptr;
	printf("array[] from %x to %x \n", &array[0], &array[ARRAY_SIZE]);
	printf("stack around %x \n", &shmid);
	if ((ptr = malloc(MALLOC_SIZE)) == NULL) perror("malloc error");
		printf("malloced from %x to %x \n", ptr, ptr + MALLOC_SIZE);
	if ((shmid = shmget(0x01010101, SHM_SIZE, IPC_CREAT | 0666)) <0)
		perror("shmget error");
	if ((shmptr = shmat(shmid, 0, 0)) == (void *) -1)
		perror("shmat error");
	printf("shared memory attached from %x to %x \n", shmptr, shmptr + SHM_SIZE);
	if (shmctl(shmid, IPC_RMID, 0) < 0)
		perror("shmctl error");
	return 0;
}
