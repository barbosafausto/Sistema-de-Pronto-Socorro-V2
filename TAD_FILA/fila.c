#include "fila.h"

#define esq(n) (2*n + 1)
#define dir(n) (2*n + 2)
#define pai(n) ((n - 1)/2)

//A fila é implementada usando uma Min-Heap

typedef struct no_fila NO;
typedef unsigned int uint;

struct fila {
    NO **arvore;
    uint final; //Índice da próxima posição a ser ocupada.
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
			free(f);
          	return NULL;
        }
        
		f->final = 0;
		f->tamanho = 100; //Tamanho inicial
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

//Função de swap entre dois nós
void fila_swap_no(NO** a, NO** b){ 
  	if(a == NULL || b == NULL) return; //Se forem iguais a NULL, a operação de derreferenciamento será inválida
	
	NO* aux;
	
  	aux = *a;
  	*a = *b;
 	*b = aux;

}

/*//Função que pega o paciente a partir de seu nó
PACIENTE *fila_get_paciente_no(NO* n){
	if(n == NULL) return NULL;
	return n->p;
}*/

//Comparação de prioridades
bool fila_checa_prioridade(NO* a, NO* b){ //Esta função é responsável por detectar qual dos dois nós comparados possui maior prioridade. Ela retorna "true" caso o primeiro nó possui maior prioridade e "false" caso o segundo possuir menor prioridade.
        if (a->urgencia < b->urgencia) return true;
        if (a->urgencia > b->urgencia) return false;
        
        return (a->ordem_chegada < b->ordem_chegada);
}

/*===============================================================================*/
//Funções sobre tamanho da fila

bool fila_cheia_aumentar(FILA *f){ //Não precisamos passar ponteiro de ponteiro já que esse parâmetro na stack vai apontar pra mesma árvore (vetor)
    if(f != NULL){
        if (f->final < f->tamanho) return false; //Se o último nó não estiver ocupando o último espaço não há de um realloc, a fila não está cheia.
        
		else{
            NO** aux;
	        f->tamanho *= 2;
	        aux = (NO**)realloc(f->arvore, f->tamanho * sizeof(NO*));
	        
			/*Caso não exista espaço contíguo suficiente na memória, "realloc()" retorna NULL.
	        Para que o ponteiro para a heap não seja "perdido" caso uma realocação falhar, um ponteiro auxiliar recebe "f->arvore" antes de "realloc()" ser chamado.
	        Caso "realloc()" realmente tenha falhado, o ponteiro auxiliar "devolve" o ponteiro para para "f->arvore" */
	        if(f->arvore == NULL){
	              f->tamanho /= 2;
	              return true; //Retorna verdadeiro caso o realloc falhar. (fila cheia)
			}
	        
			//f->tamanho /= 2;
	        f->arvore = aux;
	        return false;
		}
    }
    return true;
}

void fila_diminuir(FILA *f){
	if (f->tamanho >= 200 && (f->final) < (f->tamanho/2)) { //Se o espaço na heap não for mais necessário, um nível é removido.
			f->tamanho /= 2;
			f->arvore = (NO**)realloc(f->arvore, f->tamanho * sizeof(NO *));
	}
}

bool fila_vazia(FILA *f){
    if(f != NULL) return (f->final == 0);
	return false;
}


/*===============================================================================*/
//Funções de conserto da árvore após inserção/remoção

void fila_fix_up(FILA *f, uint posicao_inicial){
	if(f == NULL) return;

	uint posicao_atual = posicao_inicial;
	uint posicao_pai = pai(posicao_atual); //Fórmula para o pai
	
	while((posicao_atual != 0) && fila_checa_prioridade(f->arvore[posicao_atual], f->arvore[posicao_pai])){

		fila_swap_no(&(f->arvore[posicao_atual]), &(f->arvore[posicao_pai])); //Enquanto o nó inserido não for a raiz e seu pai tiver menor prioridade, ele é trocado de posição com seu pai.
		posicao_atual = posicao_pai; //Indo para a posição do pai
		posicao_pai = pai(posicao_atual); //Atualizando o pai

	}
	
	return;
}

void fila_fix_down(FILA* f, uint posicao_inicial){
	if(f == NULL) return;

    uint posicao_atual = posicao_inicial;
	uint maior_prioridade;

	while(true){
	        maior_prioridade = posicao_atual; //maior_prioridade guarda o índice do nó de maior prioridade entre os testados.
	        
	        if (esq(posicao_atual) < f->final && fila_checa_prioridade(f->arvore[esq(posicao_atual)], f->arvore[maior_prioridade])){
	              maior_prioridade = esq(posicao_atual); //Se o filho esquerdo tiver maior prioridade que a posição atual, atualiza-se o índice.
	        }
	        
	        if (dir(posicao_atual) < f->final && fila_checa_prioridade(f->arvore[dir(posicao_atual)], f->arvore[maior_prioridade])){
	              maior_prioridade = dir(posicao_atual); //Se o filho direito tiver maior prioridade que a posição de maior prioridade encontrada até agora (seja a posição atual ou o filho esquerdo), atualiza-se o índice.
	        }
	        
	        if (maior_prioridade == posicao_atual){
	            break; //Se o índice não foi atualizado, então o nó está na posição correta.
	        }
	        
	        fila_swap_no(&f->arvore[posicao_atual], &f->arvore[maior_prioridade]); //Troca-se o nó de posição com o filho de maior prioridade.
	        posicao_atual = maior_prioridade; //A posição atual do nó é atualizada.
	}
	
	return;
}

