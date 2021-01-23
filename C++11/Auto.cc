// C++14 Hearders
#include <iostream>
#include <memory>
#include <atomic>
#include <initializer_list>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>
#include <unordered_map>

// Boost Library Hearders
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

int main(int argc, char * argv[]) {
   int  x1 = 100;
   // auto x2;  // Auto Variable must be intialized Always
   auto x3 = 0;

   // C++11 Style
   auto anonymousfunc1 = [](const unique_ptr<int> & p1, const unique_ptr<int> & p2) {
                              return *p1 < *p2;
                         };

   function<bool(const unique_ptr<int> &, const unique_ptr<int> &)>
   anonymousfunc2 = [](const unique_ptr<int> & p1, const unique_ptr<int> & p2) {
                              return *p1 < *p2;
                         };

   /* Auto : it has same type returned by closure 
             it holds the closure
             it uses only memeory closure required 
      
      Functional :
             it hold the closure and has fixe size for any given signature.
             As size might not be adequate to hold the closure, its being asked.
             it will lead to allocate Heap Memeory to store the closure.

             it restrict inlining and yield function call leads to slower than 
             auto declared object. 
    */

   // C++14 Style
   auto anonymousfunc3 = [](const auto & p1, const auto & p2) {
                              return *p1 < *p2;
                         };

   // For 64 Bit Windows, unsigned in 32 bit while vector<int>::size_type is 64 bit.
   vector <int> vec;
   unsigned sz1 = vec.size();
   auto     sz2 = vec.size();

   cout <<"sizeof(sz1) : " << sz1 << endl;
   cout <<"sizeof(sz2) : " << sz2 << endl;
   
   // Type MisMatch leads to creation of Tmp Object.
   // Here key for unordered_map is std::pair<const string, int>  but the type declared for p
   // is std::pair<string, int> , Hence compiler will create a temprary object of type that p 
   // wants , then bind refrence from p to that temprary object. At End of loop temprary object 
   //  will be destroyed

   unordered_map<string, int> inmemeoryDB;
   for (const std::pair<string, int> & p :inmemeoryDB){
   }

   for (const auto & p :inmemeoryDB){
   }

   return 0;
}

