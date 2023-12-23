#include<stdio.h> /*Basic input output*/
#include<sys/types.h> /* for pid_t*/
#include<unistd.h>/*for fork() and execlp() fucntions*/
#include<sys/wait.h>/*for wait(NULL)*/

/* 
Q2. implement the following
        ls -l | wc input.txt | sort
A.  Process tree will look like
                                                A(Parent process)
                                             /  |  \
                                            /   |   \(ALL childs)
                                (for ls -l)B   C    D(for sort)
                                                |
                                        (for wc input.txt)
*/

int main(void){

    int fd1[2];
    int fd2[2];

    if(pipe(fd1) == -1 || pipe(fd2) == -1){
        perror("piping failed\n");
    }else{
        pid_t B = fork();
        if(B == 0){
            close(fd2[0]);
            close(fd2[1]);
            close(fd1[0]);
            dup2(fd1[1], 1);/*Mapping fd1[1] write end on standart output of file discriptor table*/
            close(fd1[1]);

            execlp("ls", "ls", "-l", NULL);
        }else if(B > 0){
            pid_t C = fork();
            if(C == 0){
                close(fd1[1]);
                close(fd2[0]);

                dup2(fd1[0], 0);/*Mapping fd1[0] write end on standart input of file discriptor table*/
                dup2(fd2[1], 1);/*Mapping fd2[1] write end on standart output of file discriptor table*/

                close(fd1[0]);
                close(fd2[1]);

                execlp("wc", "wc", "input.txt", NULL);
            }else if(C > 0){
                pid_t D = fork();
                if(D == 0){
                    close(fd1[1]);
                    close(fd1[0]);
                    close(fd2[1]);

                    dup2(fd2[0], 0);/*Mapping fd2[0] write end on standart input of file discriptor table*/
                    close(fd2[0]);

                    execlp("sort", "sort", NULL);
                }else if(D > 0){
                    close(fd1[1]);
                    close(fd1[0]);
                    close(fd2[1]);
                    close(fd2[0]);
                    wait(NULL);
                }else{
                    perror("forking failed for process D\n");
                }
            }else{
                perror("forking failed for process C\n");
            }
        }else{
            perror("forking failed for process B\n");
        }
    }
    return 0;
}