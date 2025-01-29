#include "Registro.hpp"

string Registro::packFixed() const{
    string data = "|" + nome + "|" + sobrenome + "|" + telefone + "|" + nascimento;
    string buffer(data.size(), '\0');

    ofstream saidaTxt;
    saidaTxt.open("saidapack.dat", ios_base::app);

    saidaTxt << data.size() << data << endl;

    buffer.resize(data.size() + sizeof(short int), '\0');
    strncpy(&buffer[0], to_string(data.size()).c_str(), sizeof(short int));
    strncpy(&buffer[sizeof(short int)], data.c_str(), data.size());

    saidaTxt.close();

    return buffer;
}

void Registro::unpackFixed(const string& buffer){
    int bufferSize = buffer.size();
    int delimiter = buffer.find('|', 0);
    string bufferAux = buffer.substr(delimiter+1, bufferSize);

    delimiter = bufferAux.find('|', 0);
    nome = bufferAux.substr(0, delimiter);
    bufferAux = bufferAux.substr(delimiter+1, bufferAux.size());

    delimiter = bufferAux.find('|', 0);
    sobrenome = bufferAux.substr(0, delimiter);
    bufferAux = bufferAux.substr(delimiter+1, bufferAux.size());

    delimiter = bufferAux.find('|', 0);
    telefone = bufferAux.substr(0, delimiter);
    bufferAux = bufferAux.substr(delimiter+1, bufferAux.size());

    delimiter = bufferAux.find('|', 0);
    nascimento = bufferAux.substr(0, delimiter);
}