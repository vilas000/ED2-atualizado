#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include "funcoes.h"

//GERAL 

long determinarTamanhoPagina(long quantidade){
    
    if(quantidade >= 10e5)
        return 2790;
    else if(quantidade >=10e4)
        return 697;
    else if(quantidade >=10e3)
        return 174;
    else if(quantidade >=10e2)
        return 43;
    else
        return 10;
}

bool nomearArquivo(int tamanhoPagina, int situacao, char* nomeArquivo){

    if(!nomeArquivo) return false;

    switch(tamanhoPagina){
        case 2790:
            switch(situacao){
                case 1:
                    strcpy(nomeArquivo, "registros/milhaoCrescente.bin");
                    break;
                case 2:
                    strcpy(nomeArquivo, "registros/milhaoDecrescente.bin");
                    break;
                case 3:
                    strcpy(nomeArquivo, "registros/milhaoDesordenado.bin");
                    break;
                default:
                    return false;
                    break;
            }
            break;
        case 697:
            switch(situacao){
                case 1:
                    strcpy(nomeArquivo, "registros/cemMilCrescente.bin");
                    break;
                case 2:
                    strcpy(nomeArquivo, "registros/cemMilDecrescente.bin");
                    break;
                case 3:
                    strcpy(nomeArquivo, "registros/cemMilDesordenado.bin");
                    break;
                default:
                    return false;
                    break;
                }
            break;
        case 174:
            switch(situacao){
                case 1:
                    strcpy(nomeArquivo, "registros/dezMilCrescente.bin");
                    break;
                case 2:
                    strcpy(nomeArquivo, "registros/dezMilDecrescente.bin");
                    break;
                case 3:
                    strcpy(nomeArquivo, "registros/dezMilDesordenado.bin");
                    break;
                default:
                    return false;
                    break;
                }
            break;
        case 43:
            switch(situacao){
            case 1:
                strcpy(nomeArquivo, "registros/milCrescente.bin");
                break;
            case 2:
                strcpy(nomeArquivo, "registros/milDecrescente.bin");
                break;
            case 3:
                strcpy(nomeArquivo, "registros/milDesordenado.bin");
                break;
            default:
                return false;
                break;
            }
            break;
        case 10:
            switch(situacao){
                case 1:
                    strcpy(nomeArquivo, "registros/cemCrescente.bin");
                    break;
                case 2:
                    strcpy(nomeArquivo, "registros/cemDecrescente.bin");
                    break;
                case 3:
                    strcpy(nomeArquivo, "registros/cemDesordenado.bin");
                    break;
                default:
                    return false;
                    break;
                }
            break;
        }
    return true;
}

bool pesquisa(int metodo, long quantidade, int situacao, long chave, bool p){

    long tamanhoPagina;
    char nomeArquivo[50];

    tamanhoPagina = determinarTamanhoPagina(quantidade);

    if(!nomearArquivo(tamanhoPagina, situacao, nomeArquivo))
        return false;

    switch(metodo){
    case 1:
        sequencialIndexado(situacao, chave, tamanhoPagina, nomeArquivo, p);
        break;
    case 2:
        arvoreBinaria(chave, nomeArquivo, p);
        break;
    case 3:
        arvoreB(chave, nomeArquivo, p);
        break;
    case 4:
        arvoreBEstrela(chave, nomeArquivo, p);
        break;
    default:
        return false;
        break;
    }
    return true;
}

void imprimeChavesSeqIndx(FILE* arq){

    printf("\n\tChaves Disponiveis:\n\n");
    Item item;
    int pulaLinha = 0;
    while (fread(&item, sizeof(Item), 1, arq) > 0){
        if(item.chave < 10)
            printf("Chave: %ld \t", item.chave);
        else printf("Chave: %ld\t", item.chave);
        pulaLinha++;
        if(pulaLinha == 3){
            printf("\n"); pulaLinha = 0;
        }

    }
    printf("\n"); rewind(arq);
}

void imprimeChavesArvores(Item item, int* pulaLinha){

        if(item.chave < 10)
            printf("Chave: %ld \t", item.chave);
        else printf("Chave: %ld\t", item.chave);
        (*pulaLinha)++;
        if(*pulaLinha == 3){
            printf("\n"); (*pulaLinha) = 0;
        }
}

