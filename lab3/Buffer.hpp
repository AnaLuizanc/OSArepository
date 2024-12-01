#ifndef BUFFER_HPP
#define BUFFER_HPP

#include "Registro.hpp"

#include <vector>

class Buffer {
    public:
        string nomeArquivo;
        string buffer;

        Buffer(const string& nomeArquivo);

        void escreverRegistroFixo(const Registro& reg);
        Registro lerRegistroFixo();
        vector<Registro> lerRegistrosTxt();
};


#endif