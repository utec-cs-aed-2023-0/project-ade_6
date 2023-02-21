#ifndef PROJECT_H
#define PROJECT_H

#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

#include "avl.h"
#include "Block.h"
#include "block_chain.h"


class project
{
  private:
    Blockchain bloching;
    int selector;

  public:
  void execute();

  private:
    void insertitionblock();
    void printdata();
    void proofofwork();
    void repairblockchain();
    void exportation();
};

void project::execute()
{
  do
  {
    // Imprimir el menu principal
    std::cout << "\n\n     BLOCKCHAIN PROJECT: Main Menu  \n\n";
    std::cout << "  1. Ingresar nuevo bloque       " << '\n';
    std::cout << "  2. Imprimir data de BlockChain " << '\n';
    std::cout << "  3. Ejecutar Prueba de Trabajo  " << '\n';
    std::cout << "  4. Reparar Blockchain          " << '\n';
    std::cout << "  5. Exportar Bloackchain        " << '\n';
    std::cout << "  6. Cerrar proyecto             " << '\n';

    // Elegir una opcion disponible del menu
    std::cout << "\n     Ingrese un numero del menu: ";
    std::cin >> selector; 

    // Ejecutar la opcion elegida
    switch(selector)
    {
      case 1:
          insertitionblock();
        break;
      case 2:
        printdata();
        break;
      case 3:
        proofofwork();
        break;
      case 4:
        repairblockchain();
        break;
      case 5:
          exportation();
        break;
      case 6:
        std::cout << '\n' << "FIN DEL PROYECTO" << '\n' << "Adios" << '\n';
        break;
      default:
        std::cout << '\n' << "El valor ingresado NO es VALIDO. Ingrese denuevo." << '\n';
        break;
    }
  } while(selector != 6);
}

void project::insertitionblock()
{
    AVLTree<int> *avl = new AVLTree<int>();
    int cantidad;
    time_t dataTime;
    std::string emisor, receptor;
    std::cout << '\n' << "INGRESANDO UN NUEVO BLOQUE" << '\n';
    std::cout << '\n' << " - Ingrese Emisor: ";
    std::cin >> emisor;
    std::cout << " - Ingrese Receptor: ";
    std::cin >> receptor;
    std::cout << " - Ingrese cantidad de BitCoins a enviar: ";
    std::cin >> cantidad;
    std::cout << '\n';
    avl->insert(cantidad);
    transaction *data = new transaction(cantidad, emisor, receptor, time(&dataTime));
    bloching.add(data);
    std::cout << '\n' << "El bloque ha sido creado e insertado" << '\n';
}

void project::printdata()
{
    bloching.print();
}

void project::proofofwork()
{
  int block;
  std::cout << '\n' << "Elija un bloque: ";
  std::cin >> block;
    bloching.proofwork(block);
}

void project::repairblockchain()
{
  std::cout << '\n' << "Reparando Blockchain..." << '\n' << '\n';
    bloching.fix_all();
  std::cout << '\n' << "Blockchain Reparada" << '\n';
}

void project::exportation()
{
  std::string file;
  std::cout << '\n' << "Ingrese nombre del archivo: ";
  std::cin >> file;
  file = file + ".txt";
    bloching.import(file);
}

#endif