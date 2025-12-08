

# 🏥 Sistema de Pronto Socorro - Versão 2
Este projeto, feito apenas em linguagem C, visa implementar algumas funcionalidades de um Sistema de Pronto Socorro por meio da implementação de Tipos Abstratos de Dados (TADs). Nesta versão, temos a implementação de árvores, estrutura que não está presente na versão 1.


# 1️⃣ Introdução

## 👥 Grupo
* 15512767 - José Fausto Vital Barbosa
* 16862551 - Eduardo Benedini Bueno
* 16816271 - João Pedro Conde Gomes Alves

## ⚠️ Como Usar

🔴 Para usar este sistema, acesse a passa `Cliente` e execute `make all; make run`. Após fazer isso, siga as instruções do menu que irá aparecer para você.

## ⚙️ Composição

O nosso sistema é composto por 5 estruturas principais:

🔹Pacientes;

🔹Procedimentos;

🔹Histórico de procedimentos;

🔹Registro de pacientes; e

🔹Fila de espera (composta por pacientes).

Todas as operações do nosso sistema são feitas nessas estruturas. A seguir, vamos descrever brevemente a composição delas, visando entender seus funcionamentos.





# ⚕️ TAD Procedimento

O TAD *Procedimento* define um tipo de dado que será armazenado, posteriormente, no *Histórico* do paciente. Cada paciente tem um *Histórico* composto por *Procedimentos*.

```C
struct procedimento {
    char* p;
};
```

### 👤 TAD Paciente

O TAD *Paciente* tem uma natureza análoga ao TAD *Procedimento*. Ele será usado na *Fila*.

```C
struct paciente {
    char* nome;
    int id;
    bool esta_na_fila; 
}; 
```

Em outras palavras:
*  A *Fila* possui um conjunto de *Pacientes*; e
* O *Histórico* possui um conjunto de *Procedimentos*;




# 🆙 TAD Histórico

O TAD *Histórico* é uma *pilha sequencial estática*, a qual implementa o método LIFO (Last-In First-Out), devido à simplicidade da sua implementação em casos em que o tamanho máximo da pilha está definido e é pequeno, que é o nosso caso. O limite da pilha é de 10 procedimentos por paciente.

Desse modo, o *Histórico* de um paciente é definido por uma struct que possui dois campos. O primeiro campo é um array de procedimentos, enquanto o segundo é o tamanho da pilha, o qual usamos para acessar o seu topo e para verificar se ela está cheia ou vazia.

```C
struct histor {
    PROCED *proceds[10];  
    int tam;
};
```




# ⏳ TAD Fila
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

O campo contador é essencial para controlar a ordem de chegada dos pacientes, enquanto `final` é o índice do próximo espaço a ser ocupado pela heap e `tamanho` guarda a capacidade máxima atual dela.


# 🗃️ Registro
TAD responsável por armazenar os dados e cadastros dos pacientes. É organizado como uma árvore do tipo AVL, a fim de evitar operações com complexidade linear.

## Structs

Como a fila, o TAD é composto por duas structs, uma representando o nó da estrutura, outra representando a estrutura em si.

### 🔹Nó do registro
```C
struct no_registro {
  PACIENTE* p;
  HISTOR *h;
  NO* dir;
  NO* esq;
  int altura;
};
```

Cada nó do registro aponta para seus filhos esquerdo e direito. Além disso, todo nó tem uma altura e guarda não só o paciente, mas também seu histórico de procedimentos.

### 🏗️ Estrutura do registro
```C
struct registro_ {
  NO* raiz;
};
```

A estrutura do registro apenas aponta para a raiz da árvore AVL.


# 👤 Cliente

Uma vez que entendemos as estruturas que compõem o nosso sistema, podemos descrever o seu funcionamento esperado. Faremos isso através da descrição das funções do arquivo `Cliente/cliente.c`.

---

💾 `bool inicializar(REGISTRO**r, FILA** f);`

