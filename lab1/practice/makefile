##############################################################################
# Exemplo de makefile para um projeto em linguagem C++...
# Para simplificar, todos os arquivos estão em um mesmo diretório
##############################################################################
# Arquivo principal: main.cpp
##############################################################################
#                       Arquivos auxiliares do projeto
##############################################################################
# functions.cpp: depende de functions.h (definição dos protótipos das funções 
#            auxiliares utilizadas no arquivo functions.c
##############################################################################

# definindo as variáveis do projeto (MAIN é o nome do arquivo principal, que contem a função main, sem a extensao)
MAIN 	:= main
# objetos a serem gerados na compilação
OBJECTS := $(MAIN).o functions.o
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
main.o: $(MAIN).cpp functions.h
	$(CC) $(FLAGS) -c $(MAIN).cpp
	
# gerando o arquivo objeto da minha biblioteca 1 (fucntions.o) que depende dos arquivos functions.c, functions.h
functions.o: functions.cpp functions.h
	$(CC) $(FLAGS) -c functions.cpp

clean:
	rm -rf $(OBJECTS)
	rm -rf $(OUTPUTMAIN)
	@echo Cleanup complete!!!

run: all
	./$(OUTPUTMAIN)
	@echo Executing 'all' complete!!!