// Programa em C++ para Implementar Árvore B
#include <iostream>

#include "btree.hpp"

int main() {
    BTree t(2);

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

    bool found = t.search(key = 222);
    if (found) {
        cout << "Chave " << key << " encontrada na árvore." << endl;
    } else {
        cout << "Chave " << key << " não encontrada na árvore." << endl;
    }

    t.remove(8);
    t.imprimeArvore();
    t.remove(32);
    t.imprimeArvore();

    return 0;
}