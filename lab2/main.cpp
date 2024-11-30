
#include <iostream>
#include <cassert>

#include "Registro.hpp"

const int MAX_NOME = 60;

using namespace std;

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

    cout << "Todos os testes passaram!" << endl;
}


int main()
{
    // Registro r1;
    testRegistro();
    return 0;
}
