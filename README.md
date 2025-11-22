# Sistema-de-Pronto-Socorro-V2
Este projeto, feito apenas em linguagem C, visa implementar algumas funcionalidades de um Sistema de Pronto Socorro por meio da implementação de Tipos Abstratos de Dados (TADs). Nesta versão, temos a implementação de árvores, estrutura que não está presente na versão 1.

## FILA

TAD responsável por representar uma fila de prioridade no sistema do hospital. Internamente ela é representa por uma min-heap, uma vez que os estados mais urgentes são dados por inteiros menores.

### Structs

O TAD é dotado de duas structs, uma representando o nó da estrutura, outra representando a estrutura em si.

O nó é dado por:

```c
    struct no_fila{
        PACIENTE *p;
        NO *dir, *esq;
        char urgencia; 
        uint ordem_chegada; 
    };
```

Além dos campos padrões, há a ordem_chegada, importante para diferenciar dois pacientes com a mesma urgência.

A estrutura é dado por:

```c
    struct fila{
        NO *frente;
        uint contador; 
    };
```

Neste caso, o contador é importante para controlar as ordens de chegada.

### Funções

- ``bool fila_cheia(FILA *f)``: retorna true, se o contador não estiver no máximo ou se não for possível mais alocações.

- ``bool fila_vazia(FILA *f)``: retorna true, se a frente da fila estiver vazia.

- ``FILA *fila_criar(void)``: aloca memória para a struct fila, colocando contador como 0 e frente como NULL.

## REGISTRO

TAD reponsável por armazenar os dados e cadastros dos pacientes. É organizado como uma árvore do tipo AVL a fim de evitar operações com complexidade linear.

### Funções

- `int_8 registro_inserir(REGISTRO* r, PACIENTE* p, bool esta_na_fila)`: chama a função registro_inserir_no para inserção do paciente p no registro r corretamente na AVL (seguindo a ordem dos ID's), utilizando rotações para a manutenção da rotação. Retorna 0, se teve sucesso; 1, se o paciente com aquele ID já estiver no registro; 2, se o paciente, além de estar no registro, está na fila. **Está com impressões de debug.**

- `void registro_listar(REGISTRO* r)`: chama a função registro_listar_no a fim de mostrar os nomes e ID's dos pacientes presentes no registro seguindo a ordem dos ID's. É feito com um percurso em-ordem.

- `bool registro_apagar(REGISTRO** r)`: desaloca todos nós da árvore, inclusive ela mesma, evitando memory leak. **Não será usada no programa final, provavelmente.**

