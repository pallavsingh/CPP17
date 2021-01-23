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
#include <unordered_map>

// Boost Library Hearders
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

namespace Arnav1 {
   class Polynomial {
      public :
        using RootsType = vector<double>;
       
         RootsType roots() const {
            lock_guard<mutex> guard(lock);
            
            if ( !rootsAreValid) {
               cout <<" Inside roots() and !rootsAreValid "<< endl;
               rootsAreValid = true;
            }

            cout <<" Inside roots() and rootsAreValid "<< endl;
            return rootVals;
         }

         // for single vaiable or memeory location requiring synchromization using atomic is Adequate
         // But once you have two or more variable/memory location that require manuplation of a unit
         // you should reach for a Mutex.

         double funcCounter() const noexcept {
              ++callcount;
         }

      private :
         mutable bool rootsAreValid { false };
         mutable RootType rootVals{ };

         // Why we have lock as mutable but not const.
         // Here both mutex and atmoic variables are movable object.
         mutable mutex lock;

         // Use atomic when ordering of threads of not imp.
         // but we have to gaurantee only thread change value 
         // of variable at given time 
         mutable atomic<unsigned> callcount{0};
   };

}

int main(int argc, char * argv[]) {
  using namespace Arnav1;
  Polynomial p;
  // Here both the threads would try to write and read on same memeory location 
  // without any Synchronization. It has Data Race leading to Undefined Behaviour.

  // Here funtion roots() is declared const is not ThreadSafe;

  // Threads - 1                  // Threads - 2
  auto rootOfP = p.roots();       auto valsGivingZero = p.roots(); 

  return 0;
}

