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

class A {
  public :
     A(string s = "default") : value(s) {  cout << "Calling default Constructor for A : " << endl; }
     A(const A & rhs) { cout << "Calling Copy Constructor for A: " << endl; }
     A(A && rhs) { cout << "Calling Move Constructor for A: "<<endl; }

  private :
     string value;
};

class B {
  public :
     // Here since constness is added to string, It will always call Copy Constrcutor of A
     // Instead of Move Constructor of A.
     explicit B(const A param) : a(move(param)) { cout << "Calling default Constructor for B : " << endl; }
     B(const B & rhs) { cout << "Calling Copy Constructor for B: " << endl; }
     B(B && rhs) { cout << "Calling Move Constructor for B: "<<endl; }

  private :
     A a;
};

//////////////////////////////////////////////////////////////////////////

void process(const A & param)  { cout << "Calling process(const A & param): " << endl; }
void process(A && param) { cout << "Calling process(A && param): " << endl; }

template <typename T>
void logAndProcess(T && param) {
     process(forward<T>(param));
}

//////////////////////////////////////////////////////////////////////////

class C {
  public :
    // Type passed to forward should Always be Non-reference
    C(C && rhs) : s(forward<string>(rhs.s)) {
      cout << "Calling the Move Constructor for C"<< endl;
    }

  private :
    static size_t moveCtorCalls;
    string s;
};

int main(int argc, char * argv[]) {
    string s1("pallav"), s2("Anrav");

#if 0
    const  A  obj1{s1};
    A obj2 = obj1; 

    // Here since constness is added to obj1, It will always call Copy Constrcutor of A
    // Instead of Move Constructor of A.
    A obj3 = move(obj1); 

    B  obj11(s2);

#endif

    A  a;
    logAndProcess(a);
    logAndProcess(move(a));

    return 0;
}

