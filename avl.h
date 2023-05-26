#ifndef AVL_H
#define AVL_H

#include "node.h"


class avl_tree {
public:
    avl_tree() = default;

    void addCpf(Pessoa *pessoa);
    void addNome(Pessoa *pessoa);
    void addData(Pessoa *pessoa);

    void searchByCPF(long long int cpf);
    void listByName(const string& prefixo);
    void listDtNasc(const Data& dtInicio, const Data& dtFinal);

    void show();
    void clear();
    ~avl_tree();

    template <typename T>
    void lerArquivoCSV(const string& nomeArquivo, T compare);

private:
    Node *root {nullptr};

    int height(Node *node);
    int updateHeight(Node* node);
    int balance(Node *node);

    Node* rightRotation(Node *p);
    Node* leftRotation(Node *p);
    Node* rightLeftRotation(Node *p);
    Node* leftRightRotation(Node *p);
    Node* rebalance(Node *node);

    template <typename T>
    Node* add(Node *node, Pessoa *pessoa, T comparator);

    Node* searchByCPF(Node *node, long long int cpf);
    void listByName(Node *node, const string& prefixo);
    void listDtNasc(Node *node, const Data& dtInicio, const Data& dtFinal);

    void show(Node *raiz, int nivel);
    void showPessoa(Pessoa *pessoa);
    void listPessoas(Node *node);

    Node* clear(Node *node);

    template <typename T>
    Node* lerArquivoCSV(Node *node, const string& nomeArquivo, T compare);
};

#endif