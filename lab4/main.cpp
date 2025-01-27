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

void buscarTituloPorID(const ArvoreBinaria<Indice>& arvore, Buffer& buffer, int id) {
    Indice indiceBusca(id, 0);
    Indice* indice = arvore.Buscar(indiceBusca);
    if (indice != nullptr) {
        buffer.inFile.clear(); 
        buffer.inFile.seekg(indice->endereco, ios::beg); 

        // Mensagens de depuração
        cout << "Endereço esperado: " << indice->endereco << endl;
        cout << "Endereço atual do ponteiro de leitura: " << buffer.inFile.tellg() << endl;

        Livro livro = buffer.lerRegistro();
        cout << endl << "Titulo do livro com ID " << id << ": " << livro.titulo << endl;
    } else {
        cout << "Livro com ID " << id << " não encontrado." << endl;
    }
}

// int main() {

//     Buffer bufferCSV("teste.csv");
//     pair<vector<Livro>, vector<Indice>> resultado = bufferCSV.lerRegistrosCSV();
//     vector<Livro> livros = resultado.first;
//     vector<Indice> indices = resultado.second;

//     Buffer bufferBin("livros.bin");

//     for (const auto& livro : livros) 
//         bufferBin.escreverRegistro(livro);

//     // cout << "Registros lidos do arquivo CSV:" << endl;
//     // for (const auto& livro : livros)
//     //     cout << "ID: " << livro.id << ", Titulo: " << livro.titulo << endl;

//     ArvoreBinaria<Indice> arvore;
//     carregarIndicesNaArvore(arvore, indices);

//     cout << "Indices na arvore:" << endl;
//     arvore.Print();

//     int idBusca = 53692;
//     buscarTituloPorID(arvore, bufferBin, idBusca);

//     return 0;
// }

int main () {
    Buffer bufferCSV("teste.csv");
    pair<vector<Livro>, vector<Indice>> resultado = bufferCSV.lerRegistrosCSV();
    vector<Livro> livros = resultado.first;
    vector<Indice> indices = resultado.second;

    Buffer bufferBin("livros.bin");
    Buffer bufferIndice("indices.bin");

    for (const auto& livro : livros) 
        bufferBin.escreverRegistro(livro);

    for (const auto& indice : indices)
        bufferIndice.escreverIndice(indice);

    // cout << "Registros lidos do arquivo CSV:" << endl;
    // for (const auto& livro : livros)
    //     cout << "ID: " << livro.id << ", Titulo: " << livro.titulo << endl;

    ArvoreBinaria<Indice> arvore;
    carregarIndicesNaArvore(arvore, indices);

    cout << "Indices na arvore:" << endl;
    arvore.Print();

    int idBusca = 53692;
    buscarTituloPorID(arvore, bufferBin, idBusca);

    return 0;
}