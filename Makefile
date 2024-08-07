CC = gcc
CFLAGS = -Wall -Wextra -I.

OBJ = main.o funcoesGerais.o funcSeqIndx.o funcArvoreBinaria.o funcArvoreB.o funcArvoreBEstrela.o

all: pesquisa

pesquisa: $(OBJ)
	$(CC) $(CFLAGS) -o pesquisa $(OBJ)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

funcoesGerais.o: funcoesGerais.c
	$(CC) $(CFLAGS) -c funcoesGerais.c

funcSeqIndx.o: funcSeqIndx.c
	$(CC) $(CFLAGS) -c funcSeqIndx.c

funcArvoreBinaria.o: funcArvoreBinaria.c
	$(CC) $(CFLAGS) -c funcArvoreBinaria.c

funcArvoreB.o: funcArvoreB.c
	$(CC) $(CFLAGS) -c funcArvoreB.c

funcArvoreBEstrela.o: funcArvoreBEstrela.c
	$(CC) $(CFLAGS) -c funcArvoreBEstrela.c

clean:
	rm -f *.o pesquisa
