#include "registro.h"

#define ESTA_FILA 2
#define ESTA_REGISTRO 1
#define NAO_ESTA 0

#define max(a, b) ((a > b) ? a : b) //Parenteses para não atrapalhar a precedência

typedef struct no_registro NO;

struct registro_ {
  NO* raiz;
};

struct no_registro {
  
  PACIENTE* p;
  NO* dir;
  NO* esq;
  int altura;

};

/*===============================================================================*/
//Funções de alocar nó e registro

REGISTRO* registro_criar(void){

  REGISTRO *r = malloc(sizeof(REGISTRO));
  if (r == NULL) {
    return NULL;
  }

  r->raiz = NULL; //Registro é criado sem raiz.
  return(r);
  
}

NO* registro_criar_no(PACIENTE* p){

  NO *node = malloc(sizeof(NO));
  if (node == NULL) {
    return NULL;
  }
  
  node->p = p;
  node->dir = NULL;
  node->esq = NULL;
  node->altura = 0;
  
  return node;
}

bool no_apagar(NO** node){

  if (node != NULL && *node != NULL) {
    paciente_apagar(&(*node)->p);
    free(*node);
    *node = NULL;
    return true;
  }

  return false;
}

/*===============================================================================*/
//Funções de cheio e vazio

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

/*===============================================================================*/
//Funções de apagar

