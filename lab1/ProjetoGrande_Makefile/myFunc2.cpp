#include "myFunc1.h"
#include "myFunc2.h"

#include <stdio.h>

void Troca(int* a, int* b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}
	
	
void PrintNome(const char* nome)
{
	Batata(321);
	printf("Nome_CONSTANTE = %s_%d\n", nome, MINHA_CONSTANTE);
}