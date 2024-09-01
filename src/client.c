/**
 * @file client.c
 * @author Pedro Faria
 * @brief sdstore
 * @version 0.1
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "globals.h"

int main(int argc, char const *argv[]){
    printf("CLIENT:client boot\n");
    char * buffer =calloc(MSIZE, sizeof(char));
     
    int pid = getpid();
    for (int i=0;i<argc;i++) printf("%d :%s\n",i,argv[i]);
    switch (argc){

    case 1:// sem args -> menu ajuda
        help();
        break;
    case 2:
        //apenas status -> verificar status de tasks e transforms
        if (strcmp(argv[1],"status")==0){
            if(!status(pid)){
                perror("Error:client>status ");
                return 1;
            }
        }else help();
        break;
    
    default:
        // proc-file
        if (strcmp(argv[1],"proc-file")){
            if(!proc(pid,argv)){
                perror("client>proc-file\n");
                return 1;
            }

        }else help();
        break;
        
    }


    return 0;
}
