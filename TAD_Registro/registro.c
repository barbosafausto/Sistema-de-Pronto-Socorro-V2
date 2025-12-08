#include "registro.h"
#include "string.h"

#define max(a, b) ((a > b) ? a : b) //Parenteses para não atrapalhar a precedência

typedef struct no_registro NO;

struct registro_ {
  NO* raiz;
};

struct no_registro {
  
  PACIENTE *p;
  HISTOR *h;
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

NO* registro_criar_no(PACIENTE* p, HISTOR* h){

  NO *node = malloc(sizeof(NO));
  if (node == NULL) {
    return NULL;
  }
  
  node->p = p;
  node->dir = NULL;
  node->esq = NULL;
  node->altura = 0;

  node->h = h;

  return node;
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
    node = NULL; //Para retornar NULL e atualizar o ponteiro do pai.
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
/*Calcula o Fator de Balanceamento do nó A*/

int registro_calcular_fb(NO* A){
  return (registro_altura_no(A->esq) - registro_altura_no(A->dir));
}

/*===============================================================================*/
//Funções de rotação e balanceamento

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

NO *registro_balanceia(NO *node) {

  if (!node) return NULL;

  node->altura = max(registro_altura_no(node->esq), registro_altura_no(node->dir)) + 1;

  //Rebalanceamento, se necessário
  int fb = registro_calcular_fb(node);
  
  //Rodar direita
  if (fb == 2) {

    //Rotação simples
    if (registro_calcular_fb(node->esq) >= 0)
      node = registro_rodar_direita(node);

    //Rotação dupla
    else node = registro_rodar_esq_dir(node);
  }

  //Rodar esquerda
  else if (fb == -2) {

    //Rotação simples
    if (registro_calcular_fb(node->dir) <= 0)
      node = registro_rodar_esquerda(node);

    //Rotação dupla
    else node = registro_rodar_dir_esq(node);
  }

  return node;
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

  NO *paciente = registro_recuperar_no(r->raiz, id); //Recupera o nó deste paciente

  if(paciente == NULL) return NULL; //Se não existir, retorna NULL
  
  return paciente->p; //Se existir, retorna o paciente
}

HISTOR* registro_recuperar_histor(REGISTRO *r, int id) {

  NO* paciente = registro_recuperar_no(r->raiz, id);

  if (paciente == NULL) return NULL;

  return paciente->h; //Se existir, retorna o histórico do paciente
}

/*===============================================================================*/
//Funções de inserção de valor

NO* registro_inserir_no(NO* node, PACIENTE** p, HISTOR *h, char* verifica){ //Aqui sabemos que p aponta para um endereço válido, derreferências não causam erro
  
  if(node == NULL) { //Chegou no local de inserção

    NO* novo = registro_criar_no(*p, h); 
    if(novo == NULL) (*verifica) = ERRO;

    return novo;
  }
  
  //Organizamos os dados na árvore de acordo com o id dos pacientes
  if (paciente_get_id(node->p) < paciente_get_id(*p)) //Se id maior, insere-se na direita
    node->dir = registro_inserir_no(node->dir, p, h, verifica);

  else if (paciente_get_id(node->p) > paciente_get_id(*p)) //Se id menor, insere-se na esquerda
    node->esq = registro_inserir_no(node->esq, p, h, verifica);

  else { //Se tem o mesmo id, não deve ser inserido: ID É ÚNICO

    //Se existe, verificamos se é, de fato, o mesmo paciente (através do nome).
    if (strcmp(paciente_get_nome(*p), paciente_get_nome(node->p)) != 0) 
      *verifica = REPETIDO; //Se for diferente, erro: pacientes distintos com mesmo ID.

    //Se for o mesmo, usamos o ponteiro original do paciente.
    else {
      *p = node->p;
      if(paciente_get_esta_fila(node->p)) (*verifica) = ESTA_FILA; //O paciente também já está na fila
      else (*verifica) = ESTA_REGISTRO;
    }
    return node; //Começa a voltar na recursão sem perder os ponteiros; se não houve inserção não é necessário fazer balanceamento
  }
  
  return registro_balanceia(node);
}

int_8 registro_inserir(REGISTRO* r, PACIENTE** p, HISTOR *h){
  
  int_8 verifica = NAO_ESTA;

  if(r != NULL){
    if(p == NULL || *p == NULL || h == NULL) return ERRO;
    r->raiz = registro_inserir_no(r->raiz, p, h, &verifica);
  }
  
  return verifica;

}

/*===============================================================================*/
//Funções de remoção de valor

NO* troca_max_esq(NO *troca, NO *raiz, PACIENTE** p) {

  //printf("Entrando no paciente %d\n", paciente_get_id(troca->p));
  if (troca->dir) { //Vai até o fim na direita
    troca->dir = troca_max_esq(troca->dir, raiz, p);
  }

  else { //Chegou no último
    
    NO* temp = troca->esq;

    *p = raiz->p;
    raiz->p = troca->p;  //Copia paciente e histórico
    raiz->h = troca->h;

    troca->esq = NULL;
    free(troca);
    troca = NULL;

    return temp;
  }

  return registro_balanceia(troca);
}

NO* registro_remover_no(NO *node, int id, PACIENTE **p) {
  
  if (!node) return NULL; //Não encontrou o paciente

  int id_no = paciente_get_id(node->p);

  //Recursão para o lado necessário
  if (id < id_no) node->esq = registro_remover_no(node->esq, id, p);
  else if (id > id_no) node->dir = registro_remover_no(node->dir, id, p);

  else { //É o nó que deve ser removido

    if (paciente_get_esta_fila(node->p)) {

      //printf("O paciente não pode ser removido, pois ele está na fila.\n");
      return node;
    }

    *p = node->p; //Guarda o paciente numa variável para retorná-lo depois.
    histor_apagar(&(node->h)); //Apago o histórico do paciente que será removido.

    if (node->esq == NULL || node->dir == NULL) { //Tem 1 ou nenhum filho
      
      NO* aux;
      if (node->esq == NULL) { //Tem possivelmente só o filho direito
        aux = node->dir;

        node->dir = NULL;
        free(node);
        node = NULL;

        return aux;
      }

      else { //Tem possivelmente só o filho esquerdo
        aux = node->esq;

        node->esq = NULL;
        free(node);
        node = NULL;

        return aux;
      }
    }

    else { //Tem dois filhos: trocar com o máximo da esquerda.
      node->esq = troca_max_esq(node->esq, node, p); 
    }
  }

  return registro_balanceia(node); //Retorna balanceado
}


PACIENTE* registro_remover(REGISTRO* r, int id) {

  if (!r) return NULL;

  PACIENTE* p = NULL;
  r->raiz = registro_remover_no(r->raiz, id, &p);

  return p;
}

/*===============================================================================*/
//Funções de listagem de valor

void registro_listar_no(NO* node){ //Percorre em ordem de ID

  if(node != NULL) {

    registro_listar_no(node->esq);
    char esta_fila = paciente_get_esta_fila(node->p) ? 'S' : 'N'; //S para caso está na fila; N para caso não
    printf("%06d|       %c      | %s\n", paciente_get_id(node->p), esta_fila, paciente_get_nome(node->p)); //Imprime os valores de forma alinhada
    histor_consultar(node->h); //Procedimentos:\n proced 1 \n proced 2...
    printf("\n");
    registro_listar_no(node->dir);
  }
}

void registro_listar(REGISTRO* r){

  if(r == NULL){
    puts("Erro ao tentar acessar o registro na memória.");
    return;
  }
  
  if (registro_vazio(r)) { //Mensagem específica para caso o registro estiver vázio
    
    puts("Não há pacientes registrados.");
    return;
  }

  puts("#     | ESTÁ NA FILA | NOME\n");
  registro_listar_no(r->raiz); 
  putc('\n', stdin); 
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

  //Aqui vamos salvar o histórico.
  histor_salvar(&(raiz->h), raiz->p);

  //Desalocando paciente
  paciente_apagar(&(raiz->p));


  free(raiz);
  raiz = NULL;

}

bool registro_salvar(REGISTRO **r) {

  if (!r || !*r) return false;

  //Abrindo o arquivo em modo de escrita para apagar o conteúdo que tem nele
  FILE *fp = fopen("../TAD_Registro/registro.txt", "w");
  fclose(fp);

  registro_salvar_no((*r)->raiz);

  free(*r);
  *r = NULL;

  return true;
}


REGISTRO* registro_carregar(void){
    
  FILE* fp = fopen("../TAD_Registro/registro.txt", "r");
  REGISTRO* r = registro_criar();
  if (fp == NULL || r == NULL){
    fclose(fp);
    return NULL;
  }
  
  int id;
  char nome[101];
  PACIENTE* p;
  HISTOR* h;
  
  while(true){

    if (fscanf(fp, " %d", &id) == EOF) {
      fclose(fp);
      return r;

    }

    fscanf(fp, " %100[^\n]", nome);
    fgetc(fp); //Tira o \n
    p = paciente_criar(nome, id);

    h = histor_criar();
    histor_carregar(h, p); //Carregando o histórico do paciente

    
    registro_inserir(r, &p, h);
    fgetc(fp); //Ignora o '\n' entre todos os pacientes.
  }

  return r;
}
