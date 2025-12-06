#include "cliente.h"

int main(void) {


  printf("Oi\n");
  REGISTRO *r;
  FILA *f;

  if (!inicializar(&r, &f)){
    printf("Erro ao inicializar os dados!\n");
  }
  
  listar_pacientes(r);
  
  registrar_paciente(r, f, 1001, "Fausto", '2');
  registrar_paciente(r, f, 1002, "Joao", '1');
  registrar_paciente(r, f, 1003, "Edu", '2');
  registrar_paciente(r, f, 1004, "Rudinei", '4');
  
  buscar_paciente_por_ID(r, 1001);
  buscar_paciente_por_ID(r, 1004);
  buscar_paciente_por_ID(r, 101);

  listar_pacientes(r);

  return 0;
}
