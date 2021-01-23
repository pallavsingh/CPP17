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

namespace Arnav1 {
  // C++11 has const-iterator as memeber function of containers
  // Use const-iterator on non-const containers

  vector<int> values{1};
  auto iter = std::find(values.cbegin(), values.cend(), 1983);
  values.insert(iter, 1983);

  // For generic code prefer non-Member function of Conatiners
  template<typename C, typename V>
  void findAndInsert(C & container, const V & targetVal, const V & insertVal) {
       using std::cbegin;
       using std::cend;

       auto iter = std::find(cbegin(container), cend(container), targetVal);
       container.insert(iter, insertVal);
  }
}

// Here we see how static-assert work at compile time in C++
namespace Arnav2 {
   template <class T>
   void swap(T& a, T& b) {
       static_assert(std::is_copy_constructible<T>::value, "Swap requires copying");
       static_assert(std::is_nothrow_move_constructible<T>::value && std::is_nothrow_move_assignable<T>::value, "Swap may throw");
       auto c = b;
       b = a;
       a = c;
   }
    
   template <class T>
   struct data_structure {
       static_assert(std::is_default_constructible<T>::value, "Data Structure requires default-constructible elements");
   };
    
   struct no_copy {
       no_copy ( const no_copy &) = delete;
       no_copy () = default;
   };
    
   struct no_default {
       no_default () = delete;
   };
}

namespace Arnav3{

/* noexpect is part of function interface, Hence Caller may depend on it.

   noexcept is valuable for
       1. move operations
       2. swap
       3. memory deallocation functions
       4. destrcutors

  Function having noexcept is more optimizable than throw()

  move_if_no_except : it will return rvalue to arg, 
                      unless Copying is better option than Move.

  // Look for dis-assembly and see function call Optimization
*/

}

int main(int argc, char * argv[]) {
    using namespace Arnav1;
    using namespace Arnav2;
  
    int a, b;
    Arnav2::swap(a, b);
 
    no_copy nc_a, nc_b;
    Arnav2::swap(nc_a, nc_b); // 1
 
    data_structure<int> ds_ok;
    data_structure<no_default> ds_error; // 2

    return 0;
}

