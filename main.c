#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include "funcoes.h"

#define SIZE_DADO2 1001
#define SIZE_DADO3 5001

int main(int argc, char* argv[]){

    bool p = false;

    if(argc != 5 && argc != 6){
        printf("Formatacao correta: pesquisa <metodo> <quantidade> <situacao> <chave> [-P]");
        return 1;
    }

    int metodo = atoi(argv[1]);
    int quantidade = atoi(argv[2]);
    int situacao = atol(argv[3]);
    int chave = atoi(argv[4]);
    if(argc == 6) p = true;
    
    pesquisa(metodo, quantidade, situacao, chave, p);
 
    return 0;
}