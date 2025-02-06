#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <utility>

#include "Buffer.hpp"

using namespace std;

//------------ESPAÇO PARA FUNÇÕES AUXILIARES------------//

void imprimeLivros(vector<Livro> liv){
    for(unsigned i=0; i<liv.size(); i++){
        cout << liv[i].id << " - ";
        cout << liv[i].titulo << " - ";
        vector<string> autores = liv[i].autores;

        cout << "{";
        for(unsigned j=0; j<autores.size(); j++){
            cout << autores[j];
            if(j + 1 < autores.size())
                cout << ",";
        }
        cout << "} - ";

        cout << liv[i].ano << " - ";
        vector<string> categorias = liv[i].categorias;

        cout << "{";
        for(unsigned j=0; j<categorias.size(); j++){
            cout << categorias[j];
            if(j+1 < categorias.size())
                cout << ",";
        }
        cout << "}\n";
    }
}

void escreveNoArquivo(ofstream& saida, vector<Livro> liv){
    for(unsigned i=0; i<liv.size(); i++){
        saida << liv[i].id << " - ";
        saida << liv[i].titulo << " - ";
        vector<string> autores = liv[i].autores;
        saida << "{";
        for(unsigned j=0; j<autores.size(); j++){
            saida << autores[j];
            if(j + 1 < autores.size())
                saida << ",";
        }
        saida << "} - ";
        saida << liv[i].ano << " - ";
        vector<string> categorias = liv[i].categorias;
        saida << "{";
        for(unsigned j=0; j<categorias.size(); j++){
            saida << categorias[j];
            if(j+1 < categorias.size())
                saida << ",";
        }
        saida << "}" << endl;
    }
}

void imprimeLivro(Livro liv){
    cout << liv.id << " - ";
    cout << liv.titulo << " - ";
    vector<string> autores = liv.autores;

    cout << "{";
    for(unsigned j=0; j<autores.size(); j++){
        cout << autores[j];
        if(j + 1 < autores.size())
            cout << ",";
    }
    cout << "} - ";

    cout << liv.ano << " - ";
    vector<string> categorias = liv.categorias;

    cout << "{";
    for(unsigned j=0; j<categorias.size(); j++){
        cout << categorias[j];
        if(j+1 < categorias.size())
            cout << ",";
    }
    cout << "}\n";
}

void imprimeIndice(vector<Indice> indices){
    cout << "ID    | Endereco " << endl;
    for(unsigned i=0; i<indices.size(); i++)
        cout << indices[i].id << "     " << indices[i].endereco << endl;
}

int pesquisaIndice(ArvoreBinaria<Indice>& arvore, int id) {
    Indice* resultado = arvore.BuscarObjeto(Indice(id, 0));
    if (resultado != NULL)
        return resultado->endereco;
    else
        return -1;
}

Livro pesquisaLivro(ArvoreBinaria<Indice>& arvore, int id){
    if(pesquisaIndice(arvore,id)){
        int posicao = pesquisaIndice(arvore,id);
        Livro livro;
        ifstream arqbin;
        arqbin.open("SAIDA.bin", ios_base::in | ios_base::binary);
        arqbin.seekg(0, ios_base::end);
        
        arqbin.seekg(0, ios_base::beg);
        int nr_regs = 0;
        while (arqbin.peek() != EOF) {
            short int tamanho;
            arqbin.read(reinterpret_cast<char*>(&tamanho), sizeof(tamanho));
            if (arqbin.eof()) break;
            arqbin.seekg(tamanho, ios_base::cur);
            nr_regs++;
        }

        string buffer;
        if(posicao > 0){
            if(posicao <= nr_regs){
                arqbin.seekg(0, ios_base::beg);
                for (int i = 0; i < posicao; i++) {
                    short int tamanho;
                    arqbin.read(reinterpret_cast<char*>(&tamanho), sizeof(tamanho));
                    buffer.resize(tamanho);
                    arqbin.read(&buffer[0], tamanho);
                }
                livro.unpackFixed(buffer);
            }
            else
                cout << "Posicao nao existe" << endl;
        }
        
        arqbin.close();

        return livro;
    }
    return Livro();
}

