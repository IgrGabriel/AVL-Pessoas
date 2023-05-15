#ifndef AVL_H
#define AVL_H

#include "node.h"


class avl_tree {
public:
    avl_tree() = default;
    void add(Pessoa *pessoa);
    void remove(int cpf);
    void show();
    void clear();
    ~avl_tree();

    void lerArquivoCSV(const string& nomeArquivo);

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

    Node* addCpf(Node *node, Pessoa *pessoa);
    Node* addNome(Node *node, Pessoa *pessoa);
    Node* addData(Node *node, Pessoa *pessoa);

    Node* remove(Node *node, int cpf);

    Node* searchByCPF(Node *node, long long int cpf);
    void listByName(Node *node, const string& prefixo);
    void listIntervaloDtNascimento(Node *node, const Data& dtInicio, const Data& dtFinal);

    void imprimirPessoa(Pessoa *pessoa);
    void show(Node *raiz, int nivel);

    Node* clear(Node *node);

    Node* lerArquivoCSV(Node *node, const string& nomeArquivo);
};

#endif