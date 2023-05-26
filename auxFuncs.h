#ifndef AUXFUNCS_H
#define AUXFUNCS_H

// converte um cpf no formato XXX.XXX.XXX-XX para um valor numerico
// usado na funcao lerArquivoCSV de arq.h
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


// converte uma string no formato DD/MM/AAAA para as variaveis dia, mes e ano
void convertDate(const std::string& data, int& dia, int& mes, int& ano) {
    std::stringstream ss(data);
    char delimiter;
    ss >> dia >> delimiter >> mes >> delimiter >> ano;
}


// #TODO: Tratar quando CPF tiver menos que 11 digitos (add 0's na frente do cpf)
void formatCPF(long long int cpf) {
    std::string cpfStr = to_string(cpf);

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