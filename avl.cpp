#include <iostream>
#include "node.h"
#include "avl.h"
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// retorna a altura do node.
// se a arvore for vazia ela tem altura 0
// caso contrario, retorna o valor que esta no campo height
int avl_tree::height(Node *node) {
    return (node == nullptr) ? 0 : node->height; 
}


// Atualiza o altura de um node
// O node recebe a maior altura entre a subarvore da esquerda e da direita + 1
int avl_tree::updateHeight(Node* node) {
    return node->height = max(height(node->left), height(node->right)) + 1;
}


// Calcula o fator de balanceamento de um node
int avl_tree::balance(Node *node) {
    return node ? height(node->left) - height(node->right) : 0;
}


// Rotacao a esquerda para balancear a arvore
Node* avl_tree::leftRotation(Node *p) {
    Node *u = p->right;
    p->right = u->left;
    u->left = p;
    // recalcular as alturas de p e de u
    updateHeight(p);
    updateHeight(u);

    return u;
}


// Rotacao a direita para balancear a arvore
Node* avl_tree::rightRotation(Node *p) {
    Node *u = p->left;
    p->left = u->right;
    u->right = p;
    // recalcular as alturas de p e de u
    updateHeight(p);
    updateHeight(u);

    return u;
}


// Rotacao direita esquerda
Node* avl_tree::rightLeftRotation(Node *p){
    p->right = rightRotation(p->right);
    return leftRotation(p);
}


// Rotacao esquerda direita
Node* avl_tree::leftRightRotation(Node *p){
    p->left = leftRotation(p->left);
    return rightRotation(p);
}


// Funcao para realizar o balanceamento da arvore apos uma insercao ou remorcao
// Recebe o node que esta desbalanceado e retorna a nova raiz apos o balanceamento
Node* avl_tree::rebalance(Node *node){
    // calcula o balanceamento de p
    int bal = balance(node);

    // Rotacao a esquerda
    if(bal < -1 && balance(node->right) <= 0)
        node = leftRotation(node);

    // Rotacao a direita
    else if(bal > 1 && balance(node->left) >= 0)
        node = rightRotation(node);

    // Rotacao dupla a esquerda
    else if(bal > 1 && balance(node->left) < 0)
        node = leftRightRotation(node);

    // Rotacao dupla direita
    if(bal < -1 && balance(node->right) > 0)
        node = rightLeftRotation(node);

    return node;
}


// add com chave para o cpf
Node* avl_tree::addCpf(Node *node, Pessoa *pessoa) {
    if (node == nullptr)
        return new Node(pessoa);
    else{ // insercao a direita ou a esquerda
        if(pessoa->cpf == node->pessoa->cpf)
            return node;
        if(pessoa->cpf > node->pessoa->cpf)
            node->right = addCpf(node->right, pessoa);
        else
            node->left = addCpf(node->left, pessoa);
    }

    // recalcula a altura de todos os nodes entre a raiz e o novo no inserido
    node->height = max(height(node->left), height(node->right)) + 1;

    // verificar a necessidade de rebalancear a arvore
    node = rebalance(node);

    return node;
}

// adicionar uma pessoa a arvore usando o nome como chave
// TODO: Considerar a possibilidade de nomes duplicados
// TODO: Considerar o sobrenome na busca (Nome Completo)
Node* avl_tree::addNome(Node *node, Pessoa *pessoa) {
    if (node == nullptr)
        return new Node(pessoa);
    else{ // insercao a direita ou a esquerda
        if(pessoa->nome == node->pessoa->nome)
            return node;
        if(pessoa->nome > node->pessoa->nome)
            node->right = addNome(node->right, pessoa);
        else
            node->left = addNome(node->left, pessoa);
    }

    // recalcula a altura de todos os nodes entre a raiz e o novo no inserido
    node->height = max(height(node->left), height(node->right)) + 1;

    // verificar a necessidade de rebalancear a arvore
    node = rebalance(node);

    return node;
}


