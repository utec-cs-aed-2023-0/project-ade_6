#ifndef CIRCULAR_H
#define CIRCULAR_H

#include <iostream>
#include <string>

template <typename T>
class CircularList
{
    private:
        struct Node;
        struct Normal;
        struct Sentinel;
        class CircularListIterator;
        typedef CircularListIterator iterator;
    private:
        Node* head;
        int nodes; 
    public:
        CircularList();
        ~CircularList();
        
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
struct CircularList<T>::Node
{
    Node* next;
    Node* prev;
    Node(Node* next, Node* prev): next(next), prev(prev) {};
    virtual ~Node() {/*std::cout << "Nodo base eliminado." << std::endl;*/};
    virtual T& get_data() = 0;
};

template <typename T>
struct CircularList<T>::Normal:Node
{
    T data;
    Normal(T value): Node(nullptr,nullptr), data(value) {};
    ~Normal() {/* std::cout << "Nodo normal eliminado." << std::endl; */};
    T& get_data() override {return data;};
};

template <typename T>
struct CircularList<T>::Sentinel:Node
{
    Sentinel(): Node(this,this) {};
    ~Sentinel() { /* std::cout << "Nodo sentinel eliminado." << std::endl; */};
    T& get_data() override {throw("Nodo Sentinel");};
};

template <typename T>
class CircularList<T>::CircularListIterator
{
    private:
        Node* current;
    public:
        CirculatListIterator(node* n = nullptr): current(n)
        {}; 
        
        bool operator == (const CircularListIterator& other)
        {return current == other.current;};

        bool operator != (const CircularListIterator& other)
        {return current == other.current;};

        CircularListIterator& operator ++ ()
        {
            currrent = current->next;
            return this;
        };

        CircularListIterator& operator -- ()
        {
            current = current->prev;
            return *this;
        };

        T operator * ()
        {return current->data;};
};

template <typename T>
CircularList<T>::CircularList():List<T>() {
    head = new Sentinel;
    nodes = 0;
}

template <typename T>
CircularList<T>::~CircularList() {
    clear();
    delete head;
}

template <typename T>
CircularList<T>::iterator CircularList<T>::begin()
{
    return iterator(head->next);
}

template <typename T>
CircularList<T>::iterator CircularList<T>::end()
{
    return iterator(head);
}

template <typename T>
T CircularList<T>::front() {return head->next->get_data();}

template <typename T>
T CircularList<T>::back() {return head->prev->get_data();}

template <typename T>
void CircularList<T>::push_front(T data) {
    Node* temp = new Normal(data);
    temp->prev = head;
    temp->next = head->next;
    head->next->prev = temp;
    head->next = temp;
    nodes++;
}

template <typename T>
void CircularList<T>::push_back(T data) {
    Node* temp = new Normal(data);
    temp->next = head;
    temp->prev = head->prev;
    head->prev->next = temp;
    head->prev = temp;
    nodes++;
}

template <typename T>
T CircularList<T>::pop_front() {
    T result = head->next->get_data();
    Node* temp1 = head->next;
    Node* temp2 = temp1->next;
    head->next = temp2;
    temp2->prev = head;
    delete temp1;
    nodes--;
    return result;
}

template <typename T>
T CircularList<T>::pop_back() {
    T result = head->prev->get_data();
    Node* temp1 = head->prev;
    Node* temp2 = temp1->prev;
    temp2->next = head;
    head->prev = temp2;
    delete temp1;
    nodes--;
    return result;
}

template <typename T>
T CircularList<T>::insert(T data, int pos) {
    if(pos < 0 || pos >= this->size())
        throw("Indice fuera de rango");
    Node* newNode = new Normal(data);
    Node* temp = head;
    for(; pos > 0; pos--)
        temp = temp->next;
    newNode->prev = temp;
    newNode->next = temp->next;
    temp->next->prev = newNode;
    temp->next = newNode;
    return data;
}

template <typename T>
bool CircularList<T>::remove(int pos) {
    if(pos < 0 || pos >= this->size())
        return false;
    Node* temp = head;
    for(; pos > 0; pos--)
        temp = temp->next;
    temp = temp->next;
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    nodes--;
    delete temp;
    return true;
}

template <typename T>
T& CircularList<T>::operator[] (int pos) {
    if(pos < 0 || pos >= this->size())
        throw("Indice fuera de rango");
    Node* temp = head;
    for(; pos > 0; pos--)
        temp = temp->next;
    return temp->next->get_data();
}

template <typename T>
bool CircularList<T>::is_empty() {
    if (head == head->next)
        return true;
    return false;
}

template <typename T>
int CircularList<T>::size() {
    return nodes;
}

template <typename T>
void CircularList<T>::clear() {
    Node* temp1 = nullptr;
    Node* temp2 = nullptr;
    while(head != head->next) {
        temp1 = head->next;
        temp2 = temp1->next;
        head->next = temp2;
        temp2->prev = head;
        delete temp1;
    } nodes = 0;
}

template <typename T>
void CircularList<T>::sort() {
    Node* temp1 = head->next;
    Node* temp2 = nullptr;
    while(temp1 != head) {
        temp2 = head->prev;
        while (temp2 != temp1) {
            if(temp2->get_data() < temp1->get_data())
            {
                T dato = temp2->get_data();
                temp2->get_data() = temp1->get_data();
                temp1->get_data() = dato;
            }
            temp2 = temp2->prev;
        }
        temp1 = temp1->next;
    }
}

template <typename T>
bool CircularList<T>::is_sorted() {
    if(this->size() == 0)
        return false;
    Node* temp = head->next;
    while(temp->next != head) {
        if(temp->get_data() > temp->next->get_data())
            return false;
        temp = temp->next;
    } return true;
}

template <typename T>
void CircularList<T>::reverse() {
    Node* temp = head;
    Node* temp2 = nullptr;
    do {
        temp2 = temp->next;
        temp->next = temp->prev;
        temp->prev = temp2;
        temp = temp->prev;
    } while (temp != head);
}

template <typename T>
std::string CircularList<T>::name() {return "CircularDoubleLinkedList";}

template <typename T>
void CircularList<T>::display()
{
    Node* temp = head->next;
    std::cout << "Circular List: ";
    while (temp != head) {
        std::cout << temp->get_data() << ' ';
        temp = temp->next;
    } std::cout << std::endl;
}

#endif