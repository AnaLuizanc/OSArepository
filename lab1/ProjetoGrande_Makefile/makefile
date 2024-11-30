##############################################################################
# Exemplo de makefile para um projeto em linguagem C++...
# Para simplificar, todos os arquivos estão em um mesmo diretório
##############################################################################
# Arquivo principal: main.cpp
##############################################################################
#                       Arquivos auxiliares do projeto
##############################################################################
# myFunc1.cpp: depende de myFunc1.h (definição dos protótipos das funções 
#            auxiliares utilizadas no arquivo myFunc1.c e algumas constantes 
#            usadas tanto em myFunc1.c, quanto em myFunc2.cpp)
# myFunc2.cpp: depende de myFunc2.h e myFunc1.h( definição de constantes e dos 
#            protótipos das funções usadas no arquivo myFunc2.cpp) 
# myFunc3.cpp: depende de myFunc3.h e outros.h (ambos contem ou constantes ou 
#            protótipos de funções contidas no arquivo myFunc3.cpp) 
##############################################################################

# definindo as variáveis do projeto (MAIN é o nome do arquivo principal, que contem a função main, sem a extensao)
MAIN 	:= main
# objetos a serem gerados na compilação
OBJECTS := $(MAIN).o myFunc1.o myFunc2.o myFunc3.o
# (para C, pode-se usar o padrão ISO 2011 (c11) ou 2018 (c18), dependendo do seu compilador...
# usar -std=c98 no lugar do c++11, c++17, c++20, etc.. 

FLAGS 	:= -Wall -Wextra -std=c++17 -pedantic-errors


# habilitar a depuração
DEBUG :=  -g

# necessário apenas quando se incluir  a biblioteca <math.h> em algum arquivo fonte no projeto
MATH 	:= -lm

# definição do compilador: para C usar o gcc, por exemplo
CC		:= g++

# ajustando alguns parâmetros/comandos ao sistema operacional
ifeq ($(OS), Windows_NT)
OUTPUTMAIN := $(MAIN).exe
else
OUTPUTMAIN := $(MAIN).out
endif

# ponto de compilação principal
all: main.exe
	@echo Compiling 'all' complete!

# gerando o arquivo executavel
main.exe: $(OBJECTS)  
	$(CC) $(FLAGS) $(OBJECTS) -o $(OUTPUTMAIN) $(MATH)
	
# gerando o arquivo objeto da função principal... adicionar as dependencias (se houverem)
main.o: $(MAIN).cpp myFunc1.h myFunc2.h myFunc3.h outros.h
	$(CC) $(FLAGS) -c $(MAIN).cpp
	
# gerando o arquivo objeto da minha biblioteca 1 (myFunc1.o) que depende dos arquivos myFunc1.c, myFunc1.h
myFunc1.o: myFunc1.cpp myFunc1.h
	$(CC) $(FLAGS) -c myFunc1.cpp

# gerando o arquivo objeto da minha biblioteca 2 (myFunc2.o) que depende dos arquivos myFunc2.c, myFunc2.h e myFunc1.h
myFunc2.o: myFunc2.cpp myFunc1.h myFunc2.h
	$(CC) $(FLAGS) -c myFunc2.cpp

# gerando o arquivo objeto da minha biblioteca 3 (myFunc3.o) que depende dos arquivos myFunc3.c, myFunc3.h e outros.h
myFunc3.o: myFunc3.cpp myFunc3.h outros.h
	$(CC) $(FLAGS) -c myFunc3.cpp

clean:
	rm -rf $(OBJECTS)
	rm -rf $(OUTPUTMAIN)
	@echo Cleanup complete!!!

run: all
	./$(OUTPUTMAIN)
	@echo Executing 'all' complete!!!