#include "cliente.h"
#include <stdbool.h>


#define char int_8

bool inicializar(REGISTRO** r, FILA** f){
  
  *r = registro_carregar();
  if (*r == NULL){
    return false;
  }
  
  *f = fila_carregar(*r);
  if (*f == NULL){
    registro_apagar(r);
    return false;
  }
  
  return true;
}

void sair(REGISTRO** r, FILA** f){ //Deve ser nessa ordem, já que registro_salvar desaloca os pacientes
  fila_salvar(f); 
  registro_salvar(r); 
}
    
int_8 registrar_paciente(REGISTRO *r, FILA *f, int id, char* nome, int_8 urgencia) {

  //Criação do paciente
  PACIENTE *p = paciente_criar(nome, id);
  HISTOR *h = histor_criar();
  PACIENTE *aux = p;
  
  //Se ele estiver na fila, então não haverá inserção
  int feedback = registro_inserir(r, &p, &h);

  //Se os pacientes têm nomes distintos, porém com ID repetido, abortamos a operaçõa.
  if (feedback == REPETIDO) {
    
    paciente_apagar(&p);
    histor_apagar(&h);

    aux = NULL;
    return feedback;
  }

  //Se ele está na fila e no registro, não precisamos continuar
  if(feedback == ESTA_FILA){
    paciente_apagar(&aux); //Apagando o paciente criado na linha 19
    histor_apagar(&h);
    return feedback;
  }

  //Se chegou aqui, o paciente está no registro ou não.
  //De todo modo, ele será colocado na fila.
  fila_inserir(f, p, urgencia); 
  
  //Se o paciente já está no registro, não precisamos alocar espaço adicional.
  if (feedback == ESTA_REGISTRO){ 
    paciente_apagar(&aux); 
    histor_apagar(&h);
  }

  return feedback;
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

bool mostrar_historico(REGISTRO *r, int id){
  HISTOR *h = registro_recuperar_histor(r, id);
  if(h == NULL) return false;
  
  histor_consultar(h);
  return true;
}

bool adicionar_procedimento(REGISTRO *r, int id, char *proced) {

  HISTOR *h = registro_recuperar_histor(r, id);

  if(!h) return false;

  PROCED *p = proced_criar(proced);
  return histor_inserir(h, p);
}

bool desfazer_procedimento(REGISTRO *r, int id) {

  HISTOR *h = registro_recuperar_histor(r, id);

  PROCED *p = histor_remover(h);
  if(!p) return false;
  
  proced_apagar(&p);
  return true;
}

    
