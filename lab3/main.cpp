#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>

using namespace std;

#include "Buffer.hpp"

//------------ESPAÇO PARA FUNÇÕES AUXILIARES------------//

void imprimeRegs(vector<Registro> regs){
    for(unsigned i=0; i<regs.size(); i++){
        cout << regs[i].nome << " - ";
        cout << regs[i].sobrenome << " - ";
        cout << regs[i].telefone << " - ";
        cout << regs[i].nascimento << endl;
    }
}

void escreveNoArquivo(ofstream& saida, vector<Registro> regs){
    for(unsigned i=0; i<regs.size(); i++){
        saida << regs[i].nome << " - ";
        saida << regs[i].sobrenome << " - ";
        saida << regs[i].telefone << " - ";
        saida << regs[i].nascimento << endl;
    }
}

//------------------------------------------------------//

int main(){

    ofstream saida;
    saida.open("SAIDA.dat", ios_base::out); //abre para escrita

    vector<Registro> regs; // lidos do arquivo txt

    Buffer bufferTxt("Dados.txt");
    regs = bufferTxt.lerRegistrosTxt();

    // para verificar se está certo
    escreveNoArquivo(saida, regs);

    Buffer bufferBin("SAIDA.bin");

    for(unsigned i=0; i<regs.size(); i++)
        bufferBin.escreverRegistroFixo(regs[i]);

    // registros lidos do arquivo binário
    vector<Registro> registrosLidos = bufferBin.lerRegistroFixo();

    cout << "Há " << registrosLidos.size() << " registros lidos." << endl;
    imprimeRegs(registrosLidos);

    return 0;
}