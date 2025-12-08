#ifndef CLIENTE_H
    #define CLIENTE_H
    
    #include "../TAD_Paciente/paciente.h"
    #include "../TAD_Fila/fila.h"
    #include "../TAD_Registro/registro.h"

    //Carrega o registro, com pacientes e seus respectivos históricos, e a fila nos arquivos designados para tal.
    bool inicializar(REGISTRO**r, FILA** f);
    //Salva o registro, inclusive os históricos, e a fila nos arquivos designados para tal, liberando a memória ocupada por essas estrturas.
    void sair(REGISTRO** r, FILA** f);
    
    //Insere o paciente no registro e na fila
    int_8 registrar_paciente(REGISTRO *r, FILA *f, int id, char* nome, int_8 urgencia);
    //Se ocorrer erro na utilização de memória, será retornado -1.
    //Se o paciente não estiver no registro e nem na fila, será retornado 0. Nesse caso, o paciente é adicionado em ambas estruturas.
    //Se o paciente já estiver no registro e não estiver na fila, será retornado 1. Nesse caso, o paciente que está no registro é inserido na fila.
    //Se o paciente já estiver em ambas estruturas, será retornado 2.
    //Se houver outro paciente com mesmo id no registro, será retornado 3. Nesse caso, o novo paciente não é inserido em nenhuma estrutura.

    //Retira o paciente de maior prioridade da fila.
    PACIENTE* dar_alta_ao_paciente(FILA* f);
    //Apaga o cadastro de um paciente do registro. O paciente não deve estar na fila.
    PACIENTE* remover_paciente(REGISTRO* r, int id);
    //Recupera o cadastro de um paciente por meio de seu id.
    PACIENTE* buscar_paciente_por_ID(REGISTRO* r, int id);
    
    //Mostra a fila de espera em ordem do mais urgente para o menos urgente. Se não houver a memória necessário para essa operação, é impresso fora de ordem.
    void mostrar_fila_de_espera(FILA** f);
    //Lista todos os pacientes que possuem cadastro, junto dos procedimentos feitos por eles.
    void listar_pacientes(REGISTRO* r);
    //Mostra o histórico de procedimentos de um paciente em específico.
    bool mostrar_historico(REGISTRO *r, int id);
    //Retorna falso, se não encontrar o histórico.

    //Adiciona um novo procedimento ao histórico de um paciente
    bool adicionar_procedimento(REGISTRO *r, int id, char *proced);
    //Desfez um procedimento do histórico de um paciente
    bool desfazer_procedimento(REGISTRO *r, int id);

    //OBS: verifique o header dos TAD's para maiores informações
     
#endif
