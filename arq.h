#ifndef ARQ_H
#define ARQ_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "node.h"
#include "avl.h"
#include "pessoa.h"
#include "auxFuncs.h"

using namespace std;

// Funcao publica para ler o arquivo CSV
template <typename T>
void avl_tree::lerArquivoCSV(const string& nomeArquivo, T compare){
    root = lerArquivoCSV(root, nomeArquivo, compare);
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
            long long int cpflong = convertCpf(cpf);

            getline(linhaStream, nome, ',');
            getline(linhaStream, sobrenome, ',');

            getline(linhaStream, dt_nasc, ',');
            convertDate(dt_nasc, mes, dia, ano);

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