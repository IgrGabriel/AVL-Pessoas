
# Documentação do código AVL Tree

Este código implementa uma árvore AVL (Adelson-Velskii e Landis), uma árvore binária de busca balanceada, utilizada para armazenar dados de pessoas. A árvore é balanceada automaticamente após inserções, garantindo que a altura da árvore seja sempre otimizada.


## Compilação e Execução

Para compilar o programa, você pode utilizar o comando `g++` seguido da opção `-o` para definir o nome do arquivo de saída e, em seguida, informar o nome dos arquivos fonte que serão compilados. No caso específico do código fornecido, você pode utilizar o seguinte comando para compilar:

```shell
g++ -o programa avl.cpp
```

Isso irá gerar um arquivo executável chamado "programa" a partir do arquivo de código-fonte "avl.cpp".

Para executar o programa, basta digitar o seguinte comando no terminal:

```shell
./programa
```

Isso irá executar o programa gerado a partir da compilação e você poderá interagir com o programa através do terminal, seguindo as opções e instruções exibidas.

Certifique-se de estar no diretório correto onde o arquivo fonte "avl.cpp" está localizado antes de executar os comandos de compilação e execução.

Observação: Lembre-se de ter um ambiente de desenvolvimento adequado configurado, com um compilador C++ instalado, para poder compilar e executar o programa corretamente.
Aqui está a adição do código fornecido à documentação anterior:

## Estrutura de diretórios

- `node.h`: Define a estrutura do nó da árvore AVL.
- `avl.h`: Declaração da classe `avl_tree` que implementa a árvore AVL e contém os métodos para adicionar, buscar e listar pessoas na árvore.
- `arq.h`: Arquivo de cabeçalho que contém definições relacionadas à manipulação de arquivos.
- `comparators.h`: Declaração dos comparadores utilizados para ordenação na árvore AVL, como CPF, nome, data de nascimento e cidade.
- `auxFuncs.h`: Declaração de funções auxiliares utilizadas na árvore AVL.
- `main.h`: Declaração de funções principais e interação com o usuário.

## Dependências

- `iostream`: Biblioteca de entrada/saída padrão em C++.
- `iomanip`: Biblioteca para manipulação de formatação de saída, utilizada para definir a largura e preenchimento de caracteres.
- `cctype`: Biblioteca para manipulação de caracteres, utilizada para converter letras maiúsculas em minúsculas.

## Funções principais

### Funções de altura e balanceamento

- `int avl_tree::height(Node *node)`: Retorna a altura de um nó da árvore. Se a árvore for vazia, a altura é 0. Caso contrário, retorna o valor armazenado no campo `height` do nó.
- `int avl_tree::updateHeight(Node* node)`: Atualiza a altura de um nó. O nó recebe a maior altura entre a subárvore da esquerda e da direita mais 1.
- `int avl_tree::balance(Node *node)`: Calcula o fator de balanceamento de um nó. O fator de balanceamento é a diferença entre a altura da subárvore esquerda e da subárvore direita.

### Funções de rotação

- `Node* avl_tree::leftRotation(Node *p)`: Realiza uma rotação simples à esquerda para balancear a árvore.
- `Node* avl_tree::rightRotation(Node *p)`: Realiza uma rotação simples à direita para balancear a árvore.
- `Node* avl_tree::rightLeftRotation(Node *p)`: Realiza uma rotação dupla à esquerda para balancear a árvore.
- `Node* avl_tree::leftRightRotation(Node *p)`: Realiza uma rotação dupla à direita para balancear a árvore.

### Funções de rebalanceamento e adição

- `Node* avl_tree::rebalance(Node *node)`: Realiza o balanceamento da árvore após uma inserção ou remoção. Recebe o nó que está desbalanceado e retorna a nova raiz após o balanceamento.
- `template <typename T> Node* avl_tree::add(Node *node, Pessoa *pessoa, T comparator)`: Função genérica para adicionar um nó à árvore AVL, usando um comparador específico para determinar a ordenação.

### Funções de busca e listagem

- `void avl_tree::searchByCPF(long long int cpf)`: Busca uma pessoa na árvore AVL pelo CPF.
- `void avl_tree::listByName(const string& prefixo)`: Lista todas as pessoas da árvore AVL cujo nome começa com o prefixo fornecido.
- `void avl_tree::listDtNasc(const Data& dtInicio, const Data& dtFinal)`: Lista todas as pessoas da árvore AVL que nasceram em um intervalo de datas.
- `void avl_tree::listByCity(const string& prefixo)`: Lista todas as pessoas da árvore AVL cuja cidade começa com o prefixo fornecido.

