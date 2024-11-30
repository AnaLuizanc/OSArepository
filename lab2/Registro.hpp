#ifndef REGISTRO_HPP
#define REGISTRO_HPP

#include <iostream>
#include <string>

using namespace std;

class Registro {
    public:
        string nome;
        int idade;

        string packFixed();
        void unpackFixed(string buffer);
};

#endif