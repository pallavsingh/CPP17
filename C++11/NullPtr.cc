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
#include <unordered_map>

// Boost Library Hearders
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

// Nullptr handle ambiguity between int and void *, but NULL is not able
void func(int    param) { cout <<"Calling func(int    param) : "<< endl; }
void func(bool   param) { cout <<"Calling func(bool   param) : "<< endl; }
void func(void * param) { cout <<"Calling func(void * param) : "<< endl; }

class  A{};
int    func1(shared_ptr<A> spw) { cout <<"Calling func1 : " << endl; }
double func2(unique_ptr<A> upw) { cout <<"Calling func2 : " << endl;}
bool   func3(A * spw) { cout << "Calling func3 :" << endl; }

// Here we see nullptr is having type but NULL , 0 donot have type
// at Compile time (Template Programming) we have only constants and types to work.
using MuxGuard = std::lock_guard<std::mutex>;

template <typename FuncType, typename MutexType, typename PtrType>
decltype(auto) lockAndCall(FuncType func, MutexType & mutexi, PtrType ptr) {
    MuxGuard guardObj(mutexi);
    return   func(ptr);
}

int main(int argc, char * argv[]) {
  func(0);
  // func(NULL); // Here all three func leads to Ambigous behaviour
  func(nullptr);

  mutex func1mutex, func2mutex, func3mutex;
  auto result1 =  lockAndCall(func1, func1mutex, 0);
  auto result2 =  lockAndCall(func2, func2mutex, NULL);
  auto result3 =  lockAndCall(func3, func3mutex, nullptr);

  return 0;
}

