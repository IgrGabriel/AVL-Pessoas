#ifndef AVL_H
#define AVL_H

#include "node.h"

// Classe para árvore AVL
class avl_tree {
public:
    avl_tree() = default;

    // Funções de adição para diferentes critérios de ordenação
    void addCpf(Pessoa *pessoa);
    void addNome(Pessoa *pessoa);
    void addData(Pessoa *pessoa);
    void addCidade(Pessoa *pessoa);

    // Funções de busca
    void searchByCPF(long long int cpf);
    void listByName(const string& prefixo);
    void listDtNasc(const Data& dtInicio, const Data& dtFinal);
    void listByCity(const string& prefixo);

    // Funções de exibição e limpeza da árvore
    void show();
    void clear();
    ~avl_tree();

    // Função para ler dados de um arquivo CSV
    template <typename T>
    void lerArquivoCSV(const string& nomeArquivo, T compare);

private:
    Node *root {nullptr}; // Ponteiro para a raiz da árvore

    // Funções auxiliares para balanceamento e rotações
    int height(Node *node);
    int updateHeight(Node* node);
    int balance(Node *node);
    Node* rightRotation(Node *p);
    Node* leftRotation(Node *p);
    Node* rightLeftRotation(Node *p);
    Node* leftRightRotation(Node *p);
    Node* rebalance(Node *node);

    // Funções auxiliares para adicionar, buscar e listar
    template <typename T>
    Node* add(Node *node, Pessoa *pessoa, T comparator);
    Node* searchByCPF(Node *node, long long int cpf);
    void listByName(Node *node, const string& prefixo);
    void listDtNasc(Node *node, const Data& dtInicio, const Data& dtFinal);
    void listByCity(Node *node, const string& prefixo);

    // Funções auxiliares para exibir e limpar a árvore
    void show(Node *raiz, int nivel);
    void showPessoa(Pessoa *pessoa);
    void listPessoas(Node *node);
    Node* clear(Node *node);

    // Função auxiliar para ler dados de um arquivo CSV
    template <typename T>
    Node* lerArquivoCSV(Node *node, const string& nomeArquivo, T compare);
};

#endif