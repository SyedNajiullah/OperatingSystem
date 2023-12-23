#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(void){

    pid_t pid = fork();
    if(pid == 0){
        printf("Child id : %d and parent id : %d\n", getpid(), getppid());
    }else if(pid > 0){
        printf("Parent id : %d and child id : %d\n", getpid(), getppid());
    }else{
        perror("forking failed\n");
    }

    return 0;
}