void imprimeItemArvore(Item item){
    printf("\n\nChave: %ld\n", item.chave);
    printf("\nDado 1: %ld\n", item.dado1);
    printf("\nDado 2: %s\n", item.dado2);
    printf("\nDado 3: %s\n", item.dado3);
}

void imprimeItemSeqIndx(Item* item){
    printf("\n\nChave: %ld\n", item->chave);
    printf("\nDado 1: %ld\n", item->dado1);
    printf("\nDado 2: %s\n", item->dado2);
    printf("\nDado 3: %s\n", item->dado3);
}


// typedef struct{
//     unsigned int chave;
//     long int dado1;
//     char dado2[SIZE_DADO2];
//     char dado3[SIZE_DADO3];
// }Item;

// typedef struct TipoPaginaB* TipoApontadorB;

// typedef struct TipoPaginaEstrela* TipoApontadorEstrela;

// typedef long TipoChave;

// typedef enum { Interna, Externa } TipoIntExt;

// typedef struct TipoPaginaB{
//     short n;
//     Item registros[M2];
//     TipoApontadorB apontadores[M2 + 1];
// }TipoPaginaB;

// typedef struct TipoPaginaEstrela {
//     TipoIntExt tipo;
//     int n;
//     union {
//         struct {
//             TipoChave rInt[M2];
//             TipoApontadorEstrela pInt[(M2) + 1];
//         };
//         struct {
//             Item rExt[M2];
//         };
//     };
// }TipoPaginaEstrela;

// typedef struct No{
//     Item dadoNo;
//     long direita;
//     long esquerda;
// } No;

// typedef struct Pagina{
//     struct No no[N_ITEM_PAG];
// } Pagina;

// bool pesquisaSeqIndx(unsigned int* tabelaChave, Item* item, FILE* arq, long tamanhoPagina);
// bool sequencialIndexado(long quantidade, int situacao, unsigned int chave, long tamanhoPagina, char* nomeArquivo);
// bool arvoreBinaria(long quantidade, int situacao, unsigned int chave, long tamanhoPagina, char* nomeArquivo);
// bool arvoreB(long quantidade, int situacao, unsigned int chave, long tamanhoPagina, char* nomeArquivo);
// bool arvoreBEstrela(long quantidade, int situacao, unsigned int chave, long tamanhoPagina, char* nomeArquivo);

// //ARVORE BINARIA

// bool insereItemBinario(No R, FILE * arq, const long qtt) {
//     // define para realizar comandos de manipulacao e leitura dos dados do arq
//     #define read_node(i, Item)     (! fseek(arq, i * sizeof(No), SEEK_SET)) && (fread(Item, sizeof(No), 1, arq) > 0)
    
//     //printf("[%s] (qtt:%ld)\n", __func__, qtt);
//     // se a quantidade de itens lidos for igual a 0 so inserimos o item no arq
//     if (qtt == 0)
//     {
//         // Caso verdadeiro, isso significa que o arq está vazio, então podemos inserir direto
//         printf("Primeiro item inserido\n");
//         fwrite(&R, sizeof(No), 1, arq);
//         return true;
        
//     }
//     // variavel temporaria para verificacao dos apontadores da arvore
//     No temp;
//     // variavel que recebe a posicao 
//     long pos = 0;
//     // while para verificar e corrigir os apontadores
//     while (read_node(pos, &temp))
//     {
//         //printf("[%s] qtt: %ld, pos=%ld, temp: <%ld, %ld, %ld>\n", __func__, qtt, pos, temp.esquerda, temp.dadoNo.chave, temp.direita);
//         // se a chave do dado a ser inserida for igual a cheve lida no arq retornamos que a chave ja esta presente no arq
//         if (temp.dadoNo.chave == R.dadoNo.chave) {
//             //caso verdadeiro retornamos que a chave ja esta presente e portanto nao foi inserida
//             printf("A chave já está presente no arq\n");
//             return false;
//         // verificacao se a chave a ser inserida é menor que a presente no arq
//         } else if (temp.dadoNo.chave > R.dadoNo.chave) {
//             // se o filho a esquerda for igual a -1 podemos inserir o novo dado e atualizar os apontadores no arq
//             if (temp.esquerda == -1) {
//                 temp.esquerda = qtt;
//                 fseek(arq, pos * sizeof(No), SEEK_SET);
//                 fwrite(&temp, sizeof(No), 1, arq);
//                 fseek(arq, qtt * sizeof(No), SEEK_SET);
//                 fwrite(&R, sizeof(No), 1, arq);
//                 return true;
//             }
//             // caso nao seja -1 atualizamos a posicao e repetimos o while
//             pos = temp.esquerda;

