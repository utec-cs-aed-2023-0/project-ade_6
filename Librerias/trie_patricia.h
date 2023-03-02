#ifndef TRIE_PATRICIA_H
#define TRIE_PATRICIA_H

#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include "circular.h"

const unsigned ALPHA_SIZE = 26;

template <typename TV>
class TriePatricia
{
  private:
    struct TrieNode;
    TrieNode* root;
  public:
    TriePatricia();
    ~TriePatricia() {std::cout << "\nTrie Patricia Eliminado";};
    void insert(std::string key, TV value);
    bool search(std::string key);
    TV get_value(std::string key);
    CircularList<TV> return_values(std::string preffix);
    CircularList<std::string> start_with(std::string preffix);
    void remove(std::string key);
    std::string toString();
  private:
    TrieNode* insert(std::string key, TV value, TrieNode* node)
    {
      if(node == nullptr)
      {
        node = new TrieNode(key,value);
        node->endWord = true;
        return node;
      }
      std::string pref = "";
      while(pref.size() < key.size() && pref.size() < node->preffix.size())
      {
        if (key[pref.size()] == node->preffix[pref.size()])
          pref += key[pref.size()];
        else
          break;
      }
      
      if (pref.size() < key.size() && pref.size() < node->preffix.size())
      {
        std::string suff_node = node->preffix.substr(pref.size());
        int pos_node = suff_node[0] - 'a';
        std::string suff_key  = key.substr(pref.size());
        int pos_key  = suff_key[0] - 'a';
        TrieNode* father = new TrieNode(pref);
        father->children[pos_node] = node;
        father->children[pos_node]->preffix = suff_node;
        father->children[pos_key] = new TrieNode(suff_key, value);
        father->children[pos_key]->endWord = true;
        return father;
      }
      else if (pref.size() < key.size() && pref.size() == node->preffix.size())
      {
        std::string suff_key  = key.substr(pref.size());
        int pos_key = suff_key[0] - 'a';
        node->children[pos_key] = insert(suff_key, value, node->children[pos_key]);
      }
      else if(pref.size() == key.size() && pref.size() < node->preffix.size())
      {
        std::string suff_node = node->preffix.substr(pref.size());
        int pos_node = suff_node[0] - 'a';
        TrieNode* father = new TrieNode(pref,value);
        father->endWord = true;
        father->children[pos_node] = node;
        father->children[pos_node]->preffix = suff_node;
        return father;
      }
      else
      {
        delete node->value;
        node->value = new TV(value);
        node->endWord = true;
      }
      return node;
    };
    
    TrieNode* search(std::string &key, TrieNode* &node)
    {
      if (node == nullptr)
        return nullptr;
    
      if (key.size() < node->preffix.size())
        return nullptr;
    
      if (key.size() == node->preffix.size())
      {
        if(key == node->preffix)
          if(node->endWord)
            return node;
        return nullptr;
      }
    
      std::string suff_key = key.substr(node->preffix.size());
      int pos_key = suff_key[0] - 'a';
      return search(suff_key, node->children[pos_key]);
    };
    
    TrieNode* start_with(std::string &preffix, TrieNode* &node, std::string& pref)
    {
      if (node == nullptr)
        return nullptr;
    
      if (preffix.size() <= node->preffix.size())
      {
        for(int i=0; i < preffix.size(); i++)
        if(node->preffix[i] != preffix[i])
          return nullptr;
        return node;
      }
    
      pref += node->preffix;
      std::string suff_preffix = preffix.substr(node->preffix.size());
      int pos_preffix = suff_preffix[0] - 'a';
      return start_with(suff_preffix, node->children[pos_preffix], pref);
    };

