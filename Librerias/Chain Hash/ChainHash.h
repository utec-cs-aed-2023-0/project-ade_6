#ifndef CHAIN_HASH_H
#define CHAIN_HASH_H

#include <iostream>
#include "forward_list.h"

using namespace std;

const int maxColision = 3;
const double maxFillFactor = 0.5;

template<typename TK, typename TV>
class ChainHash {
    private:
        template<typename UK, typename UV>
        struct Entry {
            UK key;
            UV value;
            size_t hashcode;
            Entry(UK key, UV value, size_t hashcode): key(key), value(value), hashcode(hashcode) {};
        };

        forward_list<Entry<TK,TV>>* array;
        int capacity;                                // tamanio del array
        int size;                                    // cantidad de elementos alamacenados

    public:
        ChainHash();
        ~ChainHash();
        void set(TK key, TV value);
        TV get(TK key);
        void remove(TK key);
        int bucket_count();
        int bucket_size(int pos);
        int entry_count() {return size;};

        TV& operator [] (TK key) {
            std::size_t hashcode = getHashCode(key);
            int index = hashcode % capacity;
            auto iter = array[index].begin();
            // Iteramos para buscar la key
            for(; iter != array[index].end(); ++iter) {
                if ((*iter).key == key && (*iter).hashcode == hashcode) {break;}
            }
   
            if(iter == array[index].end())
                throw("Llave invalida");

            return (*iter).value;
        };

        typename forward_list<Entry<TK,TV>>::iterator begin(int pos) {
            if (pos < 0 || pos >= capacity)
                throw("Posicion no valida");
            return array[pos].begin();
        };

        typename forward_list<Entry<TK,TV>>::iterator end(int pos)  {
            if (pos < 0 || pos >= capacity)
                throw("Posicion no valida");
            auto iter = array[pos].end();
            return iter;
        };

        //TODO +1 en el parcial: implementar el operador corchete [ ], read/write

    private:
        double fillFactor();
        size_t getHashCode(TK key);
        void rehashing();
};

template <typename TK, typename TV>
ChainHash<TK,TV>::ChainHash(): capacity(10), size(0) {
    array = new forward_list<Entry<TK,TV>> [capacity];
}

template <typename TK, typename TV>
ChainHash<TK,TV>::~ChainHash() {
    delete[] array;
}

template <typename TK, typename TV>
void ChainHash<TK,TV>::set(TK key, TV value) {
    if (fillFactor() >= maxFillFactor)
        rehashing();
    
    std::size_t hashcode = getHashCode(key);
    
    int index = hashcode % capacity;
    
    auto iter = array[index].begin();
    for(; iter != array[index].end(); ++iter) {
        if((*iter).key == key && (*iter).hashcode == hashcode)
            break;
    } 
    if (iter == array[index].end()) {
        array[index].push_front(Entry(key,value,hashcode));
        size++;
    } else {
        (*iter).value = value;
    }
}

template <typename TK, typename TV>
TV ChainHash<TK,TV>::get(TK key) {
    std::size_t hashcode = getHashCode(key);
    int index = hashcode % capacity;

    // Iteramos para buscar la key
    auto iter = array[index].begin();
    for(; iter != array[index].end(); ++iter) {
        if ((*iter).key == key && (*iter).hashcode == hashcode) {break;}
    }
    if(iter == array[index].end())
        throw("Llave invalida");
    return (*iter).value;
}

template <typename TK, typename TV>
void ChainHash<TK,TV>::remove(TK key) {
    std::size_t hashcode = getHashCode(key);
    int index = hashcode % capacity;

    // Iteramos para buscar la key
    if(!array[index].is_empty()) {
        auto iter = array[index].begin();
        if((*iter).key == key && (*iter).hashcode == hashcode) {
            array[index].pop_front();
            size--;
        } else {
            auto iter2 = iter;
            ++iter2;
            for(; iter2 != array[index].end(); ++iter2) {
                if ((*iter2).key == key && (*iter2).hashcode == hashcode){
                    iter.remove_after();
                    array[index].menos_uno();
                    size--;
                    break;
                }
                ++iter;
            }
        }
    }
}

template <typename TK, typename TV>
int ChainHash<TK,TV>::bucket_count() {
    return capacity;
}

template <typename TK, typename TV>
int ChainHash<TK,TV>::bucket_size(int pos) {
    if (pos < 0 || pos >= capacity)
        throw("Posicion no valida");
    return array[pos].size();
}

template <typename TK, typename TV>
double ChainHash<TK,TV>::fillFactor() {
    return double(size) / double(capacity * maxColision);
}

template <typename TK, typename TV>
size_t ChainHash<TK,TV>::getHashCode(TK key) {
    std::hash<TK> ptr_hash;
    return ptr_hash(key);
}

template <typename TK, typename TV>
void ChainHash<TK,TV>::rehashing() {
    int newCapacity = this->capacity + 6;
    forward_list<Entry<TK,TV>>* arrayTemp = new forward_list<Entry<TK,TV>> [newCapacity];
    int newIndex;

    for(int pos=0; pos < this->capacity; pos++) {
        for(auto it = array[pos].begin(); it != array[pos].end(); ++it) {
            newIndex = (*it).hashcode % newCapacity;
            arrayTemp[newIndex].push_front(*it);
        }
    }

    delete[] this->array;
    this->array = arrayTemp;
    this->capacity = newCapacity;
}

#endif