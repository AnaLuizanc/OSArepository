#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

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

#include "Livro.hpp"
#include "Arvore.h"
#include "Indice.hpp"

class Buffer;

using namespace std;

pair<set<string>,set<string>> CarregarStopwordAndSimbols(const string &arq, const string& arqSimbols);
string toLowerCase(string& word);
// Função de filtragem
string removerStopwordsAndSimbols(const string &texto, const pair<set<string>,set<string>> &ignore);
vector<string> splitString(string s);
void imprimeLivro(Livro liv);
int pesquisaIndice(ArvoreBinaria<Indice>& arvore, int id);
Livro pesquisaLivro(ArvoreBinaria<Indice>& arvore, int id);
void efetuarBuscas(ArvoreBinaria<Indice>& arvore, int id);
vector<int> efetuaBuscaMapa(map<string,vector<int>> mapa, vector<string> search);

#endif