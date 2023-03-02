#ifndef BTree_H
#define BTree_H
#include <iostream>
#include <sstream>

#include <queue>
#include <cmath>

using namespace std;

template <typename TK>
class BTree
{
public:
    template <typename TY>
    struct Node
            {
        TK* keys;           // An array of keys
        Node** children;   // An array of child pointers
        int count;          // Current number of keys
        bool leaf;          // Whether node is a leaf or not
        int t;	             // Minimum degree

        Node(int t, bool leaf): t(t), leaf(leaf)
        {
            keys = new TY[2*t - 1]; // odd number of keys
            children = new Node<TY>*[2*t];
            count = 0;
            }
        ~Node(){
            delete[] keys;
            delete[] children;
            }
        };

        BTree(int t);
		~BTree();

		bool search(TK key);
		void rangeSearch(TK start, TK end);
        void print_range_search(TK key, TK end);
	    void insert(TK key);
		void remove(TK key);
		string toString(string sep);
		void displayPretty();

		TK minKey();
    	TK maxKey();
        int height();
        int size();

		void clear();

    private:
	    Node<TK>* root;
	    int t;
        int n;
		int _height;

		// Common helper functions
        bool search(Node<TK>* node, TK key);
		void rangeSearch(Node<TK>* node, TK start, TK end);
        void print_range_search(TK key, Node<TK>* node,  TK end);
        void toString(Node<TK>* node, string sep, stringstream& out);
		void displayGivenLevel(Node<TK>* node, int level);

		// Helper functions for insert method
        void insertNonFull(Node<TK>*& node, TK key);
        void splitChild(Node<TK>* x, int index);

		// Helper functions for remove method
		void removeFromNode(Node<TK>* node, TK key);
		void removeFromLeaf(Node<TK>* node, int index);
		void mergeWithSuccessor(Node<TK>* node, int index);

		void fillNode(Node<TK>* node, int index);
		void borrowFromPrev(Node<TK>* node, int index);
		void borrowFromNext(Node<TK>* node, int index);
		void mergeWithNext(Node<TK>* node, int index);
		void mergeWithPrev(Node<TK>* node, int index);
		int findKeyIndex(Node<TK>* node, TK key);
};

template <typename TK>
BTree<TK>::BTree(int t) : t(t)
{
	_height = 0;
    n = 0;
    root = nullptr;
}

template <typename TK>
BTree<TK>::~BTree()
{
	clear();
}

template <typename TK>
string BTree<TK>::toString(string sep)
{
    stringstream out;
    toString(root, sep, out);
    string result = out.str();

    if (!result.empty())
        result.erase(result.size() - sep.size(), sep.size());

    return result;
}

template <typename TK>
void BTree<TK>::toString(Node<TK>* node, string sep, stringstream& out)
{
	int i = 0;
	while (i < node->count){
		if (!node->leaf)
			toString(node->children[i], sep, out);
		out << node->keys[i] << sep;
        ++i;
	}

	if (!node->leaf)
		toString(node->children[i], sep, out);
}


template <typename TK>
bool BTree<TK>::search(TK key)
{ 
    return search(root, key); 
}

template <typename TK>
bool BTree<TK>::search(Node<TK>* node, TK key)
{
    int i = 0; 
    while (i < node->count and key > node->keys[i])
        ++i;
    
    if (key == node->keys[i])
        return true;
    else if (node->leaf)
        return false;
    else
        return search(node->children[i], key);
}

template <typename TK>
void BTree<TK>::rangeSearch(TK start, TK end){
	rangeSearch(root, start, end);
}

template <typename TK>
void BTree<TK>::rangeSearch(Node<TK>* node, TK start, TK end){

    if (node == nullptr)
        return;

    int i = 0;
    while (i < node->count and node->keys[i] < start)
		++i;

    while (i < node->count and node->keys[i] <= end) {
		if (!node->leaf)
        	rangeSearch(node->children[i], start, end);

        cout << node->keys[i] << " ";
        ++i;
    }
		
	if (!node->leaf)
        rangeSearch(node->children[i], start, end);
}

template <typename TK>
void BTree<TK>::print_range_search(TK key, TK end)
{
    print_range_search(key,root,end);
}

template <typename TK>
void BTree<TK>::print_range_search(TK key ,Node<TK>* node, TK end){
    if (node == nullptr)
        return;

    int i = 0;
    while (i < node->count and node->keys[i] <= key)
        ++i;

    while (i < node->count and node->keys[i] <= end)
    {
        if (!node->leaf)
            print_range_search(key, node->children[i], end);
        cout << node->keys[i] << " ";
        ++i;
    }

    if (!node->leaf)
        if(i == node->count)
            print_range_search(key,node->children[i],end);
}

