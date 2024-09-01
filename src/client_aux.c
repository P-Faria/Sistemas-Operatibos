/**
 * @file client_aux.c
 * @author Pedro Faria
 * @brief Funções auxiliares usadas pelo cliente
 * @version 0.1
 * @date 2022-04-07
 * 
 * 
 */

#include "globals.h"

void help(){
    char *help="  >>Ajuda<<\n  >>./sdstore status\n  >>./sdstore proc-file priority input-filename output-filename transformation-id-1 transformation-id-2...\n";
        write(STDOUT_FILENO,help,115);

}

int status(int cpid){
    int fifo_fd;

    char * buffer =calloc(MSIZE, sizeof(char));
    sprintf(buffer,"%d",cpid);
    strcat(buffer,":status");
    if((fifo_fd = open(FIFO,O_WRONLY)) < 0){
        perror("client > open(fifo)");
        _exit(0);
    }
    write(fifo_fd,buffer,MSIZE);
    close(fifo_fd);
    open(fifo_fd,O_RDONLY);
    

    return 0;
}

int proc(int pid, char ** argv){

    return 0;
}