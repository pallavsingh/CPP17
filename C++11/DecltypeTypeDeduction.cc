// C++14 Hearders
#include <iostream>
#include <memory>
#include <atomic>
#include <initializer_list>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

// Boost Library Hearders
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

//C++11
template<typename T, typename U>
auto myFunc11(T&& t, U&& u) -> decltype (forward<T>(t) + forward<U>(u)) { 
     return forward<T>(t) + forward<U>(u); 
};

//C++14
template<typename T, typename U>
decltype(auto) myFunc14(T&& t, U&& u) { 
     return forward<T>(t) + forward<U>(u); 
};

/////////////////////////////////////////////////////////////
// Here auto strip off reference from return value. 
template<typename C, typename I>
auto getContainerValue1(C & c, I i) {
     return c[i];
} 

template<typename C, typename I>
decltype(auto) getContainerValue2(C & c, I i) {
     return c[i];
}

template<typename C, typename I>
decltype(auto) getContainerValue3(C && c, I i) {
     return std::forward<C>(c)[i];
}

template<typename C, typename I>
auto getContainerValue4(C && c, I i) ->decltype(std::forward<C>(c)[i]) {
     return std::forward<C>(c)[i];
}

/////////////////////////////////////////////////////////////

decltype(auto) func_expr_literal1() {
   int x = 0;
   return x; // Here x is treated as lvalue name
}


decltype(auto) func_expr_literal2() {
   int x = 0;
   return (x); // Here x is treated as expresion
}

/////////////////////////////////////////////////////////////

int main(int argc, char * argv[]) {
   cout << "decltype of myFunc11 = " << type_id_with_cvr<decltype(myFunc11(1, 2.0))>().pretty_name() << '\n';
   cout << "decltype of myFunc14 = " << type_id_with_cvr<decltype(myFunc14(1, 2.0))>().pretty_name() << '\n';

   int x = 100;
   const int & cx = x;
   auto var1 = cx;   
   decltype(auto) var2 = cx;   

   cout << "type of var1 = " << type_id_with_cvr<decltype(var1)>().pretty_name() << '\n';
   cout << "type of var2 = " << type_id_with_cvr<decltype(var2)>().pretty_name() << '\n';

   vector<int> vec{20,20};
  //  getContainerValue1(vec, 5) = 1;
   getContainerValue2(vec, 5) = 2;
   getContainerValue3(vec, 5) = 3;
   getContainerValue4(vec, 5) = 4;

   cout<<"decltype of func_expr_literal1 = "<< type_id_with_cvr<decltype(func_expr_literal1())>().pretty_name() << '\n';

   cout<<"decltype of func_expr_literal2 = "<< type_id_with_cvr<decltype(func_expr_literal2())>().pretty_name() << '\n';

   return 0;
}

