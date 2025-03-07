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

using namespace std;

pair<set<string>,set<string>> CarregarStopwordAndSimbols(const string &arq, const string& arqSimbols){ // ok
    set<string> stopwords, simbols;
    ifstream arquivo(arq), arquivoSimbols(arqSimbols);
    string palavra, simbolo;

    if (!arquivo.is_open())
        throw runtime_error("Erro ao abrir o arquivo de stopwords: " + arq);

    if(!arquivoSimbols.is_open())
        throw runtime_error("Erro ao abrir o arquivo de símbolos: " + arqSimbols);
    
    while(getline(arquivo, palavra)){
        // Remove espaços em branco no início e fim da palavra
        palavra.erase(0, palavra.find_first_not_of(" \t\n\r\f\v"));
        palavra.erase(palavra.find_last_not_of(" \t\n\r\f\v") + 1);
        
        // Adiciona apenas palavras não vazias
        if(!palavra.empty())
            stopwords.insert(palavra);
    }
    arquivo.close();

    while(getline(arquivoSimbols, simbolo)){
        // Remove espaços em branco no início e fim da simbolo
        simbolo.erase(0, simbolo.find_first_not_of(" \t\n\r\f\v"));
        simbolo.erase(simbolo.find_last_not_of(" \t\n\r\f\v") + 1);
        
        // Adiciona apenas simbolos não vazias
        if (!simbolo.empty())
            simbols.insert(simbolo);
    }

    arquivoSimbols.close();

    return make_pair(stopwords,simbols);
}

string toLowerCase(string& word){
    string lower;
    for(char c : word)
        lower += tolower(c);
    return lower;
}

// Função de filtragem
string removerStopwordsAndSimbols(const string &texto, const pair<set<string>,set<string>> &ignore) {
    istringstream iss(texto);
    ostringstream oss;
    string palavra;
    set<string> stopwords = ignore.first;
    set<string> simbols = ignore.second;

    while (iss >> palavra) {
        palavra = toLowerCase(palavra);
        // Remover símbolos da palavra
        for(const string& simbolo : simbols){
            size_t pos;
            while ((pos = palavra.find(simbolo)) != string::npos)
            palavra.erase(pos, simbolo.length());
        }
        
        if (stopwords.find(palavra) == stopwords.end()) // Se a palavra não for uma stopword
            oss << palavra << " ";
    }
    return oss.str();
}

