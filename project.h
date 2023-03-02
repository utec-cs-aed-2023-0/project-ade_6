#ifndef PROJECT_H
#define PROJECT_H

#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
#include <cctype>

#include "Librerias/AVL/avl.h"
#include "Librerias/Tries/trieBeta.h"

#include "Librerias/Btree/btree.h"

#include "Block.h"
#include "block_chain.h"


class project
{
  private:
    Blockchain bloching;
    Btree btree;
    AVLTree avlTree;

    int selector;
    /*
     * Implementar aqui el  AVL ,BTREE, TRUI¡¡
     * */

  public:
    void execute();

  private:
    void insertitionblock();
    void printdata();
    void search();
    void proofofwork();
    void repairblockchain();
    void exportation();

    void MaxValue();
    void MinValue();
    void Range();
    void Search();
    void Start();
    void Contain();

};

void project::execute()
{
  do
  {
    // Imprimir el menu principal
    std::cout << "\n\n     BLOCKCHAIN PROJECT: Main Menu  \n\n";
    std::cout << "  1. Ingresar nuevo bloque       " << '\n';
    std::cout << "  2. Imprimir data de BlockChain " << '\n';
    std::cout << "  3. Metodo de Busqueda          " << '\n';
    std::cout << "  4. Ejecutar Prueba de Trabajo  " << '\n';
    std::cout << "  5. Reparar Blockchain          " << '\n';
    std::cout << "  6. Exportar Bloackchain        " << '\n';
    std::cout << "  7. Cerrar proyecto             " << '\n';

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
        search();
        break;
      case 4:
        proofofwork();
        break;
      case 5:
        repairblockchain();
        break;
      case 6:
        exportation();
        break;
      case 7:
        std::cout << '\n' << "FIN DEL PROYECTO" << '\n' << "Adios" << '\n';
        break;
      default:
        std::cout << '\n' << "El valor ingresado NO es VALIDO. Ingrese denuevo." << '\n';
        break;
    }
  } while(selector != 7);
}

void project::insertitionblock()
{
   BTree<int>* btree = new BTree<int>(3);
   trie T;

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
    btree->insert(cantidad);
    std::cout << '\n';

    for (int i = 0; i < emisor.length(); i++) emisor[i] = tolower(emisor[i]);
    for (int i = 0; i < receptor.length(); i++) receptor[i] = tolower(receptor[i]);

    T.insert(emisor);
    T.insert(receptor);



    printf("%d\n", T.exact_match("hosmer"));
    T.words_with_prefix("h");

    transaction *data = new transaction(cantidad, emisor, receptor, time(&dataTime));
    bloching.add(data);
    std::cout << '\n' << "El bloque ha sido creado e insertado" << '\n';
}

void project::printdata()
{
    bloching.print();
}

void project::search()
{
    do
    {
        // Imprimir el menu principal
        std::cout << "\n\n     BLOCKCHAIN PROJECT: Busqueda  \n\n";
        std::cout << "  1. Max value        " << '\n';
        std::cout << "  2. Min value        " << '\n';
        std::cout << "  3. Range            " << '\n';
        std::cout << "  4. Por la inical    " << '\n';
        std::cout << "  5. Nombre           " << '\n';
        std::cout << "  6. Contenido        " << '\n';
        std::cout << "  7. Exit             " << '\n';

        // Elegir una opcion disponible del menu
        std::cout << "\n     Ingrese un numero del menu: ";
        std::cin >> selector;

        // Ejecutar la opcion elegida
        switch(selector)
        {
            case 1:
                MaxValue();
                break;
            case 2:
                MinValue();
                break;
            case 3:
                Range();
                break;
            case 4:
                Start();
                break;
            case 5:
                Search();
                break;
            case 6:
                Contain();
                break;
            case 7:
                execute();
                break;
        }
    } while(selector != 7);

}
/*----------------------------------------------------------------*/
void project::MaxValue() {
    auto btree =  BTree<int>(3);
    cout<<"Maximo monto: "<<btree.maxKey()<<endl;

}
void project::MinValue() {
    auto btree =  BTree<int>(3);
    cout<<"Minimo monto: "<<btree.minKey()<<endl;
}
void project::Range() {
    auto btree = new BTree<int>(3);
    int num;
    cout<<"Ponga el numero: " <<endl;
    cin>>num;
    cout << btree->PrintrangeSearch(num);
}
void project::Search() {
    trie T;
    string name;
    cout << "Pongan nomrbe del la persona:"<<endl;
    cin>>name;
    auto result =T.exact_match(name);
    printf("%d\n", result);
    if (result==0){
        cout << "No se encuentro el nombre"<<endl;
    }
    else cout <<"Se a encontrado el usuario"<<endl;
}
void project::Start() {
    trie T;
    string letter;
    cout << "Pongan Letra :"<<endl;
    cin>>letter;
    T.words_with_prefix(letter);
}
void project::Contain() {}
/*----------------------------------------------------------------*/
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