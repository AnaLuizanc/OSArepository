#include "Indice.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>

Indice::Indice() : id(0), endereco(0) {}
Indice::Indice(int id, long endereco) : id(id), endereco(endereco) {}

string Indice::packFixed() const {
    stringstream ss;
    ss << setw(10) << setfill('0') << id << " " << setw(10) << setfill('0') << endereco << " ";
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