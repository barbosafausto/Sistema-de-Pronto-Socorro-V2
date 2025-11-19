#include "registro.h"
#include <stdlib.h>

struct registro_ {
  NO* raiz;
};

struct no_registro {
  
  PACIENTE* p; //Como "p" acaba sendo usado como variável de paciente em testes, dar um nome único à variável dentro do nó evita confusão.
  NO* dir;
  NO* esq;
  int altura;
  bool esta_na_fila;

};

REGISTRO* registro_criar(void){

  REGISTRO *r = malloc(sizeof(REGISTRO));
  if (r == NULL) {
    return NULL;
  }

  r->raiz = NULL; //Registro é criado sem raiz.
  return(r);
  
}

NO* no_criar(PACIENTE* p, bool esta_na_fila){

  NO *n = malloc(sizeof(NO));
  if (n == NULL) {
    return NULL;
  }
  
  n->p = p;
  n->dir = NULL;
  n->esq = NULL;
  n->altura = 0;
  n->esta_na_fila = esta_na_fila; //Ao serem criados, nós são considerados como não estando na fila, pois vários nós são gerados ao carregar o registro e nem todos estarão na fila.
  
  return n;
}

bool registro_vazio(REGISTRO* r){
  
  if (r == NULL) {
    return true; //Registros inválidos são considerados vazios.
  }
  
  return (r->raiz == NULL);
}

PACIENTE* no_get_paciente(NO* n){
  if (n != NULL) {
    return (n->p);
  }
  return NULL;
}

bool no_apagar(NO** n){

  if (*n != NULL) {
    paciente_apagar(&(*n)->p);
    free(*n);
    *n = NULL;
    return true;
  }

  return false;
}

bool registro_apagar(REGISTRO** r){

  if (*r != NULL) {
    free(*r);
    *r = NULL;
    return true;
  }
  
  return false;
}
