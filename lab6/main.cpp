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
    void splitChild(BTreeNode<T>* x, int i) { //i = posição do ponteiro do filho
        BTreeNode<T>* y = x->children[i];
        BTreeNode<T>* z = new BTreeNode<T>(order, y->leaf);
        z->n = order;

        for (int j = 0; j < order; j++)
            z->keys[j] = y->keys[j + order];

        if (!y->leaf) {
            for (int j = 0; j <= order; j++)
                z->children[j] = y->children[j + order];
        }

        y->n = order/2;
        x->children.insert(x->children.begin() + i + 1, z);

        x->keys.insert(x->keys.begin() + i, y->keys[order/2]);
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
            cout << "[ ";
            for(int i=0; i<=root->n; i++){
                imprime(root->children[i]);
                if(i < root->n)
                    cout << ",";
            }
            cout << " ]";
        }
    }

    // Function to search a key in the tree
    bool search(BTreeNode<T>* x, T k) {
        int i = 0;
        while (i < x->n && k > x->keys[i])
            i++;

        if (i < x->n && k == x->keys[i])
            return true;

        if (x->leaf)
            return false;

        return search(x->children[i], k);
    }

    // Function to find the predecessor
T getPredecessor(BTreeNode<T>* node, int idx) {
    BTreeNode<T>* current = node->children[idx];
    while (!current->leaf)
        current = current->children[current->n];
    return current->keys[current->n - 1];
}

// Function to find the successor
T getSuccessor(BTreeNode<T>* node, int idx) {
    BTreeNode<T>* current = node->children[idx + 1];
    while (!current->leaf)
        current = current->children[0];
    return current->keys[0];
}

// Function to fill child node
void fill(BTreeNode<T>* node, int idx) {
    if (idx != 0 && node->children[idx - 1]->n >= order)
        borrowFromPrev(node, idx);
    else if (idx != node->n && node->children[idx + 1]->n >= order)
        borrowFromNext(node, idx);
    else {
        if (idx != node->n)
            merge(node, idx);
        else
            merge(node, idx - 1);
    }
}

// Function to borrow from previous sibling
void borrowFromPrev(BTreeNode<T>* node, int idx) {
    BTreeNode<T>* child = node->children[idx];
    BTreeNode<T>* sibling = node->children[idx - 1];

    for (int i = child->n - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];

    if (!child->leaf) {
        for (int i = child->n; i >= 0; --i)
            child->children[i + 1] = child->children[i];
    }

    child->keys[0] = node->keys[idx - 1];

    if (!child->leaf)
        child->children[0] = sibling->children[sibling->n];

    node->keys[idx - 1] = sibling->keys[sibling->n - 1];

    child->n += 1;
    sibling->n -= 1;
}

// Function to borrow from next sibling
void borrowFromNext(BTreeNode<T>* node, int idx) {
    BTreeNode<T>* child = node->children[idx];
    BTreeNode<T>* sibling = node->children[idx + 1];

    child->keys[child->n] = node->keys[idx];

    if (!child->leaf)
        child->children[child->n + 1] = sibling->children[0];

    node->keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->n; ++i)
        sibling->keys[i - 1] = sibling->keys[i];

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->children[i - 1] = sibling->children[i];
    }

    child->n += 1;
    sibling->n -= 1;
}

// Function to merge two nodes
void merge(BTreeNode<T>* node, int idx) {
    BTreeNode<T>* child = node->children[idx];
    BTreeNode<T>* sibling = node->children[idx + 1];

    child->keys[order - 1] = node->keys[idx];

    for (int i = 0; i < sibling->n; ++i)
        child->keys[i + order] = sibling->keys[i];

    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i)
            child->children[i + order] = sibling->children[i];
    }

    for (int i = idx + 1; i < node->n; ++i)
        node->keys[i - 1] = node->keys[i];

    for (int i = idx + 2; i <= node->n; ++i)
        node->children[i - 1] = node->children[i];

    child->n += sibling->n + 1;
    node->n--;

    delete sibling;
}

// Function to remove a key from a non-leaf node
void removeFromNonLeaf(BTreeNode<T>* node, int idx) {
    T k = node->keys[idx];

    if (node->children[idx]->n >= order) {
        T pred = getPredecessor(node, idx);
        node->keys[idx] = pred;
        remove(node->children[idx], pred);
    } else if (node->children[idx + 1]->n >= order) {
        T succ = getSuccessor(node, idx);
        node->keys[idx] = succ;
        remove(node->children[idx + 1], succ);
    } else {
        merge(node, idx);
        remove(node->children[idx], k);
    }
}

// Function to remove a key from a leaf node
void removeFromLeaf(BTreeNode<T>* node, int idx) {
    for (int i = idx + 1; i < node->n; ++i)
        node->keys[i - 1] = node->keys[i];

    node->n--;
}

// Function to remove a key from the tree
void remove(BTreeNode<T>* node, T k) {
    int idx = 0;
    while (idx < node->n && node->keys[idx] < k)
        ++idx;

    if (idx < node->n && node->keys[idx] == k) {
        if (node->leaf)
            removeFromLeaf(node, idx);
        else
            removeFromNonLeaf(node, idx);
    } else {
        if (node->leaf) {
            cout << "The key " << k << " is not present in the tree\n";
            return;
        }

        bool flag = ((idx == node->n) ? true : false);

        if (node->children[idx]->n < order)
            fill(node, idx);

        if (flag && idx > node->n)
            remove(node->children[idx - 1], k);
        else
            remove(node->children[idx], k);
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
            BTreeNode<T>* s = new BTreeNode<T>(order, false);
            s->children[0] = root;
            root = s;
            splitChild(root, 0);
            insertNonFull(s, k);
        } else
            insertNonFull(root, k);
    }

    void imprimeArvore(){
        imprime(root);
        cout << endl;
    }

    // Function to search a key in the tree
    bool search(T k) {
        return (root == nullptr) ? false : search(root, k);
    }

    // Function to remove a key from the tree
void remove(T k) {
    if (!root) {
        cout << "The tree is empty\n";
        return;
    }

    remove(root, k);

    if (root->n == 0) {
        BTreeNode<T>* tmp = root;
        if (root->leaf)
            root = nullptr;
        else
            root = root->children[0];

        delete tmp;
    }
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
    t.insert(25);
    t.imprimeArvore();

    int key;
    // cout << "Entre com a chave para procurar na árvore: ";
    // cin >> key;
    
    bool found = t.search(key=222);
    if (found) {
        cout << "Key " << key << " found in the tree." << endl;
    } else {
        cout << "Key " << key << " not found in the tree." << endl;
    }

    t.remove(8);
    t.imprimeArvore();
    t.remove(32);
    t.imprimeArvore();

    return 0;
}