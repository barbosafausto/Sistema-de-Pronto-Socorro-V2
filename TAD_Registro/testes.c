#include "registro.h"

int main(void) {

  
  /*TESTE DE INSERÇÃO e REMOÇÃO

  int n, id;
  PACIENTE *p, *aux;
  char nome[101], esta_na_fila;
  int_8 verifica;

  REGISTRO* r = registro_criar();
  if (r != NULL) printf("Registro criado.\n");

  printf("Quantos: ");
  scanf("%d", &n); //Quantidade de pacientes a serem adicionados

  //Inserindo pacientes
  for(int i = 0; i < n; i++) {

    printf("NOME: ");
    scanf(" %[^\n]", nome);

    printf("ID: ");
    scanf(" %d", &id);

    aux = p = paciente_criar(nome, id);

    if(!(verifica = registro_inserir(r, &p)))
      printf("Paciente adicionado.\n\n");

    else if (verifica == 1) printf("Falha, está no registro.\n\n"), paciente_apagar(&aux);

    else printf("Falha, está no registro e na fila.\n\n"), paciente_apagar(&aux);

    registro_listar(r); //Listando pacientes
    printf("\n\n");
  }
  
  registro_imprimir_arvore_visual(r);

  //Testes de remoção
  p = registro_remover(r, 3);
  paciente_apagar(&p);
  
  printf("Lista de pacientes após remoção:\n");
  registro_listar(r); //Listando pacientes


  registro_salvar(&r);
  if (r == NULL) printf("Registro salvo e apagado.\n");//*/

  /*TESTE DE REGISTRO SALVAR E REGISTRO LISTAR
  REGISTRO *r = registro_carregar();
  registro_listar(r);
  registro_salvar(&r);//*/

  return 0;
}
