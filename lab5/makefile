##############################################################################
# Exemplo de makefile para um projeto em linguagem C++...
# Para simplificar, todos os arquivos estão em um mesmo diretório
##############################################################################
# Arquivo principal: main.cpp
##############################################################################
#                       Arquivos auxiliares do projeto
##############################################################################
# Livro.cpp
# Indice.cpp
# IndiceSecundario.cpp: depende de functions.hpp
# Arvore.h: estrutura de Árvore Binária
# Buffer.cpp: depende de Livro.hpp, Indice.hpp, Arvore.h e IndiceSecundario.hpp
# functions.hpp: depende de Livro.hpp, Indice.hpp e Arvore.h
##############################################################################

# definindo as variáveis do projeto (MAIN é o nome do arquivo principal, que contem a função main, sem a extensao)
MAIN 	:= main
# objetos a serem gerados na compilação
OBJECTS := $(MAIN).o Indice.o Buffer.o Livro.o IndiceSecundario.o functions.o
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
	
# gerando o arquivo objeto da função principal... 
main.o: $(MAIN).cpp Livro.hpp Buffer.hpp Indice.hpp IndiceSecundario.hpp functions.hpp Arvore.h
	$(CC) $(FLAGS) -c $(MAIN).cpp
	
# gerando o arquivo objeto Livro.o
Livro.o: Livro.cpp Livro.hpp
	$(CC) $(FLAGS) -c Livro.cpp

# gerando o arquivo objeto Buffer.o
Buffer.o: Buffer.cpp Buffer.hpp Livro.hpp Arvore.h
	$(CC) $(FLAGS) -c Buffer.cpp

# gerando o arquivo objeto Indice.o
Indice.o: Indice.cpp Indice.hpp
	$(CC) $(FLAGS) -c Indice.cpp

# gerando o arquivo objeto IndiceSecundario.o
IndiceSecundario.o: IndiceSecundario.cpp IndiceSecundario.hpp
	$(CC) $(FLAGS) -c IndiceSecundario.cpp

# gerando o arquivo objeto functions.o
functions.o: functions.cpp functions.hpp
	$(CC) $(FLAGS) -c functions.cpp

clean:
	rm -rf $(OBJECTS)
	rm -rf $(OUTPUTMAIN)
	rm -rf *.bin
	rm -rf *.dat
	@echo Cleanup complete!!!

run: all
	rm -rf *.bin
	rm -rf *.dat
	./$(OUTPUTMAIN)
	@echo Executing 'all' complete!!!