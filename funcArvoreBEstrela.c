#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include "funcoes.h"

//ARVORE B ESTRELA

void insereBEstrela(Item Reg, TipoApontadorEstrela* pArvore) {
    bool cresceu;
    Item itemRetorno;
    TipoApontadorEstrela pRetorno, pTemp;

    InsBEstrela(Reg, *pArvore, &cresceu, &itemRetorno, &pRetorno);

    if (cresceu) {
        pTemp = (TipoApontadorEstrela)malloc(sizeof(TipoPaginaEstrela));
        if (*pArvore == NULL) {
            pTemp->tipo = Externa;
            pTemp->n = 1;
            pTemp->rExt[0] = itemRetorno;
        } else {
            pTemp->tipo = Interna;
            pTemp->n = 1;
            pTemp->rInt[0] = itemRetorno.chave;
            pTemp->pInt[0] = *pArvore;
            pTemp->pInt[1] = pRetorno;
        }
        *pArvore = pTemp;
    }

}

void inicializaArvoreBEstrela(TipoApontadorEstrela* Arvore) {
    *Arvore = NULL;
}

bool pesquisaArvoreBEstrela(Item* x, TipoApontadorEstrela* pArvore) {
    if (*pArvore == NULL){
        //arvore vazia
        return false;
    }

    TipoApontadorEstrela pagina = *pArvore;
    long i;

    // Pesquisa em paginas internas
    if (pagina->tipo == Interna) {
        i = 1;
        while (i < pagina->n && (int)x->chave > pagina->rInt[i - 1])
            i++;

        if((int)x->chave < pagina->rInt[i - 1]) i--;
        return pesquisaArvoreBEstrela(x, &pagina->pInt[i]);

    } else if (pagina->tipo == Externa) {
        // PesquisaArvoreBEstrela sequencial na pagina folha
        i = 1;
        while (i < pagina->n && x->chave > pagina->rExt[i - 1].chave) 
            i++;
        
        if (x->chave == pagina->rExt[i - 1].chave) {
            *x = pagina->rExt[i - 1];
            return true;
        }
        return false;
    }
    return false;
}

void insereNaPaginaExternaBEstrelaBEstrela(TipoApontadorEstrela pArvore, Item Reg) {
    int k = pArvore->n;

    while (k > 0 && Reg.chave < pArvore->rExt[k - 1].chave) {
        pArvore->rExt[k] = pArvore->rExt[k - 1];
        k--;
    }
    pArvore->rExt[k] = Reg;
    (pArvore->n)++;
}

void insereNaPaginaInternaBEstrelaBEstrela(TipoApontadorEstrela pArvore, TipoChave chave, TipoApontadorEstrela pDireita) {
    int k = pArvore->n;

    while (k > 0 && chave < pArvore->rInt[k - 1]) {
        pArvore->rInt[k] = pArvore->rInt[k - 1];
        pArvore->pInt[k + 1] = pArvore->pInt[k];
        k--;
    }
    pArvore->rInt[k] = chave;
    pArvore->pInt[k + 1] = pDireita;
    (pArvore->n)++;
}