//         }
//         // caso a chave a ser inserida seja menor que a presente no arq
//         else {
//              // se o filho a direita for igual a -1 podemos inserir o novo dado e atualizar os apontadores no arq
//             if (temp.direita == -1) {
//                 temp.direita = qtt;
//                 fseek(arq, pos * sizeof(No), SEEK_SET);
//                 fwrite(&temp, sizeof(No), 1, arq);
//                 fseek(arq, qtt * sizeof(No), SEEK_SET);
//                 fwrite(&R, sizeof(No), 1, arq);
//                 return true;
//             }
//             // caso nao seja -1 atualizamos a posicao e repetimos o while
//             pos = temp.direita;     
//         }   
//     }
//     return false;
// }

// bool pesquisaItemBinario(long chave, FILE * arq, const long qtt, Item * recebido) {
//     #define read_page(_IndiceDaPagina, _PaginaPtr)     ((! fseek(arq, _IndiceDaPagina * sizeof(struct Pagina), SEEK_SET)) && (fread(_PaginaPtr, sizeof(No), N_ITEM_PAG, arq) > 0))
//     // verificacao se a quantidade de itens no arq e 0
//     if (qtt == 0) {
//         printf("O arq esta vazio\n");
//         return true;
//     }
//     // variavel para leitura das paginas para pesquisa
//     Pagina temp;
//     //variaveis para a manipulacao das paginas
//     long pos = 0;
//     size_t posItem = 0;
//     size_t pag = 0;
//     size_t old_pag = 1;

//     while (true) {   
//         // verificacao para saber se a pagina do item ja foi lida
//         if (old_pag != pag) {
//             if (! read_page(pag, &temp))
//                 break;
//         }
//         // se a chave a ser pesquisada for igual a chave lida atualizamos o recebido e retormanos verdadeiro
//         if(chave == temp.no[posItem].dadoNo.chave) {
//             * recebido = temp.no[posItem].dadoNo;
//             return true;
//         }
//         // verificacao se a chave a ser pesquisada é menor que a chave lida no arq
//         else if (chave < temp.no[posItem].dadoNo.chave) {
//             // se o apontador a esquerda for nulo acabou a pesquisa pela esquerda
//             if (temp.no[posItem].esquerda == -1)  
//                 break;
//             // atualizamos a posicao a ser lida   
//             pos = temp.no[posItem].esquerda;

//             // atualizando os parâmetros de navegação 
//             old_pag = pag;
//             posItem = pos % N_ITEM_PAG;
//             pag = pos / N_ITEM_PAG;
//         } else {
//             // se o apontador a direita for nulo acabou a pesquisa pela esquerda
//             if (temp.no[posItem].direita == -1)     
//                 break;
//             // atualizamos a posicao a ser lida   
//             pos = temp.no[posItem].direita;
            
//             // atualizando os parâmetros de navegação 
//             old_pag = pag;
//             posItem = pos % N_ITEM_PAG;
//             pag = pos / N_ITEM_PAG;
//         }
//     }
//     return false;
// }

