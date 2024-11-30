#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "myFunc1.h"
#include "myFunc2.h"
#include "myFunc3.h"
#include <iostream>
using namespace std;

int main()
{
	printf("TESTE");
	Batata( 123 );
	
	PrintNome("Wagner");
	
	printf("O maior entre 1 e 2 eh = %d\n", Maior(1,2) );

	int a = 10, b = 20;

	Troca(&a, &b);

	printf("a = %d, b = %d", a, b);

	return 0;
}