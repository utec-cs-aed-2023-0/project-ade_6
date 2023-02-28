#ifndef BLOCK_CHAIN_H
#define BLOCK_CHAIN_H

#include <stdio.h>
#include <stdlib.h>

#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "Block.h"
#include "Librerias/Listas/list.h"

using namespace std;

class Blockchain
{
  private:
    list<Block> chain;

  public:
    // Constructor
    Blockchain() {};

    // Public Functions
    void add(transaction *data);
    void print();
    void import(string name);
    void proofwork(int id);
    void fix_all();
};

void Blockchain::add(transaction *data)
{
  Block* temp = new Block(data);
  string prev_hash = "";
  if (!chain.is_empty()) 
    prev_hash = chain.back()->get_hash();
  temp->set_id(chain.size()+1, prev_hash);
  temp->mine();
  chain.push(*temp);
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

void Blockchain::proofwork(int id)
{
  int cont = 1;
  list<Block>::iterator it;
  string hash_tmp;
  bool val1 = false;
  bool val2 = false;
  for (it = chain.begin(); it != chain.end(); ++it)
  {
      Block *currentBlock = *it;
      if (val2 == true) {
          currentBlock->set_hash_prev(hash_tmp);
          currentBlock->mine();
      }
      if (val1 == true) {
          currentBlock->set_hash_prev(hash_tmp);
      }
      if (cont == id) {
          string new_name;
          cout << endl << "Ingrese nombre para el nuevo receptor: ";
          cin >> new_name;
          currentBlock->modify(new_name);
          cout << endl << "Desea arreglar el blockChain? (0 o 1): ";
          bool fix;
          cin >> fix;
          if (fix == false)
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
  string hash_tmp;
  for (auto it = chain.begin(); it != chain.end(); ++it)
  {
      Block *currentBlock = *it;
      if (currentBlock->get_validation() == false) {
          currentBlock->set_hash_prev(hash_tmp);
          currentBlock->mine();
      }
      hash_tmp = currentBlock->get_hash();
  }
}

#endif