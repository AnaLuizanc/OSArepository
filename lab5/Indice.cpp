#include "Indice.hpp"

string Indice::packFixed() const{
    string data = to_string(id) + "|" + to_string(endereco);

    string buffer(data.size(), '\0');
    strncpy(&buffer[0], data.c_str(), data.size());

    return buffer;
}

void Indice::unpackFixed(const string& buffer){
    int delimiter = buffer.find('|', 0);
    
    id = stoi(buffer.substr(0, delimiter));
    endereco = stoi(buffer.substr(delimiter+1, buffer.size()-1));
}