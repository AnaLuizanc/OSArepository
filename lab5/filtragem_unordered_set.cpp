#include <iostream>
#include <string>
#include <unordered_set>
#include <sstream>
#include <fstream>
using namespace std;

unordered_set<string> CarregarStopWords(const string &arq){
    unordered_set<string> stopwords;
    ifstream arquivo(arq);
    string palavra;

    if (!arquivo.is_open()) {
        throw runtime_error("Erro ao abrir o arquivo de stopwords: " + arq);
    }

    while (getline(arquivo, palavra)) {
        // Remove espaços em branco no início e fim da palavra
        palavra.erase(0, palavra.find_first_not_of(" \t\n\r\f\v"));
        palavra.erase(palavra.find_last_not_of(" \t\n\r\f\v") + 1);
        
        // Adiciona apenas palavras não vazias
        if (!palavra.empty()) {
            stopwords.insert(palavra);
        }
    }

    arquivo.close();
    return stopwords;
}

// Função de filtragem
string removerStopwords(const string &texto, const unordered_set<string> &stopwords) {
    istringstream iss(texto);
    ostringstream oss;
    string palavra;

    while (iss >> palavra) {
        if (stopwords.find(palavra) == stopwords.end()) { // Se a palavra não for uma stopword
            oss << palavra << " ";
        }
    }
    return oss.str();
}

int main() {
    unordered_set<string> stopwords = CarregarStopWords("stopwords_en.txt");
    string texto = "Artificial intelligence is transforming the world of people and businesses.";
    string textoSemStopwords = removerStopwords(texto, stopwords);

    cout << "Texto Original: " << texto << endl;
    cout << "Texto Sem Stopwords: " << textoSemStopwords << endl;

    return 0;
}
