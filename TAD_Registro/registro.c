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


bool registro_vazio(REGISTRO* r){
  
  if (r == NULL) {
    return true; //Registros inválidos são considerados vazios.
  }
  
  return (r->raiz == NULL);
}

bool registro_cheio(REGISTRO *r) {

  NO *node = (NO*) malloc(sizeof(NO));

  if (node) {

    free(node);
    return false;
  }

  return true;
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




//---- Altura 
int registro_altura_no(NO *A) {

  if (A == NULL) return -1;

  return A->altura;
}





//Funções de rotação
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





//----Recuperação de valor
NO* registro_recuperar_no(NO *raiz, int id) {

  if (!raiz) return NULL;

  int id_no = paciente_get_id(raiz->p);

  if (id < id_no) return registro_recuperar_no(raiz->esq, id);
  if (id > id_no) return registro_recuperar_no(raiz->dir, id);
  
  return raiz;
}

PACIENTE* registro_recuperar(REGISTRO* r, int id) {

  NO *paciente = registro_recuperar_no(r->raiz, id);

  return paciente->p;
}
//---Fim da recuperação de valor




//---Inserção de valor
NO* registro_inserir_no(NO* n, PACIENTE* p, bool esta_na_fila, char* verifica){
  
  if(n == NULL) { //Chegou no fim da árvore

    NO* novo = registro_criar_no(p, esta_na_fila); //Já inicializa a altura como 0
    return novo;
  }
  
  //Organizamos os dados na árvore de acordo com o id dos pacientes
  if (paciente_get_id(n->p) < paciente_get_id(p)) //Se id maior, insere-se na direita
    n->dir = registro_inserir_no(n->dir, p, esta_na_fila, verifica);

  else if (paciente_get_id(n->p) > paciente_get_id(p)) //Se id menor, insere-se na esquerda
    n->esq = registro_inserir_no(n->esq, p, esta_na_fila, verifica);

  else { //Se tem o mesmo id, não deve ser inserido: ID É ÚNICO
    if(n->esta_na_fila) (*verifica) = ESTA_FILA; //O nó também já está na fila
    else (*verifica) = ESTA_REGISTRO;
    return n; //Começa a voltar na recursão sem perder os ponteiros;
  }
  
  n->altura = max(registro_altura_no(n->dir),registro_altura_no(n->esq))+1; //Atualizando altura

  int fb = registro_calcular_fb(n); //Para verificação do balanceamento

  if(fb >= 2) { //Está pendendo para esquerda

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
//Fim da inserção de valor




//Começo da remoção de valor
NO* troca_max_esq(NO *troca, NO *raiz, PACIENTE** p) {

  printf("Entrando no paciente %d\n", paciente_get_id(troca->p));
  if (troca->dir) {


    troca->dir = troca_max_esq(troca->dir, raiz, p);
  }

  else {
    
    NO* temp = troca->esq;

    *p = raiz->p;
    raiz->p = troca->p; 

    troca->esq = NULL;
    free(troca);
    troca = NULL;

    return temp;
  }

  printf("Atualmente no nó %d, voltando.\n", paciente_get_id(troca->p));
  //Atualização da altura
  troca->altura = max(registro_altura_no(troca->esq), registro_altura_no(troca->dir)) + 1;

  int fb = registro_calcular_fb(troca);

  printf("Fator de balanceamento: %d\n", fb);

  //Rodar direita
  if (fb == 2) {

    //Rotação simples
    if (registro_calcular_fb(troca->esq) >= 0)
      troca = registro_rodar_direita(troca), printf("Rotação direita.\n");

    //Rotação dupla
    else troca = registro_rodar_esq_dir(troca), printf("Rotação esquerda-direita.\n");
  }

  //Rodar esquerda
  else if (fb == -2) {

    //Rotação simples
    if (registro_calcular_fb(troca->dir) <= 0)
      troca = registro_rodar_esquerda(troca), printf("Rotação esquerda.\n");

    //Rotação dupla
    else troca = registro_rodar_dir_esq(troca), printf("Rotação direita-esquerda.\n");
  }

  return troca;
}

NO* registro_remover_no(NO *raiz, int id, PACIENTE **p) {
  
  if (!raiz) return NULL;

  int id_no = paciente_get_id(raiz->p);

  if (id < id_no) raiz->esq = registro_remover_no(raiz->esq, id, p);
  else if (id > id_no) raiz->dir = registro_remover_no(raiz->dir, id, p);
  else {

    *p = raiz->p;

    if (raiz->esq == NULL || raiz->dir == NULL) {
      
      NO* aux;
      if (raiz->esq == NULL) {

        aux = raiz->dir;

        raiz->dir = NULL;
        free(raiz);
        raiz = NULL;

        return aux;

      }

      else if (raiz->dir == NULL) {

        aux = raiz->esq;

        raiz->esq = NULL;
        free(raiz);
        raiz = NULL;

        return aux;
      }
    }

    else {

      printf("Fazendo a troca a partir do nó %d\n", paciente_get_id(raiz->p));
      raiz->esq = troca_max_esq(raiz->esq, raiz, p);
    }
  }

  if (raiz) {

    raiz->altura = max(registro_altura_no(raiz->esq), registro_altura_no(raiz->dir)) + 1;

    //Rebalanceamento, se necessário
    int fb = registro_calcular_fb(raiz);
    //
    //Rodar direita
    if (fb == 2) {

      //Rotação simples
      if (registro_calcular_fb(raiz->esq) >= 0)
        raiz = registro_rodar_direita(raiz), printf("Rotação direita.\n");

      //Rotação dupla
      else raiz = registro_rodar_esq_dir(raiz), printf("Rotação esquerda-direita.\n");
    }

    //Rodar esquerda
    else if (fb == -2) {

      //Rotação simples
      if (registro_calcular_fb(raiz->dir) <= 0)
        raiz = registro_rodar_esquerda(raiz), printf("Rotação esquerda.\n");

      //Rotação dupla
      else raiz = registro_rodar_dir_esq(raiz), printf("Rotação direita-esquerda.\n");
    }

    }

    return raiz;
}


PACIENTE* registro_remover(REGISTRO* r, int id) {

  if (!r) return NULL;

  PACIENTE* p = NULL;
  r->raiz = registro_remover_no(r->raiz, id, &p);

  return p;
}
//Fim da remoção de valor





//Início da listagem de nós
void registro_listar_no(NO* n){ //Percorre em ordem

  if(n != NULL) {

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
//Fim da listagem de nós




//Funções de carregamento e salvamento
void registro_salvar_no(NO *raiz) {

  if (!raiz) return;
  
  //Pós-ordem, para não perder o acesso aos ponteiros
  registro_salvar_no(raiz->esq);
  registro_salvar_no(raiz->dir);

  //Usando a opção append para escrever no final do arquivo, sem apagar nada
  FILE *fp = fopen("registro.txt", "a");

  //Escrevendo no arquivo: id, nome, esta_na_fila
  fprintf(fp, "%d\n", paciente_get_id(raiz->p));
  fprintf(fp, "%s\n", paciente_get_nome(raiz->p));
  fprintf(fp, "%d\n", raiz->esta_na_fila);
  fprintf(fp, "\n");

  //Fechando arquivo
  fclose(fp);

  //Desalocando tudo
  raiz->esq = raiz->dir = NULL;
  paciente_apagar(&raiz->p);
  free(raiz);
  raiz = NULL;

}

bool registro_salvar(REGISTRO **r) {

  if (!r || !*r) return false;

  //Abrindo o arquivo em modo de escrita para apagar o conteúdo que tem nele
  FILE *fp = fopen("registro.txt", "w");
  fclose(fp);

  /*A lógica de salvamento será:
  ID
  Nome
  esta_na_fila
  
  ID
  Nome
  esta_na_fila
  ...*/

  registro_salvar_no((*r)->raiz);

  free(*r);
  *r = NULL;

  return true;
}




void imprimir_no_visual(NO *raiz, int nivel) {

    if (raiz == NULL) return;

    imprimir_no_visual(raiz->dir, nivel + 1);

    for (int i = 0; i < nivel; i++) printf("    ");
    printf("%d\n", paciente_get_id(raiz->p)); 

    imprimir_no_visual(raiz->esq, nivel + 1);
}

void imprimir_arvore_visual(REGISTRO* r) {

    imprimir_no_visual(r->raiz, 0);
}
