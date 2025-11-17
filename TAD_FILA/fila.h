#ifndef FILA_H
    #define FILA_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include "../TAD_Paciente/paciente.h"

    typedef struct fila FILA;

    //Aloca espaço para a fila
    FILA *fila_criar(void); 

    //Cria e inseri os elementos de um arquivo na fila; nome do arquivo: "TAD_FILA/fila.txt"
    FILA *fila_carregar(void); 
    //Remove e apaga a fila, armazenando seus elementos em um arquivo; nome do arquivo: "TAD_FILA/fila.txt"
    bool fila_salvar(FILA **f);

    //Insere um paciente na fila
    bool fila_inserir(FILA *f, PACIENTE *p, char urgencia);
    //Retira o elemento de maior prioridade da fila
    PACIENTE *fila_remover(FILA *f);

    bool fila_cheia(FILA *f);
    bool fila_vazia(FILA *f);

    //Lista os elementos em ordem de prioridade
    void fila_listar(FILA *f);
#endif