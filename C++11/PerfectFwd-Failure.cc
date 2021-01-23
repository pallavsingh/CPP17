// C++14 Hearders
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

using namespace std;
using boost::typeindex::type_id_with_cvr;

///////////////////////////////////////////////////////////
void func(const vector<int> & v){
     cout <<" Calling func(const vector<int> & v)" << endl;
}

template <typename T>
void fwd(T && param){
     func(forward<T>(param));
}

template <typename... Ts>
void fwd(Ts&&... params){
   func(forward<Ts>(params)... );
}

///////////////////////////////////////////////////////////

void func1(size_t val) {
     cout <<" Calling func1(size_t val)" << endl;
}

class A {
  public :
     static const size_t MinVals = 28;
};

////////////////////////////////////////////////////////////

void func2(int (*funcptr)(int)) { cout << " func2(int (*funcptr)(int))" << endl; }

int processVal(int value) {cout <<"Calling processVal(int value) : " << endl; }
int processVal(int value, int priority) { cout <<"Calling processVal(int, int) : " << endl; }

template <typename T>
T workOnVal(T param) {
  cout << "Calling Template Function workOnVal(T param) : "<< endl;
}

template <typename T>
void fwd2(T && param){
     func2(forward<T>(param));
}

template <typename... Ts>
void fwd2(Ts&&... params){
     func2(forward<Ts>(params)... );
}

////////////////////////////////////////////////////////////

struct IPV4 {
   uint32_t X:4,
            Y:4,
            Z:6,
            A:2,
            B:16;
};

void funcipv4(size_t sz) {
     cout << "Calling Func for ipv4" << endl;
}

template <typename T>
void fwdipv4(T && param){
     funcipv4(forward<T>(param));
}

template <typename... Ts>
void fwdipv4(Ts&&... params){
     funcipv4(forward<Ts>(params)... );
}

////////////////////////////////////////////////////////////

int main(int argc, char * argv[]) {
     func({1,2,3});
     // fwd ({1,2,3});
     auto il = {1,2,3};
     fwd(il);

     vector<int> Adata;
     Adata.reserve(A::MinVals);

     func1(A::MinVals);
     // fwd(A::MinVals);

     func2(processVal);
     using ProcessFuncType = int (*)(int);
     // using ProcessFuncType = int (*)(int, int);
     ProcessFuncType processValPtr = processVal;

     fwd2(processValPtr);
     fwd2(static_cast<ProcessFuncType>(workOnVal));

     IPV4 ipv4;
     funcipv4(ipv4.B);
     // fwdipv4 (ipv4.B);
     auto length = static_cast<uint16_t>(ipv4.B);
     fwdipv4 (length);

     return 0;
}
