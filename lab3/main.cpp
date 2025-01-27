#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;


class Registro {
    public:
        string nome;
        string sobrenome;
        string telefone;
        string nascimento;

        string packFixed() const{
            size_t tamanho = nome.length() + sobrenome.length() + telefone.length() + nascimento.length();
            return "a";
        }

        void unpackFixed(const string& buffer){

        }
};

class Buffer {
    public:
        string fileName;
        Registro buffer;

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
    arquivo.open("dadinhos.txt", ios_base::in); //abre pra leitura
    
    ofstream saida;
    saida.open("saida.txt", ios_base::in);

    vector<Registro> regs;

    Buffer buffer("dadinhos.txt");
    regs = buffer.lerRegistrosTxt();

    cout << regs.size() << endl;

    imprimeRegs(regs);
    escreveNoArquivo(saida, regs);


    return 0;
}