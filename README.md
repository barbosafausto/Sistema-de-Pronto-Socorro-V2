

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

