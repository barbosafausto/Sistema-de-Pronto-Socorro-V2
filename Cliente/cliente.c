#include "cliente.h"
#include <stdbool.h>

//#define NAO_ESTA 0
//#define ESTA_REGISTRO 1
#define ESTA_FILA 2

bool inicializar(REGISTRO**r, FILA** f);
void sair(REGISTRO** r, FILA** f);
    
bool registrar_paciente(REGISTRO *r, FILA *f, int id, char* nome, int_8 urgencia) {

  //Criação do paciente
  PACIENTE *p = paciente_criar(nome, id);
  
  //Se ele estiver na fila, então não haverá inserção
  int feedback = registro_inserir(r, p);
  if (feedback == ESTA_FILA) return false;
    
  //Caso ele não esteja na fila, inserimos
  feedback = fila_inserir(f, p, urgencia);

  if (!feedback) return false; //Se houver erros
  
  //Se chegou aqui, deu tudo certo.
  return true;
}


    
bool dar_alta_ao_paciente(FILA* f);



  
PACIENTE* remover_paciente(REGISTRO* r, int id){

  return(registro_remover(r, id));
}
    
PACIENTE* buscar_paciente_por_ID(int id);
    
void mostrar_fila_de_espera(FILA* f);

void listar_pacientes(REGISTRO* r) {

  registro_listar(r);
}

    
