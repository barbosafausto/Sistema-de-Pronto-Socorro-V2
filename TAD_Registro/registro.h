#ifndef REGISTRO_H
  #define REGISTRO_H
  
  #include "../TAD_Paciente/paciente.h"
  
  /**
  Funções com "//*" em seu final ainda não foram implementadas.
  Existem funções que serão necessárias mas que ainda não foram declaradas/o usuário não terá acesso, como as funções de rotação da AVL.
  **/
  
  typedef struct registro_ REGISTRO;
  typedef struct no_registro NO;
  
  REGISTRO* registro_criar(void);
  
  //Não é necessário "bool registro_cheio()" pois em teoria não existe limite para o número de pacientes que podem estar registrados no hospital.
  bool registro_vazio(REGISTRO* r);
  
  //"registro_buscar()" busca pelo paciente no registro. "registro_verificar()" e "registro_recuperar()" chamam "registro_buscar()", suas únicas diferenças sendo o retorno das funções.
  char registro_verificar(REGISTRO* r, int id); //*
  PACIENTE* registro_recuperar(REGISTRO* r, int id); //*
  
  bool registro_inserir(REGISTRO* r, PACIENTE* p); //*
  PACIENTE* registro_remover(REGISTRO* r, int id); //*
  
  void registro_listar(REGISTRO* r); //*
  bool registro_salvar(REGISTRO** r); //*
  REGISTRO* registro_carregar(void); //*
  
  //FUNÇÃO TEMPORÁRIA PARA EVITAR VAZAMENTO DE MEMÓRIA DURANTE OS TESTES. Esta função NÃO libera os nós dentro do registro e será substituída por "registro_salvar()" futuramente.
  bool registro_apagar(REGISTRO** r);
  
#endif