// bool arvoreBinaria(long quantidade, int situacao, unsigned int chave, long tamanhoPagina, char* nomeArquivo){
//     // inicializacao das variaveis para a criacao do arq binario
//     No R = { 0 };
//     FILE *arq;
//     FILE *arqbinario;
//     R.direita = -1;
//     R.esquerda = -1;
//     // contador que indica quantos itens o arq possui
//     long qtt = 0;
//     // validacao para verificar se o arq foi aberto corretamente
//     if ((arqbinario = fopen("arvorebinaria.bin", "w+b")) == NULL)
//     {
//         printf("Erro na abertura do arq\n");
//         exit(1);
//     }
//     // validacao para verificar se o arq foi aberto corretamente
//     if ((arq = fopen("arvoreteste.bin", "rb")) == NULL)
//     {
//         printf("Erro na abertura do arq\n");
//         exit(1);
//     }
//     // leitura dos dados do arq para serem inseridos na arvore
//     while (fread(&R.dadoNo, sizeof(Item), 1, arq))
//     {
//         // printf("(Lendo) [%llu]: <%ld, %d, %ld>\n", (unsigned long long) qtt, R.esquerda, R.dadoNo.chave, R.direita);
//         // insercao e verificacao dos itens lidos  
//         if (!insereItemBinario(R, arqbinario, qtt))
//         {
//             printf("Falha ao inserir\n");
//             continue;
//         }
//         //atualizacao do contador
//         qtt++;
//         /*
//         No tempVerifica;
//         rewind(arqbinario);
//         while (fread(&tempVerifica, sizeof(No), 1, arqbinario)) {
//             printf("[%llu]: <%ld, %ld, %ld>\n", (unsigned long long) qtt,
//                 tempVerifica.esquerda, tempVerifica.dadoNo.chave, tempVerifica.direita);
//         }
//         */
//     }
//     // variavel para receber a chave a ser perquisada
//     long pesquisa;
//     // variavel que recebera as informacoes da chave encontrada
//     Item recebido;
//     // recebendo a chave a ser encontrada
//     printf("\npesquisar uma item\nDigite uma chave:\n");
//     scanf("%ld", &pesquisa);
//     // chamada da funcao e verificacao se a chave foi encontrada ou nao
//     if(pesquisaItemBinario(pesquisa, arqbinario, qtt ,&recebido)){
//         printf("Pesquisa realizada com sucesso!\nDado 1: %ld\nDado 2: %s\nDado 3: %s\n", recebido.dado1, recebido.dado2, recebido.dado3);
//     }
//     else{
//         printf("\nItem não encontrado\n");
//     }
//     // fechando os arqs utilizados
//     fclose(arq);
//     fclose(arqbinario);
//     return 0;
// }

// //ARVORE B ESTRELA

// void insereBEstrela(Item Reg, TipoApontadorEstrela* pArvore) {
//     bool cresceu;
//     Item itemRetorno;
//     // TipoChave chaveRetorno;
//     TipoApontadorEstrela pRetorno, pTemp;

//     InsBEstrela(Reg, *pArvore, &cresceu, &itemRetorno, &pRetorno);

//     if (cresceu) {
//         pTemp = (TipoApontadorEstrela)malloc(sizeof(TipoPaginaEstrela));
//         if (*pArvore == NULL) {
//             pTemp->tipo = Externa;
//             pTemp->n = 1;
//             pTemp->rExt[0] = itemRetorno;
//         } else {
//             pTemp->tipo = Interna;
//             pTemp->n = 1;
//             pTemp->rInt[0] = itemRetorno.chave;
//             pTemp->pInt[0] = *pArvore;
//             pTemp->pInt[1] = pRetorno;
//         }
//         *pArvore = pTemp;
//     }

// }

// void inicializaArvoreBEstrela(TipoApontadorEstrela* Arvore) {
//     *Arvore = NULL;
// }

// bool pesquisaArvoreBEstrela(Item* x, TipoApontadorEstrela* pArvore) {
//     if (*pArvore == NULL){
//         //arvore vazia
//         return false;
//     }

//     TipoApontadorEstrela pagina = *pArvore;
//     long i;

//     // Pesquisa em paginas internas
//     if (pagina->tipo == Interna) {
//         i = 1;
//         while (i < pagina->n && x->chave > pagina->rInt[i - 1])
//             i++;

//         if(x->chave < pagina->rInt[i - 1]) i--;
//         return pesquisaArvoreBEstrela(x, &pagina->pInt[i]);

//     } else if (pagina->tipo == Externa) {
//         // PesquisaArvoreBEstrela sequencial na pagina folha
//         i = 1;
//         while (i < pagina->n && x->chave > pagina->rExt[i - 1].chave) 
//             i++;
        
//         if (x->chave == pagina->rExt[i - 1].chave) {
//             *x = pagina->rExt[i - 1];
//             return true;
//         }
//         return false;
//     }
//     return false;
// }

// void insereNaPaginaExternaBEstrelaBEstrela(TipoApontadorEstrela pArvore, Item Reg) {
//     int k = pArvore->n;

//     while (k > 0 && Reg.chave < pArvore->rExt[k - 1].chave) {
//         pArvore->rExt[k] = pArvore->rExt[k - 1];
//         k--;
//         if (k < 1);
//     }
//     pArvore->rExt[k] = Reg;
//     (pArvore->n)++;
// }

// void insereNaPaginaInternaBEstrelaBEstrela(TipoApontadorEstrela pArvore, TipoChave chave, TipoApontadorEstrela pDireita) {
//     int k = pArvore->n;

