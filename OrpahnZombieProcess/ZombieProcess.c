#include<stdio.h> /*Basic input output*/
#include<sys/types.h> /* for pid_t*/
#include<unistd.h>/*for fork() and execlp() fucntions*/
#include<sys/wait.h> /*for wait(NULL);*/

int main(void){

    pid_t pid = fork();
    if(pid == 0){
        printf("Child process id = %d and parnet process id %d \n", getpid(), getppid());
    }else if(pid > 0){
        wait(NULL); /*So that child executes first*/
        printf("Parent process id = %d and child process id %d \n", getpid(), getppid());
    }else{
        perror("forking failed\n");
    }

    return 0;
}