#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <algorithm>

#include "Livro.hpp"
#include "Indice.hpp"
#include "Arvore.h"

class Buffer {
    public:
        string fileName;
        string buffer;
        ArvoreBinaria<Indice> arvore;

        Buffer(const string& fileName){
            this->fileName = fileName;
        }

        vector<Livro> lerLivrosCsv();
        void escreverRegistroFixo(const Livro& liv, ofstream& saidaBinario, ofstream&saidaBinIndice);
        pair<vector<Livro>,vector<Indice>> lerRegistroFixo();
};

#endif