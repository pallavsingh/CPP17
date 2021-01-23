/////////////////////////////////////////////////
// C++14 Hearders
#include <iostream>
#include <memory>
#include <atomic>
#include <initializer_list>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/////////////////////////////////////////////////
// Boost Library Hearders
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

class A {};

A getClassA(void){
  return A{};
} 

vector<A> getVectorA(void){
  vector<A> obj{A{}, A{}, A{} };
  return obj;
} 

void func1(A && param) {
     cout <<"func(A && param) : called " << endl; 
}

template <typename T>
void func2(T && param) {
     cout <<"func(T && param) : T = "     <<  type_id_with_cvr<T>().pretty_name() << '\n';
     cout <<"func(T && param) : Param = " <<  type_id_with_cvr<decltype(param)>().pretty_name() << '\n';
}

template <typename T>
void func3(const T && param) {
     cout <<"func(const T && param)  : T = "     <<  type_id_with_cvr<T>().pretty_name() << '\n';
     cout <<"func(const T && param)  : Param = " <<  type_id_with_cvr<decltype(param)>().pretty_name() << '\n';
}

template <typename T>
void func4(volatile T && param) {
     cout <<"func(volatile T && param) : T = "     <<  type_id_with_cvr<T>().pretty_name() << '\n';
     cout <<"func(volatile T && param) : Param = " <<  type_id_with_cvr<decltype(param)>().pretty_name() << '\n';
}

template <typename T>
void func5(vector<T> && param) {
     cout <<"func(vector<T> && param) : T = "     <<  type_id_with_cvr<T>().pretty_name() << '\n';
     cout <<"func(vector<T> && param) : Param = " <<  type_id_with_cvr<decltype(param)>().pretty_name() << '\n';
}

// Here we are creating anonymous functions through Lambda in C++
auto timeFuncInvocation = [](auto && func, auto && ... params){
                             forward<decltype(func)>(func)(
                                 forward<decltype(params)>(params)...
                             );
                          };

int main(int argc, char * argv[]) {

   A a1{};
   func1(forward<A>(a1));

   func2(getClassA());
   func3(getClassA());
   func4(getClassA());
   func5(getVectorA());

   return 0;
}

