#ifndef BTREE_HPP
#define BTREE_HPP

#include <iostream>
#include <vector>
using namespace std;

// Classe para o nó presente em uma Árvore B
class BTreeNode {
    public:
        // Vetor de chaves
        vector<int> keys;
        // Vetor de ponteiros para filhos
        vector<BTreeNode*> children;
        // Número atual de chaves
        int n;
        // Verdadeiro se for nó folha, falso caso contrário
        bool leaf;

        BTreeNode(int order, bool isLeaf = true) : n(0), leaf(isLeaf) {
            keys.resize(2 * order);
            children.resize(2 * order + 1, nullptr);
        }
};

// Classe para Árvore B
class BTree {
    private:
        BTreeNode* root; // Ponteiro para o nó raiz
        int order; // Ordem da Árvore B

        // Função para dividir um nó filho cheio
        void splitChild(BTreeNode* x, int i);

        // Função para inserir uma chave em um nó não cheio
        void insertNonFull(BTreeNode* x, int k);

        // Função para imprimir a árvore
        void imprime(BTreeNode* root);

        // Função para buscar uma chave na árvore
        bool search(BTreeNode* x, int k);

        // Função para encontrar o predecessor
        int getPredecessor(BTreeNode* node, int idx);

        // Função para encontrar o sucessor
        int getSuccessor(BTreeNode* node, int idx);

        // Função para preencher um nó filho
        void fill(BTreeNode* node, int idx);

        // Função para pegar emprestado do irmão anterior
        void borrowFromPrev(BTreeNode* node, int idx);

        // Função para pegar emprestado do próximo irmão
        void borrowFromNext(BTreeNode* node, int idx);

        // Função para mesclar dois nós
        void merge(BTreeNode* node, int idx);

        // Função para remover uma chave de um nó não folha
        void removeFromNonLeaf(BTreeNode* node, int idx);

        // Função para remover uma chave de um nó folha
        void removeFromLeaf(BTreeNode* node, int idx);

        // Função para remover uma chave da árvore
        void remove(BTreeNode* node, int k);

    public:
        BTree(int order) : order(order) { root = new BTreeNode(order, true); }

        // Função para inserir uma chave na árvore
        void insert(int k);

        // Função para imprimir a árvore
        void imprimeArvore();

        // Função para buscar uma chave na árvore
        bool search(int k);

        // Função para remover uma chave da árvore
        void remove(int k);
};

#endif