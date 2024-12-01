#include "Buffer.hpp"
#include "Registro.hpp"

#include <fstream>
#include <sstream>

using namespace std;

const int MAX_NOME = 30;
const int MAX_SOBRENOME = 30;
const int MAX_TELEFONE = 15;
const int MAX_NASCIMENTO = 10;

Buffer::Buffer(const string& nomeArquivo) : nomeArquivo(nomeArquivo) {}

void Buffer::escreverRegistroFixo(const Registro& reg){
    ofstream outFile(nomeArquivo, ios::binary | ios::app);
    if(outFile.is_open()){
        buffer = reg.packFixed();
        outFile.write(reinterpret_cast<const char*>(buffer.c_str()), buffer.size());
        outFile.close();
    }
}

Registro Buffer::lerRegistroFixo(){
    ifstream inFile(nomeArquivo, ios::binary);
    Registro reg;
    if(inFile.is_open()){
        buffer.resize(MAX_NOME + MAX_SOBRENOME + MAX_TELEFONE + MAX_NASCIMENTO, '\0');
        inFile.read(reinterpret_cast<char*>(&buffer[0]), buffer.size());
        if(inFile.gcount() > 0)
            reg.unpackFixed(buffer);
        inFile.close();
    }
    return reg;
}

vector<Registro> Buffer::lerRegistrosTxt(){
    vector<Registro> registros;
    ifstream infile(nomeArquivo);
    if(infile.is_open()){
        string line;
        while(getline(infile, line)){
            stringstream ss(line);
            string nome, sobrenome, telefone, nascimento;
            getline(ss, nome, '|');
            getline(ss, sobrenome, '|');
            getline(ss, telefone, '|');
            getline(ss, nascimento, '\n');
            Registro reg;
            reg.nome = nome;
            reg.sobrenome = sobrenome;
            reg.telefone = telefone;
            reg.nascimento = nascimento;
            registros.push_back(reg);
        }
        infile.close();
    }
    return registros;
}