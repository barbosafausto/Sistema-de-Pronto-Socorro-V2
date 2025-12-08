#ifndef FILA_H
    #define FILA_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    
    #include "../TAD_Paciente/paciente.h"
    #include "../TAD_Registro/registro.h"

    typedef struct fila FILA;

    //Aloca memória para a fila.
    FILA *fila_criar(void); 


    //Verifica se há espaço na fila; se a fila estiver cheia, essa é aumentada. 
    bool fila_cheia_aumentar(FILA *f); 
    //Retorna verdadeiro, se não for possível nem aumentar o tamnanho da fila.
    
    //Verfique se a fila está sem pacientes.
    bool fila_vazia(FILA *f);

    //Insere um paciente na fila.
    bool fila_inserir(FILA *f, PACIENTE *p, char urgencia);

    //Retira o paciente de maior prioridade da fila
    PACIENTE *fila_remover(FILA *f);


    //Lista os elementos em ordem de prioridade, se tiver memória necessária, isto é, o mesmo espaço ocupado pela fila no momento; se houver indisponibilidade de memória, a fila será impresso fora de ordem.
    void fila_listar(FILA **f);

    //Carrega a fila salva no arquivo "TAD_Fila/fila.txt". Nesse processo, são alocados memória para tais estruturas.
    FILA *fila_carregar(REGISTRO *r); 
    //Salva a fila no arquivo "TAD_Fila/fila.txt". Nesse processo, é liberado a memória ocupada por essa estruturas.
    bool fila_salvar(FILA **f);

    /*Formato do arquivo  "TAD_Fila/fila.txt":
	ID
	Urgência

	ID
	Urgência
	...
	*/

#endif
