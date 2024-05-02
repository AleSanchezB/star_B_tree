#ifndef TREE_B_HPP
#define TREE_B_HPP

template <typename T>
class Tree_B{
public:
	Tree_B();
	~Tree_B();
	Tree_B(const Tree_B<T>& g);
	Tree_B<T>& operator=(const Tree_B<T>& g);

private:

};

#include "../templates/Tree_B.tpp"
#endif
