#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

class Livro {
    public:
        int id;
        string titulo;
        vector<string> autores;
        int ano;
        vector<string> categorias;

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
                        cout << endl << categoria.size() << "-" << categoria << endl;
                        livro.categorias.push_back(categoria);
                    }
                    
                    livros.push_back(livro);

                }
            }
            inFile.close();

            return livros;
        }
        // void escreverRegistroFixo(const Registro& reg);
        // vector<Registro> lerRegistroFixo();
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

//------------------------------------------------------//

int main(){

    ofstream saida;
    saida.open("SAIDA.dat", ios_base::out); //abre para escrita

    vector<Livro> livros; // lidos do arquivo txt

    Buffer bufferTxt("teste.csv");
    livros = bufferTxt.lerLivrosCsv();

    // para verificar se está certo
    imprimeLivros(livros);
    escreveNoArquivo(saida, livros);

    cout << livros[0].categorias.size() << endl;
    cout << livros[2].categorias.size() << endl;

    saida.close();

    return 0;
}