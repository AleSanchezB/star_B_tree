#include "../headers/Queue.hpp"
#include <sstream>
#
/**************************************************************************/
template <typename T, int m>
Tree_B<T, m>::Tree_B(){
    root = new Node(true, true, nullptr);
}
/**************************************************************************/
template <typename T, int m>
Tree_B<T, m>::~Tree_B(){
    free(root);
    // root->free();
    // delete root;
}
/**************************************************************************/
template <typename T, int m>
Tree_B<T, m>::Tree_B(const Tree_B<T, m>& g){ *this = g; }
/**************************************************************************/
template <typename T, int m>
Tree_B<T, m>& Tree_B<T, m>::operator=(const Tree_B<T, m>& g){ return *this; }

template <typename T, int m>
void Tree_B<T, m>::free(Node* p){
    if (p == nullptr) return;
    for(int i = 0; i < p->children_size; ++i){
        free(p->children[i]);
    }
    p->free();
    delete p;
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::insert(const T& d){ insert(d, root); }
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::insert(const T& d, Node*& p){
    int i = 0;
    while (i < p->n && d > p->key[i]) {
        i++;
    }
    if(!p->leaf) {
        insert(d, p->children[i]);
        return;
    }

    if(p->isroot){
        p->insertionSort(i, d);
        p->n++;
        if(p->isOverflow()){
            splitRoot();
        }else p->children_size++;
    }else{
        p->insertionSort(i, d);
        p->n++;
        if(p->isOverflow()){
            if(!verifyRotate(p->parent, p->searchIndex())){
                split(p);
            }
        }else p->children_size++;
    }
}
/**************************************************************************/
template <typename T, int m>
bool Tree_B<T, m>::verifyRotate(Node* p, int i) {
    if(p == nullptr) return false;
    if(i == -1) return false;
    if (i == 0) {
        if(p->children[i+1]->isOverflow()) return false;
        rotateRight(p, i);
    } else {
        if(p->children[i-1]->isOverflow()) return false;
        rotateLeft(p, i);
    }
    return true;
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::Node::insertionSort(int index, const T& d) {
    for (int i = n; i > index; --i) {
        key[i] = key[i - 1];
    }
    key[index] = d;
}
/**************************************************************************/
template <typename T, int m>
bool Tree_B<T, m>::search(const T& d) const {
    return search(d, root);
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::print() const {
    print(root);
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::splitRoot(){
    
    Node* new_father = new Node(false, root->isroot, root->parent);
    Node* right = new Node(true, false, new_father);
    Node* left = new Node(root->leaf, false, new_father);
    
    int mid = root->n;
    new_father->children[0] = left;
    new_father->children[1] = right;
    int new_node_key = 0;
    if(mid % 2 == 0) {
        mid = mid/2;
        new_node_key = mid;
    }
    else {
        mid = mid/2 + 1;
        new_node_key = mid - 1;
    }
    left->children_size = mid + 1;

    new_father->n = 1;
    new_father->children_size = 2;
    new_father->key[0] = root->key[mid-1];

    for(int j = 0; j < mid; ++j){
        left->children[j] = root->children[j];
    }

    for(int j = mid; j < root->children_size; ++j){
        right->children[j-mid] = root->children[j];
    }
    for (int j = 0; j < new_node_key; ++j) {
        right->key[j] = root->key[j + mid];
        right->n++;
        right->children_size++;
    }
    for(int j = 0; j < mid; ++j){
        left->key[j] = root->key[j];
    }
    left->n = mid - 1;
    left->children_size = mid +1;
    left->max_children = m;

    root->free();
    delete root;
    root = new_father;

    root->leaf = false;
    left->isroot = false;
    left->parent = new_father;
    right->isroot = false;
    right->parent = new_father;

    if(left->children[0] != nullptr) {
        left->leaf = false;
        left->actuallyParent(left);
    }
    if(right->children[0] != nullptr) {
        right->leaf = false;
        right->actuallyParent(right);
    }
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::split(Node* p){
    if(p->isroot) splitRoot();
    else if(!p->leaf) {
        if(p->searchIndex() == 0){
            splitNotLeaf(p->parent, 1);
        }else {
            splitNotLeaf(p->parent, p->searchIndex());
        }
    }
    else {
        if(p->searchIndex() == 0){
            split(p->parent, 1);
        }else{
            split(p->parent, p->searchIndex());
        }
    }
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::printTree(Node* node, int depth, std::ostringstream& oss) {
    if (node != nullptr) {
        for (int i = 0; i < depth; i++) {
            oss << "  ";
        }
        for (int i = 0; i < node->n; i++) {
            oss << node->key[i] << " ";
        }
        oss << "\n";

        if (!node->leaf) {
            for (int i = 0; i < node->children_size; i++) {
                printTree(node->children[i], depth + 1, oss);
            }
        }
    }
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::printTree(std::ostringstream& oss) {
    printTree(root, 0, oss);
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::splitNotLeaf(Node* p, int i){
    Node* left = p->children[i - 1];
    Node* right = p->children[i];

    // Calcular el número total de claves y el rango de redistribución
    int totalKeys = left->n + right->n + 1;
    int alpha = (2 * m - 2) / 3;
    int beta = 2 * ((2 * m - 2) / 3) + 1;

    // Crear un nuevo nodo
    Node* new_node = new Node(false, false, p);

    // Crear arreglos temporales para claves e hijos
    T* keys = new T[totalKeys+1];
    Node** children = new Node*[totalKeys + 2];

    // Copiar claves e hijos en arreglos temporales
    int k = 0;
    for (int j = 0; j < left->n; ++j) {
        keys[k++] = left->key[j];
    }
    keys[k++] = p->key[i - 1];
    for (int j = 0; j < right->n; ++j) {
        keys[k++] = right->key[j];
    }

    int c = 0;
    for (int j = 0; j < left->children_size; ++j) {
        children[c++] = left->children[j];
    }
    for (int j = 0; j < right->children_size; ++j) {
        children[c++] = right->children[j];
    }

    // Redistribuir claves y actualizar nodos
    left->n = alpha;
    right->n = beta - (alpha + 1);
    new_node->n = totalKeys - beta-1;

    k = 0;
    for (int j = 0; j < alpha; ++j) {
        left->key[j] = keys[k++];
    }
    p->key[i - 1] = keys[k++];
    for (int j = 0; j < right->n; ++j) {
        right->key[j] = keys[k++];
    }
    for (int j = 0; j < new_node->n; ++j) {
        new_node->key[j] = keys[k++];
    }
    // Redistribuir hijos y actualizar nodos
    left->children_size = alpha + 1;
    right->children_size = beta - alpha;
    new_node->children_size = totalKeys - beta;
    
    c = 0;
    for (int j = 0; j < left->children_size; ++j) {
        left->children[j] = children[c++];
    }
    
    for (int j = 0; j < right->children_size; ++j) {
        right->children[j] = children[c++];
    }
    for (int j = 0; j < new_node->children_size; ++j) {
        new_node->children[j] = children[c++];
    }
    new_node->actuallyParent(new_node);
    right->actuallyParent(right);
    // Ajustar claves y hijos del nodo padre
    for (int j = p->n; j > i; --j) {
        p->key[j] = p->key[j - 1];
        p->children[j + 1] = p->children[j];
    }
    p->key[i] = keys[beta];
    p->children[i + 1] = new_node;
    p->n++;
    p->children_size = p->n + 1;

    // Limpiar asignaciones temporales
    delete[] keys;
    delete[] children;

    right->print();
    for(int j = 0; j < right->children_size; ++j){
        right->children[j]->print();
    }
    new_node->print();
    for(int j = 0; j < new_node->children_size; ++j){
        new_node->children[j]->print();
    }
    if(p->children_size > p->max_children) {
        if(!verifyRotate(p->parent, p->searchIndex())){
            split(p);
        }
    }
    // Asegurar que las propiedades del árbol B* se mantengan
    if (left->children[0] != nullptr) {
        left->leaf = false;
        left->actuallyParent(left);
    }
    if (right->children[0] != nullptr) {
        right->leaf = false;
        right->actuallyParent(right);
    }
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::split(Node* p, int i) {
    Node* left = p->children[i - 1];
    Node* right = p->children[i];
    
    int n_total = left->n + right->n + 1;
    int alpha = (2*m-2)/3;
    int beta = 2*((2*m-2)/3)+1;
    Node* new_node = new Node(true, false, p);
    T* keys = new T[n_total];

    for(int j = 0; j < left->n; ++j) keys[j] = left->key[j];
    keys[left->n] = p->key[i-1];
    for(int j = 0; j < right->n; ++j) keys[j + left->n + 1] = right->key[j];

    left->n = alpha;
    left->children_size = alpha + 1;
    right->n = beta - (alpha+1);
    right->children_size = beta - alpha;
    new_node->n = n_total - (beta + 1);
    new_node->children_size = n_total - beta;
    for(int j = 0; j < alpha; ++j) left->key[j] = keys[j];
    
    p->key[i-1] = keys[alpha];

    for(int j = alpha + 1; j < beta; ++j) right->key[j - alpha - 1] = keys[j];
    for(int j = p->n; j > i; --j) {
        p->key[j] = p->key[j-1];
        p->children[j+1] = p->children[j];
    }

    p->key[i] = keys[beta];

    for(int j = beta + 1; j < n_total; ++j) new_node->key[j - beta - 1] = keys[j];

    p->children[i+1] = new_node;
    p->n++;
    p->children_size = p->n + 1;
    delete[] keys;
    if(p->children_size > p->max_children) {
        if(!verifyRotate(p->parent, p->searchIndex())){
            split(p);
        }
    }
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::print_preorder(Node* p, int depth) const{
    if (p == nullptr) return;
    
    // Imprimir las claves del nodo actual
    for (int i = 0; i < depth; i++) {
        std::cout << "  "; // Dos espacios por nivel de profundidad
    }
    p->print();
    // Recorrer los hijos
    if (!p->leaf) {
        for (int i = 0; i < p->children_size; i++) {
            print_preorder(p->children[i], depth + 1);
        }
    }
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::print(Node* p) const{
    if (p == nullptr) return;
    //print_preorder(p,0);    
    Queue<Node*> q;
    q.enqueue(root);
    Node* aux;
    // std::cout << "Printing tree" << std::endl;
    std::cout << "/**********Printing tree**********/" << std::endl;
    while(!q.isEmpty()){
        aux = q.getFront();
        q.dequeue();
        aux->print();
        for(int i = 0; i < aux->children_size; ++i){
            if(aux->children[i] != nullptr)
                q.enqueue(aux->children[i]);
        }
    }
    std::cout << "/**********End of tree**********/" << std::endl;
}
/**************************************************************************/
template <typename T, int m>
bool Tree_B<T, m>::search(const T& d, Node* p) const {
    if (p == nullptr) {
        std::cout << "Not found" << std::endl;
        return false;
    } else {
        int i = 0;
        while (i < p->children_size && d > p->key[i]) {
            i++;
        }
        if (i < p->children_size && d == p->key[i]) {
            std::cout << "Found" << std::endl;
            return true;
        } else if (p->leaf) {
            std::cout << "Not found" << std::endl;
            return false;
        } else {
            search(d, p->children[i]);
        }
    }
    return false;
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::rotateLeft(Node* p, int i) {
    Node* left = p->children[i - 1];
    Node* right = p->children[i];
    
    left->key[left->n] = p->key[i-1];
    left->n++;
    left->children_size = left->n + 1;
    p->key[i-1] = right->key[0];

    right->n--;
    right->children_size = right->n + 1;
    
    for (int j = 0; j < right->n; ++j) {
        right->key[j] = right->key[j + 1];
    }
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::rotateRight(Node* p, int i) {
    Node* left = p->children[i];
    Node* right = p->children[i + 1];
    
    for (int j = right->n; j > 0; --j) {
        right->key[j] = right->key[j - 1];
    }
    right->key[0] = p->key[i];
    p->key[i] = left->key[left->n - 1];
    left->n--;
    left->children_size = left->n + 1;
    right->n++;
    right->children_size = right->n + 1;

}
/**************************************************************************/
/*Node functions*/
/**************************************************************************/
template <typename T, int m>
Tree_B<T, m>::Node::Node(bool leaf, bool isroot, Node* parent) : leaf(leaf), isroot(isroot), parent(parent), children_size(1), n(0) {
    min_keys = 2*m/3;
    if(!isroot) {
        max_keys = m;
        if(!leaf) min_children = (2*m-1)/3;
        else min_children = 0;
        
        max_children = m;
    } else {
        max_keys = 3*min_keys + 2;
        min_children = 2;
        max_children = 2*((int)(2*m-2)/3)+1;
        // max_children = m;
    }

    key = new T[max_keys +1];
    children = new Node*[max_children + 2];
    for (int i = 0; i < max_children; ++i) {
        children[i] = nullptr;
    }
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::Node::free() {
    delete[] key;
    delete[] children;
}
/**************************************************************************/
template <typename T, int m>
bool Tree_B<T, m>::Node::isOverflow() const {
    return children_size >= max_children;
} 
/**************************************************************************/
template <typename T, int m>
bool Tree_B<T, m>::Node::isUnderflow() const {
    return children_size < min_children;
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::Node::print() const {
    std::cout << "[";
    for (int i = 0; i < n; ++i) {
        std::cout << key[i] << ", ";
    }
    std::cout << "\b\b]";
    if(isroot) std::cout << "-> Root";
    else if(leaf) std::cout << "-> Leaf";
    else std::cout << "-> Node";
    // if(parent != nullptr){
    //     std::cout << " Parent: ";
    //     parent->print();
    // }
    std::cout << std::endl;
}
/**************************************************************************/
template <typename T, int m>
typename Tree_B<T, m>::Node* Tree_B<T, m>::Node::searchParentLeft(){
    Node* aux = parent;
    for(int i = 0; i < aux->children_size; ++i){
        if(aux->children[i] == this){
            return (i == 0) ? nullptr : aux->children[i-1];
        }
    }
    return nullptr;
}
/**************************************************************************/
template <typename T, int m>
typename Tree_B<T, m>::Node* Tree_B<T, m>::Node::searchParentRight(){
    if(isroot) return nullptr;
    Node* aux = parent;
    for(int i = 0; i < aux->children_size; ++i){
        if(aux->children[i] != nullptr && aux->children[i] == this){
            aux->print();
            return (i == aux->children_size - 1) ? nullptr : aux->children[i+1];
        }
    }
    return nullptr;
}
/**************************************************************************/
template <typename T, int m>
int Tree_B<T, m>::Node::searchIndex() const {
    if(parent == nullptr) return -1;
    int i = 0;
    for(int i = 0; i < parent->children_size; ++i){
        if(parent->children[i] != nullptr && parent->children[i] == this) return i;
    }
    return i;
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::Node::actuallyParent(Node* p) {
    for(int i = 0; i < children_size; ++i){
        if(children[i] != nullptr)children[i]->parent = p;
    }
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::remove(const T& d) {
    if (root == nullptr) {
        std::cout << "The tree is empty." << std::endl;
        return;
    }
    remove(root, d);
    if (root->n == 0) {
        if (!root->leaf) 
            root = root->children[0];
    }
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::remove(Node* p, const T& d) {
    int idx = findKey(p, d);

    if (idx < p->n && p->key[idx] == d) {
        if (p->leaf) {
            removeFromLeaf(p, idx);
        } else {
            removeFromNonLeaf(p, idx);
        }
    } else {
        if (p->leaf) {
            std::cout << "The key " << d << " is not in the tree." << std::endl;
            return;
        }

        bool flag = (idx == p->n);

        if (p->children[idx]->n < p->min_keys) {
            fill(p, idx);
        }

        if (flag && idx > p->n) {
            remove(p->children[idx - 1], d);
        } else {
            remove(p->children[idx], d);
        }
    }
}
/**************************************************************************/
template <typename T, int m>
int Tree_B<T, m>::findKey(Node* p, const T& d) {
    int idx = 0;
    while (idx < p->n && p->key[idx] < d) {
        ++idx;
    }
    return idx;
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::removeFromNonLeaf(Node* p, int idx) {
    T k = p->key[idx];

    if (p->children[idx]->n >= p->min_keys) {
        T pred = getPred(p, idx);
        p->key[idx] = pred;
        remove(p->children[idx], pred);
    } else if (p->children[idx + 1]->n >= p->min_keys) {
        T succ = getSucc(p, idx);
        p->key[idx] = succ;
        remove(p->children[idx + 1], succ);
    } else {
        merge(p, idx);
        remove(p->children[idx], k);
    }
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::removeFromLeaf(Node* p, int idx) {
    for (int i = idx + 1; i < p->n; ++i) {
        p->key[i - 1] = p->key[i];
    }
    p->n--;
}
/**************************************************************************/
template <typename T, int m>
T Tree_B<T, m>::getPred(Node* p, int idx) {
    Node* curr = p->children[idx];
    while (!curr->leaf) {
        curr = curr->children[curr->n];
    }
    return curr->key[curr->n - 1];
}
/**************************************************************************/
template <typename T, int m>
T Tree_B<T, m>::getSucc(Node* p, int idx) {
    Node* curr = p->children[idx + 1];
    while (!curr->leaf) {
        curr = curr->children[0];
    }
    return curr->key[0];
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::fill(Node* p, int idx) {
    if (idx != 0 && p->children[idx - 1]->n >= p->min_keys) {
        borrowFromPrev(p, idx);
    } else if (idx != p->n && p->children[idx + 1]->n >= p->min_keys) {
        borrowFromNext(p, idx);
    } else {
        if (idx != p->n) {
            merge(p, idx);
        } else {
            merge(p, idx - 1);
        }
    }
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::borrowFromPrev(Node* p, int idx) {
    Node* child = p->children[idx];
    Node* sibling = p->children[idx - 1];

    for (int i = child->n - 1; i >= 0; --i) {
        child->key[i + 1] = child->key[i];
    }

    if (!child->leaf) {
        for (int i = child->n; i >= 0; --i) {
            child->children[i + 1] = child->children[i];
        }
    }

    child->key[0] = p->key[idx - 1];

    if (!child->leaf) {
        child->children[0] = sibling->children[sibling->n];
    }

    p->key[idx - 1] = sibling->key[sibling->n - 1];

    child->n += 1;
    sibling->n -= 1;
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::borrowFromNext(Node* p, int idx) {
    Node* child = p->children[idx];
    Node* sibling = p->children[idx + 1];

    child->key[child->n] = p->key[idx];

    if (!child->leaf) {
        child->children[child->n + 1] = sibling->children[0];
    }

    p->key[idx] = sibling->key[0];

    for (int i = 1; i < sibling->n; ++i) {
        sibling->key[i - 1] = sibling->key[i];
    }

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; ++i) {
            sibling->children[i - 1] = sibling->children[i];
        }
    }

    child->n += 1;
    sibling->n -= 1;
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::merge(Node* p, int idx) {
    Node* child = p->children[idx];
    Node* sibling = p->children[idx + 1];

    child->key[child->n] = p->key[idx];

    for (int i = 0; i < sibling->n; ++i) {
        child->key[child->n + 1 + i] = sibling->key[i];
    }

    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i) {
            child->children[child->n + 1 + i] = sibling->children[i];
            if (child->children[child->n + 1 + i] != nullptr) {
                child->children[child->n + 1 + i]->parent = child;
            }
        }
    }

    for (int i = idx + 1; i < p->n; ++i) {
        p->key[i - 1] = p->key[i];
        p->children[i] = p->children[i + 1];
    }

    child->n += sibling->n + 1;
    p->n--;

    delete sibling;
}
/**************************************************************************/
