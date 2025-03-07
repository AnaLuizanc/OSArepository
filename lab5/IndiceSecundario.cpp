#include "IndiceSecundario.hpp"

void IndiceSecundario::mapeamentoPalavras(IndiceSecundario& ind, pair<set<string>,set<string>> ignore){
    string text = removerStopwordsAndSimbols(ind.titulo, ignore);
    stringstream ss(text);
    string palavra;
    
    while(ss >> palavra){
        auto it = lower_bound(mapeamento[palavra].begin(), mapeamento[palavra].end(), ind.id);
        mapeamento[palavra].insert(it, ind.id);
    }
}