template <typename TK>
TK BTree<TK>::minKey()
{
	if (root == nullptr)
		throw runtime_error("B tree is empty");

	Node<TK>* current = root;

	while (current->leaf == false)
	{
		current = current->children[0];
	}

	return current->keys[0];
}

template <typename TK>
TK BTree<TK>::maxKey()
{
	if (root == nullptr)
		throw runtime_error("B tree is empty");

	Node<TK>* current = root;

	while (current->leaf == false)
	{
		current = current->children[current->count];
	}

	return current->keys[current->count - 1];
}

template <typename TK>
int BTree<TK>::height()
{
    return _height;
}

template <typename TK>
int BTree<TK>::size()
{
    return n;
}

template <typename TK>
void BTree<TK>::insert(TK key)
{
	if (root == nullptr){
		root = new Node<TK>(t, true);
		root->keys[0] = key;
		root->count = 1;
		_height = 1;
	}
	else {
		if (root->count == 2*t - 1) {
			Node<TK>* s = new Node<TK>(t, false);
			s->children[0] = root;
			splitChild(s, 0);

			int i = 0;
			if (s->keys[0] < key)
				i++;
			insertNonFull(s->children[i], key);
			root = s;
			
			_height += 1;
		}
		else
			insertNonFull(root, key);
	}
    ++n;
}

template <typename TK>
void BTree<TK>::insertNonFull(Node<TK>*& node, TK key)
{
	int i = node->count - 1;
	if (node->leaf) {
		while (i >= 0 and node->keys[i] > key) {
			node->keys[i+1] = node->keys[i];
			--i;
		}
		node->keys[i+1] = key;
		++node->count;
	}
	else {
		while (i >= 0 and node->keys[i] > key)
			--i;
        ++i;
		if (node->children[i]->count == 2*t - 1) {
			splitChild(node, i);
			if (node->keys[i] < key)
				++i;
		}
		insertNonFull(node->children[i], key);
	}
}

template <typename TK>
void BTree<TK>::splitChild(Node<TK>* x, int i)
{
    Node<TK>* y = x->children[i];
	Node<TK>* z = new Node<TK>(y->t, y->leaf);
	z->count = t - 1;

	for (int j = 0; j < t - 1; j++)
		z->keys[j] = y->keys[j+t];

	if (!y->leaf) {
		for (int j = 0; j < t; j++)
			z->children[j] = y->children[j+t];
	}

	y->count = t - 1;

	for (int j = x->count; j >= i + 1; j--)
		x->children[j+1] = x->children[j];

	x->children[i+1] = z;

	for (int j = x->count - 1; j >= i; j--)
		x->keys[j+1] = x->keys[j];

	x->keys[i] = y->keys[t-1];

	++x->count;
}

template <typename TK>
void BTree<TK>::displayPretty()
{
    for (int i = 1; i <= _height; ++i) {
        displayGivenLevel(root, i);
        cout << "\n";
    }
}

template <typename TK>
void BTree<TK>::displayGivenLevel(Node<TK>* node, int level)
{
    if (node == nullptr)
        return;
    if (level == 1) {
		cout << "[ ";
		for (int i = 0; i < node->count; ++i) {
			cout << node->keys[i] << " ";
		}
		cout << "]";
	}
    else {
		for (int i = 0; i <= node->count; ++i) {
			displayGivenLevel(node->children[i], level - 1);
			cout << " ";
		}
    }
}
template <typename TK>
void BTree<TK>::remove(TK key)
{
    if (!root)
        return;

    removeFromNode(root, key);

    if (root->count == 0) {
        Node<TK>* oldRoot = root;
        if (root->leaf)
            root = nullptr;
        else
            root = root->children[0];
        _height--;
        delete oldRoot;
    }
    --n;
}

template <typename TK>
void BTree<TK>::removeFromNode(Node<TK>* node, TK key)
{
    int i = findKeyIndex(node, key);

    if (i < node->count and node->keys[i] == key) {
        if (node->leaf) {
            removeFromLeaf(node, i);
        } else {
            mergeWithSuccessor(node, i);
            removeFromNode(node->children[i], node->keys[i]);
        }
    } else {
        if (node->leaf) {
            return;
        }

        bool flag = (i == node->count);

        if (node->children[i]->count < t)
            fillNode(node, i);

        if (flag and i > node->count)
            removeFromNode(node->children[i-1], key);
        else
            removeFromNode(node->children[i], key);
    }
}

template <typename TK>
void BTree<TK>::removeFromLeaf(Node<TK>* node, int index)
{
    for (int i = index+1; i < node->count; i++)
        node->keys[i-1] = node->keys[i];

    node->count--;
}

