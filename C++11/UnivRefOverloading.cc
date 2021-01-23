// C++14 Hearders
#include <iostream>
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

////////////////////////////////////////////////////////////////////

void process(const string & param)  { cout << "Calling process(const string & param): " << endl; }
void process(string && param)  { cout << "Calling process(string && param): " << endl; }


void func(const string & s)  {
     cout << "Calling func(const string & s): " << endl; 
     process(s);
}

void func(int idx)  {
     cout << "Calling func(int idx): " << endl; 
}

template<typename T>
void func(T && s) {
     cout << "Calling func(T && s): " << endl; 
     process(forward<T>(s));
}

////////////////////////////////////////////////////////////////////

class A {
   public :
     template<typename T>
     explicit A(T && n) : name(forward<T>(n)) { cout << "Calling explicit A(T && n) : name(forward<T>(n)) : " << endl; }

     // Prefer Normal Function : if Equal match between Template generated function and 
     //                          Normal Function.
     A(const A & rhs) : name(rhs.name) { cout << "Calling A(const A & rhs) " << endl; }
     A(A && rhs) : name(rhs.name) { cout << "Calling  A(A && rhs) : " << endl; }

     explicit A(int idx) { cout << "Calling explicit A(int idx) " << endl; }

   private :
     string name;
};


int main(int argc, char * argv[]) {
    const string s1("pallav");

    func(s1);
    func(move(s1));
    func(string("pallav singh"));
    func("pallav singh");

    func(22);

    // short i = 0;
    // func(i); -- it will call Overloaded func for Universal reference.

    const  A obj("pallav");
    auto objcopied(obj);

    A obj1("pallav");
    auto objcopied1(obj1);

    return 0;
}

