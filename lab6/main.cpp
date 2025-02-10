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
class BTree {
    private:
        BTreeNode<T>* root; // Pointer to root node
        int ordem;

        

    public:
        BTree(int order) : order(order) {
            root = new BTreeNode<T>(order, true);
        }


};

int main() {
    vector<int> numbers = {20,40,10,30,15,35,7,26,18,22,5,42,13,46,27,8,32,38,24,45,25};
    BTree<int> arvore(2);


    return 0;
}
