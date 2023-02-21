#ifndef LIST_H
#define LIST_H

// Creacion de una lista circular simplemente enlazada con un centinela
template <typename T>
class list
{
  private:
    struct node;
    class list_iterator;
  public:
    typedef list_iterator iterator;
  private:
    node* sentinel;
    int num_nodes;
  public:
    list();
    iterator begin() {return iterator(sentinel->next);};
    iterator end() {return iterator(sentinel);};
    T* back();
    void push(T value);
    int size();
    bool is_empty();
};

// **************************************************************************

// Implementación de los nodos
template <typename T>
struct list<T>::node
{
  T* data    = nullptr;
  node* next = this;
  node* prev = this;
};

// **************************************************************************

// Implementación del iterador
template <typename T>
class list<T>::list_iterator
{
  private:
    node* current;
  public:
    list_iterator(node* n = nullptr): current(n)
    {};
    
    bool operator == (const list_iterator &other)
    {
      return current == other.current;
    };

    bool operator != (const list_iterator &other)
    {
      return current != other.current;
    };

    list_iterator& operator ++ ()
    {
      current = current->next;
      return *this;
    };

    list_iterator& operator -- ()
    {
      current = current->prev;
      return *this;
    };

    T* operator * ()
    {
      return current->data;
    };
};

// **************************************************************************

template <typename T> 
list<T>::list()
{
  sentinel  = new node;
  num_nodes = 0;
}

template <typename T>
T* list<T>::back()
{
  return sentinel->prev->data;
}

template <typename T>
void list<T>::push(T value)
{
  node* temp = new node;
  temp->data = new T(value);
  temp->next = sentinel;
  temp->prev = sentinel->prev;
  sentinel->prev->next = temp;
  sentinel->prev = temp;
  num_nodes++;
}

template <typename T>
int list<T>::size()
{
  return num_nodes;
}

template <typename T>
bool list<T>::is_empty()
{
  if(sentinel->next == sentinel)
    return true;
  return false;
}

#endif