#include <iostream>
#include <string>
#include <set>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <map>

#include "Arvore.h"
#include "functions.cpp"

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
        
            string buffer(data.size() + sizeof(short int), '\0');
            strncpy(&buffer[0], to_string(data.size()).c_str(), sizeof(short int));
            strncpy(&buffer[sizeof(short int)], data.c_str(), data.size());
    
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

class Indice {
    public:
        int id;
        int endereco;

        Indice() : id(0), endereco(0) {}

        Indice(int id) : id(id) {}

        Indice(int id, int endereco) : id(id), endereco(endereco) {}

        bool operator<(const Indice& other) const {
            return id < other.id;
        }

        bool operator>(const Indice& other) const {
            return id > other.id;
        }

        bool operator==(const Indice& other) const {
            return id == other.id;
        }

        friend std::ostream& operator<<(std::ostream& os, const Indice& indice) {
            os << indice.id << " - " << indice.endereco << endl;
            return os;
        }

        string packFixed() const{
            string data = to_string(id) + "|" + to_string(endereco);

            string buffer(data.size(), '\0');
            strncpy(&buffer[0], data.c_str(), data.size());
        
            return buffer;
        }

        void unpackFixed(const string& buffer){
            int delimiter = buffer.find('|', 0);
            
            id = stoi(buffer.substr(0, delimiter));
            endereco = stoi(buffer.substr(delimiter+1, buffer.size()-1));
        }
};

class IndiceSecundario{
    public:
        int id;
        string titulo;
        map<string,vector<int>> mapeamento;

        IndiceSecundario(){}

        IndiceSecundario(int id, string titulo) : id(id), titulo(titulo){}

        void mapeamentoPalavras(IndiceSecundario& ind, pair<set<string>,set<string>> ignore){
            string text = removerStopwordsAndSimbols(ind.titulo, ignore);
            stringstream ss(text);
            string palavra;
            
            while(ss >> palavra){
                auto it = lower_bound(mapeamento[palavra].begin(), mapeamento[palavra].end(), ind.id);
                mapeamento[palavra].insert(it, ind.id);
            }
        }
};

class Buffer {
    public:
        string fileName;
        string buffer;
        ArvoreBinaria<Indice> arvore;
        IndiceSecundario hash;

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

        int carregarNrRegistros(const string& metadataFile) {
            ifstream metaFile(metadataFile, ios::binary);
            int nr_regs = 0;
            
            if (metaFile.is_open()) {
                metaFile.read(reinterpret_cast<char*>(&nr_regs), sizeof(nr_regs));
                metaFile.close();
            }
            
            return nr_regs;
        }
        
        // Função para atualizar o número de registros no arquivo de metadados
        void salvarNrRegistros(const string& metadataFile, int nr_regs) {
            ofstream metaFile(metadataFile, ios::binary | ios::trunc);
            if (metaFile.is_open()) {
                metaFile.write(reinterpret_cast<const char*>(&nr_regs), sizeof(nr_regs));
                metaFile.close();
            }
        }
        
        void escreverRegistroFixo(const Livro& liv, ofstream& saidaBinario, ofstream&saidaBinIndice, const string& metaDataFile, pair<set<string>,set<string>> ignore){
            int nr_regs = carregarNrRegistros(metaDataFile);
        
            pair<string, int> retorno = liv.packFixed();
            buffer = retorno.first;
            int id = retorno.second;
            short int tamanho = buffer.size();
        
            saidaBinario.write(reinterpret_cast<char*>(&tamanho), sizeof(tamanho));
            saidaBinario.write(buffer.c_str(), tamanho);
        
            // SERIALIZAÇÃO DO ARQUIVO DE INDICES
            Indice indice(id, nr_regs+1);
            arvore.Inserir(indice);
        
            buffer = indice.packFixed();
            tamanho = buffer.size();
        
            saidaBinIndice.write(reinterpret_cast<char*>(&tamanho), sizeof(tamanho));
            saidaBinIndice.write(buffer.c_str(), tamanho);
        
            nr_regs++;
            salvarNrRegistros(metaDataFile, nr_regs);

            IndiceSecundario indS(id, liv.titulo);
            hash.mapeamentoPalavras(indS, ignore);
            
        }
        
        pair<vector<Livro>,vector<Indice>> lerRegistroFixo(){
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
        
            // DESSERIALIZAÇÃO DO ARQUIVO DE ÍNDICES
            vector<Indice> indices;
            ifstream arquivoBinIndice("INDICES.bin", ios_base::binary | ios_base::in);
            while(arquivoBinIndice.peek() != EOF){
                short int tamanhoReg;
        
                arquivoBinIndice.read(reinterpret_cast<char*>(&tamanhoReg), sizeof(tamanhoReg));
                if(arquivoBinIndice.eof()) break;
        
                string buffer(tamanhoReg, '\0');
        
                if(arquivoBinIndice.eof()) break;
                arquivoBinIndice.read(reinterpret_cast<char*>(&buffer[0]), buffer.size());
        
                Indice indice;
                indice.unpackFixed(buffer);
                indices.push_back(indice);
            }
            arquivoBinIndice.close();
        
            return make_pair(livros, indices);
        }
};

//------------ESPAÇO PARA FUNÇÕES AUXILIARES------------//

void imprimeLivro(Livro liv){
    cout << liv.id << " - ";
    cout << liv.titulo << " - ";
    vector<string> autores = liv.autores;

    cout << "{";
    for(unsigned j=0; j<autores.size(); j++){
        cout << autores[j];
        if(j + 1 < autores.size())
            cout << ",";
    }
    cout << "} - ";

    cout << liv.ano << " - ";
    vector<string> categorias = liv.categorias;

    cout << "{";
    for(unsigned j=0; j<categorias.size(); j++){
        cout << categorias[j];
        if(j+1 < categorias.size())
            cout << ",";
    }
    cout << "}\n";
}

