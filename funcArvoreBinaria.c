#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include "funcoes.h"

bool insereItemBinario(No R, FILE* arq, const long qtt) {
    // define para realizar comandos de manipulacao e leitura dos dados do arq
    #define read_node(i, Item)     (!fseek(arq, i * sizeof(No), SEEK_SET)) && (fread(Item, sizeof(No), 1, arq) > 0)
    
    //printf("[%s] (qtt:%ld)\n", __func__, qtt);
    // se a quantidade de itens lidos for igual a 0 so inserimos o item no arq
    if (qtt == 0)
    {
        // Caso verdadeiro, isso significa que o arq está vazio, então podemos inserir direto
        fwrite(&R, sizeof(No), 1, arq);
        return true;
        
    }
    // variavel temporaria para verificacao dos apontadores da arvore
    No temp;
    // variavel que recebe a posicao 
    long pos = 0;
    // while para verificar e corrigir os apontadores
    while (read_node(pos, &temp))
    {
        // se a chave do dado a ser inserida for igual a cheve lida no arq retornamos que a chave ja esta presente no arq
        if (temp.dadoNo.chave == R.dadoNo.chave) {
            //caso verdadeiro retornamos que a chave ja esta presente e portanto nao foi inserida
            printf("A chave já está presente no arq\n");
            return false;
        // verificacao se a chave a ser inserida é menor que a presente no arq
        } else if (temp.dadoNo.chave > R.dadoNo.chave) {
            // se o filho a esquerda for igual a -1 podemos inserir o novo dado e atualizar os apontadores no arq
            if (temp.esquerda == -1) {
                temp.esquerda = qtt;
                fseek(arq, pos * sizeof(No), SEEK_SET);
                fwrite(&temp, sizeof(No), 1, arq);
                fseek(arq, qtt * sizeof(No), SEEK_SET);
                fwrite(&R, sizeof(No), 1, arq);
                return true;
            }
            // caso nao seja -1 atualizamos a posicao e repetimos o while
            pos = temp.esquerda;

        }
        // caso a chave a ser inserida seja menor que a presente no arq
        else {
             // se o filho a direita for igual a -1 podemos inserir o novo dado e atualizar os apontadores no arq
            if (temp.direita == -1) {
                temp.direita = qtt;
                fseek(arq, pos * sizeof(No), SEEK_SET);
                fwrite(&temp, sizeof(No), 1, arq);
                fseek(arq, qtt * sizeof(No), SEEK_SET);
                fwrite(&R, sizeof(No), 1, arq);
                return true;
            }
            // caso nao seja -1 atualizamos a posicao e repetimos o while
            pos = temp.direita;     
        }   
    }
    return false;
}

bool pesquisaItemBinario(long chave, FILE* arq, const long qtt, Item *recebido) {
    #define read_page(_IndiceDaPagina, _PaginaPtr)     ((! fseek(arq, _IndiceDaPagina * sizeof(struct Pagina), SEEK_SET)) && (fread(_PaginaPtr, sizeof(No), N_ITEM_PAG, arq) > 0))
    // verificacao se a quantidade de itens no arq e 0
    if (qtt == 0) {
        printf("O arq esta vazio\n");
        return true;
    }
    // variavel para leitura das paginas para pesquisa
    Pagina temp;
    //variaveis para a manipulacao das paginas
    long pos = 0;
    size_t posItem = 0;
    size_t pag = 0;
    size_t old_pag = 1;

    while (true) {   
        // verificacao para saber se a pagina do item ja foi lida
        if (old_pag != pag) {
            if (! read_page(pag, &temp))
                break;
        }
        // se a chave a ser pesquisada for igual a chave lida atualizamos o recebido e retormanos verdadeiro
        if(chave == temp.no[posItem].dadoNo.chave) {
            *recebido = temp.no[posItem].dadoNo;
            return true;
        }
        // verificacao se a chave a ser pesquisada é menor que a chave lida no arq
        else if (chave < temp.no[posItem].dadoNo.chave) {
            // se o apontador a esquerda for nulo acabou a pesquisa pela esquerda
            if (temp.no[posItem].esquerda == -1)  
                break;
            // atualizamos a posicao a ser lida   
            pos = temp.no[posItem].esquerda;

            // atualizando os parâmetros de navegação 
            old_pag = pag;
            posItem = pos % N_ITEM_PAG;
            pag = pos / N_ITEM_PAG;
        } else {
            // se o apontador a direita for nulo acabou a pesquisa pela esquerda
            if (temp.no[posItem].direita == -1)     
                break;
            // atualizamos a posicao a ser lida   
            pos = temp.no[posItem].direita;
            
            // atualizando os parâmetros de navegação 
            old_pag = pag;
            posItem = pos % N_ITEM_PAG;
            pag = pos / N_ITEM_PAG;
        }
    }
    return false;
}

bool arvoreBinaria(long chave, char* nomeArquivo, bool p){
    // inicializacao das variaveis para a criacao do arq binario
    No R = { 0 };
    FILE *arq;
    FILE *arqBinario;
    int pulaLinha = 0;
    R.direita = -1;
    R.esquerda = -1;
    // contador que indica quantos itens o arq possui
    long qtt = 0;
    // validacao para verificar se o arq foi aberto corretamente
    if ((arqBinario = fopen("arvoreBinaria.bin", "w+b")) == NULL){
        printf("Erro na abertura do arq\n");
        exit(1);
    }
    // validacao para verificar se o arq foi aberto corretamente
    if ((arq = fopen(nomeArquivo, "rb")) == NULL){
        printf("Erro na abertura do arq\n");
        exit(1);
    }

    if(p)
        printf("\n\tChaves Disponiveis:\n\n");

    // leitura dos dados do arq para serem inseridos na arvore
    while (fread(&R.dadoNo, sizeof(Item), 1, arq) > 0){
        if (!insereItemBinario(R, arqBinario, qtt)){
            printf("Falha ao inserir\n");
            continue;
        }
        if(p)
            imprimeChavesArvores(R.dadoNo, &pulaLinha);
        //atualizacao do contador
            qtt++;
    }
    printf("\n"); rewind(arq);

    // variavel que recebera as informacoes da chave encontrada
    Item recebido;
    // recebendo a chave a ser encontrada
    printf("\nchave desejada: %ld\n", chave);
    // chamada da funcao e verificacao se a chave foi encontrada ou nao
    if(pesquisaItemBinario(chave, arqBinario, qtt ,&recebido))
        imprimeItemArvore(recebido);
    else
        printf("Item nao encontrado");
    
    // fechando os arqs utilizados
    fclose(arq);
    fclose(arqBinario);
    return 0;
}
