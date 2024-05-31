
template <typename T, int k>
Tree_B<T, k>::Tree_B(){}

template <typename T, int k>
Tree_B<T, k>::~Tree_B(){}

template <typename T, int k>
Tree_B<T, k>::Tree_B(const Tree_B<T, k>& g){ *this = g; }

template <typename T, int k>
Tree_B<T, k>& Tree_B<T, k>::operator=(const Tree_B<T, k>& g){}


template <typename T, int k>
void Tree_B<T, k>::insert(const T& d){ insert(d, root); }

template <typename T, int k>
void Tree_B<T, k>::insert(const T& d, Node<T>*& p){
    if(p == nullptr){
        p = new Node<T>(d);
    }else if(d < p->data){
        insert(d, p->left);
    }else if(d > p->data){
        insert(x, p->right);
    }
}

template <typename T, int k>
void Tree_B<T, k>::split(Node<T>* root, Node<T>* left, Node<T>* right){
    split(root, left, right);
}
