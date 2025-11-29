#include "fila.h"

//A fila é implementada usando uma Min-Heap

typedef struct no_fila NO;
typedef unsigned int uint;

//Mesmo com somente um campo, a struct é necessário para manter a information hiding do TAD
struct fila{
    NO **arvore;
    uint final; //Índice da atual última posição.
    uint tamanho; //Tamanho máximo atual da fila.
    uint contador; //Conta-se quantos pacientes já foram inseridos desde a última inicialização do programa.
};

struct no_fila{
    PACIENTE *p;
    char urgencia; //É utilizado inteiro de 1 byte, uma vez que há somente 5 valores diferentes para esse campo
    uint ordem_chegada; //Utilizado para diferenciar pacientes com mesma urgência, priorizando aqueles que chegaram primeiro 
};

FILA *fila_criar(void){
    FILA *f = (FILA*)malloc(sizeof(FILA));

    if(f != NULL){
    
        f->arvore = malloc(100 * sizeof(NO*)); //O vetor dentro da struct é dinâmicamente alocado.
        
        if (f->arvore == NULL){
          return NULL;
        }
        
	f->final = 0;
	f->tamanho = 100;
        f->contador = 0;
		
	return f;
    }
    return NULL;
} 

NO *fila_criar_no(PACIENTE *p, char urgencia, uint ordem_chegada){
    
    NO *novo = (NO*)malloc(sizeof(NO));
    if(novo != NULL){
        novo->p = p;
        novo->urgencia = urgencia;
        novo->ordem_chegada = ordem_chegada;
    }
    return novo;
}

FILA *fila_carregar(void); 

bool fila_salvar(FILA **f);

void TrocaNo(NO** a, NO** b){
  NO* aux;
	
  aux = *a;
  *a = *b;
  *b = aux;
	
  return;
}

PACIENTE *No_get_paciente(NO* n){
  return n->p;
}

bool ChecaPrioridade(NO* a, NO* b){
        //Esta função é responsável por detectar qual dos dois nós comparados possui maior prioridade. Ela retorna "true" caso o primeiro nó possui maior prioridade e "false" caso o segundo possuir menor prioridade.
        if (a->urgencia < b->urgencia) return true;
        if (a->urgencia > b->urgencia) return false;
        
        return (a->ordem_chegada < b->ordem_chegada);
}

void FixUp(FILA *f){
	uint PosicaoAtual = f->final;
	
	while((PosicaoAtual != 0) && ChecaPrioridade(f->arvore[PosicaoAtual], f->arvore[((PosicaoAtual) - 1)/2])){
		
		TrocaNo(&f->arvore[PosicaoAtual], &f->arvore[((PosicaoAtual) - 1)/2]); //Enquanto o nó inserido não for a raiz e seu pai tiver menor prioridade, ele é trocado de posição com seu pai.
		PosicaoAtual = (PosicaoAtual-1)/2;
	}
	
	return;
}

void FixDown(FILA* f){
        uint PosicaoAtual = 0;

	while(true){
	        uint MaiorPrioridade = PosicaoAtual; //MaiorPrioridade guarda o índice do nó de maior prioridade entre os testados.
	        
	        if (2*PosicaoAtual+1 < f->final && ChecaPrioridade(f->arvore[(2*PosicaoAtual)+1], f->arvore[MaiorPrioridade])){
	              MaiorPrioridade = (2*PosicaoAtual)+1; //Se o filho esquerdo tiver maior prioridade que a posição atual, atualiza-se o índice.
	        }
	        
	        if (2*PosicaoAtual+2 < f->final && ChecaPrioridade(f->arvore[(2*PosicaoAtual)+2], f->arvore[MaiorPrioridade])){
	              MaiorPrioridade = (2*PosicaoAtual)+2; //Se o filho direito tiver maior prioridade que a posição de maior prioridade encontrada até agora (seja a posição atual ou o filho esquerdo), atualiza-se o índice.
	        }
	        
	        if (MaiorPrioridade == PosicaoAtual){
	            break; //Se o índice não foi atualizado, então o nó está na posição correta.
	        }
	        
	        TrocaNo(&f->arvore[PosicaoAtual], &f->arvore[MaiorPrioridade]); //Troca-se o nó de posição com o filho de maior prioridade.
	        PosicaoAtual = MaiorPrioridade; //A posição atual do nó é atualizada.
	}
	
	return;
}

