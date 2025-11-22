#include "registro.h"
#include <stdlib.h>
#include <stdio.h>

#define ESTA_FILA 2
#define ESTA_REGISTRO 1
#define NAO_ESTA 0

#define max(a, b) ((a > b) ? a : b) //Parenteses para não atrapalhar a precedência

typedef struct no_registro NO;

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

NO* registro_criar_no(PACIENTE* p, bool esta_na_fila){

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

NO* registro_apagar_no(NO* n){
  
  if(n != NULL){
    
    registro_apagar_no(n->esq);
    registro_apagar_no(n->dir);

    paciente_apagar(&(n->p));
    
    free(n);
    n = NULL; //Para retornar NULL e o pai não ter mais acesso
  }

  return n;
}

bool registro_apagar(REGISTRO** r){

  if (r != NULL && *r != NULL) {
    (*r)->raiz = registro_apagar_no((*r)->raiz);
    free(*r);
    *r = NULL;
    return true;
  }
  
  return false;
}

int registro_altura_no(NO *A) {

  if (A == NULL) return -1;

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

/*Calcula o Fator de Balanceamento do nó A*/
int registro_calcular_fb(NO* A){
  return (registro_altura_no(A->esq) - registro_altura_no(A->dir));
}

NO* registro_inserir_no(NO* n, PACIENTE* p, bool esta_na_fila, char* verifica){
  
  if(n == NULL){ //Chegou no fim da árvore
    NO* novo = registro_criar_no(p, esta_na_fila); //Já inicializa a altura como 0
    return novo;
  }
  
  //Organizamos os dados na árvore de acordo com o id dos pacientes
  if(paciente_get_id(n->p) < paciente_get_id(p)){ //Se id maior, insere-se na direita
    n->dir = registro_inserir_no(n->dir, p, esta_na_fila, verifica);
  }
  else if(paciente_get_id(n->p) > paciente_get_id(p)){ //Se id menor, insere-se na esquerda
    n->esq = registro_inserir_no(n->esq, p, esta_na_fila, verifica);
  }
  else{//Se tem o mesmo id, não deve ser inserido: ID É ÚNICO
    if(n->esta_na_fila) (*verifica) = ESTA_FILA; //O nó também já está na fila
    else (*verifica) = ESTA_REGISTRO;
    return n; //Comça a voltar na recursão sem perder os ponteiros;
  }
  
  n->altura = max(registro_altura_no(n->dir),registro_altura_no(n->esq))+1; //Atualizando altura

  int fb = registro_calcular_fb(n); //Para verificação do balanceamento

  if(fb >= 2){ //Está pendendo para esquerda

    if(registro_calcular_fb(n->esq) < 0){ //E o filho esquerdo pendendo para a direita 
      printf("Rotação esquerda-direita."); //Debug
      n = registro_rodar_esq_dir(n);
    }

    else{
      printf("Rotação direita."); //Debug
      n = registro_rodar_direita(n);
    }
  }

  else if(fb <= -2){ //Está pendendo para direita

    if(registro_calcular_fb(n->dir) > 0){ //E o filho direito pendendo para a esquerda
      printf("Rotação direita-esquerda."); //Debug
      n = registro_rodar_dir_esq(n);
    }

    else{
      printf("Rotação esquerda."); //Debug
      n = registro_rodar_esquerda(n);
    }
  }
  printf("\n");
  
  return n;
}

int_8 registro_inserir(REGISTRO* r, PACIENTE* p, bool esta_na_fila){
  
  int_8 verifica = NAO_ESTA;

  if(r != NULL) r->raiz = registro_inserir_no(r->raiz, p, esta_na_fila, &verifica);
  
  return verifica;

}

void registro_listar_no(NO* n){ //Percorre em ordem
  if(n != NULL){
    registro_listar_no(n->esq);
    printf("%06d| %s\n", paciente_get_id(n->p), paciente_get_nome(n->p)); //Printa os números de forma alinhada
    registro_listar_no(n->dir);
  }
}

void registro_listar(REGISTRO* r){
  if(r != NULL){
    printf("#     | NOME\n");
    registro_listar_no(r->raiz); 
    printf("\n");
  }
}
