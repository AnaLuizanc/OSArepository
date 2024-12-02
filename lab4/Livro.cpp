#include "Livro.hpp"

#include <string>
#include <cstring>
#include <sstream>

using namespace std;

string Livro::packFixed() const {
    stringstream buffer;

    buffer << id << '\0';
    buffer << titulo.size() << '\0' << titulo;
    buffer << autores.size() << '\0';
    for(const auto& autor: autores)
        buffer << autor.size() << '\0' << autor;
    buffer << ano << '\0';
    buffer << generos.size() << '\0';
    for(const auto& genero : generos)
        buffer << genero.size() << '\0' << genero;
    
    return buffer.str();
}

void Livro::unpackFixed(const string& buffer) {
    stringstream ss(buffer);
    string temp;
    unsigned size;

    getline(ss, temp, '\0');
    id = stoi(temp);

    getline(ss, temp, '\0');
    size = stoi(temp);
    titulo.resize(size);
    ss.read(&titulo[0], size);

    getline(ss, temp, '\0');
    unsigned numAutores = stoi(temp);
    autores.resize(numAutores);
    for (int i = 0; i < numAutores; i++) {
        getline(ss, temp, '\0');
        size = stoi(temp);
        autores[i].resize(size);
        ss.read(&autores[i][0], size);
    }

    getline(ss, temp, '\0');
    ano = stoi(temp);

    getline(ss, temp, '\0');
    unsigned numGeneros = stoi(temp);
    generos.resize(numGeneros);
    for (int i = 0; i < numGeneros; i++) {
        getline(ss, temp, '\0');
        size = stoi(temp);
        generos[i].resize(size);
        ss.read(&generos[i][0], size);
    }
}