//     while (k > 0 && chave < pArvore->rInt[k - 1]) {
//         pArvore->rInt[k] = pArvore->rInt[k - 1];
//         pArvore->pInt[k + 1] = pArvore->pInt[k];
//         k--;
//         if (k < 1); 
//     }
//     pArvore->rInt[k] = chave;
//     pArvore->pInt[k + 1] = pDireita;
//     (pArvore->n)++;
// }

// void InsBEstrela(Item Reg, TipoApontadorEstrela pArvore, bool* cresceu, Item* itemRetorno, TipoApontadorEstrela* pArvoreRetorno) {
//     long i;
//     TipoApontadorEstrela pArvoreTemp;

//     if (pArvore == NULL) {
//         *cresceu = true;
//         (*itemRetorno) = Reg;
//         (*pArvoreRetorno) = NULL;
//         return;
//     }

//     if (pArvore->tipo == Interna) {
//         i = 1;
//         while (i < pArvore->n && Reg.chave > pArvore->rInt[i])
//             i++;

//         if(Reg.chave < pArvore->rInt[i - 1]) i--; //saber para onde caminhar
//         InsBEstrela(Reg, pArvore->pInt[i], cresceu, itemRetorno, pArvoreRetorno);

//         if (!*cresceu) return;

//         if (pArvore->n < (M2)) {
//             insereNaPaginaInternaBEstrelaBEstrela(pArvore, itemRetorno->chave, *pArvoreRetorno);
//             *cresceu = false;
//             return;
//         }

//         pArvoreTemp = (TipoApontadorEstrela)malloc(sizeof(TipoPaginaEstrela));
//         pArvoreTemp->tipo = Interna;
//         pArvoreTemp->n = 0;
//         pArvoreTemp->pInt[0] = NULL;

//         if (i <= M + 1) {
//             insereNaPaginaInternaBEstrelaBEstrela(pArvoreTemp, pArvore->rInt[(M2) - 1], pArvore->pInt[M2]);
//             (pArvore->n)--;
//             insereNaPaginaInternaBEstrelaBEstrela(pArvore, itemRetorno->chave, *pArvoreRetorno);
//         } 
//         else insereNaPaginaInternaBEstrelaBEstrela(pArvoreTemp, itemRetorno->chave, *pArvoreRetorno);

//         for (int j = M + 2; j <= (M2); j++) {
//             insereNaPaginaInternaBEstrelaBEstrela(pArvoreTemp, pArvore->rInt[j - 1], pArvore->pInt[j]);
//         }

//         pArvore->n = M;
//         pArvoreTemp->pInt[0] = pArvore->pInt[M + 1];
//         itemRetorno->chave = pArvore->rInt[M];
//         *pArvoreRetorno = pArvoreTemp;
//         *cresceu = true;
//         return;
//     }

//     // Externa
//     i = 1;
//     while (i < pArvore->n && Reg.chave > pArvore->rExt[i - 1].chave)
//         i++;

//     if (pArvore->n < (M2)) {
//         insereNaPaginaExternaBEstrelaBEstrela(pArvore, Reg);
//         *cresceu = false;
//         return;
//     }

//     pArvoreTemp = (TipoApontadorEstrela)malloc(sizeof(TipoPaginaEstrela));
//     pArvoreTemp->tipo = Externa;
//     pArvoreTemp->n = 0;

//     if (i < M + 1) {
//         insereNaPaginaExternaBEstrelaBEstrela(pArvoreTemp, pArvore->rExt[(M2) - 1]);
//         (pArvore->n)--;
//         insereNaPaginaExternaBEstrelaBEstrela(pArvore, Reg);
//     } 
//     else insereNaPaginaExternaBEstrelaBEstrela(pArvoreTemp, Reg);

//     for (int j = M + 1; j <= (M2); j++) {
//         insereNaPaginaExternaBEstrelaBEstrela(pArvoreTemp, pArvore->rExt[j - 1]);
//     }

//     pArvore->n = M;
//     pArvoreTemp->n = M + 1;
//     *itemRetorno = pArvoreTemp->rExt[0];
//     *pArvoreRetorno = pArvoreTemp;
//     *cresceu = true;
//     return;
// }

