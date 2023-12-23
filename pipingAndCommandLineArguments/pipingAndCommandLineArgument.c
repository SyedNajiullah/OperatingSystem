#include<stdio.h> /*for input output*/
#include<unistd.h>/*for forking*/
#include<sys/types.h>/*for pid_t*/
#include<stdlib.h>/*for atoi() function*/

/*Q:
    the program should take a array of integers from command line argumnets and send it to both its child. First child will calculate the sum of the array. Second child will calculate the average of the array. Both child will send the result back to the parent and display them from there.
*/

/*A:
    Process tree would look like 
                                            A(parnet) = will take array from command ine arguments
                                          /   \
                                        /       \
             (for sum of array(child1))B         C(for average of array(child2))
*/
int main(int argc, char* argv[]){

    int fd1[2];/* To write the array to the child */
    int fd2[2];/* To return the sum to the parent */
    int fd3[2];/* To write the array to the child */
    int fd4[2];/* To return the average to the parent */

    if(pipe(fd1) == -1 || pipe(fd2) == -1 || pipe(fd3) == -1 || pipe(fd4) == -1){/*Creating necessary pipes*/
        perror("Piping failed\n"); 
    }else{
        pid_t B = fork(); /*Creatinf first child named B*/
        if(B == 0){
            close(fd1[1]); /*Clossing all non-used pipes*/
            close(fd2[0]);
            int arr[argc - 1];
            read(fd1[0], arr, sizeof(arr)); /*reading array form the parent*/
            int sum = 0;
            for(int i = 0; i < argc - 1; i++){ /*Calculating sum*/
                sum += arr[i];
            }
            write(fd2[1], &sum, sizeof(sum));/*Writing it to the parent*/
        }else if(B > 0){
            pid_t C = fork();
            if(C == 0){
                close(fd3[1]);/*Clossing all non-used pipes*/
                close(fd4[0]);
                int arr[argc - 1];
                read(fd3[0], arr, sizeof(arr)); /*reading array form the parent*/
                float avg = 0;
                int count = 0;
                for(int i = 0; i < argc -1 ;i++){ /*Calculating sum*/
                    avg += arr[i];
                    count++;
                }
                avg = avg / count;
                write(fd4[1], &avg, sizeof(avg)); /*Writing it to the parent*/
            }else if(C > 0){
                close(fd1[0]);
                close(fd2[1]);
                close(fd3[0]);
                close(fd4[1]);
                int arr[argc - 1];
                for(int i = 1; i < argc; i++){/*Getting input from command line argumnet*/
                    arr[i - 1] = atoi(argv[i]); /*atoi() is used to convert the charecter into int and floating value*/
                }
                write(fd1[1], arr, sizeof(arr));/*Writing it to the first child*/
                int sum = 0;
                read(fd2[0], &sum, sizeof(sum)); /*Reading the sum form the first child*/
                printf("Sum of the array is : %d\n", sum);

                write(fd3[1], arr, sizeof(arr)); /*Writing it to the second child*/
                float avg = 0;
                read(fd4[0], &avg, sizeof(avg)); /*Reading average from the Second child*/
                printf("Average of array is : %f\n", avg);
            }else{
                perror("Forking failed for process C\n");
            }
        }else{
            perror("Forking failed for B process\n");
        }
    }

    return 0;
}