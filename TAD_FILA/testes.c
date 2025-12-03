#include "fila.h"

int main(void){
  
    /*TESTE DA FUNÇÃO FILA_CARREGAR

    REGISTRO *r = registro_criar();

    PACIENTE *p1 = paciente_criar("Nádia", 5);
    PACIENTE *p2 = paciente_criar("Renan", 2);
    PACIENTE *p3 = paciente_criar("Maria", 4);
    PACIENTE *p4 = paciente_criar("Luiz", 9);

    registro_inserir(r, p1, true);
    registro_inserir(r, p2, true);
    registro_inserir(r, p3, true);
    registro_inserir(r, p4, true);

    FILA *f = fila_carregar(r);
    if(f != NULL) printf("ok!\n");

    while (!fila_vazia(f)) {

      PACIENTE *p = fila_remover(f);

      printf("ID: %d\n", paciente_get_id(p));
      printf("Nome: %s\n\n", paciente_get_nome(p));

    }

    free(f);

    registro_apagar(&r);
    if (registro_vazio(r)) printf("vazio, ok!\n");


    /* TESTES DAS FUNÇÕES DA FILA
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
   
    
    Mesmo chamando estas funções, memory leak ocorrerá por ainda não existir uma função que apague a fila.
    free(p1);
    free(p2);
    free(p3);
    free(p4);*/


    /*TESTE DAS FUNÇÕES FILA_SALVAR E FILA_LISTAR
    FILA* f = fila_criar();
    REGISTRO* r = registro_criar();
    PACIENTE* p;

    int id, m, n; scanf("%d", &n);
    char urg, nome[101];

    //Inserções
    for(int i = 0; i < n; i++){
        scanf("%d %c %100[^\n]", &id, &urg, nome);
        p = paciente_criar(nome, id);
        registro_inserir(r, p, true);
        fila_inserir(f, p, urg);
        fila_listar(&f);
    }

    //Remoções
    scanf("%d", &m);
    for(int i = 0; i < m; i++){
      fila_remover(f);
      fila_listar(&f);
    }

    fila_salvar(&f);
    registro_apagar(&r);
    return 0;*/
}
