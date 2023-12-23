#include<stdio.h> /*Basic input output*/
#include<sys/types.h> /* for pid_t*/
#include<unistd.h>/*for fork() and execlp() fucntions*/
#include<fcntl.h> /*for O_WRONLY | O_CREAT | O_TRUNC*/

int main(void){
    
    int fd1[2];
    int fd;
    
    if(pipe(fd1) == -1){
        perror("piping failed\n");
    }else{
        pid_t B = fork();
        if(B == 0){
            fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
            close(fd1[1]);
            
            dup2(fd1[0], 0);/*Mapping fd1[0] write end on standart input of file discriptor table*/
            dup2(fd, 1);/*mapping fd in writing end of descriptor table*/
            
            close(fd);
            close(fd1[0]);
            execlp("sort", "mysort", NULL);
        }else if(B > 0){
            close(fd1[0]);
            close(fd);
            
            dup2(fd1[1], 1);/*Mapping fd1[1] write end on standart output of file discriptor table*/
            
            close(fd1[1]);
            
            execlp("ls", "myls", NULL);
        }else{
            perror("Forking failed\n");
        }
    }
    return 0;   
}

/*
Q : Implement the following 
    ls | sort > output.txt
A : Process tree will look like this
                                        (parnet)A (for "ls" part) 
                                                |
                                        (child )B (for "sort > output.txt")
*/