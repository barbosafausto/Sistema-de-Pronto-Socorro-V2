#ifndef FILA_H
    #define FILA_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    
    #include "../TAD_Paciente/paciente.h"
    #include "../TAD_Registro/registro.h"

    //Funções comentadas neste .h são funções auxiliares das quais o cliente não tem acesso. Estão explicitadas aqui apenas para explicar o funcionamento das outras funções.

    typedef struct fila FILA;

    //Aloca espaço para a fila
    FILA *fila_criar(void); 

    //NO *fila_criar_no(PACIENTE *p, char urgencia, uint ordem_chegada); 
    
    //Função de troca entre dois nós (para fix_up e fix_down)
    //void fila_swap_no(NO **a, NO **b);
    
    //Compara a prioridade de dois nós.
    //bool fila_checa_prioridade(NO *a, NO *b);

    //Funções fila_cheia() e fila_vazia()
    bool fila_cheia_aumentar(FILA *f); //Confere se há espaço na heap, se a fila estiver cheia aumenta o tamanho da fila
    //void fila_diminuir(FILA *f); //Reduz o tamanho da fila. Apenas usada por fila_remover.
    bool fila_vazia(FILA *f);

    //Deslocam nós no fim e no começo da fila para suas posições corretas.
    //void fila_fix_up(FILA *f);
    //void fila_fix_down(FILA *f);

    //Insere um paciente na fila
    //bool fila_inserir_no(FILA* f, NO *node); Função auxiliar.
    bool fila_inserir(FILA *f, PACIENTE *p, char urgencia);

    //Retira o elemento de maior prioridade da fila
    //NO* fila_remover_no(FILA* f); Função auxiliar.
    PACIENTE *fila_remover(FILA *f);


    //Lista os elementos em ordem de prioridade
    void fila_listar(FILA **f);

    //Cria e insere os elementos de um arquivo na fila; nome do arquivo: "TAD_Fila/fila.txt"
    FILA *fila_carregar(REGISTRO *r); 
    //Remove e apaga a fila, armazenando seus elementos em um arquivo; nome do arquivo: "TAD_Fila/fila.txt"
    bool fila_salvar(FILA **f);

#endif
