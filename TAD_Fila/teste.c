#include "fila.h"

int main(void){
    FILA *f = fila_criar();
    if(f != NULL) printf("ok!\n");
    
    PACIENTE *p1 = paciente_criar("Nádia", 1);
    PACIENTE *p2 = paciente_criar("Renan", 2);
    PACIENTE *p3 = paciente_criar("Maria", 3);
    PACIENTE *p4 = paciente_criar("Luiz", 4);
    
    if(fila_vazia(f)){
      printf("Fila está vazia.\n");
    }
    
    if (fila_inserir(f, p1, '2')){
      printf("Paciente inserido corretamente: 1\n");
    }
    
    if (fila_inserir(f, p2, '4')){
      printf("Paciente inserido corretamente: 2\n");
    }
    
    if (fila_inserir(f, p3, '4')){
      printf("Paciente inserido corretamente: 3\n");
    }
    
    if (fila_inserir(f, p4, '1')){
      printf("Paciente inserido corretamente: 4\n");
    }
    
    if(!fila_cheia(f)){
      printf("Fila não está cheia.\n");
    }
    
    
    PACIENTE* aux;
    //Espera-se que a ordem de saída da fila seja Luiz, Nádia, Renan e Maria.
    for (int i = 0; i<4; i++){
    aux = fila_remover(f);
    printf("Paciente foi chamado para atendimento: %s\n", paciente_get_nome(aux));
    }
   
    //Mesmo chamando estas funções, memory leak ocorrerá por ainda não existir uma função que apague a fila.
    free(p1);
    free(p2);
    free(p3);
    free(p4);
    
    return 0;
}