// Funcao auxiliar que recebe duas dadas e retorna true se a primeira for maior que a segunda
bool dataCompare(const Data& data1, const Data& data2) {
    if(data1.ano > data2.ano)
        return true;
    else if(data1.ano < data2.ano)
        return false;
    else {
        if(data1.mes > data2.mes)
            return true;
        else if(data1.mes < data2.mes)
            return false;
        else {
            if(data1.dia > data2.dia)
                return true;
            else
                return false;
        }
    }
}


// Compara duas datas e retorna 1 se a primeira for maior que a segunda, -1 se a primeira for menor que a segunda e 0 se forem iguais
int dataCompare2(const Data& data1, const Data& data2) {
    if(data1.ano > data2.ano) 
        return 1; 
    else if(data1.ano < data2.ano) 
        return -1;
    else {
        if(data1.mes > data2.mes)
            return 1;
        else if(data1.mes < data2.mes)
            return -1;
        else {
            if(data1.dia > data2.dia)
                return 1;
            else if(data1.dia < data2.dia)
                return -1;
            else
                return 0;
        }
    }
    
}

void avl_tree::add(Pessoa *pessoa) {
    root = addData(root, pessoa);
}

// adicionar uma pessoa a arvore usando a data de nascimento como chave
Node* avl_tree::addData(Node *node, Pessoa *pessoa) {
    if (node == nullptr)
        return new Node(pessoa);

    // Compara se a primeira data eh maior que a segunda
    if(dataCompare(pessoa->dt_nascimento, node->pessoa->dt_nascimento))
        node->right = addData(node->right, pessoa);
    else if(dataCompare(node->pessoa->dt_nascimento, pessoa->dt_nascimento))
        node->left = addData(node->left, pessoa);
    else // A pessoa tem a mesma data de nascimento, pode ser inserida #TODO: Comparar CPF
        node->left = addData(node->left, pessoa);

    // recalcula a altura de todos os nodes entre a raiz e o novo no inserido
    node->height = max(height(node->left), height(node->right)) + 1;

    // verificar a necessidade de rebalancear a arvore
    node = rebalance(node);

    return node;
}


// Remover uma pessoa da arvore usando o cpf com chave
Node* avl_tree::remove(Node *node, int cpf) {
    if(node == nullptr) // Node nao encontrado
        return nullptr;
    else { // procura o node a remover
        if(node->pessoa->cpf == cpf){
            // remover node folhas (node sem filhos)
            if(node->right == nullptr && node->left == nullptr){
                delete node;
                return nullptr;
            } else { // remove node com filhos
                // remover node com 2 filhos
                if(node->right != nullptr && node->left != nullptr){
                    Node *aux = node->left;
                    while(aux->right != nullptr)
                        aux = aux->right;
                    node->pessoa->cpf = aux->pessoa->cpf;
                    aux->pessoa->cpf = cpf;
                    node->left = remove(node->left, cpf);
                    return node;
                } 
                else {
                    // remover nodes que possuem apenas 1 filho
                    Node *aux;
                    if(node->right != nullptr)
                        aux = node->right;
                    else
                        aux = node->left;
                    delete node;
                    return aux;
                }
            }
        } else {
            if(cpf > node->pessoa->cpf) 
                node->right = remove(node->right, cpf);
            else
                node->left = remove(node->left, cpf);
        }
        
        // recalcula a altur de todos os nodes entre a raiz e o novo node inserido
        node->height = max(height(node->left), height(node->right)) + 1;

        // verifica a necessidade de rebalancear a arvore
        node = rebalance(node);

        return node;
    }
}


// Consulta uma unica pessoa na arvore pelo seu cpf e exibe os dados na tela
Node* avl_tree::searchByCPF(Node *node, long long int cpf) {
    if(node == nullptr) // arvore vazia
        return nullptr;
    else {  // procurar o cpf na arvore

        if(cpf == node->pessoa->cpf) // CPF encontrado
            return node;
        else if(cpf >  node->pessoa->cpf)
            return searchByCPF(node->right, cpf);
        else
            return searchByCPF(node->left, cpf);
        
        return node;

    }
}


