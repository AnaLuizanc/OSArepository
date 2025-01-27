#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Pessoa.h"
#include "functions.h"

using namespace std;

int main(){
    

    cout << "LEITURA DO ARQUIVO 1" << endl;
    readFile("Nomes_Idades_1.csv");
    cout << endl << "LEITURA DO ARQUIVO 2" << endl;
    readFile("Nomes_Idades_2.csv");
    cout << endl << "LEITURA DO ARQUIVO 3" << endl;
    readFile("Nomes_Idades_3.csv");
    cout << endl << "LEITURA DO ARQUIVO 4" << endl;
    readFile("Nomes_Idades_4.csv");
    cout << endl << "LEITURA DO ARQUIVO 5" << endl;
    readFile("Nomes_Idades_5.csv");

    return 0;
}