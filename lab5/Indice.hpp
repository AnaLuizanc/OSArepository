#ifndef INDICE_HPP
#define INDICE_HPP
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class Indice {
    public:
        int id;
        int endereco;

        Indice() : id(0), endereco(0) {}

        Indice(int id) : id(id) {}

        Indice(int id, int endereco) : id(id), endereco(endereco) {}

        bool operator<(const Indice& other) const {
            return id < other.id;
        }

        bool operator>(const Indice& other) const {
            return id > other.id;
        }

        bool operator==(const Indice& other) const {
            return id == other.id;
        }

        friend std::ostream& operator<<(std::ostream& os, const Indice& indice) {
            os << indice.id << " - " << indice.endereco << endl;
            return os;
        }

        string packFixed() const;
        void unpackFixed(const string& buffer);
};

#endif