#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>

using namespace std;


class Registro {
    public:
        string nome;
        string sobrenome;
        string telefone;
        string nascimento;

        string packFixed() const{
            string data = "|" + nome + "|" + sobrenome + "|" + telefone + "|" + nascimento;
            string buffer(data.size(), '\0');

            ofstream saidaTxt;
            saidaTxt.open("saidapack.txt", ios_base::app);

            saidaTxt << data.size() << data << endl;

            buffer.resize(data.size() + sizeof(short int), '\0');
            strncpy(&buffer[0], to_string(data.size()).c_str(), sizeof(short int));
            strncpy(&buffer[sizeof(short int)], data.c_str(), data.size());

            saidaTxt.close();

            return buffer;
        }

        void unpackFixed(const string& buffer){
            int bufferSize = buffer.size();
            int delimiter = buffer.find('|', 0);
            string bufferAux = buffer.substr(delimiter+1, bufferSize);

            delimiter = bufferAux.find('|', 0);
            nome = bufferAux.substr(0, delimiter);
            bufferAux = bufferAux.substr(delimiter+1, bufferAux.size());

            delimiter = bufferAux.find('|', 0);
            sobrenome = bufferAux.substr(0, delimiter);
            bufferAux = bufferAux.substr(delimiter+1, bufferAux.size());

            delimiter = bufferAux.find('|', 0);
            telefone = bufferAux.substr(0, delimiter);
            bufferAux = bufferAux.substr(delimiter+1, bufferAux.size());

            delimiter = bufferAux.find('|', 0);
            nascimento = bufferAux.substr(0, delimiter);
        }
};

class Buffer {
    public:
        string fileName;
        string buffer;

        Buffer(const string& fileName){
            this->fileName = fileName;
        }

        vector<Registro> lerRegistrosTxt(){
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

        void escreverRegistroFixo(const Registro& reg){
            ofstream saidaBinario(fileName, ios::binary | ios::app);

            buffer = reg.packFixed();
            short int tamanho = buffer.size();

            saidaBinario.write(reinterpret_cast<const char*>(&tamanho), sizeof(tamanho));
            saidaBinario.write(buffer.c_str(), tamanho);
            
            saidaBinario.close();
        }

        vector<Registro> lerRegistroFixo(){
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
};

//------------ESPAÇO PARA FUNÇÕES AUXILIARES------------//

void imprimeRegs(vector<Registro> regs){
    for(int i=0; i<regs.size(); i++){
        cout << regs[i].nome << " - ";
        cout << regs[i].sobrenome << " - ";
        cout << regs[i].telefone << " - ";
        cout << regs[i].nascimento << endl;
    }
}

void escreveNoArquivo(ofstream& saida, vector<Registro> regs){
    for(int i=0; i<regs.size(); i++){
        saida << regs[i].nome << " - ";
        saida << regs[i].sobrenome << " - ";
        saida << regs[i].telefone << " - ";
        saida << regs[i].nascimento << endl;
    }
}

//------------------------------------------------------//

int main(){

    ifstream arquivo; //arquivo menor de teste
    arquivo.open("Dadinhos.txt", ios_base::in); //abre pra leitura
    
    ofstream saida;
    saida.open("saida.txt", ios_base::out); //abre para escrita

    vector<Registro> regs; // lidos dos arquivo txt

    Buffer bufferTxt("Dadinhos.txt");
    regs = bufferTxt.lerRegistrosTxt();

    Buffer bufferBin("saida.dat");

    // imprimeRegs(regs);
    // escreveNoArquivo(saida, regs);

    for(int i=0; i<regs.size(); i++){
        bufferBin.escreverRegistroFixo(regs[i]);
    }

    // registros lidos do arquivo binário
    vector<Registro> registrosLidos = bufferBin.lerRegistroFixo();

    cout << "Há " << registrosLidos.size() << " registros lidos." << endl;
    imprimeRegs(registrosLidos);

    return 0;
}