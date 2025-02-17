#include <iostream>
#include <string>
#include <set>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility>
#include <cstring>
#include <algorithm>

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
            for(unsigned i=0; i<autores.size(); i++){
                data += autores[i];
                if(i+1 < autores.size())
                    data += ",";
            }
            data += "|" + to_string(ano) + "|";
            for(unsigned i=0; i<categorias.size(); i++){
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
        
            if(id == 29719){
                int countChar = 0;
                while(countChar < 2){
                    delimiter = bufferAux.find('|', 0);
                    bufferAux = bufferAux.substr(0, delimiter);
                    countChar++;
                }
            }
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

class Buffer {
    public:
        string fileName;
        string buffer;
        //ArvoreBinaria<Indice> arvore;

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
                    Livro livro;
                    
                    getline(ss, id, ';');
                    
                    if(line[id.size()+1] == '\"'){
                        string lineAux = line.substr(id.size()+1);
                        int contadorAspas = 0;
                        int index = 0;
                        for(char c : lineAux){
                            if(c == '\"'){
                                contadorAspas++;
                                index++;
                            }
                            else if(c == ';'){
                                if(contadorAspas%2 == 0)
                                    break;
                                else
                                    index++;
                            }
                            else
                                index++;
                        }
                        line = lineAux.substr(index+1);
                        titulo = lineAux.substr(0, index);
                        stringstream ssAux(line);
                        getline(ssAux, autores, ';');
                        getline(ssAux, ano, ';');
                        getline(ssAux, categorias, '\n');
                    }else {
                        getline(ss, titulo, ';');
                        getline(ss, autores, ';');
                        getline(ss, ano, ';');
                        getline(ss, categorias, '\n');
                    }
        
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
};

pair<set<string>,set<string>> CarregarStopwordAndSimbols(const string &arq, const string& arqSimbols){
    set<string> stopwords, simbols;
    ifstream arquivo(arq), arquivoSimbols(arqSimbols);
    string palavra, simbolo;

    if (!arquivo.is_open())
        throw runtime_error("Erro ao abrir o arquivo de stopwords: " + arq);

    if(!arquivoSimbols.is_open())
        throw runtime_error("Erro ao abrir o arquivo de símbolos: " + arqSimbols);
    
    while(getline(arquivo, palavra)){
        // Remove espaços em branco no início e fim da palavra
        palavra.erase(0, palavra.find_first_not_of(" \t\n\r\f\v"));
        palavra.erase(palavra.find_last_not_of(" \t\n\r\f\v") + 1);
        
        // Adiciona apenas palavras não vazias
        if(!palavra.empty())
            stopwords.insert(palavra);
    }
    arquivo.close();

    while(getline(arquivoSimbols, simbolo)){
        // Remove espaços em branco no início e fim da simbolo
        simbolo.erase(0, simbolo.find_first_not_of(" \t\n\r\f\v"));
        simbolo.erase(simbolo.find_last_not_of(" \t\n\r\f\v") + 1);
        
        // Adiciona apenas simbolos não vazias
        if (!simbolo.empty())
            simbols.insert(simbolo);
    }

    arquivoSimbols.close();

    return make_pair(stopwords,simbols);
}

// Função de filtragem
string removerStopwordsAndSimbols(const string &texto, const pair<set<string>,set<string>> &ignore) {
    istringstream iss(texto);
    ostringstream oss;
    string palavra;
    set<string> stopwords = ignore.first;
    set<string> simbols = ignore.second;

    while (iss >> palavra) {
        // Remover símbolos da palavra
        for(const string& simbolo : simbols){
            size_t pos;
            while ((pos = palavra.find(simbolo)) != string::npos)
            palavra.erase(pos, simbolo.length());
        }
        
        if (stopwords.find(palavra) == stopwords.end()) // Se a palavra não for uma stopword
            oss << palavra << " ";
    }
    return oss.str();
}


//------------ESPAÇO PARA FUNÇÕES AUXILIARES------------//

void imprimeLivros(vector<Livro> liv){
    for(unsigned i=0; i<liv.size(); i++){
        cout << liv[i].id << " - ";
        cout << liv[i].titulo << " - ";
        vector<string> autores = liv[i].autores;

        cout << "{";
        for(unsigned j=0; j<autores.size(); j++){
            cout << autores[j];
            if(j + 1 < autores.size())
                cout << ",";
        }
        cout << "} - ";

        cout << liv[i].ano << " - ";
        vector<string> categorias = liv[i].categorias;

        cout << "{";
        for(unsigned j=0; j<categorias.size(); j++){
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
        for(unsigned j=0; j<autores.size(); j++){
            saida << autores[j];
            if(j + 1 < autores.size())
                saida << ",";
        }
        saida << "} - ";
        saida << liv[i].ano << " - ";
        vector<string> categorias = liv[i].categorias;
        saida << "{";
        for(unsigned j=0; j<categorias.size(); j++){
            saida << categorias[j];
            if(j+1 < categorias.size())
                saida << ",";
        }
        saida << "}" << endl;
    }
}

//--------------------------------------------------------//

int main() {
    //CARREGANDO STOPWORDS E SIMBOLOS
    pair<set<string>,set<string>> ignore = CarregarStopwordAndSimbols("stopwords_en.txt", "pontuacoes.txt");

    ofstream saida;
    saida.open("SAIDA.dat", ios_base::out); //abre para escrita

    vector<Livro> livros; //lidos do arquivo txt

    //LEITURA DOS LIVROS DO ARQUIVO CSV
    Buffer bufferTxt("teste.csv");
    livros = bufferTxt.lerLivrosCsv();

    //PARA VERIFICAR SE ESTÁ CERTO
    imprimeLivros(livros);
    escreveNoArquivo(saida, livros);

    return 0;
}