/*===============================================================================*/
//Inserção

bool fila_inserir_no(FILA* f, NO *n){
	if(f != NULL && n != NULL){
		f->arvore[f->final] = n;
		fila_fix_up(f, f->final);
		f->contador++;
		f->final++;
		return true;
	}
	return false;
}

bool fila_inserir(FILA *f, PACIENTE *p, char urgencia){
	if (!fila_cheia_aumentar(f)){ //Checa se a fila está cheia e aumenta seu tamanho se necessário para a nova inserção
		
		NO* novo = fila_criar_no(p, urgencia, f->contador);
		if(novo == NULL) return false; //Falha na alocação do novo nó; A fila pode continuar do mesmo já possivelmente o espaço será usada depois
				
		fila_inserir_no(f, novo); //Não preciso olhar para o retorno, pois aqui temos a garantia que n != NULL e f != NULL
		return true;
	}
	return false;
}

/*===============================================================================*/
//Funções de remover

NO* fila_remover_no(FILA* f){ //O mesmo que fila_remover, porém retorna o nó a ser removido
	
	NO *n = NULL;

	if (!fila_vazia(f)) {

		fila_swap_no(&f->arvore[0], &f->arvore[f->final-1]);
		n = f->arvore[f->final-1];
		f->final--; //Isso basta para que o último valor não seja mais considerado da heap

		fila_fix_down(f, 0);
		
		if (f->tamanho >= 200 && (f->final) < (f->tamanho/2)) { //Se o espaço na heap não for mais necessário, um nível é removido.
			f->tamanho /= 2;
			f->arvore = (NO**)realloc(f->arvore, f->tamanho * sizeof(NO *));
		}		

	}

	return n;
}

//Remoção
PACIENTE *fila_remover(FILA *f){

	if (!fila_vazia(f)) {

		PACIENTE *p = f->arvore[0]->p; //Sempre se remove a raiz (o primeira da fila)
		fila_swap_no(&(f->arvore[0]), &(f->arvore[f->final-1]));
		free(f->arvore[f->final-1]); //Só apaga o nó e não o paciente p nele, já que iremos retorná-lo

		f->arvore[f->final-1] = NULL;
		f->final--;
		fila_fix_down(f, 0);
		
		fila_diminuir(f);
		
		return(p);
	}
	return NULL;
}

/*===============================================================================*/
//Função de listar em ordem de prioridade

void fila_listar(FILA **f){
	if(f == NULL) return;

	FILA* aux = fila_criar();
	NO* n;

	if(aux != NULL){
		printf("#     | URGÊNCIA | CHEGADA | NOME\n");
		while(!fila_vazia(*f)){
			n = fila_remover_no(*f); //Não apaga o nó

			if(n == NULL) continue; //Em caso de erro

			fila_inserir_no(aux, n); //Copia o exato mesmo nó para aux
			printf("%06d|    %c     |    %dº   |%s\n", paciente_get_id(n->p), n->urgencia, n->ordem_chegada+1, paciente_get_nome(n->p));
		}
		
		printf("\n");

		free((*f)->arvore); //Não tem mais nós no array da heap original

		free(*f); //Desalocando a struct do array original

		*f = aux; //Aux tem todas as informações retiradas da heap original
	}
}

//Funções de carregamento e salvamento
FILA *fila_carregar(REGISTRO* r) {

	/*
	Os dados foram salvos no formato (Urgência é um ):
	ID
	Urgência

	ID
	Urgência
	...
	*/

	FILE *fp = fopen("fila.txt", "r");
	if (!fp) return NULL;
	
	FILA *f = fila_criar();
	if (!f) return NULL;

	int info, acao;
	while (true) {

		acao = fscanf(fp, "%d", &info);

		if (acao == -1) break; //Recebeu EOF
		if (acao == 0) continue; //Não conseguiu fazer a leitura

		//Se chegou aqui, é porque encontrou um ID, então vamos buscar o paciente
		PACIENTE *p = registro_recuperar(r, info);

		//Temos o paciente, então podemos buscar a urgência dele
		fscanf(fp, "%d", &info);

		//Com isso, fazemos a inserção na fila de prioridade
		fila_inserir(f, p, info);

	}
	fclose(fp);

	return f;
} 

bool fila_salvar(FILA **f) {

	if(f != NULL && *f != NULL){
		NO* n;
		FILE* fp = fopen("fila.txt", "w");
		if(!fp) return false; //Erro na abertura de arquivo

		while(!fila_vazia(*f)){ //Ficar retirando os valores e colocando no arquivo
			n = fila_remover_no(*f);
			fprintf(fp, "%d\n%c\n\n", paciente_get_id(n->p), n->urgencia);
			free(n); //Não apaga o paciente, pois o registro já responsável por isso
		}

		fclose(fp); //Executa o flush

		free((*f)->arvore); //Apaga o vetor dinâmico

		free(*f);
		*f = NULL;

		return true;
	}

	return false;

}