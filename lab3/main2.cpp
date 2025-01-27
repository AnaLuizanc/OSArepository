#include <iostream>
#include <fstream>
#include <vector>

#include <string>
#include <cstring>

#include <fstream>
#include <sstream>

using namespace std;

const int MAX_NOME = 30;
const int MAX_SOBRENOME = 30;
const int MAX_TELEFONE = 15;
const int MAX_NASCIMENTO = 10;

class Registro {
    public:
        string nome;
        string sobrenome;
        string telefone;
        string nascimento;

        string Registro::packFixed() const {
            string buffer(MAX_NOME + MAX_SOBRENOME + MAX_TELEFONE + MAX_NASCIMENTO,'\0');
            strncpy(&buffer[0],nome.c_str(),MAX_NOME);
            strncpy(&buffer[MAX_NOME], sobrenome.c_str(), MAX_SOBRENOME);
            strncpy(&buffer[MAX_NOME + MAX_SOBRENOME], telefone.c_str(), MAX_TELEFONE);
            strncpy(&buffer[MAX_NOME + MAX_SOBRENOME + MAX_TELEFONE], nascimento.c_str(), MAX_NASCIMENTO);
            return buffer;
        }

        void Registro::unpackFixed(const string& buffer) {
            auto extractFixedString = [](const string& buffer, unsigned offset, unsigned maxLength) -> string {
                unsigned end = buffer.find('\0', offset);
                if (end == string::npos || end > offset + maxLength) 
                    end = offset + maxLength;
                return buffer.substr(offset, end - offset);
            };

            nome = extractFixedString(buffer, 0, MAX_NOME);
            sobrenome = extractFixedString(buffer, MAX_NOME, MAX_SOBRENOME);
            telefone = extractFixedString(buffer, MAX_NOME + MAX_SOBRENOME, MAX_TELEFONE);
            nascimento = extractFixedString(buffer, MAX_NOME + MAX_SOBRENOME + MAX_TELEFONE, MAX_NASCIMENTO);
        }
};

class Buffer {
    public:
        string nomeArquivo;
        string buffer;
        ifstream inFile;

        Buffer::Buffer(const string& nomeArquivo) : nomeArquivo(nomeArquivo), inFile(nomeArquivo, ios::binary) {}

        void Buffer::escreverRegistroFixo(const Registro& reg){
            ofstream outFile(nomeArquivo, ios::binary | ios::app);
            if(outFile.is_open()){
                buffer = reg.packFixed();
                outFile.write(reinterpret_cast<const char*>(buffer.c_str()), buffer.size());
                outFile.close();
            }
        }

        Registro Buffer::lerRegistroFixo(){
            Registro reg;
            if(inFile.is_open()){
                buffer.resize(MAX_NOME + MAX_SOBRENOME + MAX_TELEFONE + MAX_NASCIMENTO, '\0');
                inFile.read(reinterpret_cast<char*>(&buffer[0]), buffer.size());
                if(inFile.gcount() > 0)
                    reg.unpackFixed(buffer);
            }
            return reg;
        }

        vector<Registro> Buffer::lerRegistrosTxt(){
            vector<Registro> registros;
            ifstream inFile(nomeArquivo);
            if(inFile.is_open()){
                string line;
                while(getline(inFile, line)){
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

        bool Buffer::temRegistros(){
            return inFile.is_open() && !inFile.eof();
        }
};