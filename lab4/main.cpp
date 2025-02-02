#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <utility>

#include "Arvore.h"

using namespace std;

class Livro {
    public:
        int id;
        string titulo;
        vector<string> autores;
        int ano;
        vector<string> categorias;

        pair<string,int> packFixed() const{
            string data = "|" + to_string(id) + "|" + titulo + "|";
            for(int i=0; i<autores.size(); i++){
                data += autores[i];
                if(i+1 < autores.size())
                    data += ",";
            }
            data += "|" + to_string(ano) + "|";
            for(int i=0; i<categorias.size(); i++){
                data += categorias[i];
                if(i+1 < categorias.size())
                    data += ",";
            }

            ofstream saidaTxt;
            saidaTxt.open("saidapack.dat", ios_base::app);

            saidaTxt << data.size() << data << endl;
            
            string buffer(data.size() + sizeof(short int), '\0');
            strncpy(&buffer[0], to_string(data.size()).c_str(), sizeof(short int));
            strncpy(&buffer[sizeof(short int)], data.c_str(), data.size());

            saidaTxt.close();

            return make_pair(buffer,id);
        }

        void unpackFixed(const string& buffer){
            int bufferSize = buffer.size();
            int delimiter = buffer.find('|', 0);
            string bufferAux = buffer.substr(delimiter+1, bufferSize);

            delimiter = bufferAux.find('|', 0);
            id = stoi(bufferAux.substr(0, delimiter));
            bufferAux = bufferAux.substr(delimiter+1, bufferAux.size());

            delimiter = bufferAux.find('|', 0);
            titulo = bufferAux.substr(0, delimiter);
            bufferAux = bufferAux.substr(delimiter+1, bufferAux.size());

            delimiter = bufferAux.find('|', 0);
            stringstream ssAutores(bufferAux.substr(0, delimiter));
            string autor;
            while(getline(ssAutores, autor, ','))
                autores.push_back(autor);
            bufferAux = bufferAux.substr(delimiter+1, bufferAux.size());

            delimiter = bufferAux.find('|', 0);
            ano = stoi(bufferAux.substr(0, delimiter));
            bufferAux = bufferAux.substr(delimiter+1, bufferAux.size());

            delimiter = bufferAux.find('|', 0);
            stringstream ssCategorias(bufferAux.substr(0, delimiter));
            string categoria;
            while(getline(ssCategorias, categoria, ','))
                categorias.push_back(categoria);
        }
};

class Indice {
    public:
        int id;
        int endereco;

        Indice(int id, int endereco){
            this->id = id;
            this->endereco = endereco;
            
        }

        // void insereIndice(){
        //     ArvoreBinaria::Inserir
        // }
};

class Buffer {
    public:
        string fileName;
        string buffer;

        Buffer(const string& fileName){
            this->fileName = fileName;
        }

        vector<Livro> lerLivrosCsv(){
            vector<Livro> livros;
            ifstream inFile(fileName);
            if(inFile.is_open()){
                string line;
                bool isFirst = true;
                while(getline(inFile, line)){
                    if(isFirst){
                        isFirst = false;
                        continue;
                    }
                    stringstream ss(line);
                    string titulo, id, ano, autores, categorias;
                    getline(ss, id, ';');
                    getline(ss, titulo, ';');
                    getline(ss, autores, ';');
                    getline(ss, ano, ';');
                    getline(ss, categorias, '\n');
                    
                    Livro livro;
                    livro.id = stoi(id);
                    livro.titulo = titulo;
                    
                    stringstream ssAutores(autores);
                    string autor;
                    while(getline(ssAutores, autor, ','))
                        livro.autores.push_back(autor);

                    livro.ano = stoi(ano);
                    
                    stringstream ssCategorias(categorias);
                    string categoria;
                    
                    while(getline(ssCategorias, categoria, ',')){
                        categoria.erase(remove_if(categoria.begin(), categoria.begin()+1, ::isspace), categoria.begin()+1);
                        categoria.erase(remove_if(categoria.end()-1, categoria.end(), ::isspace), categoria.end());
                        if(categoria.size() == 0)
                            livro.categorias.push_back("Nenhum");
                        else
                            livro.categorias.push_back(categoria);
                    }
                    
                    livros.push_back(livro);
                }
            }
            inFile.close();

            return livros;
        }
        
