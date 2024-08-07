#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include "funcoes.h"

//SEQUENCIAL INDEXADO

bool sequencialIndexado(int situacao, long chave, long tamanhoPagina, char* nomeArquivo, bool p){

    //Acesso sequencial indexado nao pode ser utilizado para arquivos desordenados
    if(situacao == 3){
        printf("Acesso Sequencial Indexado nao pode ser realizado com um arquivo desordenado!\nTente novamente com um arquivo ordenado de forma crescente ou descrescente!\n");
        return false;
    }

    long* tabelaChave = (long*)malloc((tamanhoPagina * 3) * sizeof(long));
    Item* item = (Item*)malloc(tamanhoPagina * sizeof(Item));
    FILE *arq;

    if((arq = fopen(nomeArquivo, "rb")) == NULL){
        perror("Erro na abertura do arquivo\n");
        exit(1);
    } 

    if(p) imprimeChavesSeqIndx(arq);

    //criacao da tabela de indices com chave
    for(int i = 0; fread(item, sizeof(Item), tamanhoPagina, arq) > 0; i++)
        tabelaChave[i] = item[0].chave;
    
    //inicio da pesquisa
    item->chave = chave;

    if(pesquisaSeqIndx(tabelaChave, item, arq, tamanhoPagina, situacao)){
        imprimeItemSeqIndx(item);
    } else {
        printf("Item nao existente");
    }
    free(tabelaChave); 
    free(item);
    fclose(arq);
    return 0;
}

bool pesquisaSeqIndx(long* tabelaChave, Item* item, FILE* arq, long tamanhoPagina, int situacao){
    rewind(arq);
    long int desloc;
    int quantItens;
    Item* paginaEscolhida = (Item*)malloc(tamanhoPagina * sizeof(Item));
    // Item paginaEscolhida[tamanhoPagina];

    int i = 0; int tam = (tamanhoPagina * 3);

    if(situacao == 1){ //CRESCENTE
        while(i < tam && tabelaChave[i] <= item->chave) i++;
    } else { //DECRESCENTE (situacao == 2)
        while(i < tam && tabelaChave[i] >= item->chave) i++;
    }

    int meio; int limInf = 0; int limSup;

    if(i == 0) {
        free(paginaEscolhida);
        return false;
    } 
    if(i < tam) quantItens = tamanhoPagina;
    else{ //Chave se encontra na ultima pagina
        fseek(arq, 0, SEEK_END); //Ir pra o final do arquivo
        quantItens = (ftell(arq) / sizeof(Item)) % tamanhoPagina;
        if(quantItens == 0) quantItens = tamanhoPagina;
    }   

    desloc = sizeof(Item) * tamanhoPagina * (i - 1);
    fseek (arq, desloc, SEEK_SET);
    fread(paginaEscolhida, sizeof(Item), quantItens, arq);
    
    limSup = quantItens - 1;

    if(situacao == 1){//CRESCENTE
        while(limInf <= limSup){
            meio = (limInf + limSup) / 2;
            if(paginaEscolhida[meio].chave == item->chave){
                *item = paginaEscolhida[meio];
                free(paginaEscolhida);
                return true;
            }
            if(paginaEscolhida[meio].chave < item->chave)
                limInf = meio + 1;
            else   
                limSup = meio - 1;
        }
    } else { //DECRESCENTE(situacao == 2)
        while(limInf <= limSup){
            meio = (limInf + limSup) / 2;
            if(paginaEscolhida[meio].chave == item->chave){
                *item = paginaEscolhida[meio];
                free(paginaEscolhida);
                return true;
            }
            if(paginaEscolhida[meio].chave > item->chave)
                limInf = meio + 1;
            else   
                limSup = meio - 1;
        }
    }

    free(paginaEscolhida);
    return false;
}