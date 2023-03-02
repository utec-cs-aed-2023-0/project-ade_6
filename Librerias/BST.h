//
// Created by hosmercito on 27/02/2023.
//

#ifndef FINALPROYECTV_BTREEBETITA_H
#define FINALPROYECTV_BTREEBETITA_H


#include <iostream>

using namespace std;

template<typename T>
class BST
        {
private:
    template <typename TK>
    struct NodeBT {
        T data;
        NodeBT* left;
        NodeBT* right;
        NodeBT() : left(nullptr), right(nullptr) {}
        NodeBT(T value) : data(value), left(nullptr), right(nullptr) {}

        void killSelf(){
            if(left != nullptr) left->killSelf();
            if(right != nullptr) right->killSelf();
            delete this;
        }
    };
    NodeBT<T> *root;
public:
    BST() : root(nullptr) {}
    void insert(T value)
    {
        insert(this->root, value);
    }
    bool find(T value)
    {
        return find(this->root, value);
    }
    void remove(T value){
        remove(this->root, value);
    }
    string rangeSearch (T value1,T value2){
        string result;
        rangeSearch(this->root,value1,value2,result);
        return result;
    }
    void displayInOrder(){
        displayInOrder(this->root);
    }
    ~BST()
    {
        if (this->root != nullptr)
        {
            this->root->killSelf();
        }
    }

private:
    void insert(NodeBT<T> *&node, T value);
    bool find(NodeBT<T> *node, T value);
    void remove(NodeBT<T> *&node, T value);
    void displayInOrder(NodeBT<T> *node);
    void rangeSearch(NodeBT<T> *node, T value1, T value2,string &result);
};

template <typename T>
void BST<T>::insert(NodeBT<T> *&node, T value)
{
    if (node == nullptr)
        node = new NodeBT<T>(value);
    else if (value < node->data)
        insert(node->left, value);
    else
        insert(node->right, value);
}

template <typename T>
bool BST<T>::find(NodeBT<T> *node, T value)
{
    if (node == nullptr)
        return false;
    else if (value < node->data)
        return find(node->left, value);
    else if (value > node->data)
        return find(node->right, value);
    else
        return true;
}

template <typename T>
void BST<T>::remove(NodeBT<T> *&node, T value)
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
void BST<T>::rangeSearch(NodeBT<T>* node,T value1,T value2, string &result){
    if(!node) return;
    cout  << node->data << endl;

    if (node->left != nullptr && node->data >= value1 )
    {
        rangeSearch(node->left, value1, value2, result);
    }
    if (node->data >= value1 && node->data <= value2 )
    {
        result += to_string(node->data)+" ";
    }
    if (node->right != nullptr and node->data <= value2 and node->right->data <= value2 )
    {
        rangeSearch(node->right, value1, value2, result);
    }
}


#endif //FINALPROYECTV_BTREEBETITA_H
