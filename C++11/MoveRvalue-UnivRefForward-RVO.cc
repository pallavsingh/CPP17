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

//////////////////////////////////////////////////////////////////////////

const string getName(){
    const string s1("pallav");
    return s1;
}

class B {
  public :
     explicit B(string s = "default") : name(s) { cout << "Calling default Constructor for B : " << endl; }
     B(const B & rhs) { cout << "Calling Copy Constructor for B: " << endl; }
     // Here rhs is rvalue reference, as No Type Deduction
     B(B && rhs) : name(move(rhs.name)) { cout << "Calling Move Constructor for B: "<<endl; }

     // Here newName is Universal reference
     template<typename T>
     void setName(T && newName) {
          cout << "Calling setName(T && newName): set from universal value " << endl; 
          name = forward<T>(newName);
     }

     template<typename T>
     void setName(const T & newName) {
          cout << "Calling setName(const T & newName): on const lvalue objects" << endl; 
          name = newName;
     }

  private :
     string name;
};

//////////////////////////////////////////////////////////////////////////

// RVO apply to return-by-value only.
//     it doesnot apply to Refreneces returned

B  func1() {
   B  obj1{ };
   return obj1;
}
 
B  func2() {
   B  obj1{ };
   // Here obj1 is treated as RValue,Because No Copy Illusion was performed.
   return move(obj1); 
}
 
// Here param is not Eligible for RVO, 
// Pass-by-Value Parameter are not Eligible for RVO
B  func3(B param) {
   // Here obj1 is treated as RValue,Because No Copy Illusion was performed.
   return param; // compiler treat it as move(param); 
}
 
int main(int argc, char * argv[]) {
    string s1("pallav"), s2("Anrav");
    const string s3("pallav"), s4("Anrav");

    auto n = getName();

    B  obj1{s1};

    obj1.setName("Pallav Singh");
    obj1.setName(n);
    obj1.setName(getName());
    obj1.setName(s3);

    B  obj2 = move(obj1); 
    obj2.setName(s2);

    return 0;
}