// bool arvoreBEstrela(long quantidade, int situacao, unsigned int chave, long tamanhoPagina, char* nomeArquivo){
//     FILE* arq;
//     Item item;
//     TipoApontadorEstrela apontador;
//     static const Item itemVazio;
//     // int cont = 1;

//     if ((arq = fopen("registrosDesordenadosCem.bin", "rb")) == NULL) {
//         perror("Erro na abertura do arquivo\n");
//         exit(1);
//     }

//     // Criacao da arvore B
//     inicializaArvoreBEstrela(&apontador);

//     // Insercao de elementos na arvore
//     while (fread(&item, sizeof(Item), 1, arq) > 0) {
//         insereBEstrela(item, &apontador);
//         // Imprime(apontador, 1);
//         // cont++;
//     }

//     item = itemVazio;

//     // PesquisaArvoreBEstrela por elementos da arvore
//     printf("Qual a chave do registro que deseja? ");
//     scanf("%u", &item.chave);

//     if (pesquisaArvoreBEstrela(&item, &apontador)) {
//         printf("\nChave: %u", item.chave);
//         printf("\nDado 1: %ld", item.dado1);
//         printf("\nDado 2: %s", item.dado2);
//         printf("\nDado 3: %s", item.dado3);
//     } else {
//         printf("Item nao encontrado");
//     }

//     fclose(arq);
//     return 0; 
// }

// //ARVORE B

// bool pesquisaArvoreB(Item *x, TipoApontadorB arvore){

//     long i = 1;
    
//     if(arvore == NULL)
//         return false;

//     while(i < arvore->n && x->chave > arvore->registros[i - 1].chave) 
//         i++;

//     if(x->chave == arvore->registros[i - 1].chave){
//         *x = arvore->registros[i - 1];
//         return true;
//     }

//     if(x->chave < arvore->registros[i - 1].chave)
//         return pesquisaArvoreB(x, arvore->apontadores[i - 1]);
//     else    
//         return pesquisaArvoreB(x, arvore->apontadores[i]);
// }

// void insereNaPaginaB(TipoApontadorB pArvore, Item Reg, TipoApontadorB pDireita){
//     int k = pArvore->n; 

//     while(k > 0 && Reg.chave < pArvore->registros[k - 1].chave){
//         pArvore->registros[k] = pArvore->registros[k - 1];
//         pArvore->apontadores[k + 1] = pArvore->apontadores[k];
//         k--;
//         if(k < 1);
//     }
//     pArvore->registros[k] = Reg;
//     pArvore->apontadores[k + 1] = pDireita;
//     (pArvore->n)++;
// }

// void InsB(Item Reg, TipoApontadorB pArvore, bool *cresceu, Item *regRetorno, TipoApontadorB *pArvoreRetorno){
//     long i = 1;
//     TipoApontadorB pArvoreTemp;
//     //arvore nao existe OU no folha encontrado
//     if(pArvore == NULL){
//         *cresceu = true;
//         (*regRetorno) = Reg;
//         (*pArvoreRetorno) = NULL;
//         return;
//     }

//     while(i < pArvore->n && Reg.chave > pArvore->registros[i - 1].chave)
//          i++;

//     if(Reg.chave ==  pArvore->registros[i - 1].chave){
//         printf("Registro ja presente\n");
//         *cresceu = false;
//         return;
//     }

//     if(Reg.chave < pArvore->registros[i - 1].chave) i--; //saber para onde caminhar
//     InsB(Reg, pArvore->apontadores[i], cresceu, regRetorno, pArvoreRetorno);
   
//     if(!*cresceu) return;

//     if(pArvore->n < (M2)){ //pagina tem espaco
//         insereNaPaginaB(pArvore, *regRetorno, *pArvoreRetorno);
//         *cresceu = false;
//         return;
//     }

//     // Overflow: pagina tem que ser dividida
//     pArvoreTemp = (TipoApontadorB)malloc(sizeof(TipoPaginaB));
//     pArvoreTemp->n = 0;
//     pArvoreTemp->apontadores[0] = NULL;

//     //determina em qual das duas paginas sera inserida o novo elemento 
//     if(i < M + 1){
//         insereNaPaginaB(pArvoreTemp, pArvore->registros[(M2) - 1], pArvore->apontadores[M2]);
//         (pArvore->n)--;
//         insereNaPaginaB(pArvore, *regRetorno, *pArvoreRetorno);
//     }
//     else insereNaPaginaB(pArvoreTemp, *regRetorno, *pArvoreRetorno);

