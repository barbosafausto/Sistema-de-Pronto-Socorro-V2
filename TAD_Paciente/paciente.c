#include "paciente.h"
#include <stdlib.h>
#include <string.h>

struct paciente {
    char* nome;
    bool esta_fila; //Indica se o paciente está também na fila
    int id;
};

PACIENTE* paciente_criar(char* nome, int id) {

    //Alocando espaço p/ struct
    PACIENTE* p = (PACIENTE*) malloc(sizeof(PACIENTE));

    if (p != NULL) {

        //Alocando espaço p/ nome + '\0'
        p->nome = (char*) malloc(sizeof(char) * (strlen(nome) + 1));
        strcpy(p->nome, nome);

        p->id = id;

        p->esta_fila = false; //Consideramos inicialmente que o paciente não está fila, esse valor será alterado em funções do TAD_Fila

        return p;
    }

    return NULL;
}

bool paciente_apagar(PACIENTE** p) {

    if (*p != NULL) {

        //Liberando alocação do nome
        free((*p)->nome);
        (*p)->nome = NULL;

        //Liberando alocação da struct
        free(*p);
        *p = NULL;

        return true;
    }
    
    return false;
}

char* paciente_get_nome(PACIENTE* p) {

    if (p != NULL) {
        return p->nome;
    }

    return NULL;
}

int paciente_get_id(PACIENTE* p) {

    if (p != NULL) {
        return p->id;
    }

    return -1; //Retorna ID inválido caso o paciente não exista.
}

bool paciente_get_esta_fila(PACIENTE *p){
    if(p != NULL) return p->esta_fila;
    return false;
}

void paciente_set_esta_fila(PACIENTE *p, bool esta_fila){
    if(p != NULL) p->esta_fila = esta_fila;
}