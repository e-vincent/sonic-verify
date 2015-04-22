#ifndef __TREE_C_ITERATOR_H__
#define __TREE_C_ITERATOR_H__

namespace ast
{

template <class T>
class TreeCIterator : public TreeIterator<T>
{
private:
	ast::NodeTree<T>& _c_nodeTree;
	T _c_curr;

public:
	TreeCIterator<T>();
	TreeCIterator<T>(ast::NodeTree<T>& tree);

	TreeCIterator<T> cbegin() const;
	TreeCIterator<T> cend() const;

	TreeCIterator<T> operator++();
};

} // namespace ast

#endif // __TREE_C_ITERATOR_H__