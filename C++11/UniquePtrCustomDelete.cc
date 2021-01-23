// C++14 Hearders
#include <iostream>
#include <fstream>
#include <memory>
#include <atomic>
#include <mutex>
#include <initializer_list>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <iterator>
#include <unordered_map>

// Boost Library Hearders
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

struct Foo {
    Foo() { std::cout << "Foo...\n"; }
    ~Foo() { std::cout << "~Foo...\n"; }
};
 
struct D {
    void operator() (Foo* p) {
        std::cout << "Calling delete for Foo object... \n";
        delete p;
    }
};
 
//////////////////////////////////////////////////////////
void closer_func(FILE* f) { 
     fclose(f); 
     std::cout << "Calling delete for closer_func ... \n";
}
 
struct CloserStruct {
    void operator()(FILE* f) { 
         fclose(f); 
         std::cout << "Calling delete for CloserStruct ... \n";
    }
};

/////////////////////////////////////////////////////////

int main() {
    std::cout << "Creating new Foo...\n";
    std::unique_ptr<Foo, D> up(new Foo(), D());  // up owns the Foo pointer (deleter D)
 
    std::cout << "Replace owned Foo with a new Foo...\n";
    up.reset(new Foo());  // calls deleter for the old one
 
    std::cout << "Release and delete the owned Foo...\n";
    up.reset(nullptr);      

    std::unique_ptr<FILE, void(*)(FILE*)> log_func(fopen("file.log", "r"), closer_func);
    std::unique_ptr<FILE, CloserStruct>   log_struct(fopen("file.log", "r"));
 
    auto closer_lambda = [](FILE* f) { fclose(f); };
    std::unique_ptr<FILE, decltype(closer_lambda)> log_lambda( fopen("file.log", "r"), closer_lambda);

    return 0;
}
