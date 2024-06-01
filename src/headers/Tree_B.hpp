#ifndef TREE_B_HPP
#define TREE_B_HPP

template <typename T, int m>
class Tree_B{
private:
    struct Node{
        Node(bool leaf = true, bool isroot = false);
        T* key;
        Node** children;         
        bool leaf;
        bool isroot;
        int children_size;
        
        bool isOverflow() const;
        bool isUnderflow() const;
        void insertionSort(int i, const T& key);
        void split(int index, Node *parent);
        void insertNonFull(const T& key);
        int n;

        void print() const;
        void free();

        int min_keys;
        int max_keys;
        int min_children;
        int max_children;
    };
    Node* root;

    
    // void insert(const T& data, Node* root); 
    void remove(const T& key, Node*& root);

    void print_preorder(Node* root) const;
    void print_postorder(Node* root) const;
    void print(Node* root) const;
    void insert(const T& key, Node*& root);
    bool search(const T& key, Node* root) const;
    void split(Node* parent, int index);
    void free(Node* root);
public:
	Tree_B();
 	~Tree_B();
	Tree_B(const Tree_B<T, m>& g);
	Tree_B<T, m>& operator=(const Tree_B<T, m>& g);

    void insert(const T& key);
    void remove(const T& key);
    bool search(const T& key) const;
    void clear(Node* root);
    void print() const;
    void print_preorder() const;
    
};

#include "../templates/Tree_B.tpp"

#endif
