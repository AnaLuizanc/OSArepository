#ifndef ARQUIVO_HPP
#define ARQUIVO_HPP

#include <iostream>
#include <string>
#include <vector>

#include "Registro.hpp"

using namespace std;

class Arquivo {
    public:
        string nomeArquivo;

        vector<Registro> lerRegistrosCSV();
        void adicionarRegistroFixo(Registro reg);
        vector<Registro> lerRegistrosFixo();
};


#endif