Esta função é responsável por carregar o registro e a fila dos arquivos salvos. Ela retorna "true" caso ambos forem carregados corretamente, e "false" caso contrário. "*r" e "*f" apontarão para as structs criadas por esta função.


---

💾 `void sair(REGISTRO** r, FILA** f);`

A função de sair lida com o encerramento da sessão do sistema. Para isso ocorrer corretamente, é necessário que os dados da fila e do registro sejam salvos corretamente.

Para cumprir este fim, a função de sair funciona em duas etapas:
1. Chama a função `fila_salvar`, que apaga os nós da fila e a fila em si; e
2. Chama a função `registro_salvar`, que faz o mesmo.

Dessas duas funções, somente a do registro desaloca o espaço reservado para os pacientes e seus históricos após salvá-los.

---
    
🆕 `int_8 registrar_paciente(REGISTRO *r, FILA *f, int id, char* nome, int_8 urgencia);`

Esta é a função usada para registrar um paciente no sistema. Existem 5 tipos de retornos para esta 
função:
```C
/*Paciente novo: não está nem no registro, nem na fila. Será inserido em ambos.*/
#define NAO_ESTA 0

/*Paciente antigo: está no registro, mas não está na fila. Será inserido na fila.*/
#define ESTA_REGISTRO 1

/*Erro: tentativa de inserir um paciente que já está registrado no registro e na fila. Não faremos nada nesse caso.*/
#define ESTA_FILA 2

/*Erro: tentativa de inserir um paciente com um ID que já está em uso por outro paciente. Não faremos nada nesse caso.*/
#define REPETIDO 3

/*Erro: falta de memória para alocação do paciente ou do seu histórico. Não faremos nada nesse caso.*/
#define ERRO -1
```

É por isso que a função registrar_paciente é do tipo `int_8`: 1 byte é suficiente para essa função funcionar, então não precisamos de um inteiro de 4 bytes.
```C
typedef char int_8
```

---

🆓 `PACIENTE* dar_alta_ao_paciente(FILA* f);`

Esta função é responsável por retirar o paciente de maior prioridade da fila. Retorna esse paciente. Em caso de fila inválida, retornará `NULL`. Esse paciente não é apagado da memória, pois ainda está no registro.

---
    
🔴 `PACIENTE* remover_paciente(REGISTRO* r, int id);`

Esta função lida com a remoção de um paciente do registro. Quando isso é feito, todas as informações do paciente são apagadas, incluindo o seu histórico de procedimentos. Isso é feito através da função `registro_remover`.

Essa função só remove um paciente se ele não estiver na fila. Caso ele esteja, a operação de remoção é abortada.

---
    
🔍 `PACIENTE* buscar_paciente_por_ID(REGISTRO* r, int id);`

Busca por um paciente com ID igual ao passado para a função no registro. Retorna este paciente, se encontrar, e retorna NULL caso não exista paciente com este ID no sistema.

---
    
☰ `void mostrar_fila_de_espera(FILA** f);`

Esta função apresenta o nome, ID, urgência e a ordem de chegada dos pacientes que estão na fila. Isso é mostrada na ordem do paciente de maior prioridade para o de menor. Essa operação exige uma memória adicional, se não for possível, ela não será feita. 

---
  
☰ `void listar_pacientes(REGISTRO* r);`

Esta função é responsável por listar os pacientes que estão registrado. Ela usa a função `registro_listar()` por baixo dos panos.

Sendo assim, esta função irá dispor na tela:
* O ID do paciente;
* Seu nome; 
* Se ele está na fila; e
* O seu histórico de procedimentos.

---

☰ `bool mostrar_historico(REGISTRO *r, int id);`


descricao aq

---

🆕 `bool adicionar_procedimento(REGISTRO *r, int id, char *proced);`

Esta função é responsável por adicionar um novo procedimento na pilha que representa o histórico de procedimentos de um paciente.
  

--- 

🔴 `bool desfazer_procedimento(REGISTRO *r, int id);`

Esta função é responsável por remover o último procedimento adicionado na pilha que representa o histórico de procedimentos de um paciente.
     
