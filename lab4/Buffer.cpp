#include "Buffer.hpp"

vector<Livro> Buffer::lerLivrosCsv(){
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

void Buffer::escreverRegistroFixo(const Livro& liv, ofstream& saidaBinario, ofstream&saidaBinIndice, const string& metaDataFile){
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
}

pair<vector<Livro>,vector<Indice>> Buffer::lerRegistroFixo(){
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