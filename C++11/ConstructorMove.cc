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

using  namespace std;
using  boost::typeindex::type_id_with_cvr;

class  A {
 public :
        int i;
        A(int x) : i(x) { cout << "Calling A() : " << endl; }
        A(const A & rhs) : i(rhs.i) { cout << "Calling A(const A &) : " << endl; }
        A(A && rhs) : i(rhs.i) { rhs.i = 0;  cout << "Calling A (A &&) Move Constructor : " << endl; }
        A & operator=(const A & rhs) { i = rhs.i ; cout << "Calling A(const A &) Assignment  Operator : " << endl;  }
        A & operator=(A && rhs) { i = rhs.i; rhs.i = 0;  cout << "Calling A(const A &)  Move Assignment Operator : " << endl;  }
       ~A() { cout << "Calling A Destructor : " << endl;  }
};

A && getStructA() {
    A obj{10};
    return move(obj);
}

int main(int argc, char * argv[]) {
   A objx1{10};
   A objx2{20};

   A  objx5 = move(objx1);
   A  objx6(getStructA());
   A  objx7(static_cast<A&&>(objx2));
    

    return 0;
}
