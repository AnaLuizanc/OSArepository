#include "Buffer.hpp"
#include "Registro.hpp"

#include <fstream>

using namespace std;

const int MAX_NOME = 60;

void Buffer::escreverRegistroFixo(Registro reg, ofstream& out){
    string buffer = reg.packFixed();
    out.write(reinterpret_cast<const char*>(buffer.c_str()), buffer.size());
}

Registro Buffer::lerRegistroFixo(ifstream& in){
    string buffer(MAX_NOME + sizeof(int),'\0');
    in.read(reinterpret_cast<char*>(&buffer[0]), buffer.size());
    Registro reg;
    reg.unpackFixed(buffer);
    return reg;
}