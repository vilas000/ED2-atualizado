#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdbool.h>

#define SIZE_DADO2 1001
#define SIZE_DADO3 5001
#define M 200
#define M2 (M * 2)
#define N_ITEM_PAG 3

typedef struct{
    long int chave;
    long int dado1;
    char dado2[SIZE_DADO2];
    char dado3[SIZE_DADO3];
}Item;

typedef struct TipoPaginaB* TipoApontadorB;

typedef struct TipoPaginaEstrela* TipoApontadorEstrela;

typedef long TipoChave;

typedef enum { Interna, Externa } TipoIntExt;

// typedef struct TipoPaginaB{
//     short n;
//     Item* registros;
//     TipoApontadorB* apontadores;
// }TipoPaginaB;

typedef struct TipoPaginaB{
    short n;
    Item registros[M2];
    TipoApontadorB apontadores[M2 + 1];
}TipoPaginaB;

typedef struct TipoPaginaEstrela {
    TipoIntExt tipo;
    int n;
    union {
        struct {
            TipoChave rInt[M2];
            TipoApontadorEstrela pInt[(M2) + 1];
        };
        struct {
            Item rExt[M2];
        };
    };
}TipoPaginaEstrela;

typedef struct No{
    Item dadoNo;
    long direita;
    long esquerda;
} No;

typedef struct Pagina{
    struct No no[N_ITEM_PAG];
} Pagina;

//ARVORE BINARIA

bool insereItemBinario(No R, FILE* arq, const long qtt);

bool pesquisaItemBinario(long chave, FILE* arq, const long qtt, Item * recebido);

bool arvoreBinaria(long chave, char* nomeArquivo, bool p);

//ARVORE B ESTRELA

void insereBEstrela(Item Reg, TipoApontadorEstrela* pArvore);

void inicializaArvoreBEstrela(TipoApontadorEstrela* Arvore);

bool pesquisaArvoreBEstrela(Item* x, TipoApontadorEstrela* pArvore);

void insereNaPaginaExternaBEstrelaBEstrela(TipoApontadorEstrela pArvore, Item Reg);

void insereNaPaginaInternaBEstrelaBEstrela(TipoApontadorEstrela pArvore, TipoChave chave, TipoApontadorEstrela pDireita);

void InsBEstrela(Item Reg, TipoApontadorEstrela pArvore, bool* cresceu, Item* itemRetorno, TipoApontadorEstrela* pArvoreRetorno);

bool arvoreBEstrela(long chave, char* nomeArquivo, bool p);

//ARVORE B 

bool pesquisaArvoreB(Item *x, TipoApontadorB arvore);

void insereNaPaginaB(TipoApontadorB pArvore, Item Reg, TipoApontadorB pDireita);

void InsB(Item Reg, TipoApontadorB pArvore, bool *cresceu, Item *regRetorno, TipoApontadorB *pArvoreRetorno);

void insereB(Item Reg, TipoApontadorB *pArvore);

void inicializaArvoreB(TipoApontadorB *Arvore);

bool arvoreB(long chave, char* nomeArquivo, bool p);

void liberarArvoreB(TipoApontadorB arvore);

void liberaPagina(TipoApontadorB pagina);

//SEQUENCIAL INDEXADO

bool sequencialIndexado(int situacao, long chave, long tamanhoPagina, char* nomeArquivo, bool p);

bool pesquisaSeqIndx(long* tabelaChave, Item* item, FILE* arq, long tamanhoPagina, int situacao);

//GERAL

long determinarTamanhoPagina(long quantidade);

bool nomearArquivo(int tamanhoPagina, int situacao, char* nomeArquivo);

bool pesquisa(int metodo, long quantidade, int situacao, long chave, bool p);

void imprimeChavesSeqIndx(FILE* arq);

void imprimeChavesArvores(Item item, int* pulaLinha);

void imprimeItemArvore(Item item);

void imprimeItemSeqIndx(Item* item);

#endif //FUNCOES_H