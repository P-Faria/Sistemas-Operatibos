/**
 * @file server_aux.c
 * @author Pedro Faria
 * @brief  Contem funçoes adicionais a ser usadas com o server
 * @version 0.1
 * @date 2022-03-30
 * 
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

#include "globals.h"




/**
 * Reads a line from a file descriptor and returns the number of bytes read
 * 
 * @param fd The file descriptor of the file to read from.
 * @param line the buffer where the line will be stored.
 * @param size The size of the buffer.
 * 
 * @return The number of bytes read.
 */
ssize_t readln(int fd, char *line, size_t size){
    //não podemos usar o line porque o apontador está sempre a apontar para o inicio do array
    int next_pos = 0;
    int read_bytes = 0;

    while((read(fd, line + next_pos, 1) > 0) && next_pos < size){  // line + next_post != line[next_post]
        read_bytes ++; //para ler o '\n'
        if (line[next_pos] == '\n'){                             //line + next_post avança com o apontador
            break;                                               // line[next_post] dá o valor que está nessa posição que será um char e nao um apontador
        }                        
        next_pos ++;                                             
    }
    return read_bytes;
}



/**
 * It reads the configuration file and stores the information in a TRANSFORM array
 * 
 * @param array the array to be reallocated
 * @param config the name of the configuration file.
 * @param local the path to the directory where the transform executables are located.
 * 
 * @return The number of transforms that were read from the file.
 */
int guardaTransform(TRANSFORM ** array, char *config,char *local){
    int transformCounter=0;
    int file_fd = open(config,O_RDONLY); ///< descritor para a localização do ficheiro config

    if (file_fd<0){ ///< Verifica se o descritor é aberto
        perror("server_aux>guardaTransform>erro a abrir fd");
        exit(0);
    }

    int bRead =0; ///< numero de bytes lidos
    char buf[MSIZE]; ///< Buffer onde serão guardados os dados lidos

    while((bRead = readln(file_fd,buf,MSIZE)) > 0){
        buf[bRead] = '\0';
        TRANSFORM *tmp = realloc(*array,sizeof(TRANSFORM) * (transformCounter + 1)); ///< array temporario para os filtros
        if (!tmp) return 0; // verifica se o array temporario foi criado

        (*array) = tmp; //

        TRANSFORM t;
        t.nome= strdup(strtok(buf," ")); // guarda o nome da transformação
        t.nome[strlen(t.nome)] = '\0'; ///< sem isto não é uma string pois não termina
        t.exec= strcat(strdup(local),t.nome);// guarda o caminho do executavel
        t.max=atoi(strtok(NULL,"\0")); ///< vai nos devolver o que falta na string de nome
        t.running=0;
        tmp[transformCounter++] = t;///< guarda-se no temporario e incrementa-se o numero de filtros
    }
    close(file_fd);
    return transformCounter; // saiu com sucesso

}

/**
 * 
 * 
 * @param argc The number of arguments passed to the program.
 * @param argv The argument vector.
 * @param config the configuration file name
 * @param tFolder the folder where the transformation files are located.
 * 
 * @return 1 caso de erro
 * @return 0 caso saia com sucesso
 */
int configSetup(int argc,char const *argv[],char *config,char *tFolder){
    if  (argc>4){ 
        perror("argumentos > 3");
        return 1;
    }
    if (argc<2) { // handling dos argumentos dados
        printf("arguments not found \t>>loading defaults\n");
        strcpy(config,"etc/sdstored.conf");
        strcpy(tFolder,"bin/sdstore-transformations/");
    }else { //caso receba argumentos
        printf("arguments found!\n");
        strcpy(config,argv[1]);
        printf("config-filename: '%s'\n",config);
        strcpy(tFolder,argv[2]);
        if (tFolder[strlen(tFolder)] !="/") {
            char ch = '/';
            strncat(tFolder,&ch,1);
        }
        printf("transformations-folder: '%s'\n",tFolder);
    }
    return 0;
}

int doTask(char *buffer,TASK ** array,int taskCounter){

    TASK *tmp = realloc(*array,sizeof(TASK) * (taskCounter + 1)); ///< array temporario para as tasks
        if (!tmp) return 1; // verifica se o array temporario foi criado

        (*array) = tmp; 

        TASK t;
        t.tasknum=taskCounter;
        t.pid=strdup(strtok(buffer,":"));
        t.message=strdup(strtok(buffer,NULL));
        t.status=0;
        tmp[taskCounter] = t;
        printf("task adicionada");
    

    return 0;
}

    