//     for(int j = M + 2; j <= (M2); j++){
//         insereNaPaginaB(pArvoreTemp, pArvore->registros[j - 1], pArvore->apontadores[j]);
//     }
//         pArvore->n = M;
//         pArvoreTemp->apontadores[0] = pArvore->apontadores[M + 1];
//         *regRetorno = pArvore->registros[M];
//         *pArvoreRetorno = pArvoreTemp;        
// }

// void insereB(Item Reg, TipoApontadorB *pArvore){
//     bool cresceu;
//     Item itemRetorno;
//     TipoApontadorB pRetorno, pTemp;
//     InsB(Reg, *pArvore, &cresceu, &itemRetorno, &pRetorno);
//     if(cresceu){ // Arvore cresce na altura pela raiz
//         pTemp = (TipoPaginaB*)malloc(sizeof(TipoPaginaB));
//         pTemp->n = 1;
//         pTemp->registros[0] = itemRetorno;
//         pTemp->apontadores[0] = *pArvore;
//         pTemp->apontadores[1] = pRetorno;
//         *pArvore = pTemp;
//     }
// }

// void inicializaArvoreB(TipoApontadorB *Arvore){
//     *Arvore = NULL;
// }

// bool arvoreB(long quantidade, int situacao, unsigned int chave, long tamanhoPagina, char* nomeArquivo){

//     FILE *arq;
//     Item item;
//     TipoApontadorB apontador;
//     static const Item itemVazio;
    
//     if((arq = fopen(nomeArquivo, "rb")) == NULL){
//         perror("Erro na abertura do arquivo\n");
//         exit(1);
//     } 

//     //criacao da arvore B
//     inicializaArvoreB(&apontador);

//     //insercao de elementos na arvore
//     while(fread(&item, sizeof(Item), 1, arq) > 0)
//         insereB(item, &apontador);

//     //pesquisa por elementos da arvore

//     item = itemVazio;

//     printf("Qual a chave do registro que deseja? ");
//     scanf("%u", &item.chave);
    
//     if(pesquisaArvoreB(&item, apontador)){
//         printf("\nChave: %u", item.chave);
//         printf("\nDado 1: %ld", item.dado1);
//         printf("\nDado 2: %s", item.dado2);
//         printf("\nDado 3: %s", item.dado3);
//     } else 
//         printf("Item nao encontrado");
    
//     fclose(arq);
//     return 0;       
// }

// //GERAL 

// long determinarTamanhoPagina(long quantidade){
    
//     if(quantidade >= 10e6)
//         return 2790;
//     else if(quantidade >=10e5)
//         return 697;
//     else if(quantidade >=10e4)
//         return 174;
//     else if(quantidade >=10e3)
//         return 43;
//     else
//         return 10;
// }

// bool nomearArquivo(int tamanhoPagina, int situacao, char* nomeArquivo){

//     switch(tamanhoPagina){

//     case 2790:
//         switch(situacao)
//         {
//         case 1:
//             strcpy(nomeArquivo, "milhaoCrescente.bin");
//             break;
//         case 2:
//             strcpy(nomeArquivo, "milhaoDecrescente.bin");
//             break;
//         case 3:
//             strcpy(nomeArquivo, "milhaoDesordenado.bin");
//             break;
//         default:
//             return false;
//             break;
//         }
//         break;
//     case 697:
//         switch(situacao)
//         {
//         case 1:
//             strcpy(nomeArquivo, "cemMilCrescente.bin");
//             break;
//         case 2:
//             strcpy(nomeArquivo, "cemMilDecrescente.bin");
//             break;
//         case 3:
//             strcpy(nomeArquivo, "cemMilDesordenado.bin");
//             break;
//         default:
//             return false;
//             break;
//         }
//         break;
//     case 174:
//         switch(situacao)
//         {
//         case 1:
//             strcpy(nomeArquivo, "dezMilCrescente.bin");
//             break;
//         case 2:
//             strcpy(nomeArquivo, "dezMilDecrescente.bin");
//             break;
//         case 3:
//             strcpy(nomeArquivo, "dezMilDesordenado.bin");
//             break;
//         default:
//             return false;
//             break;
//         }
//         break;
//     case 43:
//         switch(situacao)
//         {
//         case 1:
//             strcpy(nomeArquivo, "milCrescente.bin");
//             break;
//         case 2:
//             strcpy(nomeArquivo, "milDecrescente.bin");
//             break;
//         case 3:
//             strcpy(nomeArquivo, "milDesordenado.bin");
//             break;
//         default:
//             return false;
//             break;
//         }
//         break;
//     case 10:
//         switch(situacao)
//         {
//         case 1:
//             strcpy(nomeArquivo, "cemCrescente.bin");
//             break;
//         case 2:
//             strcpy(nomeArquivo, "cemDecrescente.bin");
//             break;
//         case 3:
//             strcpy(nomeArquivo, "cemDesordenado.bin");
//             break;
//         default:
//             return false;
//             break;
//         }
//         break;
//     }
//     return true;
// }

