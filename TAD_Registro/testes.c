#include <stdio.h>
#include "registro.h"

int main(void){

  PACIENTE* p = paciente_criar("Marcelo Almeida", 2);

  //Output precisa ser "Marcelo Almeida" e "2"
  printf("%s\n", paciente_get_nome(p));
  printf("%d\n", paciente_get_id(p));
    
  REGISTRO* r = registro_criar();
  if (r != NULL) printf("Registro criado.\n");
  registro_apagar(&r);
  if (r == NULL) printf("Registro apagado.\n");

  paciente_apagar(&p);
   
  return 0;
}