### Funções de exibição e limpeza

- `void avl_tree::show()`: Exibe a árvore AVL no formato de visualização hierárquica.
- `void avl_tree::clear()`: Limpa a árvore AVL, liberando a memória ocupada pelos nós.
- `void avl_tree::show(Node *raiz, int nivel)`: Função auxiliar para exibir a árvore AVL de forma recursiva.
- `void avl_tree::showPessoa(Pessoa *pessoa)`: Exibe os dados de uma pessoa.
- `void avl_tree::listPessoas(Node *node)`: Função auxiliar para listar as pessoas da árvore AVL em ordem.

### Funções de leitura de arquivo

- `template <typename T> void avl_tree::lerArquivoCSV(const string& nomeArquivo, T compare)`: Lê um arquivo CSV com informações das pessoas e adiciona os registros na árvore AVL, usando um comparador específico para determinar a ordenação.

## Variáveis de classe

- `Node *root {nullptr}`: Ponteiro para a raiz da árvore AVL.

## Construtores e destrutor

- `avl_tree() = default`: Construtor padrão da classe `avl_tree`.
- `~avl_tree()`: Destrutor da classe `avl_tree`.

## Funções privadas

### Funções de adição e busca

- `template <typename T> Node* avl_tree::add(Node *node, Pessoa *pessoa, T comparator)`: Função auxiliar para adicionar um nó à árvore AVL de forma recursiva.
- `Node* avl_tree::searchByCPF(Node *node, long long int cpf)`: Função auxiliar para buscar uma pessoa na árvore AVL pelo CPF de forma recursiva.

### Funções de listagem

- `void avl_tree::listByName(Node *node, const string& prefixo)`: Função auxiliar para listar todas as pessoas da árvore AVL cujo nome começa com o prefixo fornecido de forma recursiva.
- `void avl_tree::listDtNasc(Node *node, const Data& dtInicio, const Data& dtFinal)`: Função auxiliar para listar todas as pessoas da árvore AVL que nasceram em um intervalo de datas de forma recursiva.
- `void avl_tree::listByCity(Node *node, const string& prefixo)`: Função auxiliar para listar todas as pessoas da árvore AVL cuja cidade começa com o prefixo fornecido de forma recursiva.

### Funções de exibição e limpeza

- `void avl_tree::show(Node *raiz, int nivel)`: Função auxiliar para exibir a árvore AVL de forma recursiva.
- `Node* avl_tree::clear(Node *node)`: Função auxiliar para limpar a árvore AVL de forma recursiva.

### Funções de leitura de arquivo

- `template <typename T> Node* avl_tree::lerArquivoCSV(Node *node, const string& nomeArquivo, T compare)`: Função auxiliar para ler um arquivo CSV com informações das pessoas e adicionar os registros na árvore AVL de forma recursiva.
## Pessoa.h

A classe `Pessoa.h` define a estrutura e os métodos da classe `Pessoa`, que representa uma pessoa com informações como nome, sobrenome, CPF, cidade e data de nascimento.

### Estrutura `Data`

A estrutura `Data` representa uma data com dia, mês e ano. É utilizada como parte dos dados da classe `Pessoa`.

```cpp
struct Data {
    int dia;
    int mes;
    int ano;

    // Construtor
    Data(int _dia, int _mes, int _ano)
        : dia(_dia), mes(_mes), ano(_ano) {}
};
```

### Classe `Pessoa`

A classe `Pessoa` representa uma pessoa com os seguintes atributos e métodos:

##### Atributos:

- `cpf` (tipo `long long int`): Armazena o CPF da pessoa.
- `nome` (tipo `std::string`): Armazena o nome da pessoa.
- `sobrenome` (tipo `std::string`): Armazena o sobrenome da pessoa.
- `dt_nascimento` (tipo `Data`): Armazena a data de nascimento da pessoa.
- `cidade` (tipo `std::string`): Armazena a cidade da pessoa.

##### Construtor:

O construtor da classe `Pessoa` é responsável por inicializar os atributos da classe com os valores fornecidos.

```cpp
// Construtor da classe
Pessoa(const std::string& _nome, const std::string& _sobrenome, long long int _cpf, const std::string& _cidade, const Data& _dt_nascimento)
    : nome(_nome), sobrenome(_sobrenome), cpf(_cpf), cidade(_cidade), dt_nascimento(_dt_nascimento) {}
```

##### Métodos:

