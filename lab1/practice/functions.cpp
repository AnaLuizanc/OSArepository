#include<vector>
#include<iostream>
#include<fstream>
#include<sstream>
#include "Pessoa.h"
#include "functions.h"

using namespace std;

void insertPessoa(vector<string> pessoa, vector<Pessoa>& P){
    Pessoa novo;

    novo.setName(pessoa[0]);
    novo.setAge(pessoa[1]);

    P.push_back(novo);
}

void imprime_(Pessoa pessoa){
    
    cout << "Name: " << pessoa.getName() << "   ";
    cout << "Age: " << pessoa.getAge() << endl;
    
}

void imprime(vector<Pessoa> pessoas){
    for(unsigned i=0; i<pessoas.size(); i++)
        imprime_(pessoas[i]);
}


void readFile(string file){
    
    ifstream fileOpened(file);

    vector<Pessoa> P;

    vector<string> linhaPessoa;

    string line;

    if(fileOpened.is_open()){
        while(getline(fileOpened, line)){
            linhaPessoa.erase(linhaPessoa.begin(), linhaPessoa.end());
            stringstream ss(line);
            string item;

            while(getline(ss, item, ','))
                linhaPessoa.push_back(item);

            insertPessoa(linhaPessoa, P);
        }
    }

    cout << "Arquivo lido. " << P.size() << " pessoas inseridas." << endl;

    imprime(P);
    
}