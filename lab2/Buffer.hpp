#ifndef BUFFER_HPP
#define BUFFER_HPP

#include "Registro.hpp"

class Buffer {
    public:
        void escreverRegistroFixo(Registro reg, ofstream& out);
        Registro lerRegistroFixo(ifstream& in);
};


#endif