int pesquisaIndice(ArvoreBinaria<Indice>& arvore, int id) {
    Indice* resultado = arvore.BuscarObjeto(Indice(id, 0));
    if (resultado != NULL)
        return resultado->endereco;
    else
        return -1;
}

Livro pesquisaLivro(ArvoreBinaria<Indice>& arvore, int id){
    if(pesquisaIndice(arvore,id) != -1){
        int posicao = pesquisaIndice(arvore,id);
        Livro livro;
        ifstream arqbin;
        arqbin.open("SAIDA.bin", ios_base::in | ios_base::binary);
        arqbin.seekg(0, ios_base::end);
        
        arqbin.seekg(0, ios_base::beg);
        int nr_regs = 0;
        while (arqbin.peek() != EOF) {
            short int tamanho;
            arqbin.read(reinterpret_cast<char*>(&tamanho), sizeof(tamanho));
            if (arqbin.eof()) break;
            arqbin.seekg(tamanho, ios_base::cur);
            nr_regs++;
        }

        string buffer;
        if(posicao > 0){
            if(posicao <= nr_regs){
                arqbin.seekg(0, ios_base::beg);
                for (int i = 0; i < posicao; i++) {
                    short int tamanho;
                    arqbin.read(reinterpret_cast<char*>(&tamanho), sizeof(tamanho));
                    buffer.resize(tamanho);
                    arqbin.read(&buffer[0], tamanho);
                }
                livro.unpackFixed(buffer);
            }
            else
                cout << "Posicao nao existe" << endl;
        }
        
        arqbin.close();

        return livro;
    }
    return Livro();
}

void efetuarBuscas(ArvoreBinaria<Indice>& arvore, int id){
    if(pesquisaIndice(arvore, id) != -1){
        Livro livro = pesquisaLivro(arvore, id);
        imprimeLivro(livro);
    }
    else
        cout << "Não existe livro com esse ID!" << endl;
}

vector<int> efetuaBuscaMapa(map<string,vector<int>> mapa, Buffer& bufferBin, vector<string> search){
    if(search.size() > 1){
        vector<int> conjunto1 = mapa.find(search[0])->second;
        vector<int> conjunto2 = mapa.find(search[1])->second;
        vector<int> intersec;
        set_intersection(conjunto1.begin(), conjunto1.end(), conjunto2.begin(), conjunto2.end(), back_inserter(intersec));
        for(int i=2; i<search.size(); i++){
            conjunto1 = mapa.find(search[i])->second;
            conjunto2 = intersec;
            intersec.clear();
            set_intersection(conjunto1.begin(), conjunto1.end(), conjunto2.begin(), conjunto2.end(), back_inserter(intersec));
        }
        return intersec;
    }
    else{
        auto it = mapa.find(search[0]);
        vector<int> ids;
        if(it != mapa.end()){
            for(int id : it->second)
                ids.push_back(id);
        }
        return ids;
    }
}

vector<string> splitString(string s){
    vector<string> splited;
    istringstream iss(s);
    string palavra;
    while(iss >> palavra)
        splited.push_back(palavra);
    return splited;
}

//--------------------------------------------------------//

int main() {
    //CARREGANDO STOPWORDS E SIMBOLOS
    pair<set<string>,set<string>> ignore = CarregarStopwordAndSimbols("stopwords_en.txt", "pontuacoes.txt");

    //LEITURA DOS LIVROS DO ARQUIVO CSV
    Buffer bufferTxt("booksDataset.csv");
    vector<Livro> livros = bufferTxt.lerLivrosCsv();

    Buffer bufferBin("SAIDA.bin");
    string metadataFile = "metadata.bin";
    //SERIALIZAÇÃO
    ofstream saidaBinario("SAIDA.bin", ios::binary | ios::app);
    ofstream saidaBinIndice("INDICES.bin", ios::binary | ios::app);
    cout << endl << "Carregando no arquivo binário..." << endl << endl;
    for(unsigned i=0; i<livros.size(); i++)
        bufferBin.escreverRegistroFixo(livros[i], saidaBinario, saidaBinIndice, metadataFile, ignore);
    saidaBinario.close();
    saidaBinIndice.close();

    //PARA MOSTRAR O MAPEAMENTO
    map<string,vector<int>> mapa = bufferBin.hash.mapeamento;
    // for (const auto& entry : mapa) {
    //     cout << entry.first << " -> ";
    //     for (size_t i = 0; i < entry.second.size(); ++i) {
    //         cout << entry.second[i];
    //         if (i < entry.second.size() - 1) cout << ", ";
    //     }
    //     cout << endl;
    // }

    //DESSERIALIAÇÃO
    pair<vector<Livro>,vector<Indice>> retornoDesserializa = bufferBin.lerRegistroFixo();
    livros = retornoDesserializa.first;
    vector<Indice> indices = retornoDesserializa.second;
    
    string search;
    cout << "Digite o que procura: ";
    getline(cin, search);
    search = removerStopwordsAndSimbols(search, ignore);
    search.erase(remove_if(search.end()-1, search.end(), ::isspace), search.end());
    vector<string> palavras = splitString(search);
    vector<int> ids = efetuaBuscaMapa(mapa, bufferBin, palavras);
    cout << "Foram encontrados " << ids.size() << " ocorrências." << endl;
    for (auto i : ids)
        efetuarBuscas(bufferBin.arvore, i);

    return 0;
}
