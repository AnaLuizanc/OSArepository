#ifndef REGISTRO_HPP
#define REGISTRO_HPP

#include <iostream>
#include <string>

using namespace std;

class Registro {
    public:
        string nome;
        string sobrenome;
        string telefone;
        string nascimento;

        string packFixed() const;
        void unpackFixed(const string& buffer);
};

#endif