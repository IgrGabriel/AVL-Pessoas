#include <iostream>

#include "node.h"
#include "avl.h"
#include "arq.h"
#include "comparators.h"
#include "auxFuncs.h"

#include <iomanip> // Para std::setfill() e std::setw()
#include <cctype> // Para std::tolower()

#include <string>

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

// funcao publica para buscar uma pessoa na arvore pelo seu cpf
void avl_tree::searchByCPF(long long int cpf) {
    listPessoas(searchByCPF(root, cpf));
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
        listPessoas(node);
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
        listPessoas(node);
        cout << "\n" << endl;
    }
    
    // verifica se o node esquerdo esta dentro do intervalo
    listDtNasc(node->left, dtInicio, dtFinal);

    // verifica se o node direito esta dentro do intervalo
    listDtNasc(node->right, dtInicio, dtFinal);
}


// Imprime os dados de uma pessoa na tela
void avl_tree::showPessoa(Pessoa *pessoa) {
    cout << pessoa->getNome() << " " << pessoa->getSobrenome();

    cout << " - ";
    formatCPF(pessoa->getCpf());
    
    cout << " - " << pessoa->getCidade();
    cout << " - " << setfill('0') << setw(2) << pessoa->getDiaNascimento() << "/" 
                << setfill('0') << setw(2) << pessoa->getMesNascimento() << "/" 
                << setfill('0') << setw(2) << pessoa->getAnoNascimento() << endl;
}


void avl_tree::listPessoas(Node *node) {
    if(node == nullptr)
        cout << "Pessoa nao encontrada" << endl;
    else{
        cout << "Nome Completo: " << node->pessoa->getNome() << " " << node->pessoa->getSobrenome() << endl;

        cout << "Numero de CPF: ";
        formatCPF(node->pessoa->getCpf()); 
        cout << "" << endl; 

        cout << "Cidade: " << node->pessoa->getCidade() << endl;

        cout << "Data nascimento: " 
                    << setfill('0') << setw(2) << node->pessoa->getDiaNascimento() << "/" 
                    << setfill('0') << setw(2) << node->pessoa->getMesNascimento() << "/" 
                    << setfill('0') << setw(2) << node->pessoa->getAnoNascimento() << endl;
    }
}


// Funcao publica para imprimir a arvore
void avl_tree::show(){
    show(root, 1);
}

// Imprime a arvore de pessoas em forma de lista
void avl_tree::show(Node *raiz, int nivel) {
    int i;
    if(raiz) {
        show(raiz->right, nivel + 1);
        showPessoa(raiz->pessoa);
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


int main() {
    avl_tree cpf, nome, data;

    CompareCpf compCpf;
    CompareNome compNome;
    CompareData compData;

    string nomeArquivo = "data.csv";
    
    cpf.lerArquivoCSV(nomeArquivo, compCpf);
    data.lerArquivoCSV(nomeArquivo, compData);
    nome.lerArquivoCSV(nomeArquivo, compNome);
    
    string prefixo, dataInicial, dataFinal, name, sobrenome, cidade, dataNascimento;
    int dia, mes, ano, dia1, mes1, ano1, dia2, mes2, ano2;
    long long int num_cpf;

    int opcao;
    do {
        cout << "Selecione uma opção:" <<endl;
        cout << "1. Consultar uma pessoa pelo CPF" << endl;
        cout << "2. Consultar pessoas pelo prefixo do nome" << endl;
        cout << "3. Consultar pessoas pelo intervalo de data de nascimento" << endl;
        cout << "4. Mostrar lista de pessoas ordenadas pelo CPF" << endl;
        cout << "5. Mostrar lista de pessoas ordenadas pelo Nome" << endl;
        cout << "6. Mostrar lista de pessoas ordenadas pela data de nascimento" << endl;
        cout << "7. Adicionar uma pessoa" << endl;
        cout << "0. Sair" << endl;
        cout << "Opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                long long int n_cpf;
                cout << "Digite o CPF da pessoa: (apenas numeros)";

                cin >> n_cpf;

                cpf.searchByCPF(n_cpf);

                break;
            case 2:
                std::cout << "Digite o prefixo do nome: ";
                std::cin.ignore();
                std::getline(std::cin, prefixo);

                cout << "Pessoas com nome iniciado por " << prefixo << ":" << endl;
                nome.listByName(prefixo);
                
                break;
            case 3:
                cout << "Digite a data inicial (no formato dd/mm/aaaa): ";
                cin.ignore();
                getline(cin, dataInicial);
                cout << "Digite a data final (no formato dd/mm/aaaa): ";
                getline(cin, dataFinal);

                convertDate(dataInicial, dia1, mes1, ano1);
                convertDate(dataFinal, dia2, mes2, ano2);

                cout << "Pessoas com data de nascimento entre " << dataInicial << " e " << dataFinal << ":" << endl;

                data.listDtNasc({dia1, mes1, ano1}, {dia2, mes2, ano2});

                break;
            case 4:
                cout << "Lista de pessoas ordenadas pelo CPF:" << endl;
                cpf.show();
                break;
            case 5:
                std::cout << "Lista de pessoas ordenadas pelo Nome:" << std::endl;
                nome.show();
                break;
            case 6:
                std::cout << "Lista de pessoas ordenadas pela Data de Nascimento:" << std::endl;
                data.show();
                break;
            case 7:

                cout << "Digite o nome: ";
                cin.ignore();
                getline(cin, name);

                cout << "Digite o sobrenome: ";
                getline(cin, sobrenome);

                cout << "Digite o CPF: ";
                cin >> num_cpf;

                cout << "Digite a cidade: ";
                getline(cin, cidade);

                cout << "Digite a data de nascimento (no formato dd/mm/aaaa): ";
                getline(cin, dataNascimento);
                convertDate(dataNascimento, dia, mes, ano);

                cpf.addCpf(new Pessoa(name, sobrenome, num_cpf, cidade, {dia, mes, ano}));
                nome.addNome(new Pessoa(name, sobrenome, num_cpf, cidade, {dia, mes, ano}));
                data.addData(new Pessoa(name, sobrenome, num_cpf, cidade, {dia, mes, ano}));

                cout << "Pessoa adicionada com sucesso!" << endl;         
                
                break;
            case 0:
                cout << "Encerrando o programa." << endl;
                break;
            default:
                cout << "Opção inválida. Tente novamente." << endl;
                break;
        }

        cout << endl;

    } while (opcao != 0);

    cpf.clear();
    nome.clear();
    data.clear();

    return 0;
}