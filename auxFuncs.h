#ifndef AUXFUNCS_H
#define AUXFUNCS_H

#include <iomanip> // Para std::setfill() e std::setw()

// Converte um cpf no formato XXX.XXX.XXX-XX para um valor numerico
// Usado na funcao lerArquivoCSV de arq.h
long long int convertCpf(const std::string& cpf) {
    std::string cpfNumerico;

    // Remove os caracteres especiais
    for (char c : cpf) {
        if (isdigit(c)) {
            cpfNumerico += c;
        }
    }

    // Converte a string para long long int
    std::stringstream ss(cpfNumerico);
    long long int cpfInt;
    ss >> cpfInt;

    return cpfInt;
}


// Converte uma string no formato DD/MM/AAAA para as variaveis dia, mes e ano
// Usado na funcao lerArquivoCSV de arq.h e na funcao main de main.h
void convertDate(const std::string& data, int& dia, int& mes, int& ano) {
    std::stringstream ss(data);
    char delimiter;
    ss >> dia >> delimiter >> mes >> delimiter >> ano;
}


// Formata um CPF numérico no formato "XXX.XXX.XXX-XX" e imprime o resultado na saída padrão. 
// Usada na funcao showPessoa e listPessoas de avl.cpp
void formatCPF(long long int cpf) {
    // std::string cpfStr = to_string(cpf);
    //  Adiciona zeros a esquerda, garantindo que o CPF tenha exatamente 11 digitos.
    std::stringstream ss;
    ss << std::setw(11) << std::setfill('0') << cpf;
    std::string cpfStr = ss.str();

    std::cout << cpfStr.substr(0, 3) << ".";
    std::cout << cpfStr.substr(3, 3) << ".";
    std::cout << cpfStr.substr(6, 3) << "-";
    std::cout << cpfStr.substr(9, 2);
}


// Funcao auxiliar para converter uma string em minuslas
// Usada na funcao listByName
std::string stringToLower(const std::string& str){
    std::string lowerStr = str;

    for(char& c : lowerStr)
        c = tolower(c);
    
    return lowerStr;
}


// Compara duas datas e retorna 1 se a primeira for maior que a segunda, -1 se a primeira for menor que a segunda e 0 se forem iguais
// Usada na funcao listDtNasc de avl.cpp e no functor CompareData de comparators.h
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

#endif