        void escreverRegistroFixo(const Livro& liv){
            Livro valor;
            long tam;
            ifstream arqbin;
            arqbin.open(fileName, ios_base::in | ios_base::binary);
            arqbin.seekg(0, ios_base::end);
            tam = arqbin.tellg();
            
            arqbin.seekg(0, ios_base::beg);
            int nr_regs = 0;
            while (arqbin.peek() != EOF) {
                short int tam;
                arqbin.read(reinterpret_cast<char*>(&tam), sizeof(tam));
                if (arqbin.eof()) break;
                arqbin.seekg(tam, ios_base::cur);
                nr_regs++;
            }            
            
            ofstream saidaBinario(fileName, ios::binary | ios::app);

            pair<string,int> retorno = liv.packFixed();
            buffer = retorno.first;
            int id = retorno.second;
            short int tamanho = buffer.size();

            saidaBinario.write(reinterpret_cast<char*>(&tamanho), sizeof(tamanho));
            saidaBinario.write(buffer.c_str(), tamanho);

            Indice indice(id, nr_regs);
            // indice.insereIndice();

            saidaBinario.close();
        }

        vector<Livro> lerRegistroFixo(){
            vector<Livro> livros;
            ifstream arquivoBin(fileName, ios_base::binary | ios_base::in);
            while(arquivoBin.peek() != EOF){
                short int tamanhoReg;

                arquivoBin.read(reinterpret_cast<char*>(&tamanhoReg), sizeof(tamanhoReg));
                if(arquivoBin.eof()) break;

                string buffer(tamanhoReg, '\0');

                if(arquivoBin.eof()) break;
                arquivoBin.read(reinterpret_cast<char*>(&buffer[0]), buffer.size());

                Livro livro;
                livro.unpackFixed(buffer);
                livros.push_back(livro);
            }
            arquivoBin.close();

            return livros;
        }
};

//------------ESPAÇO PARA FUNÇÕES AUXILIARES------------//

void imprimeLivros(vector<Livro> liv){
    for(unsigned i=0; i<liv.size(); i++){
        cout << liv[i].id << " - ";
        cout << liv[i].titulo << " - ";
        vector<string> autores = liv[i].autores;
        
        cout << "{";
        for(int j=0; j<autores.size(); j++){
            cout << autores[j];
            if(j + 1 < autores.size())
                cout << ",";
        }
        cout << "} - ";
        
        cout << liv[i].ano << " - ";
        vector<string> categorias = liv[i].categorias;
        
        cout << "{";
        for(int j=0; j<categorias.size(); j++){
            cout << categorias[j];
            if(j+1 < categorias.size())
                cout << ",";
        }
        cout << "}\n";
    }
}

void escreveNoArquivo(ofstream& saida, vector<Livro> liv){
    for(unsigned i=0; i<liv.size(); i++){
        saida << liv[i].id << " - ";
        saida << liv[i].titulo << " - ";
        vector<string> autores = liv[i].autores;
        saida << "{";
        for(int j=0; j<autores.size(); j++){
            saida << autores[j];
            if(j + 1 < autores.size())
                saida << ",";
        }
        saida << "} - ";
        saida << liv[i].ano << " - ";
        vector<string> categorias = liv[i].categorias;
        saida << "{";
        for(int j=0; j<categorias.size(); j++){
            saida << categorias[j];
            if(j+1 < categorias.size())
                saida << ",";
        }
        saida << "}" << endl;
    }
}

void imprimeLivro(Livro liv){
    cout << liv.id << " - ";
    cout << liv.titulo << " - ";
    vector<string> autores = liv.autores;
    
    cout << "{";
    for(int j=0; j<autores.size(); j++){
        cout << autores[j];
        if(j + 1 < autores.size())
            cout << ",";
    }
    cout << "} - ";
    
    cout << liv.ano << " - ";
    vector<string> categorias = liv.categorias;
    
    cout << "{";
    for(int j=0; j<categorias.size(); j++){
        cout << categorias[j];
        if(j+1 < categorias.size())
            cout << ",";
    }
    cout << "}\n";
}

//------------------------------------------------------//

int main(){

    ofstream saida;
    saida.open("SAIDA.dat", ios_base::out); //abre para escrita

    vector<Livro> livros; // lidos do arquivo txt

    Buffer bufferTxt("teste.csv");
    livros = bufferTxt.lerLivrosCsv();

    // para verificar se está certo
    //imprimeLivros(livros);
    escreveNoArquivo(saida, livros);

    Buffer bufferBin("SAIDA.bin");

    for(unsigned i=0; i<livros.size(); i++)
        bufferBin.escreverRegistroFixo(livros[i]);

    vector<Livro> livrosLidos = bufferBin.lerRegistroFixo();

    // cout << "há " << livrosLidos.size() << " livros lidos." << endl;
    // imprimeLivros(livrosLidos);

    saida.close();

    return 0;
}