// bool pesquisa(int metodo, long quantidade, int situacao, unsigned int chave){

//     long tamanhoPagina;
//     char* nomeArquivo = NULL;

//     tamanhoPagina = determinarTamanhoPagina(quantidade);
//     if(!nomearArquivo(tamanhoPagina, situacao, nomeArquivo))
//         return false;

//     switch(metodo){
//     case 1:
//         sequencialIndexado(quantidade, situacao, chave, tamanhoPagina, nomeArquivo);
//         break;
//     case 2:
//         arvoreBinaria(quantidade, situacao, chave, tamanhoPagina, nomeArquivo);
//         break;
//     case 3:
//         arvoreB(quantidade, situacao, chave, tamanhoPagina, nomeArquivo);
//         break;
//     case 4:
//         arvoreBEstrela(quantidade, situacao, chave, tamanhoPagina, nomeArquivo);
//         break;
//     default:
//         return false;
//         break;
//     }
//     return true;
// }

// //SEQUENCIAL INDEXADO

// bool sequencialIndexado(long quantidade, int situacao, unsigned int chave, long tamanhoPagina, char* nomeArquivo){

//     unsigned int tabelaChave[tamanhoPagina * 2]; 
//     Item item[tamanhoPagina];
//     FILE *arq;

//     if((arq = fopen(nomeArquivo, "rb")) == NULL){
//         perror("Erro na abertura do arquivo\n");
//         exit(1);
//     } 

//     //criacao da tabela de indices com chave
//     for(int i = 0; fread(item, sizeof(Item), tamanhoPagina, arq) > 0; i++)
//         tabelaChave[i] = item[0].chave; 
    
//     //inicio da pesquisa
//     printf("Chave desejada: ");
//     scanf("%u", &item->chave); //chave 

//     if(pesquisaSeqIndx(tabelaChave, item, arq, tamanhoPagina)){
//         printf("\nChave: %u", item->chave);
//         printf("\nDado 1: %ld", item->dado1);
//         printf("\nDado 2: %s", item->dado2);
//         printf("\nDado 3: %s", item->dado3);
//     } else {
//         printf("Item nao existente");
//     }
//     fclose(arq);
//     return 0;
// }

// bool pesquisaSeqIndx(unsigned int* tabelaChave, Item* item, FILE* arq, long tamanhoPagina){
//     rewind(arq);

//     long int desloc;
//     int quantItens;
//     Item paginaEscolhida[tamanhoPagina];
//     int i = 0; int tam = tamanhoPagina * 2;
//     while(i < tam && tabelaChave[i] <= item->chave) i++;
//     int meio; int limInf = 0; int limSup;

//     if(i == 0) return false; 
//     if(i < tam) quantItens = tamanhoPagina;
//     else{ //Chave se encontra na ultima pagina
//         fseek(arq, 0, SEEK_END); //Ir pra o final do arquivo
//         quantItens = (ftell(arq) / sizeof(Item)) % tamanhoPagina;
//         if(quantItens == 0) quantItens = tamanhoPagina;
//     }   
//     desloc = sizeof(Item) * tamanhoPagina * (i - 1);
//     fseek (arq, desloc, SEEK_SET);
//     fread(paginaEscolhida, sizeof(Item), quantItens, arq);
    
//     limSup = quantItens - 1;

//     while(limInf <= limSup){
//         meio = (limInf + limSup) / 2;
//         if(paginaEscolhida[meio].chave == item->chave){
//             *item = paginaEscolhida[meio];
//             return true;
//         }
//         if(paginaEscolhida[meio].chave < item->chave)
//             limInf = meio + 1;
//         else   
//             limSup = meio - 1;
//     }
//     return false;
// }

//MAIN