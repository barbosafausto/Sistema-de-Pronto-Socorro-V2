#ifndef REGISTRO_H
  #define REGISTRO_H
  
  #include <stdlib.h>
  #include <stdio.h>
  #include "../TAD_Paciente/paciente.h"

  /**
  Funções com "//" em seu final ainda não foram implementadas.
  Existem funções que serão necessárias mas que ainda não foram declaradas/o usuário não terá acesso, como as funções de rotação da AVL.
  **/
  
  typedef struct registro_ REGISTRO;
  typedef char int_8;
  
  REGISTRO* registro_criar(void);

  //As funções abaixo talvez sejam removidas do projeto posteriormente.
  //registro_criar_no(): cria um nó e inicializa os dados
  //no_get_paciente(): pega o paciente de um nó
  //no_apagar(): apagar um nó e seu paciente 
  
  bool registro_vazio(REGISTRO* r);
  bool registro_cheio(REGISTRO* r);

  //registro_apagar_no() é chamada como auxiliar
  bool registro_apagar(REGISTRO** r);

  //registro_altura_no() será muito útil em inserções/remoções

  //registro_rodar_esquerda()
  //registro_rodar_direita()
  //registro_rodar_esq_dir()
  //registro_rodar_dir_esq()

  //registro_calcular_fb() para o fator de balanceamento

  //"registro_recuperar_no()" (auxiliar) busca pelo paciente no registro e retorna um nó.
  PACIENTE* registro_recuperar(REGISTRO *r, int id); //*
  
  //Retorna 0, se teve sucesso na inserção; 1, se o valor já está no registro; 2, se, além do registro, também já estiver na fila
  //Usa registro_inserir_no() como função auxiliar para inserir no local certo.
  int_8 registro_inserir(REGISTRO* r, PACIENTE** p); //Se o paciente com aquele id já estiver no registro o ponteiro p apaontará para ele.


  //Usa a função registro_remover_no() para buscar o nó e removê-lo
  //Usa a função troca_max_esq() para substituir o nó quando necessário
  PACIENTE* registro_remover(REGISTRO* r, int id); //*
 
  
  //Percorre o registro em-ordem mostrando seus elementos
  //Usa a função auxiliar registro_listar_no
  void registro_listar(REGISTRO*r); 


  //As funções abaixo ainda serão implementadas
  bool registro_salvar(REGISTRO** r); //*
  REGISTRO* registro_carregar(void); //*
  

  //Funções úteis para testes
  //Usa a função imprimir_no_visual (auxiliar)
  void registro_imprimir_arvore_visual(REGISTRO* r);
    
#endif
