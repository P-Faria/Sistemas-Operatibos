/**
 * @file globals.h
 * @author Pedro Faria
 * @brief Ficheiro com todas as variaveis globais, structs e esqueletos de funções
 * @version 0.1
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#define MSIZE 1024 ///< Tamanho maximo (geralmente usado para limitar o buffer)

#define FIFO "tmp/fifo" ///< Defenição standard da localização do fifo 





/** 
 *
 * @struct transform
 * @brief Contem todas as informações para uma transformação 
 * @param nome nome da transformação
 * @param exec localização do executavel
 * @param max maximo numero de transformações concorrentes permitido
 * @param running numero atual de transformações em utilização
 * 
 */
typedef struct transform
{
    char *nome; 
    char *exec; 
    int max;    
    int running;
}TRANSFORM;

/**
 * 
 * @struct client
 * @brief Define um cliente
 * 
 */
typedef struct client{
    char *pid; ///< numero do processo do cliente
    char *message; ///< ultima mensagem transmitida
}CLIENT;


typedef struct task{
    int tasknum; ///< numero da task
    char *pid; ///< numero do processo do requerente
    char *message; ///< mensagem com a task pedida
    int status; ///< 0 - não tem task\n 1 - em execução\n 2- Terminada
}TASK;

//server_aux
int guardaTransform(TRANSFORM ** array, char *config,char *local);
int configSetup(int argc,char const *argv[],char *config,char *tFolder);
int doTask(char *buffer,TASK ** tsk_array,int taskCounter);

//client_aux
void help();
int status(int cpid);
int proc(int pid, char ** argv);
