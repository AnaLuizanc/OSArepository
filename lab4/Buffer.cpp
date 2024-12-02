#include "Buffer.hpp"

#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

Buffer::Buffer(const string& nomeArquivo) : nomeArquivo(nomeArquivo), inFile(nomeArquivo, ios::binary) {}

void Buffer::escreverRegistroFixo(const Livro& reg){
    ofstream outFile(nomeArquivo, ios::binary | ios::app);
    if(outFile.is_open()){
        string buffer = reg.packFixed();
        size_t dataSize = buffer.size();
        outFile.write(reinterpret_cast<const char*>(&dataSize), sizeof(dataSize));
        outFile.write(buffer.c_str(), dataSize);
        outFile.close();
    }
}

Livro Buffer::lerRegistroFixo(){
    if(inFile){
        size_t dataSize;
        inFile.read(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));
        if(inFile.eof())
            return Livro();
        string buffer(dataSize, '\0');
        inFile.read(&buffer[0], dataSize);
        Livro reg;
        reg.unpackFixed(buffer);
        
        return reg;
    }
}

vector<Livro> Buffer::lerRegistrosCSV(){
    ifstream csvFile(nomeArquivo);
    if(csvFile){
        vector<Livro> livros;
        string line;
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
        }
        csvFile.close();
        
        return livros;
    }
}