

# 🏥 Sistema de Pronto Socorro - Versão 2
Este projeto, feito apenas em linguagem C, visa implementar algumas funcionalidades de um Sistema de Pronto Socorro por meio da implementação de Tipos Abstratos de Dados (TADs). Nesta versão, temos a implementação de árvores, estrutura que não está presente na versão 1.

# 1️⃣ Introdução

## ⚠️ Como Usar

🔴 Para usar este sistema, acesse a passa `Cliente` e execute `make all; make run`. Após fazer isso, siga as instruções do menu que irá aparecer para você.

## ⚙️ Composição

O nosso sistema é composto por três estruturas principais:

🔹Pacientes;

🔹Registro de pacientes; e

🔹Fila de espera.

Todas as operações do nosso sistema são feitas nessas estruturas. A seguir, vamos descrever brevemente a composição delas, visando entender seus funcionamentos.



# ⏳ Fila
TAD responsável por representar uma fila de prioridade no sistema do hospital. Internamente, ela é representada por uma min-heap, uma vez que as condições mais urgentes dos pacientes são dadas por valores inteiros menores.

## 📦 Structs 
O TAD é composto por duas structs, uma representando o nó da estrutura, outra representando a estrutura em si.

### 🔹 Nó da fila :

```C
struct no_fila {
    PACIENTE *p;
    char urgencia; 
    uint ordem_chegada; 
};
```

Além dos campos padrões, há o campo ordem_chegada, importante para diferenciar dois pacientes com a mesma urgência.

### 🏗️ Estrutura da fila
```C
struct fila {
    NO **heap;
    uint final;
    uint tamanho;
    uint contador; 
};
```

O campo contador é essencial para controlar a ordem de chegada dos pacientes, enquant final aponta para o último paciente da heap e tamanho guarda a capacidade máxima atual dela.

## ⚙️ Funções

🚫 `bool fila_cheia(FILA *f)`: retorna true, se o contador não estiver no máximo ou se não for possível mais alocações.

🔷 `bool fila_vazia(FILA *f)`: retorna true, se a frente da fila estiver vazia.

🆕 `FILA *fila_criar(void)`: aloca memória para a struct fila, colocando contador como 0 e frente como NULL.

📂 `FILA *fila_carregar(REGISTRO *r)`: carrega os pacientes salvos no arquivo fila.txt. São feitas buscas no registro para encontrar o ponteiro para cada paciente e colocá-lo na fila.


# 🗃️ Registro
TAD reponsável por armazenar os dados e cadastros dos pacientes. É organizado como uma árvore do tipo AVL a fim de evitar operações com complexidade linear.

## Structs

Como a fila, o TAD é composto por duas structs, uma representando o nó da estrutura, outra representando a estrutura em si.

### 🔹Nó do registro
```C
struct no_registro {
  PACIENTE* p;
  NO* dir;
  NO* esq;
  int altura;
  bool esta_na_fila;
};
```

Cada nó do registro aponta para seus filhos esquerdo e direito. Além disso, todo nó tem uma altura e guarda não só o paciente, mas se este paciente está na fila.

### 🏗️ Estrutura do registro
```C
struct registro_ {
  NO* raiz;
};
```

A estrutura do registro apenas aponta para a raiz da árvore AVL.


## ⚙️ Funções
📥 `int_8 registro_inserir(REGISTRO* r, PACIENTE* p, bool esta_na_fila)`: chama a função registro_inserir_no para inserção do paciente p no registro r corretamente na AVL (seguindo a ordem dos ID's), utilizando rotações para a manutenção da rotação. Retorna 0, se teve sucesso; 1, se o paciente com aquele ID já estiver no registro; 2, se o paciente, além de estar no registro, está na fila. Está com impressões de debug.

📜 `void registro_listar(REGISTRO* r)`: chama a função registro_listar_no a fim de mostrar os nomes e ID's dos pacientes presentes no registro seguindo a ordem dos ID's. É feito com um percurso em-ordem.

🗑️ `bool registro_apagar(REGISTRO** r)`: desaloca todos nós da árvore, inclusive ela mesma, evitando memory leak. Não será usada no programa final, provavelmente.

💾 `bool registro_salvar(REGISTRO** r)`: percorre a AVL recursivamente, em pós-ordem, salvando os nós no arquivo registro.txt a partir das folhas.