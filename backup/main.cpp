#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>

#include "Registro.hpp"
#include "Buffer.hpp"

using namespace std;

int main()
{
    string nomeArquivo = "Dados.txt";
    string nomeArquivoBin = "Dados.bin";

    Buffer bufferTxt(nomeArquivo);
    vector<Registro> registros = bufferTxt.lerRegistrosTxt();

    Buffer bufferBinarioEscrita(nomeArquivoBin);
    for (const auto& reg : registros)
        bufferBinarioEscrita.escreverRegistroFixo(reg);

    Buffer bufferBinarioLeitura(nomeArquivoBin);
    vector<Registro> registrosLidos;
    while(bufferBinarioLeitura.temRegistros()) {
        Registro reg = bufferBinarioLeitura.lerRegistroFixo();
        if (reg.nome.empty() && reg.sobrenome.empty() && reg.telefone.empty() && reg.nascimento.empty())
            break;
        registrosLidos.push_back(reg);
    }

    assert(registros.size() == registrosLidos.size());
    for (unsigned i = 0; i < registros.size(); ++i) {
        assert(registros[i].nome == registrosLidos[i].nome);
        assert(registros[i].sobrenome == registrosLidos[i].sobrenome);
        assert(registros[i].telefone == registrosLidos[i].telefone);
        assert(registros[i].nascimento == registrosLidos[i].nascimento);
    }

    return 0;
}
