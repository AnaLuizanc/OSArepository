#include "Indice.hpp"

string Indice::packFixed() const{
    string data = to_string(id) + "|" + to_string(endereco);

    ofstream saidaTxt;
    saidaTxt.open("indices.dat", ios_base::app);

    saidaTxt << data << endl;

    string buffer(data.size(), '\0');
    strncpy(&buffer[0], data.c_str(), data.size());

    saidaTxt.close();

    return buffer;
}

void Indice::unpackFixed(const string& buffer){
    int bufferSize = buffer.size();
    int delimiter = buffer.find('|', 0);
    
    id = stoi(buffer.substr(0, delimiter));
    endereco = stoi(buffer.substr(delimiter+1, buffer.size()-1));
}