void InsBEstrela(Item Reg, TipoApontadorEstrela pArvore, bool* cresceu, Item* itemRetorno, TipoApontadorEstrela* pArvoreRetorno) {
    long i;
    TipoApontadorEstrela pArvoreTemp;

    if (pArvore == NULL) {
        *cresceu = true;
        (*itemRetorno) = Reg;
        (*pArvoreRetorno) = NULL;
        return;
    }

    if (pArvore->tipo == Interna) {
        i = 1;
        while (i < pArvore->n && (int)Reg.chave > pArvore->rInt[i])
            i++;

        if((int)Reg.chave < pArvore->rInt[i - 1]) i--; //saber para onde caminhar
        InsBEstrela(Reg, pArvore->pInt[i], cresceu, itemRetorno, pArvoreRetorno);

        if (!*cresceu) return;

        if (pArvore->n < (M2)) {
            insereNaPaginaInternaBEstrelaBEstrela(pArvore, itemRetorno->chave, *pArvoreRetorno);
            *cresceu = false;
            return;
        }

        pArvoreTemp = (TipoApontadorEstrela)malloc(sizeof(TipoPaginaEstrela));
        pArvoreTemp->tipo = Interna;
        pArvoreTemp->n = 0;
        pArvoreTemp->pInt[0] = NULL;

        if (i <= M + 1) {
            insereNaPaginaInternaBEstrelaBEstrela(pArvoreTemp, pArvore->rInt[(M2) - 1], pArvore->pInt[M2]);
            (pArvore->n)--;
            insereNaPaginaInternaBEstrelaBEstrela(pArvore, itemRetorno->chave, *pArvoreRetorno);
        } 
        else insereNaPaginaInternaBEstrelaBEstrela(pArvoreTemp, itemRetorno->chave, *pArvoreRetorno);

        for (int j = M + 2; j <= (M2); j++) {
            insereNaPaginaInternaBEstrelaBEstrela(pArvoreTemp, pArvore->rInt[j - 1], pArvore->pInt[j]);
        }

        pArvore->n = M;
        pArvoreTemp->pInt[0] = pArvore->pInt[M + 1];
        itemRetorno->chave = pArvore->rInt[M];
        *pArvoreRetorno = pArvoreTemp;
        *cresceu = true;
        return;
    }

    // Externa
    i = 1;
    while (i < pArvore->n && Reg.chave > pArvore->rExt[i - 1].chave)
        i++;

    if (pArvore->n < (M2)) {
        insereNaPaginaExternaBEstrelaBEstrela(pArvore, Reg);
        *cresceu = false;
        return;
    }

    pArvoreTemp = (TipoApontadorEstrela)malloc(sizeof(TipoPaginaEstrela));
    pArvoreTemp->tipo = Externa;
    pArvoreTemp->n = 0;

    if (i < M + 1) {
        insereNaPaginaExternaBEstrelaBEstrela(pArvoreTemp, pArvore->rExt[(M2) - 1]);
        (pArvore->n)--;
        insereNaPaginaExternaBEstrelaBEstrela(pArvore, Reg);
    } 
    else insereNaPaginaExternaBEstrelaBEstrela(pArvoreTemp, Reg);

    for (int j = M + 1; j <= (M2); j++) {
        insereNaPaginaExternaBEstrelaBEstrela(pArvoreTemp, pArvore->rExt[j - 1]);
    }

    pArvore->n = M;
    pArvoreTemp->n = M + 1;
    *itemRetorno = pArvoreTemp->rExt[0];
    *pArvoreRetorno = pArvoreTemp;
    *cresceu = true;
    return;
}

bool arvoreBEstrela(long chave, char* nomeArquivo, bool p){
    FILE* arq;
    Item item;
    int pulaLinha = 0;
    TipoApontadorEstrela apontador;
    static const Item itemVazio;

    if ((arq = fopen(nomeArquivo, "rb")) == NULL) {
        perror("Erro na abertura do arquivo\n");
        exit(1);
    }

    // Criacao da arvore B
    inicializaArvoreBEstrela(&apontador);

    if(p)
        printf("\n\tChaves Disponiveis:\n\n");

    // Insercao de elementos na arvore
    while (fread(&item, sizeof(Item), 1, arq) > 0){
        insereBEstrela(item, &apontador);
        if(p)
            imprimeChavesArvores(item, &pulaLinha);
    }
            printf("\n"); rewind(arq);

    item = itemVazio; item.chave = chave;

    if (pesquisaArvoreBEstrela(&item, &apontador))
        imprimeItemArvore(item);
    else 
        printf("\nItem nao encontrado\n");

    fclose(arq);
    return 0; 
}

