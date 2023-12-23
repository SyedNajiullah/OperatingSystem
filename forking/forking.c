#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(void){

    pid_t B = fork();
    printf("A forks B\n");
    if(B == 0){
        pid_t E = fork();
        printf("B forks E\n");
        if(E == 0){
            /*CHILD process of E continues*/
        }else if(E > 0){
            pid_t F = fork();
            printf("B forks F\n");
            if(F == 0){
                pid_t H = fork();
                printf("F forks H\n");
                if(H == 0){
                    /*CHILD process of H continues*/
                }else if(H > 0){
                    /*PARENT process of H continues*/
                }else{
                    perror("Forking failed for process H\n");
                }
            }else if(F > 0){
                /*PARENT process of F continues*/
            }else{
                perror("forking failed for process F\n");
            }
        }else{
            perror("Forking fialed for process E\n");
        }
    }else if(B > 0){
        pid_t C = fork();
        printf("A forks C\n");
        if(C == 0){
            pid_t G = fork();
            printf("C forks G\n");
            if(G == 0){
                /*CHILD process of G continues*/
            }else if(G > 0){
                /*PARENT process of G continues*/
            }else{
                perror("forking failed for process G\n");
            }
        }else if(C > 0){
            pid_t D = fork();
            printf("A forks D\n");
            if(D == 0){
                /*CHILD process of D continues*/
            }else if(D > 0){
                /*PARENT process of D continues*/
            }else{
                perror("Forking failed for process D\n");
            }
        }else{
            perror("Forking failed for process C\n");
        }
    }else{
        perror("Forking failed for process B\n");
    }
    
    return 0;
}

/*SAMPLE CODE*/
/*
pid_t pid = fork();
    if(pid == 0){
        printf("Child id : %d and parent id : %d\n", getpid(), getppid());
    }else if(pid > 0){
        printf("Parent id : %d and child id : %d\n", getpid(), getppid());
    }else{
        perror("forking failed\n");
    }
*/

/*Forking creats a parent and a child process having different id's*/
/*Q :                                       A
                                          / | \
                                        /   |   \
                                       B    C    D
                                      / \   |    
                                     /   \  |
                                    E    F  G
                                         |
                                         |
                                         H
*/