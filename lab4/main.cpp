#include <iostream>
#include <cassert>
#include <vector>
#include <utility>

#include "Livro.hpp"
#include "Buffer.hpp"
#include "Indice.hpp"
#include "Arvore.h"

using namespace std;

void carregarIndicesNaArvore(ArvoreBinaria<Indice>& tree, const vector<Indice>& indices) {
    for (const auto& indice : indices) {
        tree.Inserir(indice);
    }
}

int main() {

    Buffer bufferCSV("teste.csv");
    pair<vector<Livro>, vector<Indice>> resultado = bufferCSV.lerRegistrosCSV();
    vector<Livro> livros = resultado.first;
    vector<Indice> indices = resultado.second;

    Buffer bufferBin("livros.dat");

    for (const auto& livro : livros) 
        bufferBin.escreverRegistro(livro);

    ArvoreBinaria<Indice> arvore;
    carregarIndicesNaArvore(arvore, indices);

    cout << "Índices na árvore:" << endl;
    arvore.Print();

    return 0;
}