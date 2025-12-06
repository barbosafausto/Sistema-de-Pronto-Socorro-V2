#ifndef PACIENTE_H 
    #define PACIENTE_H

    #include <stdbool.h>
    
    typedef struct paciente PACIENTE;

    /*
    As funções que retornam ponteiros retornarão NULL se mal-sucedidas,
    as que retornam booleano irão retornar false se mal-sucedidas.
    */

    PACIENTE* paciente_criar(char* nome, int id);
    bool paciente_apagar(PACIENTE** p);

    char* paciente_get_nome(PACIENTE* p);
    int paciente_get_id(PACIENTE* p); //Essa função retornará -1 se o ponteiro for inválido
    bool paciente_get_esta_fila(PACIENTE *p); //Essa função retornará false se o ponteiro for inválido

    void paciente_set_esta_fila(PACIENTE *p, bool esta_fila);
#endif
