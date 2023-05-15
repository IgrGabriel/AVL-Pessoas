#ifndef NODE_H
#define NODE_H
#include <string>

using namespace std;

struct Data {
    int dia;
    int mes;
    int ano;

    // Construtor
    Data(int _dia, int _mes, int _ano)
        : dia(_dia), mes(_mes), ano(_ano) {}
};


struct Pessoa {
    long long int cpf;
    string nome;
    string sobrenome;
    Data dt_nascimento;
    string cidade;

    // Contrutor
    Pessoa(const string& _nome, const string& _sobrenome, long long int _cpf, const string& _cidade, const Data& _dt_nascimento)
        : nome(_nome), sobrenome(_sobrenome), cpf(_cpf), cidade(_cidade), dt_nascimento(_dt_nascimento) {}
};

struct Node {
    Pessoa *pessoa;
    int height;
    Node *left, *right;

    // Construtor
    Node(Pessoa *pessoa, Node *left = nullptr, Node *right = nullptr, int height = 1): pessoa(pessoa), height(height), left(left), right(right) {}
};

#endif