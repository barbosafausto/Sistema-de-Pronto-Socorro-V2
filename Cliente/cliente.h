#ifndef CLIENTE_H
    #define CLIENTE_H
    
    #include "../TAD_Paciente/paciente.h"
    #include "../TAD_Fila/fila.h"
    #include "../TAD_Registro/registro.h"
    
    bool inicializar(REGISTRO**r, FILA** f);
    void sair(REGISTRO** r, FILA** f);
    
    bool registrar_paciente(REGISTRO *r, FILA *f, int id, char* nome, int_8 urgencia);
    
    PACIENTE* dar_alta_ao_paciente(FILA* f);
    PACIENTE* remover_paciente(REGISTRO* r, int id);
    
    PACIENTE* buscar_paciente_por_ID(REGISTRO* r, int id);
    
    void mostrar_fila_de_espera(FILA** f);
    void listar_pacientes(REGISTRO* r);
     
#endif
