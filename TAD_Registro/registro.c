#include "registro.h"
#include <stdlib.h>

#define max(a, b) ((a > b) ? a : b)

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

int registro_altura_no(NO *A) {

  if (!A) return -1;

  return A->altura;
}

NO* registro_rodar_esquerda(NO* A) {

  NO* B = A->dir;

  A->dir = B->esq;
  B->esq = A;

  A->altura = max(registro_altura_no(A->esq), registro_altura_no(A->dir)) + 1;

  return B;
}

NO* registro_rodar_direita(NO* A) {

  NO *B = A->esq;

  A->esq = B->dir;
  B->dir = A;

  A->altura = max(registro_altura_no(A->esq), registro_altura_no(A->dir)) + 1;
  
  return B;
}

NO* registro_rodar_esq_dir(NO* A) {


  A->esq = registro_rodar_esquerda(A->esq);

  return registro_rodar_direita(A);
}

NO* registro_rodar_dir_esq(NO* A) {

  A->dir = registro_rodar_direita(A->dir);

  return registro_rodar_esquerda(A);
}