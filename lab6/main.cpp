#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class BTreeNode{
    public:
        vector<T> chaves;
        vector<BTreeNode*> filhos;
        int n; // qtd de chaves
        bool ehFolha;

        BTreeNode(int ordem, bool folha = true) : n(0), ehFolha(folha), chaves(ordem-1), filhos(ordem, nullptr){}

};

// class for B-Tree
template <typename T>
class BTree{
    private:
        BTreeNode<T>* raiz; // Ponteiro para o nó da raiz
        int ordem;

        void insereNoNaoCheio(BTreeNode<T>* noAtual, T novo){
            int posicao = noAtual->n - 1;
            
            if(noAtual->ehFolha){
                cout << "folha" << endl;
                while(posicao >= 0 && novo < noAtual->chaves[posicao]){
                    noAtual->chaves[posicao+1] = noAtual->chaves[posicao];
                    posicao--;
                }
                noAtual->chaves[posicao+1] = novo;
                (noAtual->n)++;
            }
            else{
                while(posicao >= 0 && novo < noAtual->chaves[posicao])
                    posicao--;
                posicao++;
                if(noAtual->filhos[posicao]->n == ordem*2){
                    cout << "ta cheio" << endl;
                }
                insereNoNaoCheio(noAtual->filhos[posicao], novo);
            }
        }

    public:
        BTree(int ordem) : ordem(ordem){
            raiz = new BTreeNode<T>(ordem, true);
        }

        void insere(T novo){
            if(raiz->n == ordem*2){
                BTreeNode<T>* novoNo = new BTreeNode<T>(ordem, false);
                novoNo->filhos[0] = raiz;
                raiz = novoNo;
                //divideNoFilhoCheio(raiz,0);
                // tem algo aqui ainda
            }
            else
                insereNoNaoCheio(raiz, novo);

        }

};

int main() {
    vector<int> numbers = {20,40,10,30,15,35,7,26,18,22,5,42,13,46,27,8,32,38,24,45,25};
    BTree<int> arvore(2);

    arvore.insere(numbers[0]);
    arvore.insere(numbers[1]);
    arvore.insere(numbers[2]);
    arvore.insere(numbers[3]);
    arvore.insere(numbers[4]);

    return 0;
}
