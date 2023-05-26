#ifndef NODE_H
#define NODE_H

#include "pessoa.h"

using namespace std;

struct Node {
    Pessoa* pessoa;
    int height;
    Node *left, *right;

    // Construtor
    Node(Pessoa* pessoa, Node *left = nullptr, Node *right = nullptr, int height = 1): pessoa(pessoa), height(height), left(left), right(right) {}
};

#endif