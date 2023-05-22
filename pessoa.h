#ifndef PESSOA_H
#define PESSOA_H

#include <string>
#include "node.h"

struct Data {
    int dia;
    int mes;
    int ano;

    // Construtor
    Data(int _dia, int _mes, int _ano)
        : dia(_dia), mes(_mes), ano(_ano) {}
};


class Pessoa {
public:
    // Construtor da classe
    Pessoa(const std::string& _nome, const std::string& _sobrenome, long long int _cpf, const std::string& _cidade, const Data& _dt_nascimento)
        : nome(_nome), sobrenome(_sobrenome), cpf(_cpf), cidade(_cidade), dt_nascimento(_dt_nascimento) {}


    // Getters
    std::string getNome() const {
        return nome;
    }

    std::string getSobrenome() const {
        return sobrenome;
    }

    long long int getCpf() const {
        return cpf;
    }

    std::string getCidade() const {
        return cidade;
    }

    int getDiaNascimento() const {
        return dt_nascimento.dia;
    }

    int getMesNascimento() const {
        return dt_nascimento.mes;
    }

    int getAnoNascimento() const {
        return dt_nascimento.ano;
    }

    Data getDtNascimento() const {
        return dt_nascimento;
    }

private:
    long long int cpf;
    std::string nome;
    std::string sobrenome;
    Data dt_nascimento;
    std::string cidade;
};

#endif