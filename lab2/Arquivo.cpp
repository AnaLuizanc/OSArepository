#include "Arquivo.hpp"
#include "Buffer.hpp"

#include <fstream>
#include <sstream>

vector<Registro> Arquivo::lerRegistrosCSV(){
    vector<Registro> registros;
    ifstream infile(nomeArquivo);
    if(infile.is_open()){
        string line;
        while(getline(infile, line)){
            stringstream ss(line);
            string nome;
            int idade;
            getline(ss, nome, ',');
            ss >> idade;
            Registro reg;
            reg.nome = nome;
            reg.idade = idade;
            registros.push_back(reg);
        }
    }
    infile.close();
    return registros;
}

void Arquivo::adicionarRegistroFixo(Registro reg) {
    ofstream outFile(nomeArquivo, ios::binary | ios::app);
    if(outFile.is_open()){
        Buffer buffer;
        buffer.escreverRegistroFixo(reg, outFile);
    }
    outFile.close();
}

vector<Registro> Arquivo::lerRegistrosFixo() {
    vector<Registro> registros;
    ifstream inFile(nomeArquivo, ios::binary);
    if(inFile.is_open()){
        Buffer buffer;
        while(inFile.peek() != EOF){
            Registro reg = buffer.lerRegistroFixo(inFile);
            registros.push_back(reg);
        }
    }
    inFile.close();
    return registros;
}