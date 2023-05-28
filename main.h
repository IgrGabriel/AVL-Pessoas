#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <limits>
#include <cstdlib>

// Limpa a tela
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    std::cout << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
}

//  Aguardar a entrada do usuario 
void waitForInput() {
    std::cout << "\nPressione Enter para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void programName() {
    std::cout << "============================================" << std::endl;
    std::cout << "        ÁRVORE BALANCEADA DE PESSOAS         " << std::endl;
    std::cout << "============================================" << std::endl;
}

void displayMenu() {
    std::cout << "Selecione uma opção:" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "1. Consultar uma pessoa pelo CPF" << std::endl;
    std::cout << "2. Consultar pessoas pelo prefixo do nome" << std::endl;
    std::cout << "3. Consultar pessoas pelo intervalo de data de nascimento" << std::endl;
    std::cout << "4. Filtrar pessoas pela cidade" << std::endl;
    std::cout << "5. Mostrar lista de pessoas ordenadas pelo CPF" << std::endl;
    std::cout << "6. Mostrar lista de pessoas ordenadas pelo Nome" << std::endl;
    std::cout << "7. Mostrar lista de pessoas ordenadas pela data de nascimento" << std::endl;
    std::cout << "8. Mostrar lista de pessoas ordenadas pela cidade" << std::endl;
    std::cout << "9. Adicionar uma pessoa" << std::endl;
    std::cout << "0. Sair" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "Opção: ";
}

int main() {
    avl_tree cpf, nome, data, cidade;

    CompareCpf compCpf;
    CompareNome compNome;
    CompareData compData;
    CompareCidade compCidade;

    string nomeArquivo = "data.csv";
    
    cpf.lerArquivoCSV(nomeArquivo, compCpf);
    data.lerArquivoCSV(nomeArquivo, compData);
    nome.lerArquivoCSV(nomeArquivo, compNome);
    cidade.lerArquivoCSV(nomeArquivo, compCidade);
    
    string prefixo, dataInicial, dataFinal, name, surname, city, dataNascimento;
    int dia, mes, ano, dia1, mes1, ano1, dia2, mes2, ano2;
    long long int num_cpf;

    int opcao = -1;
    
    do {
        if (opcao == -1)
            programName();
        else
            clearScreen();

        displayMenu();
        std::cin >> opcao;

        switch (opcao) {
            case 1:
                long long int n_cpf;
                std::cout << "\nDigite o CPF da pessoa: (apenas numeros): ";

                std::cin >> n_cpf;
                std::cout << std::endl;

                cpf.searchByCPF(n_cpf);
                waitForInput();
                break;

            case 2:
                std::cout << "\nDigite o prefixo do nome: ";
                std::cin.ignore();
                std::getline(std::cin, prefixo);
                
                std::cout << std::endl;
                std::cout << "Pessoas com nome iniciado por " << prefixo << ":" << std::endl;
                std::cout << std::endl;

                nome.listByName(prefixo);
                waitForInput();
                break;

            case 3:
                std::cout << "\nDigite a data inicial (no formato dd/mm/aaaa): ";
                std::cin.ignore();
                std::getline(std::cin, dataInicial);
                std::cout << "Digite a data final (no formato dd/mm/aaaa): ";
                std::getline(std::cin, dataFinal);

                convertDate(dataInicial, dia1, mes1, ano1);
                convertDate(dataFinal, dia2, mes2, ano2);

                std::cout << "\nPessoas com data de nascimento entre " << dataInicial << " e " << dataFinal << ":\n" << endl;

                data.listDtNasc({dia1, mes1, ano1}, {dia2, mes2, ano2});
                waitForInput();
                break;

            case 4:
                std::cout << "\nDigite o prefixo do Cidade: ";
                std::cin.ignore();
                std::getline(std::cin, prefixo);

                std::cout << "\nPessoas com a Cidade iniciado por " << prefixo << ":\n" << std::endl;
                cidade.listByCity(prefixo);
                waitForInput();
                break;
            case 5:
                std::cout << "\nLista de pessoas ordenadas pelo CPF:\n" << std::endl;
                cpf.show();
                waitForInput();
                break;

            case 6:
                std::cout << "\nLista de pessoas ordenadas pelo Nome:\n" << std::endl;
                nome.show();
                waitForInput();
                break;

            case 7:
                std::cout << "\nLista de pessoas ordenadas pela Data de Nascimento:\n" << std::endl;
                data.show();
                waitForInput();
                break;

            case 8:
                std::cout << "\nLista de pessoas ordenadas pela Cidade:\n" << std::endl;
                cidade.show();
                waitForInput();
                break;

            case 9:
                std::cout << "\nDigite o nome: ";
                std::cin.ignore();
                std::getline(std::cin, name);

                std::cout << "Digite o sobrenome: ";
                std::getline(std::cin, surname);

                std::cout << "Digite o CPF: ";
                std::cin >> num_cpf;

                std::cout << "Digite a cidade: ";
                std::cin.ignore();
                std::getline(std::cin, city);

                std::cout << "Digite a data de nascimento (no formato dd/mm/aaaa): ";
                std::getline(std::cin, dataNascimento);
                convertDate(dataNascimento, dia, mes, ano);

                cpf.addCpf(new Pessoa(name, surname, num_cpf, city, {dia, mes, ano}));
                nome.addNome(new Pessoa(name, surname, num_cpf, city, {dia, mes, ano}));
                data.addData(new Pessoa(name, surname, num_cpf, city, {dia, mes, ano}));
                cidade.addCidade(new Pessoa(name, surname, num_cpf, city, {dia, mes, ano}));

                std::cout << "Pessoa adicionada com sucesso!" << std::endl;
                waitForInput();
                break;

            case 0:
                std::cout << "Encerrando o programa." << std::endl;
                break;

            default:
                std::cout << "\nOpção inválida. Tente novamente." << std::endl;
                waitForInput();
                break;
        }

    } while (opcao != 0);

    cpf.clear();
    nome.clear();
    data.clear();
    cidade.clear();

    return 0;
}


#endif