#ifndef REGISTRO_H
  #define REGISTRO_H
  
  #include <stdlib.h>
  #include <stdio.h>
  #include "../TAD_Paciente/paciente.h"
  #include "../TAD_Historico/historico.h"
  
  typedef struct registro_ REGISTRO;
  typedef char int_8;
  
  REGISTRO* registro_criar(void);
  
  bool registro_vazio(REGISTRO* r);
  bool registro_cheio(REGISTRO* r);

  //Apaga o registro inteiro.
  bool registro_apagar(REGISTRO** r);

  //Funções de busca.
  PACIENTE* registro_recuperar(REGISTRO *r, int id);
  HISTOR* registro_recuperar_histor(REGISTRO *r, int id);
  
  //Retorna 0, se teve sucesso na inserção; 1, se o valor já está no registro; 2, se, além do registro, também já estiver na fila
  int_8 registro_inserir(REGISTRO* r, PACIENTE** p, HISTOR **h); //Se o paciente com aquele id já estiver no registro o ponteiro p apaontará para ele.

  //Remove um cadastro do registro e retorna o paciente removido.
  PACIENTE* registro_remover(REGISTRO* r, int id);
 
  
  //Percorre o registro em-ordem mostrando seus elementos
  void registro_listar(REGISTRO*r); 

  bool registro_salvar(REGISTRO** r);
  REGISTRO* registro_carregar(void);

#endif