    TrieNode* remove(std::string key, TrieNode* node)
    {
      if(node == nullptr)
        return nullptr;
      
      if (key.size() <= node->preffix.size())
      {
        if (key == node->preffix)
        {
          if(node->endWord && node->value != nullptr)
          {
            delete node->value;
            node->value = nullptr;
          }
          node->endWord = false;
          if (node->is_empty())
          {
            delete node;
            node = nullptr;
          }
        }
        return node;
      }
      
      std::string suff_key = key.substr(node->preffix.size());
      if(node->preffix + suff_key == key)
      {
        int pos = suff_key[0] - 'a';
        node->children[pos] = remove(suff_key,node->children[pos]);
        if(node->endWord == false)
        {
          if(node->is_empty())
          {
            delete node;
            node = nullptr;
          }
        }
      }
      return node;
    }
    
    void add_values(CircularList<TV>* the_list, TrieNode* &node)
    {
        if(node != nullptr)
        {
            if(node->endWord)
                the_list->push_back(*(node->value));
            for (unsigned int i=0; i < ALPHA_SIZE; i++)
                add_values(the_list, node->children[i]);
        }
    };

    void add_results(CircularList<std::string>* the_list, TrieNode* &node, std::string pref)
    {
        if(node != nullptr)
        {
            pref = pref + node->preffix;
            if(node->endWord)
                the_list->push_back(pref);
            for (unsigned int i=0; i < ALPHA_SIZE; i++)
                add_results(the_list, node->children[i], pref);
        }
    };

    std::string toString(TrieNode* temp, std::string pref)
    {
        pref = pref + temp->preffix;
        std::string result = "";
        if(temp->endWord)
        {
            std::stringstream word;
            word << '\n' << pref << ": " << *(temp->value);
            result = word.str();
        }
        for (unsigned int i=0; i < ALPHA_SIZE; i++)
        {
            if(temp->children[i] != nullptr)
                result = result + toString(temp->children[i], pref);
        }
        return result;
    };
};

template <typename TV>
struct TriePatricia<TV>::TrieNode
{          
  TrieNode **children;           
  std::string preffix;
  bool endWord;
  TV* value;

  TrieNode(std::string _preffix, TV _value): preffix(_preffix), endWord(false)
  {
    value = new TV(_value);
    children = new TrieNode*[ALPHA_SIZE];
    for(int i=0; i < ALPHA_SIZE; i++)
      children[i] = nullptr;
  }

  TrieNode(std::string _preffix): preffix(_preffix), endWord(false), value(nullptr)
  {
    children = new TrieNode*[ALPHA_SIZE];
    for(int i=0; i < ALPHA_SIZE; i++)
      children[i] = nullptr;
  };

  bool is_empty()
  {
    for (int i=0; i < ALPHA_SIZE; i++)
      if (children[i] != nullptr)
        return false;
    return true;
  };
};

template <typename TV>
TriePatricia<TV>::TriePatricia(): root(nullptr)
{
  std::cout << "\nTrie Patricia Generado";
}

template <typename TV>
void TriePatricia<TV>::insert(std::string key, TV value)
{
  root = insert(key,value,root);
}

template <typename TV>
bool TriePatricia<TV>::search(std::string key)
{
  if (search(key,root) == nullptr)
    return false;
  return true;
}

template <typename TV>
TV TriePatricia<TV>::get_value(std::string key)
{
  TrieNode* result = search(key,root);
  if(result == nullptr)
    throw("The key is invalid.");
  return *(result->value);
}

template <typename TV>
CircularList<TV> TriePatricia<TV>::return_values(std::string preffix)
{
  CircularList<TV> result;
  std::string pref = "";
  TrieNode* finded = start_with(preffix, root, pref);
  add_values(&result, finded);
  return result;
};

template <typename TV>
CircularList<std::string> TriePatricia<TV>::start_with(std::string preffix)
{
  CircularList<std::string> result;
  std::string pref = "";
  TrieNode* finded = start_with(preffix, root, pref);
  add_results(&result, finded, pref);
  return result;
}

template <typename TV>
void TriePatricia<TV>::remove(std::string key)
{
  root = remove(key,root);
}

template <typename TV>
std::string TriePatricia<TV>::toString()
{
  if(root == nullptr)
    return "";
  return toString(root,"");
}
#endif