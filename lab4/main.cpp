#include <iostream>
#include <cassert>
#include <vector>

#include "Livro.hpp"
#include "Buffer.hpp"
// #include "Indice.hpp"
// #include "Arvore.h"

using namespace std;

void testPackUnpack() {
    // Cria uma instância de Livro e preenche seus atributos
    Livro livroOriginal;
    livroOriginal.id = 1;
    livroOriginal.titulo = "O Senhor dos Anéis";
    livroOriginal.autores = {"J.R.R. Tolkien"};
    livroOriginal.ano = 1954;
    livroOriginal.generos = {"Fantasia", "Aventura"};

    // Empacota os dados em uma string
    string packedData = livroOriginal.packFixed();

    // Cria uma nova instância de Livro e desempacota os dados
    Livro livroDesempacotado;
    livroDesempacotado.unpackFixed(packedData);

    // Verifica se os dados foram preservados corretamente
    assert(livroOriginal.id == livroDesempacotado.id);
    assert(livroOriginal.titulo == livroDesempacotado.titulo);
    assert(livroOriginal.autores == livroDesempacotado.autores);
    assert(livroOriginal.ano == livroDesempacotado.ano);
    assert(livroOriginal.generos == livroDesempacotado.generos);

    // Se todas as asserções passarem, imprime uma mensagem de sucesso
    cout << "Teste de empacotamento e desempacotamento passou com sucesso!" << endl;
}

void testBuffer() {
    // Cria um objeto Buffer para ler os registros do arquivo CSV
    Buffer bufferCSV("teste.csv");
    vector<Livro> livros = bufferCSV.lerRegistrosCSV();

    // Verifica se todos os registros foram lidos corretamente
    cout << "Registros lidos do arquivo CSV:" << endl;
    for (const auto& livro : livros) {
        cout << "ID: " << livro.id << ", Título: " << livro.titulo << endl;
    }

    // Cria um objeto Buffer para escrever os registros no arquivo binário
    Buffer bufferBin("livros.bin");

    // Escreve os registros no arquivo binário
    for (const auto& livro : livros) {
        bufferBin.escreverRegistro(livro);
    }

    // Lê os registros do arquivo binário e verifica se os dados foram preservados corretamente
    bufferBin.inFile.clear(); // Limpa o estado do stream
    bufferBin.inFile.seekg(0, ios::beg); // Move o cursor para o início do arquivo

    cout << "Teste de leitura e escrita de registro fixo passou com sucesso!" << endl;
}

// void carregarIndicesNaArvore(ArvoreBinaria<Indice>& tree, const vector<Indice>& indices) {
//     for (const auto& indice : indices) {
//         tree.Inserir(indice);
//     }
// }

/*

int main() {

    Buffer bufferCSV("teste.csv");
    vector<Livro> livros = bufferCSV.lerRegistrosCSV();

    // cout << "Registros lidos do arquivo CSV:" << endl;
    // for (const auto& livro : livros)
    //     cout << "ID: " << livro.id << ", Titulo: " << livro.titulo << endl;

    Buffer bufferBin("teste.bin");

    for (const auto& livro : livros)
        bufferBin.escreverRegistroFixo(livro);

    vector<Indice> indices = bufferBin.lerIndices();

    // // Cria uma árvore binária de pesquisa e carrega os índices na árvore
    ArvoreBinaria<Indice> arvore;
    carregarIndicesNaArvore(arvore, indices);

    cout << "Indices na arvore: " << endl;
    arvore.Print();

    // // Testa a inserção e pesquisa na árvore
    Indice novoIndice(123, 456);
    arvore.Inserir(novoIndice);

    // if (arvore.Pesquisar(novoIndice)) {
    //     cout << "Índice encontrado na árvore!" << endl;
    // } else {
    //     cout << "Índice não encontrado na árvore." << endl;
    // }

    // for (const auto& livro : livros) {
    //     cout << livro.id << "#" << livro.titulo << "#";
    //     for (const auto& autor : livro.autores)
    //         cout << autor << ",";
    //     cout << "#" << livro.ano << "#";
    //     for (const auto& genero : livro.generos)
    //         cout << genero << ",";
    //     cout << endl << endl;
    // } 

    arvore.Print();

    return 0;
}

*/

int main() {
    testBuffer();

    return 0;
}