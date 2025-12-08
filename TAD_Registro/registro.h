#ifndef REGISTRO_H
  #define REGISTRO_H
  
  #include <stdlib.h>
  #include <stdio.h>
  #include "../TAD_Paciente/paciente.h"
  #include "../TAD_Historico/historico.h"

  #define ERRO -1
  #define NAO_ESTA 0
  #define ESTA_REGISTRO 1
  #define ESTA_FILA 2
  #define REPETIDO 3
  
  typedef struct registro_ REGISTRO;
  typedef char int_8; //inteiro de 8 bits (economia de memória)

  //Aloca memória para o registro  
  REGISTRO* registro_criar(void);
  
  //Funções de verificação
  bool registro_vazio(REGISTRO* r);
  bool registro_cheio(REGISTRO* r);

  //Apaga o registro inteiro.
  bool registro_apagar(REGISTRO** r);

  //Funções de busca.
  PACIENTE* registro_recuperar(REGISTRO *r, int id);
  HISTOR* registro_recuperar_histor(REGISTRO *r, int id);
  
  //Insere um cadastro no registro
  int_8 registro_inserir(REGISTRO* r, PACIENTE** p, HISTOR *h); 
  //Retorna 0, se teve sucesso total na inserção; 1, se o paciente já está no registro (mesmo nome e mesmo ID); 2, se, além do registro, também já estiver na fila; 3, se existir um paciente com esse ID já registrado (nome diferente e mesmo ID); -1, se houve erro de alocação de memória para o novo cadastro. 
  //Se o retorno for 1 ou 2, p apontará para o paciente de mesmo ID.

  //Remove um cadastro do registro e retorna o paciente removido.
  PACIENTE* registro_remover(REGISTRO* r, int id);
 
  
  //Percorre o registro em-ordem mostrando seus elementos.
  void registro_listar(REGISTRO*r); 

  //Salva os pacientes do registro no arquivo "TAD_Registro/registro.txt" e seus respectivos históricos no arquivo "TAD_Historico/proceds/ID.txt". Nesse processo, é liberado a memória ocupada por essas estruturas.
  bool registro_salvar(REGISTRO** r);
  //Carrega o registro salvo no arquivo "TAD_Registro/registro.txt" e seus respectivos históricos no arquivo "TAD_Historico/proceds/id.txt". Nesse processo, são alocados memória para tais estruturas.
  REGISTRO* registro_carregar(void);

  /*Formato do arquivo "TAD_Registro/registro.txt":
  ID
  Nome
  
  ID
  Nome
  ...*/

#endif
