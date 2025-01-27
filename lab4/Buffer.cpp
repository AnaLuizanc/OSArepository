#include "Buffer.hpp"
#include "Indice.hpp"

#include <fstream>
#include <sstream>
#include <vector>
#include <utility>

using namespace std;

Buffer::Buffer(const string& nomeArquivo) : nomeArquivo(nomeArquivo), inFile(nomeArquivo, ios::binary) {}

void Buffer::escreverRegistro(const Livro& reg){
    ofstream outFile(nomeArquivo, ios::binary | ios::app);
    if(outFile.is_open()){
        long endereco = outFile.tellp();
        string buffer = reg.packFixed();
        size_t dataSize = buffer.size();
        outFile.write(reinterpret_cast<const char*>(&dataSize), sizeof(dataSize));
        outFile.write(buffer.c_str(), dataSize);
        outFile.close();

        Indice indice(reg.id, endereco);
        escreverIndice(indice);
    }
}

Livro Buffer::lerRegistro(){
    if (!inFile.is_open())
        inFile.open(nomeArquivo, ios::binary);
    if(inFile.is_open()){
        size_t dataSize;
        inFile.read(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));
        if(inFile.eof() || dataSize == 0)
            return Livro();
        string buffer(dataSize, '\0');
        inFile.read(&buffer[0], dataSize);
        Livro reg;
        reg.unpackFixed(buffer);

        return reg;
    }
    return Livro();
}

pair<vector<Livro>, vector<Indice>> Buffer::lerRegistrosCSV(){
    ifstream csvFile(nomeArquivo);
    if(csvFile){
        vector<Livro> livros;
        vector<Indice> indices;
        string line;
        int endereco = 0;
        while(getline(csvFile,line)){
            stringstream ss(line);
            string field;
            Livro liv;
            getline(ss, field, ';');
            liv.id = stoi(field);
            getline(ss, field, ';');
            liv.titulo = field;
            getline(ss, field, ';');
            stringstream ssAutores(field);
            string autor;
            while(getline(ssAutores, autor, ','))
                liv.autores.push_back(autor);
            getline(ss, field, ';');
            liv.ano = stoi(field);
            getline(ss, field, ';');
            stringstream ssGeneros(field);
            string genero;
            while(getline(ssGeneros, genero, ','))
                liv.generos.push_back(genero);
            
            livros.push_back(liv);

            Indice indice(liv.id, endereco++);
            indices.push_back(indice);
        }
        csvFile.close();
        
        return make_pair(livros, indices);
    }
    return make_pair(vector<Livro>(), vector<Indice>());
}

void Buffer::escreverIndice(const Indice& indice){
    ofstream outFile(nomeArquivo, ios::binary | ios::app);
    if(outFile){
        string buffer = indice.packFixed();
        size_t dataSize = buffer.size();
        outFile.write(reinterpret_cast<const char*>(&dataSize), sizeof(dataSize));
        outFile.write(buffer.c_str(), dataSize);
        outFile.close();
    }
}

vector<Indice> Buffer::lerIndices(){
    ifstream inFile("indices.bin", ios::binary);
    vector<Indice> indices;
    while(true){
        size_t dataSize;
        inFile.read(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));
        if(inFile.eof())
            break;
        string buffer(dataSize, '\0');
        inFile.read(&buffer[0], dataSize);
        if(inFile.eof())
            break;
        Indice indice;
        indice.unpackFixed(buffer);
        indices.push_back(indice);
    }
    inFile.close();
    return indices;
}