- `getNome()`: Retorna o nome da pessoa.
- `getSobrenome()`: Retorna o sobrenome da pessoa.
- `getCpf()`: Retorna o CPF da pessoa.
- `getCidade()`: Retorna a cidade da pessoa.
- `getDiaNascimento()`: Retorna o dia de nascimento da pessoa.
- `getMesNascimento()`: Retorna o mês de nascimento da pessoa.
- `getAnoNascimento()`: Retorna o ano de nascimento da pessoa.
- `getDtNascimento()`: Retorna a data de nascimento completa da pessoa.
## Node.h

O arquivo `Node.h` contém a definição da estrutura `Node`, que é utilizada para representar os nós da árvore AVL.

### Estrutura `Node`

A estrutura `Node` possui os seguintes atributos e métodos:

##### Atributos:

- `pessoa` (tipo `Pessoa*`): Armazena um ponteiro para um objeto `Pessoa`, representando os dados do nó.
- `height` (tipo `int`): Armazena a altura do nó na árvore.
- `left` (tipo `Node*`): Ponteiro para o filho esquerdo do nó.
- `right` (tipo `Node*`): Ponteiro para o filho direito do nó.

##### Construtor:

O construtor da estrutura `Node` é responsável por inicializar os atributos da estrutura com os valores fornecidos.

```cpp
// Construtor
Node(Pessoa* pessoa, Node *left = nullptr, Node *right = nullptr, int height = 1)
    : pessoa(pessoa), height(height), left(left), right(right) {}
```
## Comparators.h

A classe `Comparators.h` contém functors (funções objeto) que são usados para comparar objetos da classe `Pessoa` com base em critérios específicos. Esses comparadores são utilizados na classe `avl_tree` para determinar a ordenação dos nós na árvore AVL.

### Comparador de CPFs (`CompareCpf`)

O functor `CompareCpf` é usado para comparar dois objetos `Pessoa` com base em seus CPFs. A comparação é feita utilizando o operador `>`, o que resulta em uma ordenação decrescente com base no CPF. O operador `>` é usado para garantir que o objeto com o CPF maior seja considerado "menor" e, portanto, seja posicionado antes na árvore AVL.

```cpp
struct CompareCpf{
    bool operator()(const Pessoa* a, const Pessoa* b) const {
        return a->getCpf() > b->getCpf();
    }
};
```

### Comparador de Nomes (`CompareNome`)

O functor `CompareNome` é usado para comparar dois objetos `Pessoa` com base em seus nomes completos (nome + sobrenome). A comparação é feita concatenando os nomes completos e utilizando o operador `>`. Isso resulta em uma ordenação alfabética decrescente com base nos nomes completos. O operador `>` é usado para garantir que o objeto com o nome completo "maior" seja considerado "menor" e, portanto, seja posicionado antes na árvore AVL.

```cpp
struct CompareNome{
    bool operator()(const Pessoa* a, const Pessoa* b) const {
        return (a->getNome() + " " + a->getSobrenome()) > (b->getNome() + " " + b->getSobrenome());
    }
};
```

### Comparador de Datas (`CompareData`)

O functor `CompareData` é usado para comparar dois objetos `Pessoa` com base em suas datas de nascimento. A comparação é feita utilizando a função `dataCompare` definida em `auxFuncs.h`, que retorna um valor inteiro indicando se a primeira data é anterior (valor -1), igual (valor 0) ou posterior (valor 1) à segunda data. O operador `== 1` é usado para garantir que o objeto com a data de nascimento posterior seja considerado "menor" e, portanto, seja posicionado antes na árvore AVL.

```cpp
struct CompareData{
    bool operator()(const Pessoa* a, const Pessoa* b) const {
        return dataCompare(a->getDtNascimento(), b->getDtNascimento()) == 1;
    }
};
```

### Comparador de Cidades (`CompareCidade`)

O functor `CompareCidade` é usado para comparar dois objetos `Pessoa` com base em suas cidades. A comparação é feita utilizando o operador `>`, o que resulta em uma ordenação alfabética decrescente com base nas cidades. O operador `>` é usado para garantir que o objeto com a cidade "maior" seja considerado "menor" e, portanto, seja posicionado antes na árvore AVL.

```cpp
struct CompareCidade{
    bool operator()(const Pessoa* a, const Pessoa* b) const {
        return a->getCidade() > b->getCidade();
    }
};
```
## AuxFuncs.h

O arquivo `auxfuncs.h` contém um conjunto de funções auxiliares que são utilizadas em diferentes partes do código. Essas funções realizam tarefas como conversão de dados, formatação e comparação. A seguir, estão as descrições de cada uma dessas funções:

### Função `convertCpf`

