#ifndef ARQ_H
#define ARQ_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "node.h"
#include "avl.h"
#include "pessoa.h"

using namespace std;

// Funcao publica para ler o arquivo CSV
template <typename T>
void avl_tree::lerArquivoCSV(const string& nomeArquivo, T compare){
    root = lerArquivoCSV(root, nomeArquivo, compare);
}


// converte um cpf no formato XXX.XXX.XXX-XX para um valor numerico
long long int converteCpf(const string& cpf) {
    string cpfNumerico;

    // Remove os caracteres especiais
    for (char c : cpf) {
        if (isdigit(c)) {
            cpfNumerico += c;
        }
    }

    // Converte a string para long long int
    stringstream ss(cpfNumerico);
    long long int cpfInt;
    ss >> cpfInt;

    return cpfInt;
}


// converte uma string no formato MM/DD/AAAA para as variaveis dia, mes e ano
void converterData(const string& data, int& dia, int& mes, int& ano) {
    stringstream ss(data);
    char delimiter;
    ss >> mes >> delimiter >> dia >> delimiter >> ano;
}


// ler os dados de um arquivo CSV e adiciona os dados na arvore
template <typename T>
Node* avl_tree::lerArquivoCSV(Node *node, const string& nomeArquivo, T compare) {
    ifstream arquivo(nomeArquivo);

    if (arquivo.is_open()) {
        string linha;
        getline(arquivo, linha); // Ignora a primeira linha (cabeçalho)

        while (getline(arquivo, linha)) {
            istringstream linhaStream(linha);
            string cpf, dt_nasc, cidade, nome, sobrenome;
            int dia, mes, ano;
            Pessoa* p;

            getline(linhaStream, cpf, ',');
            long long int cpflong = converteCpf(cpf);

            getline(linhaStream, nome, ',');
            getline(linhaStream, sobrenome, ',');

            getline(linhaStream, dt_nasc, ',');
            converterData(dt_nasc, dia, mes, ano);

            getline(linhaStream, cidade, ',');

            p = new Pessoa(nome, sobrenome, cpflong, cidade, {dia, mes, ano});

            node = add(node, p, compare);
        }
        arquivo.close();
    } else {
        cerr << "Não foi possível abrir o arquivo." << endl;
    }

    return node;
}

#endif