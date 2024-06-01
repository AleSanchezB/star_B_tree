#include "../headers/Queue.hpp"
template <typename T, int m>
Tree_B<T, m>::Tree_B(){
    root = nullptr;
}

template <typename T, int m>
Tree_B<T, m>::~Tree_B(){
    free(root);
    // root->free();
    // delete root;
}

template <typename T, int m>
Tree_B<T, m>::Tree_B(const Tree_B<T, m>& g){ *this = g; }

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
template <typename T, int m>
void Tree_B<T, m>::insert(const T& d){ insert(d, root); }

template <typename T, int m>
void Tree_B<T, m>::insert(const T& d, Node*& p){
    if (p == nullptr) {
        p = new Node(true, true);
        p->key[0] = d;
        p->n++;
        p->children_size++;
        // std::cout << "Inserted " << d << std::endl;
        p->print();
    } else {
        int i = 0;
        while (i < p->n && d > p->key[i]) {
            i++;
        }
        if(p->children[i] != nullptr) {
            if (p->children[i]->isOverflow()) {
                // std::cout << "overflow " << d << std::endl;
                p->insertionSort(i, d);
                p->n++;
                split(p, i);
                return;
            }
            else {
                insert(d, p->children[i]);
                return;
            }
            insert(d, p->children[i]);
            return;
        }
        if (p->isOverflow()) {
            // std::cout << "overflow a " << d << std::endl;
            p->insertionSort(i, d);
            p->n++;
            // split(p, i);
            Node* new_node = new Node(p->leaf, p->isroot);
            Node* child = p;
            Node* new_father = new Node(p->leaf, p->isroot);
            
            for (int j = 0; j < child->n / 2; ++j) {
                new_node->key[j] = child->key[j + child->n/2];
                new_node->n++;
            }

            new_father->n = 1;
            new_father->children_size = 2;
            new_father->key[0] = child->key[child->n/2-1];

            new_father->children[0] = child;
            new_father->children[1] = new_node;

            if(child->n % 2 == 0) child->n = child->n/2 - 1;
            else child->n = child->n/2 + 1;
            child->children_size = child->children_size/2;
            
            for (int j = child->n - 1; j > 0; --j) {
                new_node->children[j] = child->children[j + child->n/2];
            }

            for(int j = 0; i < child->n; ++j){
                new_node->children[j] = child->children[j + child->n/2];
            }
            child->children_size++;
            // child->print();
            // new_node->print();
            // new_father->print();
            root = new_father;
            return;
        }
        else {
            p->insertionSort(i, d);
            p->n++;
            p->children_size++;

        }
    }
}

// template <typename T, int m>
// void Tree_B<T, m>::Node::splitRoot() {
//     Node* new_node = new Node(leaf, false);
//     Node* child = this;

//     for (int j = 0; j < child->n / 2; ++j) {
//         new_node->key[j] = child->key[j + child->n/2];
//     }

//     child->n = m/2;
//     child->children_size = m/2;
//     for (int j = n; j > 0; --j) {
//         new_node->children[j] = child->children[j + child->n/2];
//     }
//     new_node->children[0] = child->children[child->n/2];
//     for (int j = n; j > 0; --j) {
//         child->key[j] = child->key[j - 1];
//     }
//     child->key[0] = child->key[m/2 - 1];
//     child->children_size = m/2;
//     child->key[m/2 - 1] = 0;
//     n++;
//     children_size++;
//     std::cout << "Split " << key[0] << std::endl;
//     print();
// }

template <typename T, int m>
void Tree_B<T, m>::Node::insertionSort(int index, const T& d) {
    for (int i = n; i > index; --i) {
        key[i] = key[i - 1];
    }

    key[index] = d;
}

template <typename T, int m>
bool Tree_B<T, m>::search(const T& d) const {
    return search(d, root);
}

template <typename T, int m>
void Tree_B<T, m>::print() const {
    print(root);
}

