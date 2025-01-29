#include "Buffer.hpp"

Buffer::Buffer(const string& fileName){
    this->fileName = fileName;
}

vector<Registro> Buffer::lerRegistrosTxt(){
    vector<Registro> registros;
    ifstream inFile(fileName);
    if(inFile.is_open()){
        string line;
        bool isFirst = true;
        while(getline(inFile, line)){
            if(isFirst){
                isFirst = false;
                continue;
            }
            stringstream ss(line);
            string nome, sobrenome, telefone, nascimento;
            getline(ss, nome, '|');
            getline(ss, sobrenome, '|');
            getline(ss, telefone, '|');
            getline(ss, nascimento);
            Registro reg;
            reg.nome = nome;
            reg.sobrenome = sobrenome;
            reg.telefone = telefone;
            reg.nascimento = nascimento;
            registros.push_back(reg);
        }
        inFile.close();
    }
    return registros;
}

void Buffer::escreverRegistroFixo(const Registro& reg){
    ofstream saidaBinario(fileName, ios::binary | ios::app);

    buffer = reg.packFixed();
    short int tamanho = buffer.size();

    saidaBinario.write(reinterpret_cast<const char*>(&tamanho), sizeof(tamanho));
    saidaBinario.write(buffer.c_str(), tamanho);

    saidaBinario.close();
}

vector<Registro> Buffer::lerRegistroFixo(){
    vector<Registro> registros;
    ifstream arquivoBin(fileName, ios_base::binary | ios_base::in);
    while(arquivoBin.peek() != EOF){
        short int tamanhoReg;

        arquivoBin.read(reinterpret_cast<char*>(&tamanhoReg), sizeof(tamanhoReg));
        if(arquivoBin.eof()) break;

        string buffer(tamanhoReg, '\0');

        if(arquivoBin.eof()) break;
        arquivoBin.read(reinterpret_cast<char*>(&buffer[0]), buffer.size());

        Registro reg;
        reg.unpackFixed(buffer);
        registros.push_back(reg);
    }

    arquivoBin.close();

    return registros;
}