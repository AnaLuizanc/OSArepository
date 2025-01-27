#include "Registro.hpp"

#include <string>
#include <cstring>
#include <string.h>

using namespace std;

const int MAX_NOME = 60;

string Registro::packFixed() {
    string buffer(MAX_NOME + sizeof(int),'\0');
    strncpy(&buffer[0],nome.c_str(),MAX_NOME);
    memcpy(&buffer[MAX_NOME],&idade,sizeof(int));
    return buffer;
}

void Registro::unpackFixed(string buffer) {
    size_t lenght = buffer.find('\0', 0);
    if(lenght == string::npos || lenght > MAX_NOME)
        lenght = MAX_NOME;
    nome = string(buffer.c_str(), lenght);
    memcpy(&idade, &buffer[MAX_NOME],sizeof(int));
}