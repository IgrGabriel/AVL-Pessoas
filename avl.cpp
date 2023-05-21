#include <iostream>
#include "node.h"
#include "avl.h"
#include <fstream>
#include <string>
#include <sstream>

#include <iomanip> // Para std::setfill() e std::setw()
#include <cctype> // Para std::tolower()

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


// Compara duas datas e retorna 1 se a primeira for maior que a segunda, -1 se a primeira for menor que a segunda e 0 se forem iguais
int dataCompare(const Data& data1, const Data& data2) {
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


// Functor para comparar CPFs
struct CompareCpf{
    bool operator()(const Pessoa* a, const Pessoa* b) const {
        return a->getCpf() > b->getCpf();
    }
};


// #TODO: Considerar o nome completo(nome + sobrenome)
// #TODO: Tratar o quando houver a add de nomes iguais
// Functor para comparar Nomes
struct CompareNome{
    bool operator()(const Pessoa* a, const Pessoa* b) const {
        return a->getNome() > b->getNome();
    }
};


// Functor para comparar Datas
struct CompareData{
    bool operator()(const Pessoa* a, const Pessoa* b) const {
        return dataCompare(a->getDtNascimento(), b->getDtNascimento()) == 1;
    }
};


// Funcao generica add
template <typename T>
Node* avl_tree::add(Node *node, Pessoa *pessoa, T comparator) {
    if (node == nullptr)
        return new Node(pessoa);
    else {
        if (comparator(pessoa, node->pessoa))
            node->right = add(node->right, pessoa, comparator);
        else
            node->left = add(node->left, pessoa, comparator);
    }

    // recalcula a altura de todos os nodes entre a raiz e o novo no inserido
    node->height = max(height(node->left), height(node->right)) + 1;

    // verificar a necessidade de rebalancear a arvore
    node = rebalance(node);

    return node;
}


void avl_tree::addCpf(Pessoa *pessoa) {
    CompareCpf compCpf;
    root = add(root, pessoa, compCpf);
}
void avl_tree::addNome(Pessoa *pessoa) {
    CompareNome compNome;
    root = add(root, pessoa, compNome);
}
void avl_tree::addData(Pessoa *pessoa) {
    CompareData compData;
    root = add(root, pessoa, compData);
}


// Remover uma pessoa da arvore usando o cpf com chave
// Node* avl_tree::remove(Node *node, int cpf) {
//     if(node == nullptr) // Node nao encontrado
//         return nullptr;
//     else { // procura o node a remover
//         if(node->pessoa->cpf == cpf){
//             // remover node folhas (node sem filhos)
//             if(node->right == nullptr && node->left == nullptr){
//                 delete node;
//                 return nullptr;
//             } else { // remove node com filhos
//                 // remover node com 2 filhos
//                 if(node->right != nullptr && node->left != nullptr){
//                     Node *aux = node->left;
//                     while(aux->right != nullptr)
//                         aux = aux->right;
//                     node->pessoa->cpf = aux->pessoa->cpf;
//                     aux->pessoa->cpf = cpf;
//                     node->left = remove(node->left, cpf);
//                     return node;
//                 } 
//                 else {
//                     // remover nodes que possuem apenas 1 filho
//                     Node *aux;
//                     if(node->right != nullptr)
//                         aux = node->right;
//                     else
//                         aux = node->left;
//                     delete node;
//                     return aux;
//                 }
//             }
//         } else {
//             if(cpf > node->pessoa->cpf) 
//                 node->right = remove(node->right, cpf);
//             else
//                 node->left = remove(node->left, cpf);
//         }
        
//         // recalcula a altur de todos os nodes entre a raiz e o novo node inserido
//         node->height = max(height(node->left), height(node->right)) + 1;

//         // verifica a necessidade de rebalancear a arvore
//         node = rebalance(node);

//         return node;
//     }
// }


// funcao publica para buscar uma pessoa na arvore pelo seu cpf
void avl_tree::searchByCPF(long long int cpf) {
    Node* node = searchByCPF(root, cpf);
    showPerson(node);
}


// Consulta uma unica pessoa na arvore pelo seu cpf e exibe os dados na tela
Node* avl_tree::searchByCPF(Node *node, long long int cpf) {
    if(node == nullptr) // arvore vazia
        return nullptr;
    else {  // procurar o cpf na arvore

        if(cpf == node->pessoa->getCpf()) // CPF encontrado
            return node;
        else if(cpf >  node->pessoa->getCpf())
            return searchByCPF(node->right, cpf);
        else
            return searchByCPF(node->left, cpf);
        
        return node;
    }
}


// Funcao auxiliar para converter uma string em minuslas
// Usada na funcao listByName
string stringToLower(const string& str){
    string lowerStr = str;

    for(char& c : lowerStr)
        c = tolower(c);
    
    return lowerStr;
}


// funcao publica para consultar todas as pessoas cujo nome comece com uma string informada pelo usuario
void avl_tree::listByName(const string& prefixo){
    listByName(root, prefixo);
}


// Consulta todas as pessoa cujo nome comece com uma string informada pelo uduario
// E exibe todos os dados dessas pessoas na forma de lista
void avl_tree::listByName(Node *node, const string& prefixo) {
    if(node == nullptr) // arvore vazia
        return;

    string completeName = stringToLower(node->pessoa->getNome() + " " + node->pessoa->getSobrenome());
    string lowerPrefix = stringToLower(prefixo);
    
    if(completeName.compare(0, prefixo.length(), lowerPrefix) == 0) {
        showPerson(node);
        cout << "\n" << endl;
    }    

    listByName(node->left, prefixo);
    listByName(node->right, prefixo);
}


// funcao publica para consultar todas as pessoas cujo data de nascimento esteja em um intervalo estabelecido pelo usuario
void avl_tree::listDtNasc(const Data& dtInicio, const Data& dtFinal){
    listDtNasc(root, dtInicio, dtFinal);
}


// Consulta todas as pessoas cuja a data de nascimento esteja em um intervalo estabelecido pelo usuario
// E exibe todos os dados dessas pessoas na forma de lista
void avl_tree::listDtNasc(Node *node, const Data& dtInicio, const Data& dtFinal){
    if(node == nullptr) // arvore vazia
        return;
    
    // verifica se a data de nascimento do no esta dentro do intervalo
    if(dataCompare(dtInicio, node->pessoa->getDtNascimento()) <= 0 && dataCompare(dtFinal, node->pessoa->getDtNascimento()) >= 0){
        showPerson(node);
        cout << "\n" << endl;
    }
    
    // verifica se o node esquerdo esta dentro do intervalo
    listDtNasc(node->left, dtInicio, dtFinal);

    // verifica se o node direito esta dentro do intervalo
    listDtNasc(node->right, dtInicio, dtFinal);
}


// Funcao publica para imprimir a arvore
void avl_tree::show(){
    show(root, 1);
}


// #TODO: Tratar quando CPF tiver menos que 11 digitos (add 0's na frente do cpf)
void imprimirCPF(long long int cpf) {
    string cpfStr = to_string(cpf);

    // if (cpfStr.length() != 11) {
    //     std::cout << "CPF inválido!" << std::endl;
    //     return;
    // }

    cout << cpfStr.substr(0, 3) << ".";
    cout << cpfStr.substr(3, 3) << ".";
    cout << cpfStr.substr(6, 3) << "-";
    cout << cpfStr.substr(9, 2);
}


// Imprime os dados de uma pessoa na tela
void avl_tree::imprimirPessoa(Pessoa *pessoa) {
    cout << pessoa->getNome() << " " << pessoa->getSobrenome();

    cout << " - ";
    imprimirCPF(pessoa->getCpf());
    
    cout << " - " << pessoa->getCidade();
    cout << " - " << setfill('0') << setw(2) << pessoa->getDiaNascimento() << "/" 
                << setfill('0') << setw(2) << pessoa->getMesNascimento() << "/" 
                << setfill('0') << setw(2) << pessoa->getAnoNascimento() << endl;
}


void avl_tree::showPerson(Node *node) {
    if(node == nullptr)
        cout << "Pessoa nao encontrada" << endl;
    else{
        cout << "Nome Completo: " << node->pessoa->getNome() << " " << node->pessoa->getSobrenome() << endl;

        cout << "Numero de CPF: ";
        imprimirCPF(node->pessoa->getCpf()); 
        cout << "" << endl; 

        cout << "Cidade: " << node->pessoa->getCidade() << endl;

        cout << "Data nascimento: " 
                    << setfill('0') << setw(2) << node->pessoa->getDiaNascimento() << "/" 
                    << setfill('0') << setw(2) << node->pessoa->getMesNascimento() << "/" 
                    << setfill('0') << setw(2) << node->pessoa->getAnoNascimento() << endl;
    }
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


int main() {
    avl_tree cpf, nome, data;

    CompareCpf compCpf;
    CompareNome compNome;
    CompareData compData;

    cout << "---------------------------- CPF ----------------------------\n" << endl;

    string nomeArquivo = "data.csv";
    cpf.lerArquivoCSV(nomeArquivo, compCpf);
    cpf.addCpf(new Pessoa("Igor", "Gabriel", 62545698702, "Baturite", {10, 9, 2001}));
    cpf.show();

    cout << "\n>> Busca por CPF: \n" << endl;
    cpf.searchByCPF(71537946897);

    cout << "\n---------------------------- Nome ----------------------------\n" << endl;

    nome.lerArquivoCSV(nomeArquivo, compNome);
    nome.addNome(new Pessoa("Igor", "Gabriel", 62545698702, "Baturite", {10, 9, 2001}));
    nome.show();

    cout << "\n>> Busca por Nome: \n" << endl;
    nome.listByName("carlos CORREIA");

    cout << "\n---------------------------- Data ----------------------------\n" << endl;

    data.lerArquivoCSV(nomeArquivo, compData);
    data.addData(new Pessoa("Igor", "Gabriel", 62545698702, "Baturite", {10, 9, 2001}));
    data.show();

    cout << "\n>> Busca por Data: \n" << endl;
    data.listDtNasc({15, 3, 1946}, {2, 7, 1956});

    cpf.clear();
    nome.clear();
    data.clear();

    return 0;
}
