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
#include <string.h>
#include <algorithm>
#include <iterator>
#include <unordered_map>
// Boost Library Hearders
#include <boost/type_index.hpp>

using  namespace std;
using  boost::typeindex::type_id_with_cvr;

// UserDefined Tag InheritanceTree to Resolving Function Overloading at CompileTime
class A { };
class B { };

class Overloading_Tag_Generic{ };
class Overloading_Tag_A{ };
class Overloading_Tag_B{ };

template<typename T>
struct  trait {
  typedef Overloading_Tag_Generic  create;
};

template< >
struct trait< A > {
  typedef Overloading_Tag_A  create;
};

template< >
struct trait< B > {
  typedef Overloading_Tag_B  create;
};

void  func(const Overloading_Tag_Generic arg) { 
  cout << "Calling func(const Overloading_Tag_Generic arg) : " << endl; 
}

void  func(const Overloading_Tag_A arg) { 
  cout << "Calling func(const Overloading_Tag_A arg) : " << endl; 
}

void  func(const Overloading_Tag_B arg) { 
  cout << "Calling func(const Overloading_Tag_B arg) : " << endl; 
}

int main(int argc, char * argv[]) {
    func(typename trait<A>::create{ });
    func(typename trait<B>::create{ });
    func(typename trait<int>::create{ });

    return 0;
};