NO* registro_apagar_no(NO* node){
  
  if(node != NULL){
    
    registro_apagar_no(node->esq);
    registro_apagar_no(node->dir);

    paciente_apagar(&(node->p));
    
    free(node);
    node = NULL; //Para retornar NULL e o pai não ter mais acesso
  }

  return node;
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


/*===============================================================================*/
//---- Altura 

int registro_altura_no(NO *A) {

  if (A == NULL) return -1;

  return A->altura;
}

/*===============================================================================*/
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

/*===============================================================================*/
/*Calcula o Fator de Balanceamento do nó A*/

int registro_calcular_fb(NO* A){
  return (registro_altura_no(A->esq) - registro_altura_no(A->dir));
}

/*===============================================================================*/
//Funções de recuperação de valor

NO* registro_recuperar_no(NO *raiz, int id) {

  if (!raiz) return NULL;

  int id_no = paciente_get_id(raiz->p);

  if (id < id_no) return registro_recuperar_no(raiz->esq, id);
  if (id > id_no) return registro_recuperar_no(raiz->dir, id);
  
  return raiz;
}

PACIENTE* registro_recuperar(REGISTRO* r, int id) {

  NO *paciente = registro_recuperar_no(r->raiz, id);

  if(paciente == NULL) return NULL;
  
  return paciente->p;
}

/*===============================================================================*/
//Funções de inserção de valor

NO* registro_inserir_no(NO* node, PACIENTE** p, char* verifica){
  
  if(node == NULL) { //Chegou no fim da árvore

    NO* novo = registro_criar_no(*p); //Já inicializa a altura como 0
    return novo;
  }
  
  //Organizamos os dados na árvore de acordo com o id dos pacientes
  if (paciente_get_id(node->p) < paciente_get_id(*p)) //Se id maior, insere-se na direita
    node->dir = registro_inserir_no(node->dir, p, verifica);

  else if (paciente_get_id(node->p) > paciente_get_id(*p)) //Se id menor, insere-se na esquerda
    node->esq = registro_inserir_no(node->esq, p, verifica);

  else { //Se tem o mesmo id, não deve ser inserido: ID É ÚNICO
    *p = node->p;
    if(paciente_get_esta_fila(node->p)) (*verifica) = ESTA_FILA; //O paciente também já está na fila
    else (*verifica) = ESTA_REGISTRO;
    return node; //Começa a voltar na recursão sem perder os ponteiros; se não houve inserção não é necessário fazer balanceamento
  }
  
  node->altura = max(registro_altura_no(node->dir),registro_altura_no(node->esq))+1; //Atualizando altura

  int fb = registro_calcular_fb(node); //Para verificação do balanceamento

  if(fb >= 2) { //Está pendendo para esquerda

    if(registro_calcular_fb(node->esq) < 0){ //E o filho esquerdo pendendo para a direita 
      //printf("Rotação esquerda-direita."); //Debug
      node = registro_rodar_esq_dir(node);
    }

    else{
      //printf("Rotação direita."); //Debug
      node = registro_rodar_direita(node);
    }
  }

  else if(fb <= -2){ //Está pendendo para direita

    if(registro_calcular_fb(node->dir) > 0){ //E o filho direito pendendo para a esquerda
      //printf("Rotação direita-esquerda."); //Debug
      node = registro_rodar_dir_esq(node);
    }

    else{
      //printf("Rotação esquerda."); //Debug
      node = registro_rodar_esquerda(node);
    }
  }
  printf("\n");
  
  return node;
}

int_8 registro_inserir(REGISTRO* r, PACIENTE** p){
  
  int_8 verifica = NAO_ESTA;

  if(r != NULL) r->raiz = registro_inserir_no(r->raiz, p, &verifica);
  
  return verifica;

}

/*===============================================================================*/
//Funções de remoção de valor

NO* troca_max_esq(NO *troca, NO *raiz, PACIENTE** p) {

  //printf("Entrando no paciente %d\n", paciente_get_id(troca->p));
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

  //printf("Atualmente no nó %d, voltando.\n", paciente_get_id(troca->p));
  //Atualização da altura
  troca->altura = max(registro_altura_no(troca->esq), registro_altura_no(troca->dir)) + 1;

  int fb = registro_calcular_fb(troca);

  //printf("Fator de balanceamento: %d\n", fb);

  //Rodar direita
  if (fb == 2) {

    //Rotação simples
    if (registro_calcular_fb(troca->esq) >= 0)
      troca = registro_rodar_direita(troca); //printf("Rotação direita.\n");

    //Rotação dupla
    else troca = registro_rodar_esq_dir(troca); //printf("Rotação esquerda-direita.\n");
  }

  //Rodar esquerda
  else if (fb == -2) {

    //Rotação simples
    if (registro_calcular_fb(troca->dir) <= 0)
      troca = registro_rodar_esquerda(troca); //printf("Rotação esquerda.\n");

    //Rotação dupla
    else troca = registro_rodar_dir_esq(troca); //printf("Rotação direita-esquerda.\n");
  }

  return troca;
}

NO* registro_remover_no(NO *node, int id, PACIENTE **p) {
  
  if (!node) return NULL; //Não encontrou o paciente

  int id_no = paciente_get_id(node->p);

  if (id < id_no) node->esq = registro_remover_no(node->esq, id, p);
  else if (id > id_no) node->dir = registro_remover_no(node->dir, id, p);
  else { //É o nó que deve ser removido

    if (paciente_get_esta_fila(node->p)) {

      //printf("O paciente não pode ser removido, pois ele está na fila.\n");
      return node;
    }

    *p = node->p;

    if (node->esq == NULL || node->dir == NULL) { //Tem 1 ou nenhum filho
      
      NO* aux;
      if (node->esq == NULL) { //Tem possivelmente só o filho direito
        aux = node->dir;

        node->dir = NULL;

        free(node);
        node = NULL;

        return aux;
      }

      else { //Tem o filho esquerdo
        aux = node->esq;

        node->esq = NULL;
        free(node);
        node = NULL;

        return aux;
      }
    }

    else {
      //printf("Fazendo a troca a partir do nó %d\n", paciente_get_id(node->p));
      node->esq = troca_max_esq(node->esq, node, p);
    }
  }

  if (node) { //Verificação para caso a árvore tivesse apenas um nó

    node->altura = max(registro_altura_no(node->esq), registro_altura_no(node->dir)) + 1;

    //Rebalanceamento, se necessário
    int fb = registro_calcular_fb(node);
    
    //Rodar direita
    if (fb == 2) {

      //Rotação simples
      if (registro_calcular_fb(node->esq) >= 0)
        node = registro_rodar_direita(node), printf("Rotação direita.\n");

      //Rotação dupla
      else node = registro_rodar_esq_dir(node), printf("Rotação esquerda-direita.\n");
    }

    //Rodar esquerda
    else if (fb == -2) {

      //Rotação simples
      if (registro_calcular_fb(node->dir) <= 0)
        node = registro_rodar_esquerda(node), printf("Rotação esquerda.\n");

      //Rotação dupla
      else node = registro_rodar_dir_esq(node), printf("Rotação direita-esquerda.\n");
    }

  }

  return node;
}


PACIENTE* registro_remover(REGISTRO* r, int id) {

  if (!r) return NULL;

  PACIENTE* p = NULL;
  r->raiz = registro_remover_no(r->raiz, id, &p);

  return p;
}

/*===============================================================================*/
//Funções de listagem de valor

void registro_listar_no(NO* node){ //Percorre em ordem

  if(node != NULL) {

    registro_listar_no(node->esq);
    char esta_fila = paciente_get_esta_fila(node->p) ? 'S' : 'N';
    printf("%06d|       %c      |%s\n", paciente_get_id(node->p), esta_fila, paciente_get_nome(node->p)); //Imprime os números de forma alinhada
    registro_listar_no(node->dir);
  }
}

void registro_listar(REGISTRO* r){

  if(r != NULL){

    printf("#     | ESTÁ NA FILA |NOME \n");
    registro_listar_no(r->raiz); 
    printf("\n");
  }
}

void registro_imprimir_no_visual(NO *raiz, int nivel) { //Imprime a árvore de forma identada

    if (raiz == NULL) return;

    registro_imprimir_no_visual(raiz->dir, nivel + 1);

    for (int i = 0; i < nivel; i++) printf("    ");
    printf("%d\n", paciente_get_id(raiz->p)); 

    registro_imprimir_no_visual(raiz->esq, nivel + 1);
}

void registro_imprimir_arvore_visual(REGISTRO* r) {

    registro_imprimir_no_visual(r->raiz, 0);
}


/*===============================================================================*/
//Funções de carregamento e salvamento

void registro_salvar_no(NO *raiz) {

  if (!raiz) return;
  
  //Pós-ordem, para não perder o acesso aos ponteiros
  registro_salvar_no(raiz->esq);
  registro_salvar_no(raiz->dir);
  raiz->esq = raiz->dir = NULL; //Os filhos já foram apagados

  //Usando a opção append para escrever no final do arquivo, sem apagar nada
  FILE *fp = fopen("../TAD_Registro/registro.txt", "a");

  //Escrevendo no arquivo: id, nome, esta_na_fila
  fprintf(fp, "%d\n", paciente_get_id(raiz->p));
  fprintf(fp, "%s\n", paciente_get_nome(raiz->p));
  fprintf(fp, "\n");

  //Fechando arquivo
  fclose(fp);

  //Desalocando tudo
  paciente_apagar(&(raiz->p));
  free(raiz);
  raiz = NULL;

}

bool registro_salvar(REGISTRO **r) {

  if (!r || !*r) return false;

  //Abrindo o arquivo em modo de escrita para apagar o conteúdo que tem nele
  FILE *fp = fopen("../TAD_Registro/registro.txt", "w");
  fclose(fp);

  /*A lógica de salvamento será:
  ID
  Nome
  
  ID
  Nome
  ...*/

  registro_salvar_no((*r)->raiz);

  free(*r);
  *r = NULL;

  return true;
}


REGISTRO* registro_carregar(void){
    
  FILE* fp = fopen("registro.txt", "r");
  REGISTRO* r = registro_criar();
  if (fp == NULL || r == NULL){
    fclose(fp);
    return NULL;
  }
  
  int id;
  char nome[101];
  PACIENTE* p;
  
  while(true){
    if (fscanf(fp, " %d", &id) == EOF){
      fclose(fp);
      return r;
    }
    fscanf(fp, " %100[^\n]", nome);
    fgetc(fp); //Tira o \n
    p = paciente_criar(nome, id);
    
    registro_inserir(r, &p);
    fgetc(fp); //Ignora o '\n' entre todos os pacientes.
  }

  return NULL;
}