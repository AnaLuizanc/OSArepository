#include "Registro.hpp"

#include <string>
#include <cstring>

using namespace std;

const int MAX_NOME = 60;

string Registro::packFixed() {
    string buffer(MAX_NOME + sizeof(int),'\0');
    strncpy(&buffer[0],nome.c_str(),MAX_NOME);
    memcpy(&buffer[MAX_NOME],&idade,sizeof(int));
    return buffer;
}

void Registro::unpackFixed(string buffer) {
    nome = string(buffer.c_str(),strnlen(buffer.c_str(),MAX_NOME));
    memcpy(&idade, &buffer[MAX_NOME],sizeof(int));
}