// Consulta todas as pessoa cujo nome comece com uma string informada pelo uduario
// E exibe todos os dados dessas pessoas na forma de lista
void avl_tree::listByName(Node *node, const string& prefixo) {
    if(node == nullptr) // arvore vazia
        return;
    
    if(node->pessoa->nome.compare(0, prefixo.length(), prefixo) == 0) {
        cout << node->pessoa->nome << " " << node->pessoa->sobrenome;
        cout << " - " << node->pessoa->cpf; 
        cout << " - " << node->pessoa->cidade;
        cout << " - " << node->pessoa->dt_nascimento.dia << "/" << node->pessoa->dt_nascimento.mes << "/" << node->pessoa->dt_nascimento.ano << endl;
    }    

    listByName(node->left, prefixo);
    listByName(node->right, prefixo);
}


// Consulta todas as pessoas cuja a data de nascimento esteja em um intervalo estabelecido pelo usuario
// E exibe todos os dados dessas pessoas na forma de lista
void avl_tree::listIntervaloDtNascimento(Node *node, const Data& dtInicio, const Data& dtFinal){
    if(node == nullptr) // arvore vazia
        return;
    
    // verifica se a data de nascimento do no esta dentro do intervalo
    if(dataCompare2(dtInicio, node->pessoa->dt_nascimento) <= 0 && dataCompare2(dtFinal, node->pessoa->dt_nascimento) >= 0){
        cout << node->pessoa->nome << " " << node->pessoa->sobrenome;
        cout << " - " << node->pessoa->cpf; 
        cout << " - " << node->pessoa->cidade;
        cout << " - " << node->pessoa->dt_nascimento.dia << "/" << node->pessoa->dt_nascimento.mes << "/" << node->pessoa->dt_nascimento.ano << endl;
    }
    
    // verifica se o node esquerdo esta dentro do intervalo
    listIntervaloDtNascimento(node->left, dtInicio, dtFinal);

    // verifica se o node direito esta dentro do intervalo
    listIntervaloDtNascimento(node->right, dtInicio, dtFinal);
}


// Funcao publica para imprimir a arvore
void avl_tree::show(){
    show(root, 1);
}


// Imprime os dados de uma pessoa na tela
void avl_tree::imprimirPessoa(Pessoa *pessoa) {
    cout << pessoa->nome << " " << pessoa->sobrenome;
    cout << " - " << pessoa->cpf; 
    cout << " - " << pessoa->cidade;
    cout << " - " << pessoa->dt_nascimento.dia << "/" << pessoa->dt_nascimento.mes << "/" << pessoa->dt_nascimento.ano << endl;
}


// Imprime a arvore de pessoas em forma de lista
void avl_tree::show(Node *raiz, int nivel) {
    int i;
    if(raiz) {
        show(raiz->right, nivel + 1);
        imprimirPessoa(raiz->pessoa);
        show(raiz->left, nivel + 1);
    }
}


void avl_tree::clear() {
    root = clear(root);
}


Node *avl_tree::clear(Node *node) {
    if(node != nullptr) {
        node->left = clear(node->left);
        node->right = clear(node->right);
        delete node;
    }
    return nullptr;
}


avl_tree::~avl_tree() {
    clear();
}


// -------------------- Arquivo CSV --------------------

// Funcao publica para ler o arquivo CSV
void avl_tree::lerArquivoCSV(const string& nomeArquivo){
    root = lerArquivoCSV(root, nomeArquivo);
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
Node* avl_tree::lerArquivoCSV(Node *node, const string& nomeArquivo) {
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


int main() {
    avl_tree t;

    string nomeArquivo = "data.csv";
    t.lerArquivoCSV(nomeArquivo);

    t.show();

    return 0;
}
