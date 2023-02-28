#ifndef NODE1_H
#define NODE1_H

#include <iostream>

// Nodo para el Forward List
namespace forward_list_node {
    template <typename T>
    struct Node {
        T data;
        Node<T>* next;
        Node(T value): data(value), next(nullptr) {};
    };
};

#endif