```cpp
long long int convertCpf(const std::string& cpf)
```

Esta função converte um CPF no formato "XXX.XXX.XXX-XX" para um valor numérico. Ela recebe uma string `cpf` contendo o CPF no formato especificado e retorna um valor `long long int` representando o CPF numérico correspondente. A função remove os caracteres especiais (pontos e traços) do CPF e converte a string resultante para um valor numérico.

### Função `convertDate`

```cpp
void convertDate(const std::string& data, int& dia, int& mes, int& ano)
```

Esta função converte uma string de data no formato "DD/MM/AAAA" para as variáveis `dia`, `mes` e `ano`. Ela recebe uma string `data` contendo a data no formato especificado e preenche as variáveis `dia`, `mes` e `ano` com os valores correspondentes. A função utiliza a biblioteca `<sstream>` para extrair os valores da string, considerando o delimitador "/" entre os valores.

### Função `formatCPF`

```cpp
void formatCPF(long long int cpf)
```

Esta função formata um CPF numérico no formato "XXX.XXX.XXX-XX" e imprime o resultado na saída padrão. Ela recebe um CPF numérico como argumento e imprime o CPF formatado. A função utiliza a biblioteca `<iomanip>` para garantir que o CPF tenha exatamente 11 dígitos, preenchendo com zeros à esquerda, e realiza a formatação adequada do CPF com pontos e traço.

### Função `stringToLower`

```cpp
std::string stringToLower(const std::string& str)
```

Esta função converte uma string para letras minúsculas. Ela recebe uma string `str` como argumento e retorna uma nova string contendo a versão em letras minúsculas da string original. A função percorre cada caractere da string original e os converte para minúsculas utilizando a função `tolower()`.

### Função `dataCompare`

```cpp
int dataCompare(const Data& data1, const Data& data2)
```

Esta função compara duas datas e retorna um valor inteiro indicando a relação entre elas. Ela recebe duas estruturas `Data` como argumentos, `data1` e `data2`, e compara os campos `dia`, `mes` e `ano` para determinar qual data é maior. A função retorna 1 se `data1` for maior que `data2`, -1 se `data1` for menor que `data2` e 0 se as datas forem iguais.

Essas funções auxiliares são utilizadas em diferentes partes do código para realizar operações específicas, como conversões de formato, formatação de dados e comparações. Ao utilizar essas funções, é possível melhorar a organização e a legibilidade do código, além de facilitar a reutilização dessas funcionalidades em diferentes partes do programa. 
## Main.h

O código adicionado ao arquivo `main.h` inclui funções adicionais para a interação com o usuário, limpeza da tela, exibição do menu e processamento das opções selecionadas. Aqui está a descrição dessas funções:

### Função `clearScreen`

A função `clearScreen` é responsável por limpar a tela do console. Ela detecta o sistema operacional em que o código está sendo executado (Windows ou outro) e chama o comando apropriado para limpar a tela.

### Função `waitForInput`

A função `waitForInput` aguarda a entrada do usuário antes de continuar. Ela exibe uma mensagem solicitando ao usuário para pressionar Enter e espera pela entrada do usuário antes de prosseguir.

### Função `programName`

A função `programName` exibe o nome do programa na tela. É chamada no início da execução do programa e exibe um cabeçalho informativo.

### Função `displayMenu`

A função `displayMenu` exibe o menu de opções para o usuário. Ele mostra as opções disponíveis e solicita que o usuário selecione uma delas.

### Função `main`

A função `main` é a função principal do programa. Ela define as árvores AVL (`cpf`, `nome`, `data` e `cidade`) e os comparadores (`compCpf`, `compNome`, `compData` e `compCidade`). Em seguida, lê os dados de um arquivo CSV usando os comparadores apropriados.

O programa entra em um loop que exibe o menu, lê a opção selecionada pelo usuário e executa a ação correspondente. Cada opção do menu é tratada em um bloco `case` diferente. As opções incluem consultar uma pessoa pelo CPF, consultar pessoas pelo prefixo do nome, consultar pessoas pelo intervalo de data de nascimento, filtrar pessoas pela cidade, mostrar listas de pessoas ordenadas por CPF, nome, data de nascimento e cidade, adicionar uma pessoa e sair do programa.

Depois que a opção é tratada, o programa aguarda a entrada do usuário antes de continuar. Ao selecionar a opção 0 para sair do programa, as árvores são limpas e o programa é encerrado.
## Autor

- [@IgrGabriel](https://www.github.com/IgrGabriel)


## Licença

[MIT](https://choosealicense.com/licenses/mit/)

