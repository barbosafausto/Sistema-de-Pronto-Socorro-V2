#include "fila.h"

//A fila é implementada usando uma Min-Heap

typedef struct no_fila NO;
typedef unsigned int uint;

//Mesmo com somente um campo, a struct é necessário para manter a information hiding do TAD
struct fila{
    NO *frente;
    uint contador; //Conta-se quantos pacientes já foram inseridos
};

struct no_fila{
    PACIENTE *p;
    NO *dir, *esq;
    char urgencia; //É utilizado inteiro de 1 byte, uma vez que há somente 5 valores diferentes para esse campo
    uint ordem_chegada; //Utilizado para diferenciar pacientes com mesma urgência, priorizando aqueles que chegaram primeiro 
};

FILA *fila_criar(void){
    FILA *f = (FILA*)malloc(sizeof(FILA));

    if(f != NULL){
        f->frente = NULL;
        f->contador = 0;
    }
    return f;
} 

NO *fila_criar_no(PACIENTE *p, char urgencia, uint ordem_chegada){
    
    NO *novo = (NO*)malloc(sizeof(NO));
    if(novo != NULL){
        novo->p = p;
        novo->dir = novo->esq = NULL;
        novo->urgencia = urgencia;
        novo->ordem_chegada = ordem_chegada;
    }
    return novo;
}


FILA *fila_carregar(void); 

bool fila_salvar(FILA **f);

bool fila_inserir(FILA *f, PACIENTE *p, char urgencia);

PACIENTE *fila_remover(FILA *f);

bool fila_cheia(FILA *f){
    if(f != NULL){
        NO *teste = fila_criar_no(NULL, 0, 0); //Como é um teste, não importa os dados passados, eles ocupam o mesmo espaço
        if(teste != NULL && f->contador < __UINT32_MAX__){ //Valor máximo para um unsigned int
            return false;
        }
    }
    return true;
}

bool fila_vazia(FILA *f){
    if(f != NULL) return f->frente == NULL;
    return false;
}

void fila_listar(FILA *f);