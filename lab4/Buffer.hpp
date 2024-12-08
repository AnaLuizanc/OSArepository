#ifndef BUFFER_HPP
#define BUFFER_HPP

#include "Livro.hpp"
#include "Indice.hpp"

#include <vector>
#include <fstream>

class Buffer {
    public:
        string nomeArquivo;
        string buffer;
        ifstream inFile;

        Buffer(const string& nomeArquivo);

        void escreverRegistro(const Livro& reg);
        Livro lerRegistro();
        vector<Livro> lerRegistrosCSV();
        void escreverIndice(const Indice& indice);
        vector<Indice> lerIndices();
        bool temRegistros();
};

#endif