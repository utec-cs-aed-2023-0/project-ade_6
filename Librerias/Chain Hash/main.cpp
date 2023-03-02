#include <iostream>
#include "ChainHash.h"

using namespace std;

int main() {
    ChainHash<std::string,std::string> hash;
    hash.set("heider", "sanchez");
    hash.set("maria", "vega");
    hash.set("paolo", "vasquez");
    hash.set("heider", "gonzales");
    
    string letter = "0";
    for(int i = 0; i < 26; i++) {
        letter[0] = 'a'+i;
        hash.set(letter, letter);
    }
    
    hash.remove("maria");
    hash.remove("paolo");
    
    hash["heider"] = "Sanchez";
    
    
    int n = hash.bucket_count();
    std::cout << "Capacidad del hashtable " << hash.entry_count() << std::endl;
    std::cout << "Capacidad del hashtable " << n << std::endl;

    for(int i = 0; i < n; i++) {
        std::cout << "Bucket #" << i << " tiene " << hash.bucket_size(i) << std::endl;
        for(auto it = hash.begin(i); it != hash.end(i); ++it)
            std::cout << "\t [" << (*it).key << ":" << (*it).value << "]" << std::endl;
        std::cout << std::endl;
    }
    

    
    try {   
        std::cout << hash["pancracio"] << std::endl;
    } catch (const char* message) {
        cerr << message << endl;
    }
    
    std::cout << "RAAAAAAAAAAAAAAAAA" << std::endl;
    return 0;

    // Investigar sobre try catch
}