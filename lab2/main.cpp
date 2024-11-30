
#include <iostream>
#include <cassert>
#include <fstream>

#include "Registro.hpp"
#include "Buffer.hpp"
#include "Arquivo.hpp"

const int MAX_NOME = 60;

using namespace std;

void testArquivo() {
    Arquivo arquivoCSV;
    arquivoCSV.nomeArquivo = "teste_registros.csv";

    // Cria um arquivo CSV de teste
    ofstream outFileCSV(arquivoCSV.nomeArquivo);
    outFileCSV << "Joao,25\nMaria,30\nPedro,22\n";
    outFileCSV.close();

    // Lê registros do arquivo CSV
    vector<Registro> registrosCSV = arquivoCSV.lerRegistrosCSV();
    assert(registrosCSV.size() == 3);
    assert(registrosCSV[0].nome == "Joao");
    assert(registrosCSV[0].idade == 25);
    assert(registrosCSV[1].nome == "Maria");
    assert(registrosCSV[1].idade == 30);
    assert(registrosCSV[2].nome == "Pedro");
    assert(registrosCSV[2].idade == 22);

    Arquivo arquivoBinario;
    arquivoBinario.nomeArquivo = "teste_registros.dat";

    // Adiciona registros fixos ao arquivo binário
    for (const auto& reg : registrosCSV) {
        arquivoBinario.adicionarRegistroFixo(reg);
    }

    // Lê registros fixos do arquivo binário
    vector<Registro> registrosBinario = arquivoBinario.lerRegistrosFixo();
    assert(registrosBinario.size() == 3);
    assert(registrosBinario[0].nome == "Joao");
    assert(registrosBinario[0].idade == 25);
    assert(registrosBinario[1].nome == "Maria");
    assert(registrosBinario[1].idade == 30);
    assert(registrosBinario[2].nome == "Pedro");
    assert(registrosBinario[2].idade == 22);

    cout << "Arquivo::Todos os testes passaram!" << endl;
}

void testBuffer() {
    // Cria um objeto Registro e define os valores dos atributos
    Registro reg1;
    reg1.nome = "Joao";
    reg1.idade = 25;

    // Abre um arquivo para escrita
    ofstream outFile("teste_registro.dat", ios::binary);
    Buffer buffer;
    buffer.escreverRegistroFixo(reg1, outFile);
    outFile.close();

    // Abre o arquivo para leitura
    ifstream inFile("teste_registro.dat", ios::binary);
    Registro reg2 = buffer.lerRegistroFixo(inFile);
    inFile.close();

    // Verifica se os valores dos atributos foram preservados
    assert(reg2.nome == "Joao");
    assert(reg2.idade == 25);

    cout << "Buffer::Todos os testes passaram!" << endl;
}

void testRegistro() {
    // Cria um objeto Registro e define os valores dos atributos
    Registro reg1;
    reg1.nome = "Joao";
    reg1.idade = 25;

    // Serializa o objeto
    string buffer = reg1.packFixed();

    // Cria um novo objeto Registro e desserializa o buffer
    Registro reg2;
    reg2.unpackFixed(buffer);

    // Verifica se os valores dos atributos foram preservados
    assert(reg2.nome == "Joao");
    assert(reg2.idade == 25);

    // Teste com nome maior que MAX_NOME
    Registro reg3;
    reg3.nome = "NomeMuitoGrandeParaTestarSeFuncionaCorretamente";
    reg3.idade = 30;

    // Serializa o objeto
    buffer = reg3.packFixed();

    // Cria um novo objeto Registro e desserializa o buffer
    Registro reg4;
    reg4.unpackFixed(buffer);

    // Verifica se os valores dos atributos foram preservados
    assert(reg4.nome == std::string("NomeMuitoGrandeParaTestarSeFuncionaCorretamente").substr(0, MAX_NOME));
    assert(reg4.idade == 30);

    cout << "Registro::Todos os testes passaram!" << endl;
}


int main()
{
    // Registro r1;
    testRegistro();
    testBuffer();
    testArquivo();
    return 0;
}
