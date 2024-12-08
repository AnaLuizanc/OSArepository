#include "Indice.hpp"

#include <iostream>
#include <sstream>

Indice::Indice() : id(0), endereco(0) {}
Indice::Indice(int id, long endereco) : id(id), endereco(endereco) {}

string Indice::packFixed() const {
    stringstream ss;
    ss << id << " " << endereco << " ";
    return ss.str();
}

void Indice::unpackFixed(const string& buffer) {
    stringstream ss(buffer);
    ss >> id >> endereco;
}

bool Indice::operator>(const Indice& other) const {
    return id > other.id;
}

bool Indice::operator<(const Indice& other) const {
    return id < other.id;
}

bool Indice::operator==(const Indice& other) const {
    return id == other.id;
}