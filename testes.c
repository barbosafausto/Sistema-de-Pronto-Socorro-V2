#include "paciente.h"
#include <stdio.h>

//Arquivo para testes

int main() {

    PACIENTE* p = paciente_criar("Carlos", 1);
    
    //Output precisa ser "Carlos" e "1"
    printf("%s\n", paciente_get_nome(p));
    printf("%d\n", paciente_get_id(p));

    paciente_apagar(&p);


    printf("-------\n");


    p = paciente_criar("Marcelo", 2);

    //Output precisa ser "Marcelo Almeida" e "2"
    printf("%s\n", paciente_get_nome(p));
    printf("%d\n", paciente_get_id(p));

    paciente_apagar(&p);

    
    printf("-------\n");


    if (p == NULL) printf("Missão cumprida!\n");
    
    return 0;
}

