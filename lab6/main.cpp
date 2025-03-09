// Programa em C++ para Implementar Árvore B
#include <iostream>

#include "btree.hpp"

int main() {

    BTree t1(1);
    cout << "Árvore de ordem 1:" << endl;
    t1.insert(12);
    t1.insert(34);
    t1.insert(23);
    t1.insert(65);
    t1.insert(2);
    t1.insert(8);
    t1.insert(11);
    t1.insert(33);
    t1.insert(3);
    t1.imprimeArvore();
    
    int k;
    cout << "Digite chave para procura: ";
    cin >> k;
    (t1.search(k) != false)? cout << "\nPresente\n" : cout << "\nAusente\n";

    BTree t2(2);

    cout << "Árvore de ordem 2:" << endl;
    t2.insert(48);
    t2.insert(43);
    t2.insert(30);
    t2.insert(16);
    t2.insert(42);
    t2.insert(24);
    t2.insert(6);
    t2.insert(22);
    t2.insert(5);
    t2.insert(42);
    t2.insert(13);
    t2.insert(46);
    t2.insert(27);
    t2.insert(8);
    t2.insert(32);
    t2.insert(38);
    t2.insert(25);
    t2.imprimeArvore();

    cout << "Digite chave para procura: ";
    cin >> k;
    (t2.search(k) != false)? cout << "\nPresente\n" : cout << "\nAusente\n";

    BTree t3(3);

    cout << "Árvore de ordem 3:" << endl;
    t3.insert(48);
    t3.insert(43);
    t3.insert(30);
    t3.insert(100);
    t3.insert(42);
    t3.insert(221);
    t3.insert(6);
    t3.insert(22);
    t3.insert(50);
    t3.insert(42);
    t3.insert(13);
    t3.insert(47);
    t3.insert(23);
    t3.insert(88);
    t3.insert(32);
    t3.insert(380);
    t3.insert(25);
    t3.imprimeArvore();

    cout << "Digite chave para procura: ";
    cin >> k;
    (t3.search(k) != false)? cout << "\nPresente\n" : cout << "\nAusente\n";

    return 0;
}