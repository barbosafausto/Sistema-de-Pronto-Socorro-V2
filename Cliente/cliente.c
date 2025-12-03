#include "cliente.h"

  bool inicializar(REGISTRO**r, FILA** f);
  void sair(REGISTRO** r, FILA** f);
    
  PACIENTE* registrar_paciente(int id, char* nome);
    
  bool dar_alta_ao_paciente(FILA* f);
  
  PACIENTE* remover_paciente(REGISTRO* r, int id){
    return(registro_remover(r, id));
  }
    
  PACIENTE* buscar_paciente_por_ID(int id);
    
  void mostrar_fila_de_espera(FILA* f);
  void listar_pacientes(REGISTRO* r);
    
