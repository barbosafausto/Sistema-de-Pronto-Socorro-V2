#include "historico.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIM 10

//stderr é a saída de erro

//O histórico de cada paciente tem no máximo 10 procedimentos 
struct histor{
    PROCED *proceds[LIM];  
    int tam; //Aponta para a próxima posição não ocupada (topo = tam - 1)
};

HISTOR *histor_criar(){

    HISTOR *h = (HISTOR*) malloc(sizeof(HISTOR));
    if(h != NULL){
        h->tam = 0;
    }

    return h; //Se der errado a alocação, vai retornar NULL
}

void histor_salvar(HISTOR **h, PACIENTE *p) {

    if(h != NULL && *h != NULL){    

        PROCED *proced;

        char nomeArq[60]; //Estimo que não vamos ter um número maior que 10^9 para a id do paciente
        sprintf(nomeArq, "../TAD_Historico/proceds/%d.txt", paciente_get_id(p));

        //Criando arquivo para escrita
        FILE *arq = fopen(nomeArq, "w");
        if(arq == NULL){
            return;
        }

        //Desalocando todos os procedimentos
        while(!histor_vazio(*h)){
            proced = histor_remover(*h);
            
            //Colocando string dos procedimentos no arquivo
            fprintf(arq, "%s\n", proced_get_proced(proced));
            proced_apagar(&proced);

        }
        fclose(arq);

        //Desalocando a pilha
        free(*h);
        *h = NULL;
    }

    //Caso o ponteiro esteja nulo, não acontece nada
    //Isso não é um erro, apenas significa que o histórico já foi desalocado
}

void histor_carregar(HISTOR *h, PACIENTE *p) {
    if(h != NULL){
        PROCED *proced;
        
        //Para desinverter a pilha receberemos os valores do arquivo primeiro por uma pilha auxiliar
        HISTOR *aux = histor_criar();
        FILE *arq;
        
        //Vetor já é um ponteiro inicializado para uso de fscanf
        char txtProced[101];

        char nomeArq[101];
        sprintf(nomeArq, "../TAD_Historico/proceds/%d.txt", paciente_get_id(p));


        //Abrindo arquivo para leitura
        arq = fopen(nomeArq, "r");
        if(arq == NULL){
            free(aux);
            aux = NULL;
            return;
        }

        //Criando os procedimentos e inserindo na pilha auxiliar
        while(!histor_cheio(aux) && fscanf(arq, " %100[^\n]\n", txtProced) == 1){
            proced = proced_criar(txtProced);
            histor_inserir(aux, proced);
        }

        //Desempilhando pilha auxiliar e colocando na pilha passada como parâmetro
        while(!histor_vazio(aux) && !histor_cheio(h)){
            proced = histor_remover(aux);
            histor_inserir(h, proced);
        }
        fclose(arq);

        free(aux);
        aux = NULL;
    }

}

void histor_apagar(HISTOR **h) {

    if(h != NULL && *h != NULL){    

        PROCED *proced;

        //Desalocando todos os procedimentos
        while(!histor_vazio(*h)){

            proced = histor_remover(*h);
            proced_apagar(&proced);
        }

        free(*h);
        *h = NULL;
    }
}

bool histor_cheio(HISTOR *h){
    //Histórico está cheio somente se tem a quantidade maximo de elementos
    if(h != NULL) return h->tam == LIM;

    return false;
}

bool histor_vazio(HISTOR *h){
    //Histórico está vazio somente se não tiver elementos
    if(h != NULL) return h->tam == 0;

    return true;
}
    
bool histor_inserir(HISTOR *h, PROCED *proced) {

    if(h != NULL && !histor_cheio(h)) {
        //h->tam inidica proxima posição desocupada
        h->proceds[h->tam] = proced;
        h->tam++;

        return true;
    }
    
    return false;
}

PROCED *histor_remover(HISTOR *h){

    PROCED *proced = NULL;

    if(!histor_vazio(h)){

        h->tam--;
        proced = h->proceds[h->tam];
        h->proceds[h->tam] = NULL; //Não desaloca o procedimento já que retornamos ele
    }
    return proced;
}

void histor_consultar(HISTOR *h){

    if(h != NULL){
        
        if(histor_vazio(h)){
            puts("Esse paciente não possui procedimentos registrados.");
            return;
        }
        puts("Procedimentos: ");
        //Mostra do último ao primeiro procedimento que está no histórico do paciente
        for(int i = h->tam-1; i >= 0; i--){
            printf("%s\n", proced_get_proced(h->proceds[i]));
        }
    }
}

int histor_get_tam(HISTOR *h){

    if(h != NULL){
        return h->tam;
    }

    return -1; //Não é possível h tem -1 elementos e, portanto, usamos esse valor como sinal de erro
}