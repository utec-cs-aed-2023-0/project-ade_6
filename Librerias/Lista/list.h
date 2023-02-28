#ifndef LIST_H
#define LIST_H

template <typename T>
class List
{
    private:
        class ListIterator;
        typedef ListIterator iterator;
    public:
        virtual ~List() {};
        virtual T front() = 0;
        virtual T back() = 0;
        virtual void push_front(T) = 0;
        virtual void push_back(T) = 0;
        virtual T pop_front() = 0;
        virtual T pop_back() = 0;
        virtual T insert(T, int) = 0;
        virtual bool remove(int) = 0;
        virtual T& operator[](int) = 0;
        virtual bool is_empty() = 0;
        virtual int size() = 0;
        virtual void clear() = 0;
        virtual void sort() = 0;
        virtual bool is_sorted() = 0;
        virtual void reverse() = 0;
        virtual std::string name() = 0;
        virtual void display() = 0;
};

template <typename T>
class List<T>::ListIterator
{
    public:
        ListIterator() {};
        virtual ~ListIterator() {};
        bool operator == (const ListIterator* &other) = 0;
        bool operator != (const ListIterator* &other) = 0;
        ListIterator*& operator ++ () = 0;
        ListIterator*& operator -- () = 0;
        T operator * () = 0;
};

#endif
