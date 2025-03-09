#include "btree.hpp"

// MÉTODOS PRIVADOS

// Função para dividir um nó filho cheio
void BTree::splitChild(BTreeNode* x, int i) { // i = posição do ponteiro do filho
    BTreeNode* y = x->children[i];
    BTreeNode* z = new BTreeNode(order, y->leaf);
    z->n = order;

    // Copia as últimas chaves de y para z
    for (int j = 0; j < order; j++)
        z->keys[j] = y->keys[j + order];

    // Copia os filhos de y para z
    if (!y->leaf) {
        for (int j = 0; j <= order; j++)
            z->children[j] = y->children[j + order];
    }

    y->n = order / 2;
    x->children.insert(x->children.begin() + i + 1, z);

    // Insere a chave mediana em x
    x->keys.insert(x->keys.begin() + i, y->keys[order / 2]);
    x->n = x->n + 1;
}

// Função para inserir uma chave em um nó não cheio
void BTree::insertNonFull(BTreeNode* x, int k) {
    int i = x->n - 1;

    if (x->leaf) {
        // Encontra a posição onde a nova chave deve ser inserida
        while (i >= 0 && k < x->keys[i]) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }

        // Insere a nova chave
        x->keys[i + 1] = k;
        x->n = x->n + 1;
    } else {
        // Encontra o filho que deve receber a nova chave
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

// Função para imprimir a árvore
void BTree::imprime(BTreeNode* root) {
    cout << "(";
    for (int i = 0; i < root->n; i++) {
        cout << root->keys[i];
        if (i + 1 < root->n)
            cout << ",";
    }
    cout << ")";
    if (!root->leaf) {
        cout << "[ ";
        for (int i = 0; i <= root->n; i++) {
            imprime(root->children[i]);
            if (i < root->n)
                cout << ",";
        }
        cout << " ]";
    }
}

// Função para buscar uma chave na árvore
bool BTree::search(BTreeNode* x, int k) {
    int i = 0;
    while (i < x->n && k > x->keys[i])
        i++;

    if (i < x->n && k == x->keys[i])
        return true;

    if (x->leaf)
        return false;

    return search(x->children[i], k);
}

// Função para encontrar o predecessor
int BTree::getPredecessor(BTreeNode* node, int idx) {
    BTreeNode* current = node->children[idx];
    while (!current->leaf)
        current = current->children[current->n];
    return current->keys[current->n - 1];
}

// Função para encontrar o sucessor
int BTree::getSuccessor(BTreeNode* node, int idx) {
    BTreeNode* current = node->children[idx + 1];
    while (!current->leaf)
        current = current->children[0];
    return current->keys[0];
}

// Função para preencher um nó filho
void BTree::fill(BTreeNode* node, int idx) {
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

// Função para pegar emprestado do irmão anterior
void BTree::borrowFromPrev(BTreeNode* node, int idx) {
    BTreeNode* child = node->children[idx];
    BTreeNode* sibling = node->children[idx - 1];

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

// Função para pegar emprestado do próximo irmão
void BTree::borrowFromNext(BTreeNode* node, int idx) {
    BTreeNode* child = node->children[idx];
    BTreeNode* sibling = node->children[idx + 1];

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

// Função para mesclar dois nós
void BTree::merge(BTreeNode* node, int idx) {
    BTreeNode* child = node->children[idx];
    BTreeNode* sibling = node->children[idx + 1];

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

// Função para remover uma chave de um nó não folha
void BTree::removeFromNonLeaf(BTreeNode* node, int idx) {
    int k = node->keys[idx];

    if (node->children[idx]->n >= order) {
        int pred = getPredecessor(node, idx);
        node->keys[idx] = pred;
        remove(node->children[idx], pred);
    } else if (node->children[idx + 1]->n >= order) {
        int succ = getSuccessor(node, idx);
        node->keys[idx] = succ;
        remove(node->children[idx + 1], succ);
    } else {
        merge(node, idx);
        remove(node->children[idx], k);
    }
}

// Função para remover uma chave de um nó folha
void BTree::removeFromLeaf(BTreeNode* node, int idx) {
    for (int i = idx + 1; i < node->n; ++i)
        node->keys[i - 1] = node->keys[i];

    node->n--;
}

// Função para remover uma chave da árvore
void BTree::remove(BTreeNode* node, int k) {
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
            cout << "A chave " << k << " não está presente na árvore\n";
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

// MÉTODOS PÚBLICOS

void BTree::insert(int k) {
    // Se a árvore estiver vazia
    if (root == NULL){
        // Aloca memória para a raiz
        root = new BTreeNode(order, true);
        root->keys[0] = k;  // Insere a chave
        root->n = 1;  // Atualiza o número de chaves na raiz
    }
    else{ // Se a árvore não estiver vazia
        // Se a raiz estiver cheia, a árvore cresce em altura
        if (root->n == 2*order){
            // Aloca memória para a nova raiz
            BTreeNode *s = new BTreeNode(order, false);

            // Faz a raiz antiga ser filha da nova raiz
            s->children[0] = root;

            // Divide a raiz antiga e move uma chave para a nova raiz
            splitChild(s,0);

            // A nova raiz tem dois filhos agora. Decide qual dos
            // dois filhos vai receber a nova chave
            int i = 0;
            if (s->keys[0] < k)
                i++;
            insertNonFull(s->children[i], k);

            // Muda a raiz
            root = s;
        }
        else  // Se a raiz não estiver cheia, chama insertNonFull para a raiz
            insertNonFull(root, k);
    }
}

// Função para imprimir a árvore
void BTree::imprimeArvore() {
    imprime(root);
    cout << endl;
}

// Função para buscar uma chave na árvore
bool BTree::search(int k) {
    return (root == nullptr) ? false : search(root, k);
}

// Função para remover uma chave da árvore
void BTree::remove(int k) {
    if (!root) {
        cout << "A árvore está vazia\n";
        return;
    }

    remove(root, k);

    if (root->n == 0) {
        BTreeNode* tmp = root;
        if (root->leaf)
            root = nullptr;
        else
            root = root->children[0];

        delete tmp;
    }
}