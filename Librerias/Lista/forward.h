#ifndef FORWARD_H
#define FORWARD_H

#include <iostream>
#include <string>

template <typename T>
class ForwardList
{
    private:
        struct Node;
        class ForwardListIterator;
        typedef ForwardListIterator iterator;
    private:
        Node<T>* head;
        int nodes;

    public:
        ForwardList();
        ~ForwardList();
        iterator begin();
        iterator end();
        T front();
        T back();
        void push_front(T data);
        void push_back(T data);
        T pop_front();
        T pop_back();
        T insert(T data, int pos);
        bool remove(int pos);
        T& operator[](int pos);
        bool is_empty();
        int size();
        void clear();
        void sort();
        bool is_sorted();
        void reverse();
        std::string name();
        void display();
};

template <typename T>
struct ForwardList<T>::Node
{
    T data;
    Node<T>* next;
    Node(T value): data(value), next(nullptr) {};
};

template <typename T>
class ForwardList<T>::ForwardListIterator
{
    private:
        Node* current;
        Node* head;
    public:
        ForwardListIterator(): current(nullptr), head(nullptr)
        {};

        ForwardListIterator(node* _current, node* _head): current(_current), head(_head)
        {}; 
        
        bool operator == (const ForwardListIterator& other)
        {return current == other.current && head == other.head;};

        bool operator != (const ForwardListIterator& other)
        {return current != other.current && head != other.head;};

        ForwardListIterator& operator ++ ()
        {
            if (current == nullptr)
                current = head;
            currrent = current->next;
            return this;
        };

        T operator * ()
        {
            if(current == nullptr)
                throw("This iterator doesn't contain any element");
            return current->data;
        };
};

template <typename T>
ForwardList<T>::ForwardList(): List<T>(), head(nullptr), nodes(0)
{}

template <typename T>
ForwardList<T>::~ForwardList()
{
    this->clear();
}

template <typename T>
ForwardList<T>::iterator ForwardList<T>::begin()
{
    return iterator(head,head);
}

template <typename T>
ForwardList<T>::iterator ForwardList<T>::end()
{
    return iterator(nullptr, head);
}

template <typename T>
T ForwardList<T>::front() {
    if (this->is_empty())
        throw ("Lista VACIA");
    return head->data;
}

template <typename T>
T ForwardList<T>::back() {
    if (this->is_empty())
        throw ("Lista VACIA");
    Node<T>* temp = head;
    while(temp->next != nullptr)
        temp = temp->next;
    return temp->data;
}

template <typename T>
void ForwardList<T>::push_front(T data) {
    Node<T>* temp = new Node<T>(data);
    temp->next = head;
    head = temp;
    nodes++;
}

template <typename T>
void ForwardList<T>::push_back(T data) {
    if(is_empty()) {
        head = new Node<T>(data);
    } else {
        Node<T>* temp = head;
        while(temp->next != nullptr)
            temp = temp->next;
        temp->next = new Node<T>(data);
    } nodes++;
}

template <typename T>
T ForwardList<T>::pop_front() {
    if (this->is_empty())
        throw("Lista VACIA");
    T result = head->data;
    Node<T>* temp = head;
    head = head->next;
    delete temp;
    nodes--;
    return result;
}

template <typename T>
T ForwardList<T>::pop_back() {
    if(this->is_empty())
        throw("Lista VACIA");
    T result;
    if (this->size() == 1) {
        result = head->data;
        delete head;
        head = nullptr;
    } else {
        Node<T>* temp = head;
        while(temp->next->next != nullptr)
            temp = temp->next;
        result = temp->next->data;
        delete temp->next;
        temp->next = nullptr;
    } nodes--;
    return result;
}

template <typename T>
T ForwardList<T>::insert(T data, int pos){
    if(pos < 0 || pos >= this->size())
        throw("Index out of range");
    this->push_front(data);
    Node<T>* temp = head;
    for(; pos > 0; pos--) {
        T d = temp->data;
        temp->data = temp->next->data;
        temp->next->data = d;
        temp = temp->next;
    }
    return data;
}

template <typename T>
bool ForwardList<T>::remove(int pos) {
    if(pos < 0 || pos >= this->size()) {
        std::cout << "Indice fuera de rango" << std::endl;
        return false;
    }
    if (pos == 0) {
        this->pop_front();
    } else {
        Node<T>* temp1 = head;
        Node<T>* temp2 = nullptr;
        for(; pos > 1; pos--)
            temp1 = temp1->next;
        temp2 = temp1->next->next;
        delete temp1->next;
        temp1->next = temp2;
    }
    return true;
    
}

template <typename T>
T& ForwardList<T>::operator[] (int pos) {
    if(pos < 0 || pos >= this->size())
        throw("Index out of range");
    Node<T>* temp = head;
    for(; pos > 0; pos--)
        temp = temp->next;
    return temp->data;
}


template <typename T>
bool ForwardList<T>::is_empty() {
    if(head == nullptr)
        return true;
    return false;
}

template <typename T>
int ForwardList<T>::size() {
    return nodes;
}

template <typename T>
void ForwardList<T>::clear() {
    Node<T>* temp = nullptr;
    while(head != nullptr) {
        temp = head->next;
        delete head;
        head = temp;
    } nodes = 0;
}

template <typename T>
void ForwardList<T>::sort() {
    Node<T>* head_temp = nullptr;
    Node<T>* temp = nullptr;
    while(head != nullptr) {
        temp = head;
        head = head->next;
        temp->next = head_temp;
        head_temp = temp;
        while(temp->next != nullptr) {
            if (temp->data > temp->next->data) {
                T n = temp->data;
                temp->data = temp->next->data;
                temp->next->data = n;
                temp = temp->next;
            } else {break;}
        }
    }
    head = head_temp;
}

template <typename T>
bool ForwardList<T>::is_sorted() {
    if(this->is_empty()) 
        return false;
    Node<T>* temp = head;
    while(temp->next != nullptr) {
        if(temp->data > temp->next->data)
            return false;
        temp = temp->next;
    }
    return true;
}

template <typename T>
void ForwardList<T>::reverse() {
    Node<T>* head_temp = nullptr;
    Node<T>* temp = nullptr;
    while(head != nullptr) {
        temp = head;
        head = head->next;
        temp->next = head_temp;
        head_temp = temp;
    }
    head = head_temp;
}

template <typename T>
std::string ForwardList<T>::name() {
    return "ForwardList";
}

template <typename T>
void ForwardList<T>::display()
{
    Node<T>* temp = head;
    std::cout << "Forward List: ";
    while (temp != nullptr) {
        std::cout << temp->data << ' ';
        temp = temp->next;
    } std::cout << std::endl;
}

#endif