#ifndef PROJECT_H
#define PROJECT_H

#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
#include <cctype>

#include "Librerias/AVL/avl.h"
#include "Librerias/trie_patricia.h"
#include "Librerias/btree.h"

#include "Block.h"
#include "block_chain.h"


class project
{
  private:
    Blockchain the_block_chain;
    TriePatricia<transaction*> trie_patricia;
    BTree<int>* btree;
    int selector;

  public:
    project();
    void execute();

  private:
    void insert_block();
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

project::project()
{
    btree = new BTree<int>(3);
}

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
        insert_block();
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

void project::insert_block()
{

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

    for (int i = 0; i < emisor.length(); i++)
        emisor[i] = tolower(emisor[i]);
    for (int i = 0; i < receptor.length(); i++)
        receptor[i] = tolower(receptor[i]);

    transaction *data = new transaction(cantidad, emisor, receptor, time(&dataTime));
    trie_patricia.insert(data->senderkey, data);
    btree->insert(cantidad);
    the_block_chain.add(data);
    std::cout << '\n' << "El bloque ha sido creado e insertado" << '\n';
}

void project::printdata()
{
    the_block_chain.print();
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
void project::MaxValue()
{
    cout << "Maximo monto: "<<btree->maxKey()<<endl;
}

void project::MinValue()
{
    cout<<"Minimo monto: "<< btree->minKey() << endl;
}

void project::Range()
{
    int num;
    cout<<"Ponga el numero: " <<endl;
    cin>>num;
    btree->print_range_search(num,the_block_chain.size());
}

void project::Search()
{
    string name;
    cout << "Pongan el nombre del emisor:" << endl;
    cin>>name;
    try
    {
        transaction* data = trie_patricia.get_value(name);
        data->print_data();
    }
    catch (const char* message)
    {
        std::cerr << message << std::endl;
    }
}

void project::Start()
{
    string letter;
    cout << "Pongan Letra :"<<endl;
    cin>>letter;
    CircularList<transaction*> resultados = trie_patricia.return_values(letter);
    for(auto iter = resultados.begin(); iter != resultados.end(); ++iter)
        (*iter)->print_data();
}

void project::Contain()
{
    int index = 0;
    do
    {
        cout << "\nInserte un numero: ";
        cin >> index;
    } while(index < 1 || index > the_block_chain.size());
    Block* result = the_block_chain.get_block(index-1);
    result->show_block_info(cout);
}

/*----------------------------------------------------------------*/

void project::proofofwork()
{
  int block;
  std::cout << '\n' << "Elija un bloque: ";
  std::cin >> block;
  the_block_chain.proof_of_work(block);
}

void project::repairblockchain()
{
  std::cout << '\n' << "Reparando Blockchain..." << '\n' << '\n';
  the_block_chain.fix_all();
  std::cout << '\n' << "Blockchain Reparada" << '\n';
}

void project::exportation()
{
  std::string file;
  std::cout << '\n' << "Ingrese nombre del archivo: ";
  std::cin >> file;
  file = file + ".txt";
  the_block_chain.import(file);
}

#endif