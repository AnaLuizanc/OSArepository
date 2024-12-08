#ifndef INDICE_HPP
#define INDICE_HPP

#include <iostream>
#include <sstream>

using namespace std;

class Indice {
    public:
        int id;
        long endereco;

        Indice();
        Indice(int id, long endereco);

        string packFixed() const;
        void unpackFixed(const string& buffer);

        bool operator>(const Indice& other) const;
        bool operator<(const Indice& other) const;
        bool operator==(const Indice& other) const;

        friend ostream& operator<<(ostream& os, const Indice& indice) {
            os << "ID: " << indice.id << ", Endereco: " << indice.endereco;
            return os;
        }
};

#endif