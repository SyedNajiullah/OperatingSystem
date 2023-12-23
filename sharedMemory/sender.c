#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/shm.h>
#include<stdlib.h>
int main(void)
{
	void *shared_memory;
	char buffer[100];
	int shmid;
	shmid=shmget((key_t)1122,1024,0666|IPC_CREAT);//
	printf("Key of Shared Memory is %d\n",shmid);//
	shared_memory=shmat(shmid,NULL,0);//
	printf("Process attached at %p\n",shared_memory);//
	printf("Enter data to write\n");
	read(0,buffer,100);
	strcpy(shared_memory,buffer);
	printf("You write: %s\n", (char *)shared_memory);
	return 0;
}

