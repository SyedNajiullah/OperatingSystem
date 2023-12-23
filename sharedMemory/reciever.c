#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<string.h>
int main(void)
{
	void *shared_memory;
	char buffer[100];
	int shmid;
	shmid=shmget((key_t)1122,1024,0666);
	printf("Key of shared memory is = %d\n",shmid);
	shared_memory=shmat(shmid,NULL,0);
	printf("Process attach at %p\n",shared_memory);
	printf("Data Read from shared memory is: %s\n", (char *)shared_memory);
    return 0;

}