bool fila_inserir(FILA *f, PACIENTE *p, char urgencia){
	if (f != NULL){
		
		NO* novo = fila_criar_no(p, urgencia, f->contador);
		if (novo == NULL) return false;
		if (f->final >= f->tamanho) //Caso não houver mais espaço na heap, adiciona-se um novo nível para ela.
		{
			NO** aux = f->arvore;
			f->tamanho *= 2;
			f->arvore = (NO**)realloc(f->arvore, f->tamanho * sizeof(NO *));
			/*Caso não exista espaço contíguo suficiente na memória, "realloc()" retorna NULL.
			Para que o ponteiro para a heap não seja "perdido" caso uma realocação falhar, um ponteiro auxiliar recebe "f->arvore" antes de "realloc()" ser chamado.
			Caso "realloc()" realmente tenha falhado, o ponteiro auxiliar "devolve" o ponteiro para para "f->arvore" */
			if (f->arvore == NULL){
			
			        f->arvore = aux;
			        f->tamanho /= 2;
				return false;
			}
			aux = NULL;
		}
		
		f->arvore[f->final] = novo;
		FixUp(f); //A última posição da árvore recebe o novo nó, que então é colocado na posição correta.
		f->final++;
		f->contador++;
		return true;
	}
	return false;
}

PACIENTE *fila_remover(FILA *f){
	if (f != NULL && f->final != 0){
		PACIENTE *p = No_get_paciente(f->arvore[0]);
		TrocaNo(&f->arvore[0], &f->arvore[f->final - 1]);
		free(f->arvore[f->final-1]);
		f->arvore[f->final-1] = NULL;
		f->final--;
		FixDown(f);
		
		if (f->tamanho => 200 && (f->final) == (f->tamanho/2) //Se o espaço na heap não for mais necessário, um nível é removido.
		{ 
			f->tamanho /= 2;
			f->arvore = (NO**)realloc(f->arvore, f->tamanho * sizeof(NO *));
		}
		
		return(p);
	}
	return NULL;
}

bool fila_cheia(FILA *f){
    if(f != NULL){
        if (!(f->final >= f->tamanho)) return false; //Se o último nó não estiver ocupando o último espaço antes da necessidade de um realloc, a fila não está cheia.
        else{
                NO** aux = f->arvore;
	        f->tamanho *= 2;
	        f->arvore = (NO**)realloc(f->arvore, f->tamanho * sizeof(NO *));
	        /*Caso não exista espaço contíguo suficiente na memória, "realloc()" retorna NULL.
	        Para que o ponteiro para a heap não seja "perdido" caso uma realocação falhar, um ponteiro auxiliar recebe "f->arvore" antes de "realloc()" ser chamado.
	        Caso "realloc()" realmente tenha falhado, o ponteiro auxiliar "devolve" o ponteiro para para "f->arvore" */
	        if (f->arvore == NULL){	
	              f->arvore = aux;
	              f->tamanho /= 2;
	              return true; //Retorna verdadeiro caso o realloc falhar.
	        }
	        aux = NULL;
	        f->tamanho /= 2;
	        f->arvore = (NO**)realloc(f->arvore, f->tamanho * sizeof(NO *));
	        return false;
	}
    }
    return true;
}

bool fila_vazia(FILA *f){
    if(f != NULL) return (f->final == 0);
return false;
}

void fila_listar(FILA *f);
