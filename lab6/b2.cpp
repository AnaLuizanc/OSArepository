// C++ Program to Implement B-Tree
#include <iostream>
#include <vector>
using namespace std;

// class for the node present in a B-Tree
template <typename T>
class BTreeNode {
public:
    // Vector of keys
    vector<T> keys;
    // Vector of child pointers
    vector<BTreeNode*> children;
    // Current number of keys
    int n;
    // True if leaf node, false otherwise
    bool leaf;

    BTreeNode(int order, bool isLeaf = true) : n(0), leaf(isLeaf) {
        keys.resize(2 * order);
        children.resize(2 * order + 1, nullptr);
    }
};

// class for B-Tree
template <typename T>
class BTree {
private:
    BTreeNode<T>* root; // Pointer to root node
    int order; // Order of the B-Tree

    // Function to split a full child node
    void splitChild(BTreeNode<T>* x, int i) { // i = posição do ponteiro do filho
        BTreeNode<T>* y = x->children[i];
        BTreeNode<T>* z = new BTreeNode<T>(order, y->leaf);
        z->n = order;

        for (int j = 0; j < order; j++)
            z->keys[j] = y->keys[j + order];

        if (!y->leaf) {
            for (int j = 0; j <= order; j++)
                z->children[j] = y->children[j + order]; // talvez precisa limpar o ponteiro em y
        }

// talvez aqui
        y->n = order/2;
        x->children.insert(x->children.begin() + i + 1, z);

        x->keys.insert(x->keys.begin() + i, y->keys[order/2]);
// até aqui
        x->n = x->n + 1;

    }

    // Function to insert a key in a non-full node
    void insertNonFull(BTreeNode<T>* x, T k) {
        int i = x->n - 1;

        if (x->leaf) {
            while (i >= 0 && k < x->keys[i]) {
                x->keys[i + 1] = x->keys[i];
                i--;
            }

            x->keys[i + 1] = k;
            x->n = x->n + 1;
        } else {
            while (i >= 0 && k < x->keys[i])
                i--;

            i++;
            if (x->children[i]->n == 2 * order) {
                splitChild(x, i);

                if (k > x->keys[i])
                    i++;
            }
            insertNonFull(x->children[i], k);
        }
    }

    void imprime(BTreeNode<T>* root){
        cout << "(";
        for(int i=0; i<root->n; i++){
            cout << root->keys[i];
            if(i+1 < root->n)
                cout << ",";
        }
        cout << ")";
        if(!root->leaf){
            cout << "[";
            for(int i=0; i<=root->n; i++){
                imprime(root->children[i]);
                if(i < root->n)
                    cout << ",";
            }
            cout << "]";
        }
    }

public:
    BTree(int order) : order(order) { root = new BTreeNode<T>(order, true); }

    // Function to insert a key in the tree
    void insert(T k) {
        int posicao = 0;
        for(int i=0; i<root->n; i++){
            if(root->keys[i] < k)
                posicao++;
        }
        bool filhoTemEspaco = false;

        if (root->children[posicao] != nullptr && root->children[posicao]->n < order * 2)
            filhoTemEspaco = true;

        if (root->n == 2 * order && !filhoTemEspaco) {
            cout << k << "-1" << endl;
            BTreeNode<T>* s = new BTreeNode<T>(order, false);
            s->children[0] = root;
            root = s;
            splitChild(s, 0);
            insertNonFull(s, k);
        } else{
            cout << k << "-2" << endl;
            insertNonFull(root, k);
        }
    }

    void imprimeArvore(){
        imprime(root);
        cout << endl;
    }

    int getNR(){
        return root->keys[0];
    }

    // Function to traverse the tree
    void traverse() {
        if (root != nullptr)
            traverse(root);
    }

};

int main() {
    BTree<int> t(2);

    t.insert(20);
    t.insert(40);
    t.insert(10);
    t.insert(30);
    t.insert(15);
    t.insert(35);
    t.insert(7);
    t.insert(26);
    t.insert(18);
    t.insert(22);
    t.insert(5);
    t.insert(42);
    t.insert(13);
    t.insert(46);
    t.insert(27);
    t.insert(8);
    t.insert(32);
    t.insert(38);
    t.insert(24);
    t.insert(45);
    t.imprimeArvore();
    t.insert(25);
    t.imprimeArvore();

    return 0;
}