template <typename TK>
void BTree<TK>::mergeWithSuccessor(Node<TK>* node, int index)
{
    Node<TK>* child = node->children[index];
    Node<TK>* successor = node->children[index+1];

    child->keys[t-1] = node->keys[index];

    for (int i = 0; i < successor->count; i++)
        child->keys[i+t] = successor->keys[i];

    if (!child->leaf) {
        for (int i = 0; i <= successor->count; i++)
            child->children[i+t] = successor->children[i];
    }

    for (int i = index+1; i < node->count; i++)
        node->keys[i-1] = node->keys[i];

    for (int i = index+2; i <= node->count; i++)
        node->children[i-1] = node->children[i];

    child->count += successor->count + 1;
    node->count--;

    delete successor;
}

template <typename TK>
void BTree<TK>::fillNode(Node<TK>* node, int index)
{
    if (index != 0 and node->children[index-1]->count >= t)
        borrowFromPrev(node, index);
    else if (index != node->count and node->children[index+1]->count >= t)
        borrowFromNext(node, index);
    else {
        if (index != node->count)
            mergeWithNext(node, index);
        else
            mergeWithPrev(node, index);
    }
}

template <typename TK>
void BTree<TK>::borrowFromPrev(Node<TK>* node, int index)
{
    Node<TK>* child = node->children[index];
    Node<TK>* sibling = node->children[index-1];

    for (int i = child->count-1; i >= 0; i--)
        child->keys[i+1] = child->keys[i];

    if (!child->leaf) {
        for (int i = child->count; i >= 0; i--)
            child->children[i+1] = child->children[i];
    }

    child->keys[0] = node->keys[index-1];

    if (!node->leaf)
        child->children[0] = sibling->children[sibling->count];

    node->keys[index-1] = sibling->keys[sibling->count-1];

    child->count += 1;
    sibling->count -= 1;
}

template <typename TK>
void BTree<TK>::borrowFromNext(Node<TK>* node, int index)
{
    Node<TK>* child = node->children[index];
    Node<TK>* sibling = node->children[index+1];

    child->keys[child->count] = node->keys[index];

    if (!child->leaf)
        child->children[child->count+1] = sibling->children[0];

    node->keys[index] = sibling->keys[0];

    for (int i = 1; i < sibling->count; i++)
        sibling->keys[i-1] = sibling->keys[i];

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->count; i++)
            sibling->children[i-1] = sibling->children[i];
    }

    child->count += 1;
    sibling->count -= 1;
}

template <typename TK>
void BTree<TK>::mergeWithNext(Node<TK>* node, int index)
{
    Node<TK>* child = node->children[index];
    Node<TK>* sibling = node->children[index+1];

    child->keys[t-1] = node->keys[index];

    for (int i = 0; i < sibling->count; i++)
        child->keys[i+t] = sibling->keys[i];

    if (!child->leaf) {
        for (int i = 0; i <= sibling->count; i++)
            child->children[i+t] = sibling->children[i];
    }

    for (int i = index+1; i < node->count; i++)
        node->keys[i-1] = node->keys[i];

    for (int i = index+2; i <= node->count; i++)
        node->children[i-1] = node->children[i];

    child->count += sibling->count+1;
    node->count--;

    delete sibling;
}

template <typename TK>
void BTree<TK>::mergeWithPrev(Node<TK>* node, int index)
{
    Node<TK>* child = node->children[index];
    Node<TK>* sibling = node->children[index-1];

    sibling->keys[sibling->count] = node->keys[index-1];

    for (int i = 0; i < child->count; i++)
        sibling->keys[sibling->count+1+i] = child->keys[i];

    if (!child->leaf) {
        for (int i = 0; i <= child->count; i++)
            sibling->children[sibling->count+1+i] = child->children[i];
    }

    for (int i = index-1; i < node->count-1; i++)
        node->keys[i] = node->keys[i+1];

    for (int i = index; i < node->count; i++)
        node->children[i] = node->children[i+1];

    sibling->count += child->count+1;
    node->count--;

    delete child;
}


template <typename TK>
int BTree<TK>::findKeyIndex(Node<TK>* node, TK key)
{
    int index = 0;
    while (index < node->count and node->keys[index] < key)
        index++;
    return index;
}


template <typename TK>
void BTree<TK>::clear() {
    if (!root) return;

    queue<Node<TK>*> q;
    q.push(root);

    while (!q.empty()) {
        Node<TK>* node = q.front();
        q.pop();

        for (int i = 0; i < node->count; i++) {
            if (!node->leaf) q.push(node->children[i]);
        }

        delete node;
    }

    root = nullptr;
    _height = 0;
    n = 0;
}


#endif
