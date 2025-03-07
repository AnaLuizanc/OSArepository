#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <iostream>
#include <string>
#include <set>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <map>

#include "Arvore.h"
#include "Livro.hpp"
#include "Indice.hpp"
#include "IndiceSecundario.hpp"

using namespace std;

class Buffer {
    private: 
        int carregarNrRegistros(const string& metadataFile) {
            ifstream metaFile(metadataFile, ios::binary);
            int nr_regs = 0;
            
            if (metaFile.is_open()) {
                metaFile.read(reinterpret_cast<char*>(&nr_regs), sizeof(nr_regs));
                metaFile.close();
            }
            
            return nr_regs;
        }
        
        // Função para atualizar o número de registros no arquivo de metadados
        void salvarNrRegistros(const string& metadataFile, int nr_regs) {
            ofstream metaFile(metadataFile, ios::binary | ios::trunc);
            if (metaFile.is_open()) {
                metaFile.write(reinterpret_cast<const char*>(&nr_regs), sizeof(nr_regs));
                metaFile.close();
            }
        }
        
    public:
        string fileName;
        string buffer;
        ArvoreBinaria<Indice> arvore;
        IndiceSecundario hash;

        Buffer(const string& fileName){
            this->fileName = fileName;
        }

        vector<Livro> lerLivrosCsv();
        void escreverRegistroFixo(const Livro& liv, ofstream& saidaBinario, ofstream&saidaBinIndice, const string& metaDataFile, pair<set<string>,set<string>> ignore);
        pair<vector<Livro>,vector<Indice>> lerRegistroFixo();
};


#endif