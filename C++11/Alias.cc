// C++14 Hearders
#include <iostream>
#include <memory>
#include <atomic>
#include <mutex>
#include <initializer_list>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <list>
#include <string>
#include <unordered_map>

// Boost Library Hearders
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

// Alais decleartion may be Templatized while typedef's cannot.

// C++98 
typedef unique_ptr<unordered_map<string, string> > UPtrMapSS1;
typedef void (*FP1)(int, const string &);

// C++11 Alias creation
using UPtrMapSS2 = unique_ptr<unordered_map<string, string> >;
using FP2        = void (*)(int, const string &);

//////////////////////////////////////////////////////////////////

template <typename T>
class MyAlloc{};

template<typename T>
using MyAllocList1 = list<T, MyAlloc<T> >;

template<typename T>
class A1{
   private :
     MyAllocList1<T> list;
};

////////////////////////////////////////////////////////////////

template <typename T>
struct MyAllocList2 {
       typedef list<T, MyAlloc<T> > type;
};

class Wine{};

template < >
struct MyAllocList2<Wine> {
   private :
     enum class WineType{ White, Red, Rose};
     WineType type;
};

template<typename T>
class A2{
   private :
     typename MyAllocList2<T>::type list;
};

int main(int argc, char * argv[]) {

   //A2<int>  obj1;
    A2<Wine> obj2;

  return 0;
}

