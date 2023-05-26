#ifndef COMPARATORS_H
#define COMPARATORS_H

#include "pessoa.h"
#include "auxFuncs.h"

using namespace std;

// Functor para comparar CPFs
struct CompareCpf{
    bool operator()(const Pessoa* a, const Pessoa* b) const {
        return a->getCpf() > b->getCpf();
    }
};


// Functor para comparar Nomes
// Considera o nome completo(nome + sobrenome)
struct CompareNome{
    bool operator()(const Pessoa* a, const Pessoa* b) const {
        return (a->getNome() + " " + a->getSobrenome()) > (b->getNome()+ " " + b->getSobrenome());
    }
};


// Functor para comparar Datas
struct CompareData{
    bool operator()(const Pessoa* a, const Pessoa* b) const {
        return dataCompare(a->getDtNascimento(), b->getDtNascimento()) == 1;
    }
};

// Functor para comparar Datas
struct CompareCidade{
    bool operator()(const Pessoa* a, const Pessoa* b) const {
        return  a.getCidade() > b.getCidade();
    }
};

#endif