#include "cliente.h"
#include <stdbool.h>

#define NAO_ESTA 0
#define ESTA_REGISTRO 1
#define ESTA_FILA 2

bool inicializar(REGISTRO** r, FILA** f){
  
  *r = registro_carregar();
  if (*r == NULL){
    return false;
  }
  
  *f = fila_carregar(*r);
  if (*f == NULL){
    return false;
  }
  
  return true;
}

void sair(REGISTRO** r, FILA** f){ //Deve ser nessa ordem, já que registro_salvar desaloca os pacientes
  fila_salvar(f); 
  registro_salvar(r); 
}
    
bool registrar_paciente(REGISTRO *r, FILA *f, int id, char* nome, int_8 urgencia) {

  //Criação do paciente
  PACIENTE *p = paciente_criar(nome, id);
  PACIENTE *aux = p;
  
  //Se ele estiver na fila, então não haverá inserção
  int feedback = registro_inserir(r, &p);
  if (feedback == ESTA_REGISTRO){ //Então ele não está na fila, precisa ser adicionado
    fila_inserir(f, p, urgencia); //Nesse caso, p guarda o paciente 
    paciente_apagar(&aux); //Apagando o paciente criado na linha 19
    return false;
  }

  if(feedback == ESTA_FILA){
    paciente_apagar(&aux); //Apagando o paciente criado na linha 19
    return false;
  }
    
  //Caso ele não esteja na fila, inserimos
  feedback = fila_inserir(f, p, urgencia);

  if (!feedback) return false; //Se houver erros
  
  //Se chegou aqui, deu tudo certo.
  return true;
}

PACIENTE* dar_alta_ao_paciente(FILA* f){
  PACIENTE *p = fila_remover(f);
  return p;
}
  
PACIENTE* remover_paciente(REGISTRO* r, int id){

  return(registro_remover(r, id));
}
    
PACIENTE* buscar_paciente_por_ID(REGISTRO* r, int id){
  
  PACIENTE* p = registro_recuperar(r, id); //Esta função realiza uma busca no registro e retorna ponteiro para paciente.
  return p;
}
    
void mostrar_fila_de_espera(FILA** f){

  fila_listar(f); //As conferência estão dentro da função
}

void listar_pacientes(REGISTRO* r) {

  registro_listar(r);
}

    