void efetuarBuscas(ArvoreBinaria<Indice>& arvore, int id){
    int opcao;
    cout << endl << "1. Titulo do livro" << endl;
    cout << "2. Autor(es) do livro" << endl;
    cout << "3. Data de publicacao do livro" << endl;
    cout << "4. Categoria(s) do livro" << endl;
    cout << "5. Tudo" << endl;
    cout << "Deseja buscar por qual opcao? ";
    cin >> opcao;
    Livro livro = pesquisaLivro(arvore, id);
    switch (opcao){
    case 1:
        cout << livro.titulo << endl;
        break;
    case 2:
        for(unsigned i=0; i<livro.autores.size(); i++){
            cout << livro.autores[i];
            if(i + 1 < livro.autores.size())
                cout << ","; 
        }
        cout << endl;
        break;
    case 3:
        cout << livro.ano << endl;
        break;
    case 4:
        for(unsigned i=0; i<livro.categorias.size(); i++){
            cout << livro.categorias[i];
            if(i + 1 < livro.categorias.size())
                cout << ","; 
        }
        cout << endl;
        break;
    case 5:
        imprimeLivro(livro);
        break;
    default:
        break;
    }

}

//------------------------------------------------------//

int main(){

    ofstream saida;
    saida.open("SAIDA.dat", ios_base::out); //abre para escrita

    vector<Livro> livros; //lidos do arquivo txt

    //LEITURA DOS LIVROS DO ARQUIVO CSV
    Buffer bufferTxt("./csvFiles/booksDataset.csv");
    livros = bufferTxt.lerLivrosCsv();

    //PARA VERIFICAR SE ESTÁ CERTO
    //imprimeLivros(livros);
    escreveNoArquivo(saida, livros);

    Buffer bufferBin("SAIDA.bin");
    string metadataFile = "metadata.bin";
    //SERIALIZAÇÃO
    ofstream saidaBinario("SAIDA.bin", ios::binary | ios::app);
    ofstream saidaBinIndice("INDICES.bin", ios::binary | ios::app);
    cout << endl << "Carregando no arquivo binário..." << endl << endl;
    for(unsigned i=0; i<livros.size(); i++)
        bufferBin.escreverRegistroFixo(livros[i], saidaBinario, saidaBinIndice, metadataFile);
    saidaBinario.close();
    saidaBinIndice.close();

    //DESSERIALIAÇÃO
    pair<vector<Livro>,vector<Indice>> retornoDesserializa = bufferBin.lerRegistroFixo();
    livros = retornoDesserializa.first;
    vector<Indice> indices = retornoDesserializa.second;
    //imprimeLivros(livros);

    //NOVAS INSERÇÕES DE LIVROS
    bufferTxt.fileName = "./csvFiles/novosLivros.csv";
    livros = bufferTxt.lerLivrosCsv();
    escreveNoArquivo(saida, livros);
    saidaBinario.open("SAIDA.bin", ios::binary | ios::app);
    saidaBinIndice.open("INDICES.bin", ios::binary | ios::app);
    for(unsigned i=0; i<livros.size(); i++)
        bufferBin.escreverRegistroFixo(livros[i], saidaBinario, saidaBinIndice, metadataFile);
    saidaBinario.close();
    saidaBinIndice.close();
    retornoDesserializa = bufferBin.lerRegistroFixo();
    livros = retornoDesserializa.first;
    indices = retornoDesserializa.second;
    //imprimeLivros(livros);

    //PARA PESQUISAR LIVRO POR ID
    int pesquisa;
    cout << "Digite ID do livro para pesquisa: ";
    cin >> pesquisa;
    efetuarBuscas(bufferBin.arvore, pesquisa);

    saida.close();
    return 0;
}