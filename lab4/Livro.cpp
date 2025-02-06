#include "Livro.hpp"

pair<string,int> Livro::packFixed() const{
    string data = "|" + to_string(id) + "|" + titulo + "|";
    for(unsigned i=0; i<autores.size(); i++){
        data += autores[i];
        if(i+1 < autores.size())
            data += ",";
    }
    data += "|" + to_string(ano) + "|";
    for(unsigned i=0; i<categorias.size(); i++){
        data += categorias[i];
        if(i+1 < categorias.size())
            data += ",";
    }

    ofstream saidaTxt;
    saidaTxt.open("saidapack.dat", ios_base::app);

    saidaTxt << data.size() << data << endl;

    string buffer(data.size() + sizeof(short int), '\0');
    strncpy(&buffer[0], to_string(data.size()).c_str(), sizeof(short int));
    strncpy(&buffer[sizeof(short int)], data.c_str(), data.size());

    saidaTxt.close();

    return make_pair(buffer,id);
}

void Livro::unpackFixed(const string& buffer){
    int bufferSize = buffer.size();
    int delimiter = buffer.find('|', 0);
    string bufferAux = buffer.substr(delimiter+1, bufferSize);

    delimiter = bufferAux.find('|', 0);
    id = stoi(bufferAux.substr(0, delimiter));
    bufferAux = bufferAux.substr(delimiter+1, bufferAux.size());

    delimiter = bufferAux.find('|', 0);
    titulo = bufferAux.substr(0, delimiter);
    bufferAux = bufferAux.substr(delimiter+1, bufferAux.size());

    if(id == 29719){
        int countChar = 0;
        while(countChar < 2){
            delimiter = bufferAux.find('|', 0);
            bufferAux = bufferAux.substr(0, delimiter);
            countChar++;
        }
    }
    delimiter = bufferAux.find('|', 0);
    stringstream ssAutores(bufferAux.substr(0, delimiter));
    string autor;
    while(getline(ssAutores, autor, ','))
        autores.push_back(autor);
    bufferAux = bufferAux.substr(delimiter+1, bufferAux.size());

    delimiter = bufferAux.find('|', 0);
    ano = stoi(bufferAux.substr(0, delimiter));
    bufferAux = bufferAux.substr(delimiter+1, bufferAux.size());

    delimiter = bufferAux.find('|', 0);
    stringstream ssCategorias(bufferAux.substr(0, delimiter));
    string categoria;
    while(getline(ssCategorias, categoria, ','))
        categorias.push_back(categoria);
}