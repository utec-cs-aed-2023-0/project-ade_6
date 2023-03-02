#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

template <typename T>
class forward_list {
    private:
        template <typename U> struct Node;
        Node<T>* head;
        int num_nodes;
    public:
        template <typename U> class forward_list_iterator;
        typedef forward_list_iterator<T> iterator;
        iterator begin() {return iterator(head,head);};
        iterator end() {return iterator(nullptr,head);};
        forward_list();
        ~forward_list();
        T front();
        void push_front(T value);
        T pop_front();
        int size();
        bool is_empty();
        void clear();
        void menos_uno() {this->num_nodes--;};
};

template <typename T>
template <typename U>
struct forward_list<T>::Node {
    U value;
    Node<U>* next;
    Node(U value): value(value), next(nullptr) {};
};

template <typename T>
template <typename U>
class forward_list<T>::forward_list_iterator {
    private:
        Node<U>* pointer;
        Node<U>* head;
    public:
        forward_list_iterator(): pointer(nullptr), head(nullptr) {};
        forward_list_iterator(Node<U>* pointer, Node<U>* head): pointer(pointer), head(head) {};

        bool operator == (const forward_list_iterator &other) { return this->pointer == other.pointer; };

        bool operator != (const forward_list_iterator &other) { return this->pointer != other.pointer; };
        
        forward_list_iterator& operator ++ () {
            if(pointer != nullptr)
                pointer = pointer->next;
            else
                pointer = head;
            return *this;
        };

        U& operator * () {
            if(pointer == nullptr)
                throw("ERROR");
            return pointer->value;
        }

        void remove_after() {
            if(pointer != nullptr) {
                    if (pointer->next != nullptr) {
                        Node<U>* temp = pointer->next;
                        pointer->next = temp->next;
                        delete temp;
                    }
            }
        }
};

template <typename T>
forward_list<T>::forward_list(): head(nullptr), num_nodes(0) {}

template <typename T>
forward_list<T>::~forward_list() {
    this->clear();
} 

template <typename T>
void forward_list<T>::push_front(T value) {
    Node<T>* temp = new Node<T>(value);
    temp->next = head;
    head = temp;
    this->num_nodes++;
}

template <typename T>
T forward_list<T>::front() {
    if(this->is_empty())
        throw("Lista VACIA");
    return head->value;
}

template <typename T>
T forward_list<T>::pop_front() {
    if(this->is_empty())
        throw("Lista VACIA");
    T value = head->value;
    Node<T>* temp = head->next;
    delete head;
    head = temp;
    this->num_nodes--;
    // std::cout << "Nodo " << value << " eliminado." << std::endl;
    return value;
}

template <typename T>
int forward_list<T>::size() {
    return this->num_nodes;
}

template <typename T>
bool forward_list<T>::is_empty() {
    if(head == nullptr)
        return true;
    return false;
}

template <typename T>
void forward_list<T>::clear() {
    while(! this->is_empty())
        this->pop_front();
}

#endif