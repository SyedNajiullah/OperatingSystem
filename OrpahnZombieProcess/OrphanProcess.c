#include<stdio.h> /*Basic input output*/
#include<sys/types.h> /* for pid_t*/
#include<unistd.h>/*for fork() and execlp() fucntions*/
#include<sys/wait.h> /*for wait(NULL);*/
#include<stdlib.h>/*for exit(0)*/

int main(void){

    pid_t pid = fork();
    if(pid == 0){
        sleep(5); /*wait for 5 seconds*/
        printf("After 5 seconds child is executing\n");
        printf("Child process id = %d and parnet process id %d \n", getpid(), getppid());
    }else if(pid > 0){
        printf("Parent process id = %d and child process id %d \n", getpid(), getppid());
        exit(0); /*exit from the parent process and making a orphan*/
    }else{
        perror("forkin failed\n");
    }

    return 0;
}