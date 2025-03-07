#include <iostream>
#include <string>
#include <set>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <map>

#include "functions.hpp"
#include "Buffer.hpp"

using namespace std;

int main() {
    //CARREGANDO STOPWORDS E SIMBOLOS
    pair<set<string>,set<string>> ignore = CarregarStopwordAndSimbols("stopwords_en.txt", "pontuacoes.txt");

    //LEITURA DOS LIVROS DO ARQUIVO CSV
    Buffer bufferTxt("booksDataset.csv");
    vector<Livro> livros = bufferTxt.lerLivrosCsv();

    Buffer bufferBin("SAIDA.bin");
    string metadataFile = "metadata.bin";
    //SERIALIZAÇÃO
    ofstream saidaBinario("SAIDA.bin", ios::binary | ios::app);
    ofstream saidaBinIndice("INDICES.bin", ios::binary | ios::app);
    cout << endl << "Carregando no arquivo binário..." << endl << endl;
    for(unsigned i=0; i<livros.size(); i++)
        bufferBin.escreverRegistroFixo(livros[i], saidaBinario, saidaBinIndice, metadataFile, ignore);
    saidaBinario.close();
    saidaBinIndice.close();

    //PARA MOSTRAR O MAPEAMENTO
    map<string,vector<int>> mapa = bufferBin.hash.mapeamento;
    // for (const auto& entry : mapa) {
    //     cout << entry.first << " -> ";
    //     for (size_t i = 0; i < entry.second.size(); ++i) {
    //         cout << entry.second[i];
    //         if (i < entry.second.size() - 1) cout << ", ";
    //     }
    //     cout << endl;
    // }

    //DESSERIALIAÇÃO
    pair<vector<Livro>,vector<Indice>> retornoDesserializa = bufferBin.lerRegistroFixo();
    livros = retornoDesserializa.first;
    vector<Indice> indices = retornoDesserializa.second;
    
    string search;
    cout << "Digite o que procura: ";
    getline(cin, search);
    search = removerStopwordsAndSimbols(search, ignore);
    search.erase(remove_if(search.end()-1, search.end(), ::isspace), search.end());
    vector<string> palavras = splitString(search);
    vector<int> ids = efetuaBuscaMapa(mapa, palavras);
    cout << "Foram encontrados " << ids.size() << " ocorrências." << endl;
    for (auto i : ids)
        efetuarBuscas(bufferBin.arvore, i);

    return 0;
}
