#include "Registro.hpp"

#include <string>
#include <cstring>

using namespace std;

const int MAX_NOME = 30;
const int MAX_SOBRENOME = 30;
const int MAX_TELEFONE = 15;
const int MAX_NASCIMENTO = 10;

string Registro::packFixed() const {
    string buffer(MAX_NOME + MAX_SOBRENOME + MAX_TELEFONE + MAX_NASCIMENTO,'\0');
    strncpy(&buffer[0],nome.c_str(),MAX_NOME);
    strncpy(&buffer[MAX_NOME], sobrenome.c_str(), MAX_SOBRENOME);
    strncpy(&buffer[MAX_NOME + MAX_SOBRENOME], telefone.c_str(), MAX_TELEFONE);
    strncpy(&buffer[MAX_NOME + MAX_SOBRENOME + MAX_TELEFONE], nascimento.c_str(), MAX_NASCIMENTO);
    return buffer;
}

void Registro::unpackFixed(const string& buffer) {
    nome = string(buffer.c_str(), strnlen(buffer.c_str(), MAX_NOME));
    sobrenome = string(buffer.c_str() + MAX_NOME, strnlen(buffer.c_str() + MAX_NOME, MAX_SOBRENOME));
    telefone = string(buffer.c_str() + MAX_NOME + MAX_SOBRENOME, strnlen(buffer.c_str() + MAX_NOME + MAX_SOBRENOME, MAX_TELEFONE));
    nascimento = string(buffer.c_str() + MAX_NOME + MAX_SOBRENOME + MAX_TELEFONE, strnlen(buffer.c_str() + MAX_NOME + MAX_SOBRENOME + MAX_TELEFONE, MAX_NASCIMENTO));
}