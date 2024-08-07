#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include "funcoes.h"

//ARVORE B

bool pesquisaArvoreB(Item *x, TipoApontadorB arvore){

    long i = 1;
    
    if(arvore == NULL)
        return false;

    while(i < arvore->n && x->chave > arvore->registros[i - 1].chave) 
        i++;

    if(x->chave == arvore->registros[i - 1].chave){
        *x = arvore->registros[i - 1];
        return true;
    }

    if(x->chave < arvore->registros[i - 1].chave)
        return pesquisaArvoreB(x, arvore->apontadores[i - 1]);
    else    
        return pesquisaArvoreB(x, arvore->apontadores[i]);
}

void insereNaPaginaB(TipoApontadorB pArvore, Item Reg, TipoApontadorB pDireita){
    int k = pArvore->n; 

    while(k > 0 && Reg.chave < pArvore->registros[k - 1].chave){
        pArvore->registros[k] = pArvore->registros[k - 1];
        pArvore->apontadores[k + 1] = pArvore->apontadores[k];
        k--;
    }
    pArvore->registros[k] = Reg;
    pArvore->apontadores[k + 1] = pDireita;
    (pArvore->n)++;
}

void InsB(Item Reg, TipoApontadorB pArvore, bool *cresceu, Item *regRetorno, TipoApontadorB *pArvoreRetorno){
    long i = 1;
    TipoApontadorB pArvoreTemp;
    //arvore nao existe OU no folha encontrado
    if(pArvore == NULL){
        *cresceu = true;
        *regRetorno = Reg;
        *pArvoreRetorno = NULL;
        return;
    }

    while(i < pArvore->n && Reg.chave > pArvore->registros[i - 1].chave)
         i++;

    if(Reg.chave ==  pArvore->registros[i - 1].chave){
        printf("Registro ja presente\n");
        *cresceu = false;
        return;
    }

    if(Reg.chave < pArvore->registros[i - 1].chave) i--; //saber para onde caminhar
    InsB(Reg, pArvore->apontadores[i], cresceu, regRetorno, pArvoreRetorno);
   
    if(!*cresceu) return;

    if(pArvore->n < M2){ //pagina tem espaco
        insereNaPaginaB(pArvore, *regRetorno, *pArvoreRetorno);
        *cresceu = false;
        return;
    }

    // Overflow: pagina tem que ser dividida
    pArvoreTemp = (TipoApontadorB)malloc(sizeof(TipoPaginaB));
    if (pArvoreTemp == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    pArvoreTemp->n = 0;
    pArvoreTemp->apontadores[0] = NULL;

    //determina em qual das duas paginas sera inserida o novo elemento 
    if(i < M + 1){
        insereNaPaginaB(pArvoreTemp, pArvore->registros[(M2) - 1], pArvore->apontadores[M2]);
        (pArvore->n)--;
        insereNaPaginaB(pArvore, *regRetorno, *pArvoreRetorno);
    }
    else insereNaPaginaB(pArvoreTemp, *regRetorno, *pArvoreRetorno);

    for(int j = M + 2; j <= (M2); j++){
        insereNaPaginaB(pArvoreTemp, pArvore->registros[j - 1], pArvore->apontadores[j]);
    }
        pArvore->n = M;
        pArvoreTemp->apontadores[0] = pArvore->apontadores[M + 1];
        *regRetorno = pArvore->registros[M];
        *pArvoreRetorno = pArvoreTemp;        
}

void insereB(Item Reg, TipoApontadorB *pArvore){
    bool cresceu;
    Item itemRetorno;
    TipoApontadorB pRetorno, pTemp;
    InsB(Reg, *pArvore, &cresceu, &itemRetorno, &pRetorno);
    if(cresceu){ // Arvore cresce na altura pela raiz
        pTemp = (TipoPaginaB*)malloc(sizeof(TipoPaginaB));
         if (pTemp == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        pTemp->n = 1;
        pTemp->registros[0] = itemRetorno;
        pTemp->apontadores[0] = *pArvore;
        pTemp->apontadores[1] = pRetorno;
        *pArvore = pTemp;
    }

    #if false //debug  
        static int cont = 0;
        cont++;
        if (cont % 10000 == 0) { 
            printf("Inseriu %d itens\n", cont);
        }
    #endif


}




void inicializaArvoreB(TipoApontadorB *Arvore){
    *Arvore = NULL;
}

bool arvoreB(long chave, char* nomeArquivo, bool p){

    FILE *arq;
    Item item;
    int pulaLinha = 0;
    TipoApontadorB apontador;
    static const Item itemVazio;
    
    if((arq = fopen(nomeArquivo, "rb")) == NULL){
        perror("Erro na abertura do arquivo\n");
        exit(1);
    } 

    //criacao da arvore B
    inicializaArvoreB(&apontador);

    if(p)
        printf("\n\tChaves Disponiveis:\n\n");

    //insercao de elementos na arvore
    while(fread(&item, sizeof(Item), 1, arq) > 0){
        insereB(item, &apontador);
        if(p)
            imprimeChavesArvores(item, &pulaLinha);
    }
            printf("\n"); rewind(arq);
    //pesquisa por elementos da arvore

    item = itemVazio;

    // printf("Qual a chave do registro que deseja? ");
    // scanf("%u", &item.chave);

    item.chave = chave;
    
    if(pesquisaArvoreB(&item, apontador)){
        imprimeItemArvore(item);
    } else 
        printf("Item nao encontrado");
    
    liberarArvoreB(apontador);

    fclose(arq);
    return 0;       
}

void liberarArvoreB(TipoApontadorB arvore){
    if (arvore == NULL) return;
    for (int i = 0; i <= arvore->n; i++) {
        liberarArvoreB(arvore->apontadores[i]);
    }
    free(arvore);
}