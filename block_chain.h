#ifndef BLOCK_CHAIN_H
#define BLOCK_CHAIN_H

#include <stdio.h>
#include <stdlib.h>

#include <list>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "Librerias/circular.h"
#include "Block.h"
#include "transaction.h"

using namespace std;

class Blockchain
{
  private:
    CircularList<Block*> chain;
  public:
    Blockchain() {};
    // Public Functions
    int size();
    Block* get_block(int index);
    void add(transaction *data);
    void print();
    void import(string name);
    void proof_of_work(int id);
    void fix_all();
};

int Blockchain::size()
{
    return chain.size();
}

Block* Blockchain::get_block(int index)
{
    return chain[index];
}

void Blockchain::add(transaction *data)
{
  if (data != nullptr)
  {
      auto* temp = new Block(data,1);
      string prev_hash = std::string(64,'0');
      if (!chain.is_empty())
          prev_hash = chain.back()->get_hash();
      temp->set_id(chain.size()+1, prev_hash);
      temp->mine();
      chain.push_back(temp);
  }
}

void Blockchain::print()
{
  for (auto val= chain.begin(); val != chain.end(); ++val)
    (*val)->show_block_info(cout);
}

void Blockchain::import(string name)
{
    ofstream file(name, ios::out);
    for (auto it = chain.begin(); it != chain.end(); ++it)
        (*it)->show_block_info(file);
    file.close();
}

void Blockchain::proof_of_work(int id)
{
  int cont = 1;
  string hash_tmp;
  bool val1 = false;
  bool val2 = false;
  for (auto it = chain.begin(); it != chain.end(); ++it)
  {
      Block *currentBlock = *it;
      if (val2)
      {
          currentBlock->set_hash_prev(hash_tmp);
          currentBlock->mine();
      }
      if (val1)
      {
          currentBlock->set_hash_prev(hash_tmp);
      }
      if (cont == id)
      {
          string new_name;
          cout << endl << "Ingrese nombre para el nuevo receptor: ";
          cin >> new_name;
          currentBlock->modify(new_name);
          cout << endl << "Desea arreglar el blockChain? (0 o 1): ";
          bool fix;
          cin >> fix;
          if (!fix)
              val1 = true;
          else
          {
              currentBlock->mine();
              val2 = true;
          }
      }
      hash_tmp = currentBlock->get_hash();
      cont++;
  }
}

void Blockchain::fix_all()
{
  string hash_tmp = chain.front()->get_hash_prev();
  for (auto it = chain.begin(); it != chain.end(); ++it)
  {
      if (!(*it)->get_validation())
      {
          (*it)->set_hash_prev(hash_tmp);
          (*it)->mine();
      }
      hash_tmp = (*it)->get_hash();
  }
}

#endif