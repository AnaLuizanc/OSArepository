/*********************************************************************
 * PROGRAMA 2: INTRODUÇÃO A LINGUAGEM C++
 * *******************************************************************
 * DESCRICAO: programa para exibir a soma de dois numeros inteiros
 * PROGRAMADOR: Wagner F. Barros
 * DATA: 06/10/2021
 * MODIFICACAO: 24/10/2024
 * *******************************************************************/

// inclusão de bibliotecas
#include "funcoes.h"
#include <iostream>
using namespace std;

int main()
{
    int a, b;
    a=123;
    b=321;
    cout<< "Soma de A+B = "<<Soma(a, b)<<endl; // Saída ==> "Soma de A+B = 444"
    return 0;
}