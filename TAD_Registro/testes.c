#include <stdio.h>
#include "registro.h"

int main(void){

  PACIENTE* p = paciente_criar("Marcelo Almeida", 2);

  //Output precisa ser "Marcelo Almeida" e "2"
  printf("%s\n", paciente_get_nome(p));
  printf("%d\n", paciente_get_id(p));
    
  NOr* n = no_criar(p);
  printf("%s\n", paciente_get_nome(no_get_paciente(n)));
  printf("%d\n", paciente_get_id(no_get_paciente(n)));
    
  no_apagar(&n);
  if (n == NULL) printf("Nó apagado.\n");
  p = NULL; //O ponteiro para paciente dentro do nó não é o mesmo que esta variável "p".
  
  REGISTRO* r = registro_criar();
  if (r != NULL) printf("Registro criado.\n");
  registro_apagar(&r);
  if (r == NULL) printf("Registro apagado.\n");
  
  return 0;
}
