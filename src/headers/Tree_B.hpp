#ifndef TREE_B_HPP
#define TREE_B_HPP

template <typename T, int k>
class Tree_B{
private:
    template <typename U>
    struct Node{
        Node(T data, Node<U>* left = nullptr, Node<U>* right = nullptr);
        U datas[k];
        Node<U>* left;
        Node<U>* right;
        Node<U> children[k];
    };
    Node<T>* root;
    Node<T>* copy(const Node<T>* root);
public:
	Tree_B();
	~Tree_B();
	Tree_B(const Tree_B<T, k>& g);
	Tree_B<T, k>& operator=(const Tree_B<T, k>& g);

    void insert(const T& data);
    void remove(const T& data);
    bool search(const T& data) const;
    void insert(const T& data, Node<T>*& root);
    void remove(const T& data, Node<T>*& root);
    bool search(const T& data, Node<T>* root) const;
    void clear(Node<T>* root);
    void copy(Node<T>* root, Node<T>*& new_root);
    void print(Node<T>* root) const;
    void print() const;
    void print_preorder(Node<T>* root) const;
    void print_preorder() const;
    void print_postorder(Node<T>* root) const;
    void split(Node<T>* root, Node<T>* left, Node<T>* right);
};

#include "../templates/Tree_B.tpp"

#endif
