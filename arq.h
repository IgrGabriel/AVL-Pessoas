#ifndef ARQ_H
#define ARQ_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "node.h"
#include "avl.h"

using namespace std;

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

void converterData(const string& data, int& dia, int& mes, int& ano) {
    stringstream ss(data);
    char delimiter;
    ss >> mes >> delimiter >> dia >> delimiter >> ano;
}

Node* lerArquivoCSV(Node *node, const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);

    if (arquivo.is_open()) {
        string linha;
        getline(arquivo, linha); // Ignora a primeira linha (cabeçalho)

        while (getline(arquivo, linha)) {
            istringstream linhaStream(linha);
            string cpf, dt_nasc, cidade, nome, sobrenome;
            int dia, mes, ano;
            Pessoa *p;

            getline(linhaStream, cpf, ',');
            long long int cpflong = converteCpf(cpf);

            getline(linhaStream, nome, ',');
            getline(linhaStream, sobrenome, ',');

            getline(linhaStream, dt_nasc, ',');
            converterData(dt_nasc, dia, mes, ano);

            getline(linhaStream, cidade, ',');

            p = new Pessoa(nome, sobrenome, cpflong, cidade, {dia, mes, ano});

            node = addData(node, p);
        }
        arquivo.close();
    } else {
        cerr << "Não foi possível abrir o arquivo." << endl;
    }

    return node;
}

#endif