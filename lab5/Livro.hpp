#ifndef LIVRO_HPP
#define LIVRO_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <cstring>

using namespace std;

class Livro {
    public:
        int id;
        string titulo;
        vector<string> autores;
        int ano;
        vector<string> categorias;

        pair<string,int> packFixed() const;
        void unpackFixed(const string& buffer);
};

#endif