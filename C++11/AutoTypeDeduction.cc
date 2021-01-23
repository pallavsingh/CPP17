// C++14 Hearders
#include <iostream>
#include <memory>
#include <atomic>
#include <initializer_list>
#include <type_traits>
#include <typeinfo>
#include <utility>

// Boost Library Hearders
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

void someFunc(int, double) {}

template <typename T>
void func(T param){ 
   cout <<" Calling func(T param) with initializer_list "<< endl;
}

template <typename T>
void func(initializer_list<T> param){ 
   cout <<" Calling func(initializer_list<T> param) with initializer_list "<< endl;
}


int main(int argc, char * argv[]) {
   auto x = 27;
   cout << "Type of x = " << type_id_with_cvr<decltype(x)>().pretty_name() << '\n';
   const auto   cx = x;
   cout << "Type of cx = " << type_id_with_cvr<decltype(cx)>().pretty_name() << '\n';
   const auto & crx = x;
   cout << "Type of crx = " << type_id_with_cvr<decltype(crx)>().pretty_name() << '\n';

   ///////////// Type deduction for universal refrences ///////

   auto && uref1 = x;
   cout << "Type of universal reference   x = " << type_id_with_cvr<decltype(uref1)>().pretty_name() << '\n';
   auto && uref2 = cx;
   cout << "Type of universal reference crx = " << type_id_with_cvr<decltype(uref2)>().pretty_name() << '\n';
   auto && uref3 = 27;
   cout << "Type of universal reference Integer Literal = " << type_id_with_cvr<decltype(uref3)>().pretty_name() << '\n';

   ////////// Type deduction for Array ////////////////////////

   const char name[] = "Array-Argument";
   auto arr1 = name;
   cout << "Type of auto arr1 = " << type_id_with_cvr<decltype(arr1)>().pretty_name() << '\n';
   auto & arr2 = name;
   cout << "Type of auto & arr2 = " << type_id_with_cvr<decltype(arr2)>().pretty_name() << '\n';

   /////////// Type deduction for functions  //////////////////

   auto   func1 = someFunc;
   cout << "Type of func1 = " << type_id_with_cvr<decltype(func1)>().pretty_name() << '\n';
   auto & func2 = someFunc;
   cout << "Type of auto & func2 = " << type_id_with_cvr<decltype(func2)>().pretty_name() << '\n';

   auto x1 = 27;
   auto x2 = 27;
   auto x3 = {27};
   auto x4{27};

   cout << "Type of x1 = " << type_id_with_cvr<decltype(x1)>().pretty_name() << '\n';
   cout << "Type of x2 = " << type_id_with_cvr<decltype(x2)>().pretty_name() << '\n';
   cout << "Type of x3 = " << type_id_with_cvr<decltype(x3)>().pretty_name() << '\n';
   cout << "Type of x4 = " << type_id_with_cvr<decltype(x4)>().pretty_name() << '\n';

   // error: unable to deduce ‘std::initializer_list<auto>’ from ‘{1, 2, 3.0e+0}’
   // auto x5 = {1, 2, 3.0};
   // cout << "Type of x5= " << type_id_with_cvr<decltype(x5)>().pretty_name() << '\n';

   auto x6 = {1, 2, 3};
   cout << "Type of x6= " << type_id_with_cvr<decltype(x6)>().pretty_name() << '\n';

   // Template cannot deduce type from initializer_list
   // but Auto can deduce type from initializer_list
   func({11, 22, 9});
 
   return 0;
}

