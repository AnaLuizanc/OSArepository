#ifndef BUFFER_HPP
#define BUFFER_HPP

#include "Livro.hpp"
#include "Indice.hpp"

#include <vector>
#include <fstream>
#include <utility>

class Buffer {
    public:
        string nomeArquivo;
        string buffer;
        ifstream inFile;

        Buffer(const string& nomeArquivo);

        void escreverRegistro(const Livro& reg);
        Livro lerRegistro();
        pair<vector<Livro>, vector<Indice>> lerRegistrosCSV();
        void escreverIndice(const Indice& indice);
        vector<Indice> lerIndices();
        Livro lerRegistroPorEndereco(long endereco);
};

#endif