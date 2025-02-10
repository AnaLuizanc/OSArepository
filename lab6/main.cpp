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

        BTreeNode(int ordem, bool folha = true) : n(0), ehFolha(folha), chaves(ordem*2), filhos(ordem*2+1, nullptr){}

};

// class for B-Tree
template <typename T>
class BTree{
    private:
        BTreeNode<T>* raiz; // Ponteiro para o nó da raiz
        int ordem;

        void divideNoFilhoCheio(BTreeNode<T>* atual, int posicao){
            BTreeNode<T>* esquerda = atual->filhos[posicao];
            BTreeNode<T>* direita = new BTreeNode<T>(ordem,esquerda->ehFolha);
            direita->n = ordem; //ordem * 2 / 2

            for(int j=0; j<ordem; j++)
                direita->chaves[j] = esquerda->chaves[j+ordem];

            if(!esquerda->ehFolha){
                for(int i=0; i<ordem; i++)
                    direita->filhos[i] = esquerda->filhos[i+ordem];
            }

            esquerda->n = ordem-1;

            for(int i = atual->n - 1; i >= posicao; i--) {
                if (i + 1 < ordem * 2)
                    atual->chaves[i + 1] = atual->chaves[i];
            }

            atual->chaves[posicao] = esquerda->chaves[ordem-1];

            for(int i=atual->n; i>= posicao+1; i--)
                atual->filhos[i+1] = atual->filhos[i];

            atual->filhos[posicao+1] = direita;
            atual->filhos[posicao] = esquerda;

            (atual->n)++;

        }

        void insereNoNaoCheio(BTreeNode<T>* noAtual, T novo){
            int posicao = noAtual->n-1;
            if(noAtual->ehFolha){
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
                    divideNoFilhoCheio(noAtual, posicao);
                    if(novo > noAtual->chaves[posicao])
                        posicao++;
                }
                insereNoNaoCheio(noAtual->filhos[posicao], novo);
            }
        }

        void imprime(BTreeNode<T> raiz){
            cout << "(";
            for(int i=0; i<raiz.n; i++){
                cout << raiz.chaves[i];
                if(i+1 < raiz.n)
                    cout << ",";
            }
            cout << ")";
            if(!raiz.ehFolha){
                cout << "[";
                for(int i=0; i<=raiz.n; i++){
                    imprime(*raiz.filhos[i]);
                    if(i < raiz.n)
                        cout << ",";
                }
                cout << "]";
            }
        }

    public:
        BTree(int ordem) : ordem(ordem){
            raiz = new BTreeNode<T>(ordem, true);
        }

        void insere(T novo){
            int posicao = 0;
            for(int i=0; i<raiz->n; i++){
                if(raiz->chaves[i] < novo)
                    posicao++;
            }
            bool filhoTemEspaco = false;

            if (raiz->filhos[posicao] != nullptr && raiz->filhos[posicao]->n < ordem * 2)
                filhoTemEspaco = true;

            if(raiz->n == ordem*2 && !filhoTemEspaco){
                    cout << novo << "-1" << endl;
                BTreeNode<T>* novoNo = new BTreeNode<T>(ordem, false);
                novoNo->filhos[0] = raiz;
                raiz = novoNo;
                divideNoFilhoCheio(novoNo,0);
                insereNoNaoCheio(novoNo, novo);
            }
            else{
                cout << novo << "-2" << endl;
                insereNoNaoCheio(raiz, novo);
            }
        }

        void imprimeArvore(){
            imprime(*raiz);
            cout << endl;
        }

};

int main() {
    vector<int> numbers = {20,40,10,30,15,35,7,26,18,22,5,42,13,46,27,8,32,38,24,45,25};
    BTree<int> arvore(2);

    arvore.insere(20);
    arvore.insere(40);
    arvore.insere(10);
    arvore.insere(30);
    arvore.insere(15);
    arvore.insere(35);
    arvore.insere(7);
    arvore.insere(26);
    arvore.insere(18);
    arvore.imprimeArvore();
    arvore.insere(22);
    
    arvore.insere(5);
    arvore.insere(42);
    arvore.insere(13);
    arvore.insere(46);
    arvore.insere(27);
    arvore.insere(8);
    arvore.insere(32);
    arvore.imprimeArvore();
    arvore.insere(38);
    arvore.insere(24);
    arvore.insere(45);
    arvore.insere(25);


    arvore.imprimeArvore();

    return 0;
}
