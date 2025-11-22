#ifndef REGISTRO_H
  #define REGISTRO_H
  
  #include "../TAD_Paciente/paciente.h"

  /**
  Funções com "//*" em seu final ainda não foram implementadas.
  Existem funções que serão necessárias mas que ainda não foram declaradas/o usuário não terá acesso, como as funções de rotação da AVL.
  **/
  
  typedef struct registro_ REGISTRO;
  typedef char int_8;
  
  REGISTRO* registro_criar(void);
  
  //Não é necessário "bool registro_cheio()" pois em teoria não existe limite para o número de pacientes que podem estar registrados no hospital.
  bool registro_vazio(REGISTRO* r);
  
  //"registro_buscar()" busca pelo paciente no registro. "registro_verificar()" e "registro_recuperar()" chamam "registro_buscar()", suas únicas diferenças sendo o retorno das funções.
  //char registro_verificar(REGISTRO* r, int id); //*
  PACIENTE* registro_recuperar(REGISTRO* r, int id); //*
  
  //Retonra 0, se teve sucesso na inserção; 1, se o valor já está no registro; 2, se, além do registro, também já estiver na fila
  int_8 registro_inserir(REGISTRO* r, PACIENTE* p, bool esta_na_fila);  
  PACIENTE* registro_remover(REGISTRO* r, int id); //*
  
  //Percorre o registro em-ordem mostrando seus elementos
  void registro_listar(REGISTRO* r); 
  bool registro_salvar(REGISTRO** r); //*
  REGISTRO* registro_carregar(void); //*
  
  //FUNÇÃO TEMPORÁRIA PARA EVITAR VAZAMENTO DE MEMÓRIA DURANTE OS TESTES. Esta função NÃO libera os nós dentro do registro e será substituída por "registro_salvar()" futuramente.
  bool registro_apagar(REGISTRO** r);
    
#endif
