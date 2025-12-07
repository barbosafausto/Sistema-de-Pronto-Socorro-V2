#include "fila.h"

int main(void){
  
    /*TESTE DA FUNÇÃO FILA_CARREGAR

    REGISTRO *r = registro_criar();

    PACIENTE *p1 = paciente_criar("Nádia", 5);
    PACIENTE *p2 = paciente_criar("Renan", 2);
    PACIENTE *p3 = paciente_criar("Maria", 4);
    PACIENTE *p4 = paciente_criar("Luiz", 9);

    //Como o registro inicia vazia não precisa fazer a conferência de ID repetido
    registro_inserir(r, &p1);
    registro_inserir(r, &p2);
    registro_inserir(r, &p3);
    registro_inserir(r, &p4);

    registro_listar(r);
    
    //É bom o arquivo fila.txt ter alguns dos ID's dos pacientes p1, p2, p3, p4 para o teste rodar corretamente
    //Lembrnado que não possível 
    FILA *f = fila_carregar(r);
    if(f != NULL) printf("ok!\n");

    fila_listar(&f);
    registro_listar(r);


    while (!fila_vazia(f)) {

      PACIENTE *p = fila_remover(f);

      printf("ID: %d\n", paciente_get_id(p));
      printf("Nome: %s\n\n", paciente_get_nome(p));

    }

    fila_listar(&f);
    registro_listar(r);

    fila_salvar(&f);
    registro_apagar(&r);
    if (registro_vazio(r)) printf("vazio, ok!\n");//*/


    /* TESTES DAS FUNÇÕES DA FILA
    FILA *f = fila_criar();

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
    
    if(!fila_cheia_aumentar(f)){
      printf("Fila não está cheia.\n");
    }

    fila_listar(&f); //Testando fila listar
    
    PACIENTE* aux;
    //Espera-se que a ordem de saída da fila seja Luiz, Nádia, Renan e Maria.
    for (int i = 0; i<4; i++){
      aux = fila_remover(f);
      printf("Paciente foi chamado para atendimento: %s\n", paciente_get_nome(aux));
      paciente_apagar(&aux);
    }
   
    fila_listar(&f); //Deve escrever: A fila está vazia
    
    fila_salvar(&f);//*/

    /*TESTE DAS FUNÇÕES FILA_SALVAR E FILA_LISTAR
    FILA* f = fila_criar();
    REGISTRO* r = registro_criar();
    PACIENTE* p, *aux;

    int id, m, n, feedback; scanf("%d", &n);
    char urg, nome[101];

    //Inserções 
    for(int i = 0; i < n; i++){
        scanf("%d %c %100[^\n]", &id, &urg, nome);
        aux = p = paciente_criar(nome, id);
        feedback = registro_inserir(r, &p);
        if(!feedback) fila_inserir(f, p, urg);
        else if(feedback == 1) paciente_apagar(&aux), fila_inserir(f, p, urg);
        else if(feedback == 2) paciente_apagar(&aux);
        fila_listar(&f);
    }
    registro_listar(r);

    //Remoções
    scanf("%d", &m);
    for(int i = 0; i < m; i++){
      fila_remover(f);
      fila_listar(&f);
    }
    registro_listar(r);

    fila_salvar(&f);
    registro_apagar(&r);//*/
    return 0;
}
