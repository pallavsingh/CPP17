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

class A {};
class matrix {};

vector<bool> features(const A & obj) { 
   vector<bool> x(10, true);
   return x;
}

void  processWidget(const A & obj, bool highPriority){}

double func();

int main(int argc, char * argv[]) {
   A obj; 
   matrix m1, m2, m3, m4;

   bool highPriority1 = features(obj)[5];
   processWidget(obj, highPriority1);

   // For auto : output is undefined Behaviour as Internal Implementation of
   // Vector<bool> differ from library to library

   // auto  highPriority2 = features(obj)[5];

   // Here we are explicitly forcing the compiler to deduce the type  we want
   auto  highPriority2 = static_cast<bool>(features(obj)[5]);
   processWidget(obj, highPriority2);

   // Auto get deduced from Proxy class insted of type being proxied
   matrix sum1 = (m1 + (m2 + (m3 + m4))); // Here m3 + m4 will return proxy object
   auto   sum2 = static_cast<matrix>(m1 + m2 + m3 + m4);

   // Implicit Conversions Double -> float : Loss of precision Values
   float ep = func(); 
   auto  ep1 = static_cast<float>(func()); // Correct way to use

   return 0;
}

