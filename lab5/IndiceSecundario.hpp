#ifndef INDICESECUNDARIO_HPP
#define INDICESECUNDARIO_HPP

#include "functions.hpp"

using namespace std;

class IndiceSecundario{
    public:
        int id;
        string titulo;
        map<string,vector<int>> mapeamento;

        IndiceSecundario(){}

        IndiceSecundario(int id, string titulo) : id(id), titulo(titulo){}

        void mapeamentoPalavras(IndiceSecundario& ind, pair<set<string>,set<string>> ignore);
};

#endif