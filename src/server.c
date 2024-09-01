/**
 * @file server.c
 * @author Pedro Faria - a72640
 * @brief sdstored
 * @version 0.1
 * @date 2022-03-23
 * 
 * 
 */


#include "globals.h"

int transformCounter = 0; ///< Variavel global para numero de transformações

int taskCounter = 0;


/**
 * @brief Função que inicia o servidor
 * 
 * @param argc Numero de argumentos passados pelo utilizador
 * @param argv Argumentos passados pelo utilizador
 * @return int 
 */

int main(int argc, char const *argv[]){

    
    char config[MSIZE]; // Variavel onde é guardado o nome do ficheiro de config
    char tFolder[MSIZE]; // Variavel onde é guardado o nome do diretorio das transformações
    TRANSFORM *t_array = NULL; // Variavel onde será guardado as transformaçoes retiradas de config
    TASK *tsk_array = NULL;
    
    if (configSetup(argc,argv,config,tFolder)){ // Configuração do servidor
        perror("main>configSetup");
        exit(EXIT_FAILURE);
    }
    
    if(!(transformCounter = guardaTransform(&t_array,config,tFolder))){ // inicialização dos filtros
        perror("main>guardaTransform>");
        exit(EXIT_FAILURE);
    }
    
    
    
    
    printf("---server boot---\n");
    // criação do fifoma
    if (mkfifo(FIFO,0644)<0){
        perror("server>fifo");
        return 1;
    } else printf("fifos criados\n");
    int fifo_fd;
    

    // criaçao de buffer usando calloc, para garantir que o bloco de memoria está "limpo"
    char * buffer =calloc(MSIZE, sizeof(char));
    int bytes_read=0;
    //abertura dos fifos

    

    

    while(1){
        
        if ((fifo_fd = open(FIFO,O_RDONLY)) < 0){ //funcional, como não esta O_NONBLOCK ele ira aguardar alguma mensagem seja enviada
        perror("server > open(fifo)");
        _exit(0);
        }

        if ((bytes_read = read(fifo_fd,buffer,MSIZE)) > 0){
             doTask(buffer,&tsk_array,taskCounter++);
        }       
    }

    close(fifo_fd);

    return 0;
}
