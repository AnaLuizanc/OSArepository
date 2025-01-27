#ifndef BUFFER_HPP
#define BUFFER_HPP

#include "Registro.hpp"

#include <vector>
#include <fstream>

class Buffer {
    public:
        string nomeArquivo;
        string buffer;
        ifstream inFile;

        Buffer(const string& nomeArquivo);

        void escreverRegistroFixo(const Registro& reg);
        Registro lerRegistroFixo();
        vector<Registro> lerRegistrosTxt();
        bool temRegistros();
};


#endif