template <typename T, int m>
void Tree_B<T, m>::split(Node* p, int i) {
    // Node* new_node = new Node(p->leaf, false);
    // Node* child = p->children[i];

    // for (int j = 0; j < child->n / 2; ++j) {
    //     new_node->key[j] = child->key[j + child->n/2];
    // }

    // new_node->print();
    // child->n = m/2;
    // child->children_size = m/2;
    // for (int j = p->n; j > i; --j) {
    //     p->children[j + 1] = p->children[j];
    // }
    // p->children[i + 1] = new_node;
    // for (int j = p->n; j > i; --j) {
    //     p->key[j] = p->key[j - 1];
    // }
    // p->key[i] = child->key[m/2 - 1];
    // child->key[m/2 - 1] = 0;
    // p->n++;
    // p->children_size++;
    // std::cout << "Split " << p->key[i] << std::endl;
    // p->print();
    // std::cout << "overflow a " << d << std::endl;
    // split(p, i);
    Node* new_node = new Node(p->leaf, p->isroot);
    Node* child = p->children[i];
    Node* new_father = new Node(p->leaf, p->isroot);
            
    for (int j = 0; j < child->n / 2; ++j) {
        new_node->key[j] = child->key[j + child->n/2];
        new_node->n++;
    }

    new_father->n = 1;
    new_father->children_size = 2;
    new_father->key[0] = child->key[child->n/2-1];

    new_father->children[0] = child;
    new_father->children[1] = new_node;

    if(child->n % 2 == 0) child->n = child->n/2 - 1;
    else child->n = child->n/2 + 1;
    child->children_size = child->children_size/2;
            
    for (int j = child->n - 1; j > 0; --j) {
        new_node->children[j] = child->children[j + child->n/2];
    }

    for(int j = 0; i < child->n; ++j){
        new_node->children[j] = child->children[j + child->n/2];
    }
    child->children_size++;
    std::cout << "Split " << child->key[i] << std::endl;
    child->print();
    std::cout << "Split " << new_node->key[0] << std::endl;
    new_node->print();
    std::cout << "Split " << new_father->key[0] << std::endl;
    new_father->print();
    p = new_father;
}
template <typename T, int m>
void Tree_B<T, m>::print(Node* p) const{
    if (p == nullptr) return;

    Queue<Node*> q;
    q.enqueue(root);
    Node* aux;
    std::cout << "Printing tree\n";
    while(!q.isEmpty()){
        aux = q.getFront();
        q.dequeue();
        aux->print();
        for(int i = 0; i < aux->children_size; ++i){
            if(aux->children[i] != nullptr)
                q.enqueue(aux->children[i]);
        }
    }
    // // std::cout << "print: " << p->children_size << " " << p->n << "\n";
    // p->print();
    // for(int i = 0; i < p->children_size; ++i){
    //     print(p->children[i]);
    // }
}

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

template <typename T, int m>
Tree_B<T, m>::Node::Node(bool leaf, bool isroot) : leaf(leaf), isroot(isroot), children_size(1), n(0) {
    min_keys = 2*m/3;
    if(!isroot) {
        max_keys = m - 1;
        if(!leaf) min_children = (2*m-1)/3;
        else min_children = 0;
        
        max_children = m;
    } else {
        max_keys = 3*min_keys + 2;
        min_children = 2;
        max_children = 2*((2*m-2)/3)+1;
        
    }

    key = new T[max_keys];
    children = new Node*[max_children];
    for (int i = 0; i < max_children; ++i) {
        children[i] = nullptr;
    }
}

template <typename T, int m>
void Tree_B<T, m>::Node::free() {
    delete[] key;
    delete[] children;
}

template <typename T, int m>
bool Tree_B<T, m>::Node::isOverflow() const {
    return children_size == max_children - 1;
}

template <typename T, int m>
bool Tree_B<T, m>::Node::isUnderflow() const {
    return children_size < min_children;
}

template <typename T, int m>
void Tree_B<T, m>::Node::print() const {
    for (int i = 0; i < n; ++i) {
        std::cout << key[i] << ", ";
    }
    std::cout << "\b\b \n";
}

