#ifndef REGISTRO_HPP
#define REGISTRO_HPP

#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>

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