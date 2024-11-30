
#include <iostream>
#include <cassert>
#include <fstream>

#include "Registro.hpp"
#include "Buffer.hpp"
#include "Arquivo.hpp"

const int MAX_NOME = 60;

using namespace std;

int main()
{
    Arquivo csv1, csv2, csv3, csv4, csv5;
    csv1.nomeArquivo = "Nomes_Idades_1.csv";
    csv2.nomeArquivo = "Nomes_Idades_2.csv";
    csv3.nomeArquivo = "Nomes_Idades_3.csv";
    csv4.nomeArquivo = "Nomes_Idades_4.csv";
    csv5.nomeArquivo = "Nomes_Idades_5.csv";
    vector<Registro> registrosCSV1 = csv1.lerRegistrosCSV();
    vector<Registro> registrosCSV2 = csv2.lerRegistrosCSV();
    vector<Registro> registrosCSV3 = csv3.lerRegistrosCSV();
    vector<Registro> registrosCSV4 = csv4.lerRegistrosCSV();
    vector<Registro> registrosCSV5 = csv5.lerRegistrosCSV();

    Arquivo bin1, bin2, bin3, bin4, bin5;
    
    bin1.nomeArquivo = "Nomes_Idades_1.bin";
    for(const auto& reg : registrosCSV1)
        bin1.adicionarRegistroFixo(reg);

    bin2.nomeArquivo = "Nomes_Idades_2.bin";
    for(const auto& reg : registrosCSV2)
        bin2.adicionarRegistroFixo(reg);

    bin3.nomeArquivo = "Nomes_Idades_3.bin";
    for(const auto& reg : registrosCSV3)
        bin3.adicionarRegistroFixo(reg);

    bin4.nomeArquivo = "Nomes_Idades_4.bin";
    for(const auto& reg : registrosCSV4)
        bin4.adicionarRegistroFixo(reg);

    bin5.nomeArquivo = "Nomes_Idades_5.bin";
    for(const auto& reg : registrosCSV5)
        bin5.adicionarRegistroFixo(reg);

    vector<Registro> registrosBin1 = bin1.lerRegistrosFixo();
    for (const auto& reg : registrosBin1)
        cout << reg.nome << " " << reg.idade << endl;
    
    vector<Registro> registrosBin2 = bin2.lerRegistrosFixo();
    for (const auto& reg : registrosBin2)
        cout << reg.nome << " " << reg.idade << endl;
    
    vector<Registro> registrosBin3 = bin3.lerRegistrosFixo();
    for (const auto& reg : registrosBin3)
        cout << reg.nome << " " << reg.idade << endl;
    
    vector<Registro> registrosBin4 = bin4.lerRegistrosFixo();
    for (const auto& reg : registrosBin4)
        cout << reg.nome << " " << reg.idade << endl;
    
    vector<Registro> registrosBin5 = bin5.lerRegistrosFixo();
    for (const auto& reg : registrosBin5)
        cout << reg.nome << " " << reg.idade << endl;

    return 0;
}
