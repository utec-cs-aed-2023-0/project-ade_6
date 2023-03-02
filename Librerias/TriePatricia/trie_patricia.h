#ifndef TRIE_PATRICIA_H
#define TRIE_PATRICIA_H

#include <iostream>
#include "trie.h"

// template <typename T>
class TriePatricia : public Trie
{
  private:
    struct TrieNode;
    TrieNode* root;
  public:
    TriePatricia();
    ~TriePatricia() {};
    void insert(std::string key);
    bool search(std::string key);
    std::list<std::string> start_with(std::string preffix);
    void remove(std::string key);
    std::string toString(std::string sep);
  private:
    TrieNode* insert(std::string key, TrieNode* node);
    TrieNode* search(std::string &key, TrieNode* &node);
    TrieNode* start_with(std::string &preffix, TrieNode* &node, std::string& pref);
    void add_results(std::list<std::string>* the_list, TrieNode* &node, std::string pref);
    TrieNode* remove(std::string key, TrieNode* node);
    std::string toString(std::string sep, TrieNode* temp, std::string pref);
};

struct TriePatricia::TrieNode
{          
  TrieNode **children;           
  std::string preffix;
  bool endWord;

  TrieNode(std::string _preffix): preffix(_preffix), endWord(false)
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

TriePatricia::TriePatricia(): root(nullptr)
{
  std::cout << "Trie Patricia Generado" << std::endl;
};

void TriePatricia::insert(std::string key)
{
  root = insert(key,root);
}

TriePatricia::TrieNode* TriePatricia::insert(std::string key, TrieNode* node)
{
  if(node == nullptr)
  {
    node = new TrieNode(key);
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
    father->children[pos_key] = new TrieNode(suff_key);
    father->children[pos_key]->endWord = true;
    return father;
  }
  else if (pref.size() < key.size() && pref.size() == node->preffix.size())
  {
    std::string suff_key  = key.substr(pref.size());
    int pos_key = suff_key[0] - 'a';
    node->children[pos_key] = insert(suff_key,node->children[pos_key]);
  }
  else if(pref.size() == key.size() && pref.size() < node->preffix.size())
  {
    std::string suff_node = node->preffix.substr(pref.size());
    int pos_node = suff_node[0] - 'a';
    TrieNode* father = new TrieNode(pref);
    father->endWord = true;
    father->children[pos_node] = node;
    father->children[pos_node]->preffix = suff_node;
    return father;
  }
  else
  {
    node->endWord = true;
  }
  return node;
}

bool TriePatricia::search(std::string key)
{
  if (search(key,root) == nullptr)
    return false;
  return true;
}

TriePatricia::TrieNode* TriePatricia::search(std::string &key, TrieNode* &node)
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
}

std::list<std::string> TriePatricia::start_with(std::string preffix)
{
  std::list<std::string> result;
  std::string pref = "";
  TrieNode* finded = start_with(preffix, root, pref);
  add_results(&result, finded, pref);
  return result;
}

TriePatricia::TrieNode* TriePatricia::start_with(std::string &preffix, TrieNode* &node, std::string& pref)
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
}

void TriePatricia::add_results(std::list<std::string>* the_list, TrieNode* &node, std::string pref)
{
  if(node != nullptr)
  {
    pref = pref + node->preffix;
    if(node->endWord)
      the_list->push_back(pref);
    for (unsigned int i=0; i < ALPHA_SIZE; i++)
      add_results(the_list, node->children[i], pref);
  }
}


void TriePatricia::remove(std::string key)
{
  root = remove(key,root);
}

TriePatricia::TrieNode* TriePatricia::remove(std::string key, TrieNode* node)
{
  if (key.size() <= node->preffix.size())
  {
    if (key == node->preffix)
    {
      node->endWord = false;
      if (node->is_empty())
      {
        delete node;
        node = nullptr;
      }
      return node;
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

std::string TriePatricia::toString(std::string sep)
{
  if(root == nullptr)
    return "";
  return toString(sep,root,"");
}

std::string TriePatricia::toString(std::string sep, TrieNode* temp, std::string pref)
{
  pref = pref + temp->preffix;
  std::string result = "";
  if(temp->endWord)
    result = pref + sep;
  for (unsigned int i=0; i < ALPHA_SIZE; i++)
  {
    if(temp->children[i] != nullptr)
      result = result + toString(sep, temp->children[i], pref);
  }
  return result;
}

#endif