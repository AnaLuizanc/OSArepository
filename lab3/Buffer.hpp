#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <string>
#include <vector>

using namespace std;

#include "Registro.hpp"

class Buffer {
    public:
        string fileName;
        string buffer;

        Buffer(const string& fileName);

        vector<Registro> lerRegistrosTxt();
        void escreverRegistroFixo(const Registro& reg);
        vector<Registro> lerRegistroFixo();
};

#endif