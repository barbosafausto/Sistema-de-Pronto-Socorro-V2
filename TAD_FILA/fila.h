#ifndef FILA_H
    #define FILA_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include "../TAD_Paciente/paciente.h"

    typedef struct fila FILA;

    //Aloca espaço para a fila
    FILA *fila_criar(void); 

    //fila_criar_no(): cria um nó e o preenche
    //TrocaNo(): faz swap entre dois nós
    //No_get_paciente(): pega o paciente de seu nó

    //ChecaPrioridade(): verifica qual é mais prioritório entre 2 pacientes

    //Funções fila_cheia() e fila_vazia()
    bool fila_cheia(FILA *f);
    bool fila_vazia(FILA *f);

    //FixUp()
    //FixDown()

    //Insere um paciente na fila
    bool fila_inserir(FILA *f, PACIENTE *p, char urgencia);

    //Retira o elemento de maior prioridade da fila
    PACIENTE *fila_remover(FILA *f);


    //Lista os elementos em ordem de prioridade
    void fila_listar(FILA *f);



    //Cria e inseri os elementos de um arquivo na fila; nome do arquivo: "TAD_FILA/fila.txt"
    FILA *fila_carregar(void); 
    //Remove e apaga a fila, armazenando seus elementos em um arquivo; nome do arquivo: "TAD_FILA/fila.txt"
    bool fila_salvar(FILA **f);
#endif