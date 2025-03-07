#include "functions.hpp"
#include "Buffer.hpp"

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

string toLowerCase(string& word){
    string lower;
    for(char c : word)
        lower += tolower(c);
    return lower;
}

string removerStopwordsAndSimbols(const string &texto, const pair<set<string>,set<string>> &ignore) {
    istringstream iss(texto);
    ostringstream oss;
    string palavra;
    set<string> stopwords = ignore.first;
    set<string> simbols = ignore.second;

    while (iss >> palavra) {
        palavra = toLowerCase(palavra);
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

vector<string> splitString(string s){
    vector<string> splited;
    istringstream iss(s);
    string palavra;
    while(iss >> palavra)
        splited.push_back(palavra);
    return splited;
}

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

vector<int> efetuaBuscaMapa(map<string,vector<int>> mapa, vector<string> search){
    if(search.size() > 1){
        vector<int> conjunto1 = mapa.find(search[0])->second;
        vector<int> conjunto2 = mapa.find(search[1])->second;
        vector<int> intersec;
        set_intersection(conjunto1.begin(), conjunto1.end(), conjunto2.begin(), conjunto2.end(), back_inserter(intersec));
        for(unsigned i=2; i<search.size(); i++){
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