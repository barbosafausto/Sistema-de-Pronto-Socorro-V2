#include "registro.h"
#include <stdlib.h>

struct registro_ {
  PACIENTE* raiz;
};

struct no_registro {
  
  PACIENTE* ficha; //Como "p" acaba sendo usado como variável de paciente em testes, dar um nome único à variável dentro do nó evita confusão.
  NOr* Fdir;
  NOr* Fesq;
  int altura;
  bool estanafila;

};

REGISTRO* registro_criar(void){

  REGISTRO *r = malloc(sizeof(REGISTRO));
  if (r == NULL)
  {
    return NULL;
  }
  r->raiz = NULL; //Registro é criado sem raiz.
  return(r);
  
}

NOr* no_criar(PACIENTE* p){

  NOr *n = malloc(sizeof(NOr));
  if (n == NULL)
  {
    return NULL;
  }
  n->ficha = p;
  n->Fdir = NULL;
  n->Fesq = NULL;
  n->altura = 0;
  n->estanafila = false; //Ao serem criados, nós são considerados como não estando na fila, pois vários nós são gerados ao carregar o registro e nem todos estarão na fila.

}

bool registro_vazio(REGISTRO* r){
  
  if (r == NULL)
  {
    return true; //Registros inválidos são considerados vazios.
  }
  
  if (r->raiz != NULL)
  {
    return false;
  }
  else
  {
    return true; 
  }
}

PACIENTE* no_get_paciente(NOr* n){
  if (n != NULL)
  {
    return (n->ficha);
  }
  return NULL;
}

bool no_apagar(NOr** n){
  if (*n != NULL)
  {
    paciente_apagar(&(*n)->ficha);
    free(*n);
    *n = NULL;
    return true;
  }
  return false;
}

bool registro_apagar(REGISTRO** r){

  if (*r != NULL)
  {
    free(*r);
    *r = NULL;
    return true;
  }
  
  return false;
}
