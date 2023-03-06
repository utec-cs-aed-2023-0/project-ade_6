#ifndef AVLTree_H
#define AVLTree_H
#include "alvN.h"
#include <string>
#include <stack>
#include <queue>
#include <sstream>
using namespace std;

template <typename T>
class AVLTree
{
private:
    NodeBT<T> *root;
    int nodes;


public:
    AVLTree() : root(nullptr) {}
    void insert(T value)
    {
        insert(root,value);
    }
    bool find(T value)
    {
        return find(value, root);
    }

    string getPreOrder(){
        stringstream display;
        getPreOrder(root, display);
        return display.str();
    }

    int height()
    {
        return height(root);
    }
    T minValue()
    {
        return minValue(root)->data;
    }
    T maxValue()
    {
        return maxValue(root)->data;
    }
    bool isBalanced()
    {
        return isBalanced(root) > 0 ? true : false;
    }
    int size()
    {
        return nodes;
    }
    void remove(T value)
    {
        remove(root, value);
    }
    void displayPretty()
    {
        displayPretty(this->root, 1);
    }

    ~AVLTree(){
        if(this->root != nullptr){
            this->root->killSelf();
        }
    }

private:
    void getPreOrder(NodeBT<T>* node, stringstream& display);
    void insert(NodeBT<T> *& node, T value);//*
    bool find(NodeBT<T> *node, T value);
    int height(NodeBT<T>* top);//*
    bool isBalanced(NodeBT<T> *node);//*
    T minValue(NodeBT<T> *node);
    T maxValue(NodeBT<T> *node);
    int size(NodeBT<T> *node);
    void remove(NodeBT<T> *&node, T value);//*
    void displayPretty(NodeBT<T> *node, int level);

    /*add for avl*/    
    int balancingFactor(NodeBT<T> *node);
    void updateHeight(NodeBT<T> *node);
    void balance(NodeBT<T> *&node);
    void left_rota(NodeBT<T> *&node);
    void right_rota(NodeBT<T> *&node);


};

template <typename T>
void AVLTree<T>::getPreOrder(NodeBT<T>* node, stringstream& display){
    if(!node){
        return;
    }
    display << node->data << ' ';
    getPreOrder(node->left, display);
    getPreOrder(node->right, display);
}
template <typename T>
void AVLTree<T>::insert(NodeBT<T> * & node, T value)
{
    if (node == nullptr)
        node = new NodeBT<T>(value);
    if (value < node->data)
        insert(node->left, value);
    else if (value > node->data)
        insert(node->right, value);
    else
    node->height = 1 + max(height(node->left),height(node->right));

    int balance = balancingFactor(node);
    if (balance > 1 && value < node->left->data)
        right_rota(node);
    if (balance < -1 && value > node->right->data)
        left_rota(node);

    if (balance > 1 && value > node->left->data)
    {
        left_rota(node->left);
        right_rota(node);
    }

    if (balance < -1 && value < node->right->data)
    {
        right_rota(node->right);
        left_rota(node);
    }
}

template <typename T>
bool AVLTree<T>::find(NodeBT<T>* node,T value){
    if(!node){
        return false;
    }

    if(value < node->data){
        return find(value, node->left);
    }
    else if(node->data < value){
        return find(value, node->right);
    }

    return node;
}

template <typename T>
int AVLTree<T>::height(NodeBT<T>* node){
    if(node == nullptr){
        return -1;
    }
    int heightRightSubtree = height(node->right);
    int heightLeftSubtree = height(node->left);

    return 1 + max(heightRightSubtree, heightLeftSubtree);
}

template <typename T>
bool AVLTree<T>::isBalanced(NodeBT<T> *node)
{
    int balance = balancingFactor(node);
    if (balance == 0)
    {
        return true;
    }
    return false;
}

template <typename T>
T AVLTree<T>::minValue(NodeBT<T> *node)
{
    if (node == nullptr)
        throw("The tree is empty");
    else if (node->left == nullptr)
        return node->data;
    else
        return minValue(node->left);
}

template <typename T>
T AVLTree<T>::maxValue(NodeBT<T> *node)
{
    if (node == nullptr)
        throw("The tree is empty");
    else if (node->right == nullptr)
        return node->data;
    else
        return maxValue(node->right);
}

template <typename T>
void AVLTree<T>::remove(NodeBT<T> *&node, T value)
{
    if (node == nullptr)
        return;
    else if (value < node->data)
        remove(node->left, value);
    else if (value > node->data)
        remove(node->right, value);
    else
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            delete node; //free
            node = nullptr;
        }
        else if (node->left == nullptr)
        {
            NodeBT<T> *temp = node;
            node = node->right;
            delete temp;
        }
        else if (node->right == nullptr)
        {
            NodeBT<T> *temp = node;
            node = node->left;
            delete temp;
        }
        else
        {
            T temp = maxValue(node->left);
            node->data = temp;
            remove(node->left, temp);
        }
    }
}




template <typename T>
int AVLTree<T>::balancingFactor(NodeBT<T> *node)
{
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

template <typename T>
void AVLTree<T>::updateHeight(NodeBT<T> *node) {
    if (node)return;
    node->height=max(height(node->left),height(node->right))+ 1;
}
template <typename T>
void AVLTree<T>::left_rota(NodeBT<T> *&node)
{
    NodeBT<T> *y = node->right;
    NodeBT<T> *T2 = y->left;

    y->left = node;
    node->right = T2;

    node->height = max(height(node->left),
                       height(node->right)) +
                   1;
    y->height = max(height(y->left),
                    height(y->right)) +
                1;

}

template <typename T>
void AVLTree<T>::right_rota(NodeBT<T> *&node)
{
    NodeBT<T> *x = node->left;
    NodeBT<T> *T2 = x->right;

    // Perform rotation
    x->right = node;
    node->left = T2;

    // Update heights
    node->height = max(height(node->left),
                       height(node->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;

}
#endif
