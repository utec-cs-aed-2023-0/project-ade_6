#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <list>
#include <string>

const unsigned ALPHA_SIZE = 26;

// template <typename TV>
class Trie
{
  public:
    Trie() {std::cout << "Trie Generado" << std::endl;};
    virtual ~Trie() {std::cout << "Trie Eliminado" << std::endl;};
    virtual void insert(std::string key) = 0;
    virtual bool search(std::string key) = 0;
    virtual void remove(std::string key) = 0;
    virtual std::list<std::string> start_with(std::string preffix) = 0;
    virtual std::string toString(std::string sep=" ") = 0;
};

#endif