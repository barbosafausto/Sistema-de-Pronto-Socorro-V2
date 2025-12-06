#include "cliente.h"

int main(void) {

  REGISTRO *r = registro_criar();
  FILA *f = fila_criar();

  registrar_paciente(r, f, 1, "Fausto", '1');

  registrar_paciente(r, f, 1, "Joao", '1');
  registrar_paciente(r, f, 2, "Joao", '2');
  
  registrar_paciente(r, f, 2, "Edu", '2');
  registrar_paciente(r, f, 3, "Edu", '1');
  
  PACIENTE *p = fila_remover(f);
  registro_atualiza(r, paciente_get_id(p));
  p = fila_remover(f);
  registro_atualiza(r, paciente_get_id(p));
  p = fila_remover(f);
  registro_atualiza(r, paciente_get_id(p));

  remover_paciente(r, 2);

  listar_pacientes(r);


  return 0;
}
