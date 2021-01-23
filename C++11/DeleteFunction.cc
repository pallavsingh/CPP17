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

namespace Arnav1 {
    class A {
      public :
        template <typename T>
        void funcPointer(T * ptr) { cout << " Inside Class A:: funcPointer(T * ptr) : " << endl; }
    };
    
    // Template Specialization must be written in Namespace scope, not in Class Scope
    // C++14 Checks the Accessbilty of Function , Before Checking Delete status.

    template <>
    void A::funcPointer<void>(void * ptr) = delete; // { cout << " Inside Class A:: funcPointer(void * ptr) : " << endl; }
    
    template <>
    void A::funcPointer<char>(char * ptr) = delete; 
    
    template <>
    void A::funcPointer<const void>(const void * ptr) = delete; 
    
    template <>
    void A::funcPointer<const char>(const char * ptr) = delete;

}

namespace Arnav2{
   void func1(int param) { cout << "Calling func1(int param) "<< endl ; }
   void func1(char param)   = delete; // { cout << "Calling func1(int param) "<< endl ; }
   void func1(bool param)   = delete; // { cout << "Calling func1(int param) "<< endl ; }
   void func1(double param) = delete; // { cout << "Calling func1(int param) "<< endl ; }
}
  
int main(int argc, char * argv[]) {
  using namespace Arnav1;
  using namespace Arnav2;

  func1(100);
  // func1('c');   -- It will give Compile Time Error
  // func1(false); -- It wil give Compile Time Error

  return 0;
}

