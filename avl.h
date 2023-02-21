#ifndef AVLTree_H
#define AVLTree_H
#include "node.h"

using namespace std;

template <typename T>
class AVLTree
{
private:
    NodeBT<T> *root;
public:
    AVLTree() : root(nullptr) {};
    
    void insert(T value) {insert(this->root, value);};

    int height() {return height(this->root);};
    
    T minValue() {
        if (root == nullptr)
            throw("The tree is empty");
        return minValue(this->root);};
    
    T maxValue() {
        if (root == nullptr)
            throw("The tree is empty");
        return maxValue(this->root);};
    
    bool isBalanced() {
        if(this->root == nullptr)
            return false;
        return isBalanced(this->root);
    };

    void remove(T value) {remove(this->root, value);};

    ~AVLTree(){
        if(this->root != nullptr){
            this->root->killSelf();
        }
    }

private:

    void insert(NodeBT<T> *&node, T value);
    bool find(NodeBT<T> *node, T value);

    T minValue(NodeBT<T> *node);
    T maxValue(NodeBT<T> *node);

    int height(NodeBT<T> *node);
    int balancingFactor(NodeBT<T> *node);
    void updateHeight(NodeBT<T> *node);
    void balance(NodeBT<T> *&node);
    void left_rota(NodeBT<T> *&node);
    void right_rota(NodeBT<T> *&node);

};


template <typename T>
void AVLTree<T>::insert(NodeBT<T>* &node, T value)
{
    if(node == nullptr)
        node = new NodeBT<T>(value);
    else if (value < node->data)
        insert(node->left, value);
    else if (value > node->data)
        insert(node->right, value);
    updateHeight(node);
    this->balance(node);
}


template <typename T>
T AVLTree<T>::minValue(NodeBT<T> *node)
{
    if (node->left == nullptr)
        return node->data;
    return minValue(node->left);
}

template <typename T>
T AVLTree<T>::maxValue(NodeBT<T> *node)
{
    if (node->right == nullptr)
        return node->data;
    return maxValue(node->right);
}

template <typename T>
int AVLTree<T>::height(NodeBT<T> *node)
{
    if(node == nullptr)
        return -1;
    return 1 + max(height(node->left), height(node->right));
}
template <typename T>
int AVLTree<T>::balancingFactor(NodeBT<T>* node) {
    if (node == nullptr)
        throw("The tree is empty");
    return ((node->left != nullptr) ? node->left->height : -1) - ((node->right != nullptr) ? node->right->height : -1);
}

template <typename T>
void AVLTree<T>::updateHeight(NodeBT<T> *node) {
    node->height = 1 + std::max(((node->left != nullptr) ? node->left->height : -1), ((node->right != nullptr) ? node->right->height : -1));
}

template <typename T>
void AVLTree<T>::balance(NodeBT<T>* &node) {
    if (node != nullptr) {
        if(this->balancingFactor(node) > 1) {
            right_rota(node);
        } else if (this->balancingFactor(node) < -1) {
            left_rota(node);
        }
    }
}

template <typename T>
void AVLTree<T>::left_rota(NodeBT<T> *&node) {
    NodeBT<T>* temp = nullptr;
    NodeBT<T>* temp2 = nullptr;
    if (this->balancingFactor(node->right) <= 0) {
        temp = node;
        node = node->right;
        temp->right = node->left;
        node->left = temp;
        updateHeight(temp);
        updateHeight(node);
    } else {
        temp = node;
        node = node->right;
        temp2 = node;
        node = node->left;
        temp->right = node->left;
        temp2->left = node->right;
        node->left = temp;
        node->right = temp2;
        updateHeight(temp);
        updateHeight(temp2);
        updateHeight(node);
    }
}

template <typename T>
void AVLTree<T>::right_rota(NodeBT<T> *&node) {
    NodeBT<T>* temp = nullptr;
    NodeBT<T>* temp2 = nullptr;
    if (this->balancingFactor(node->left) >= 0) {
        temp = node;
        node = node->left;
        temp->left = node->right;
        node->right = temp;
        updateHeight(temp);
        updateHeight(node);
    } else {
        temp = node;
        node = node->left;
        temp2 = node;
        node = node->right;
        temp->left = node->right;
        temp2->right = node->left;
        node->right = temp;
        node->left = temp2;
        updateHeight(temp);
        updateHeight(temp2);
        updateHeight(node);
    }
}


#endif
