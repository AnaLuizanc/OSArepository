#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> // setw
#include <vector>

using namespace std;

int main() {
    // CRIA UM ARQUIVO CASO NÃO EXISTA
    // ofstream arqtxt; // ofstream é o modo escrita do arquivo
    // arqtxt.open("arquivo.txt", ios_base::trunc); // ios_base::trunc apaga o conteúdo do arquivo se já existir
    // arqtxt.close();

    // ESCREVE UMA MENSAGEM SOLICITADA NO ARQUIVO 
    // char mensagem[50];
    // cin.getline(mensagem, sizeof(mensagem));
    // ofstream arqtxt;
    // arqtxt.open("arquivo.txt", ios_base::app); // ios_base::app mantém o conteúdo do arquivo se já existir (app = append -> inserção)
    // // ios_base::app posiciona o ponteiro de controle de egistros sempre no final do arquivo
    // arqtxt << mensagem << endl; // escreve a mensagem no arquivo + quebra de linha
    // arqtxt.close();
    

    // MOSTRA AS MENSAGENS ESCRITAS NO ARQUIVO
    // char mensagem;
    // ifstream arqtxt; // ifstream é o modo leitura do arquivo
    // arqtxt.open("arquivo.txt", ios_base::in); // ios_base::in abre o arquivo para leitura
    // while(!arqtxt.eof()){ // enquanto o final do arquivo não for alcançado (end of file)
    //     mensagem = arqtxt.get();
    //     cout.put(mensagem);
    // }
    // arqtxt.close();

    // ESCREVE UM VETOR DE FLOATS EM UM ARQUIVO BINÁRIO E EM UM ARQUIVO DE TEXTO
    // float a[5];
    // ofstream arqbin; // || ofstream arqbin("arquivobinario.bin", ios_base::binary);
    // ofstream arqtxt; 
    // arqbin.open("arquivobinario.bin", ios_base::binary); // ios_base::binary abre o arquivo em modo binário
    // arqtxt.open("arquivo.txt", ios_base::in);
    // for(int i=0; i<5; i++){
    //     cout << "Digite o elemento " << setw(2) << i+1 << ": "; // setw(2) ajusta a largura do campo para 2 caracteres
    //     cin >> a[i];
    //     arqtxt << a[i] << endl;
    // }
    // arqbin.write(reinterpret_cast<char*>(&a), sizeof(a)); /* escreve todos os valores do vetor no arquivo binário
    //                                                         para1: endereço inicial que se encontra o primeiro elemento do vetor
    //                                                         para2: tamanho ocupado para o armazenamento dos elementos do vetor 
    //                                                         reinterpret_cast<char*> força a conversão do tipo float para ponteiro char
    //                                                         */ 
    // arqbin.close();
    // arqtxt.close();

    // LÊ UM ARQUIVO BINÁRIO E MOSTRA OS VALORES NA TELA
    // float a[5];
    // ifstream arqbin, arqtxt;
    // arqbin.open("arquivobinario.bin", ios_base::binary);
    // arqtxt.open("arquivo.txt");
    // arqbin.read(reinterpret_cast<char*>(&a), sizeof(a)); // lê todos os valores do arquivo binário e armazena no vetor
    // for(int i=0; i<5; i++)
    //     cout << "Elemento " << setw(2) << i+1 << ": " << a[i] << endl;
    // arqbin.close();
    // arqtxt.close();

    // ESCREVE UM VETOR DE INTEIROS EM UM ARQUIVO BINÁRIO E EM UM ARQUIVO DE TEXTO
    // fstream arqbin("number.bin", ios_base::out | ios_base::binary);
    // fstream arqtxt("number.txt", ios_base::app);
    // int a[10];
    // for(int i=0, j=1; i<10; i++, j+=3){
    //     a[i] = j;
    //     arqtxt << a[i] << endl;
    // }
    // arqbin.write(reinterpret_cast<char*>(&a), sizeof(a));
    // arqbin.close();
    // arqtxt.close();

    // LÊ UM ARQUIVO BINÁRIO E MOSTRA OS VALORES NA TELA
    // int a[10];
    // fstream arqbin("number.bin", ios_base::in | ios_base::binary);
    // arqbin.read(reinterpret_cast<char*>(&a), sizeof(a));
    // for(int i=0; i<10; i++)
    //     cout << "Elemento " << setw(2) << i+1 << ": " << a[i] << endl;
    // arqbin.close();

    // ESCREVE UM VETOR DE STRINGS EM UM ARQUIVO BINÁRIO E EM UM ARQUIVO DE TEXTO
    // vector<string> vetor = {"ana", "estudando", "prova", "osa"};
    // fstream arqbin("string.bin", ios_base::out | ios_base::binary);
    // ofstream arqtxt("string.txt", ios_base::out);
    // for(int i=0; i<vetor.size(); i++){
    //     arqtxt << vetor[i] << endl;
    //     arqbin.write(reinterpret_cast<char*>(&vetor[i]), sizeof(vetor[i]));
    // }
    // arqbin.close();
    // arqtxt.close();
    // // LÊ UM ARQUIVO BINÁRIO E MOSTRA OS VALORES NA TELA
    // fstream arqbin2("string.bin", ios_base::in | ios_base::binary);
    // arqbin.read(reinterpret_cast<char*>(&vetor), sizeof(vetor));
    // for(int i=0; i<vetor.size(); i++)
    //     cout << vetor[i] << endl;
    // arqbin2.close();

    // ESCREVE NUMEROS EM UM ARQUIVO BINÁRIO E TRANSFERE O QUE FOI LIDO PARA OUTRO VETOR 
    // int a[5], b[5];
    // ofstream arq1("numeros.bin", ios_base::binary);
    // ifstream arq2("numeros.bin", ios_base::binary);
    // ofstream txt1("numeros.txt", ios_base::app);
    // for(int i=0, j=20; i<5; i++, j-=2){
    //     a[i] = j-3;
    //     txt1 << a[i] << endl;
    // }
    // arq1.write(reinterpret_cast<char*>(&a), sizeof(a));
    // txt1.close();
    // arq1.close();
    // cout << "Entrada de dados feita" << endl;
    // arq2.read(reinterpret_cast<char*>(&b), sizeof(b));
    // for(int i=0; i<5; i++){
    //     cout << "Elemento " << setw(3) << i+1 << ": ";
    //     cout << b[i] << endl;
    // }
    // arq2.close();

    // ofstream arqbin, arqtxt;
    // int valor;
    // arqbin.open("direto.bin", ios_base::app | ios_base::binary);
    // arqtxt.open("direto.txt", ios_base::app | ios_base::in);
    // do {
    //     cin >> valor;
    //     if(valor != 0){
    //         arqbin.write(reinterpret_cast<char*>(&valor), sizeof(valor));
    //         arqtxt << valor << endl;
    //     }
    // }while(valor != 0);
    // arqbin.close();
    // arqtxt.close();

    // SOLICITA POSICAO E RETORNA O REGISTRO DO ARQUIVO BIN NESSA POSICAO
    // int posicao, valor;
    // long tamanho, nr_regs;
    // ifstream arqbin;
    // arqbin.open("direto.bin", ios_base::in | ios_base::binary);
    // arqbin.seekg(0, ios_base::end);
    // tamanho = arqbin.tellg();
    // nr_regs = tamanho / 4;
    // do {
    //     cin >> posicao;
    //     if(posicao > 0){
    //         if(posicao <= nr_regs){
    //             arqbin.seekg((posicao-1) * sizeof(posicao), ios_base::beg);
    //             arqbin.read(reinterpret_cast<char*>(&valor), sizeof(valor));
    //             cout << "Na posicao " << posicao << " esta " << valor << endl;
    //         }
    //         else
    //             cout << "Posicao nao existe" << endl;
    //     }
    // }while(posicao > 0);
    // arqbin.close();

    // MUDA VALOR UM REGISTRO EM UMA POSICAO NO ARQUIVO TXT E BINÁRIO
    // int posicao, valor;
    // long tamanho, nr_regs;
    // fstream arqbin, arqtxt;
    // arqbin.open("direto.bin", ios_base::in | ios_base::out | ios_base::binary);
    // arqtxt.open("direto.txt", ios_base::in | ios_base::out);
    // arqbin.seekg(0, ios_base::end);
    // tamanho = arqbin.tellg();
    // nr_regs = tamanho / 4;

    // vector<string> linhas;
    // string linha;
    // while (getline(arqtxt, linha))
    //     linhas.push_back(linha);

    // do {
    //     cin >> posicao;
    //     if(posicao > 0){
    //         if(posicao <= nr_regs){
    //             cout << "Novo valor: ";
    //             cin >> valor;
    //             arqbin.seekg((posicao-1)*sizeof(posicao), ios_base::beg);
    //             arqbin.write(reinterpret_cast<char*>(&valor), sizeof(valor));
                
    //             if (posicao <= linhas.size())
    //                 linhas[posicao - 1] = to_string(valor);
    //             else
    //                 cout << "Posição no arquivo de texto não existe" << endl;

    //             arqtxt.close();
    //             arqtxt.open("direto.txt", ios_base::out | ios_base::trunc);

    //             for (const auto& l : linhas)
    //                 arqtxt << l << endl;
    //             cout << valor << " na posicao " << posicao << endl;
    //         }
    //         else
    //             cout << "POsicao nao existe" << endl;
    //     }
    // }while(posicao > 0);
    // arqbin.close();
    // arqtxt.close();

    return 0;
}