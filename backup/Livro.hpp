#ifndef LIVRO_HPP
#define LIVRO_HPP

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Livro {
    public:
        int id;
        string titulo;
        vector<string> autores;
        int ano;
        vector<string> generos;

        string packFixed() const;
        void unpackFixed(const string& buffer);
};

#endif