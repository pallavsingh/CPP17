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

class A {
  public :
    A(){ cout <<"Calling Constructor for Class A :" << endl; }
    A(const A & rhs) { cout <<"Calling Copy Constructor for Class A :" << endl; }
    A(A && rhs) { cout <<"Calling Move Constructor for Class A :" << endl; }
   ~A(){ cout <<"Calling Destructor for Class A :" << endl; }
};

auto loggingDel = [ ](A * ptr) {
                      cout << "Calling Lambda (logging function) :" << endl;    
                      delete ptr;
                  };

auto customDeleter1 = [ ](A * ptr) {
                          cout << "Calling Lambda ( customDeleter1 function) :" << endl;    
                          delete ptr;
                      };

auto customDeleter2 = [ ](A * ptr) {
                          cout << "Calling Lambda ( customDeleter2 function) :" << endl;    
                          delete ptr;
                      };

auto customDeleter3 = [ ](A * ptr) {
                          cout << "Calling Lambda ( customDeleter3 function) :" << endl;    
                          delete ptr;
                      };

class B : public enable_shared_from_this<B> {
  public :
    B() { cout << "Calling Constructor for Class B :" << endl; }
    B(const A & rhs) { cout << "Calling Copy Constructor for Class B :" << endl; }
    B(B && rhs) { cout << "Calling Move Constructor for Class B :" << endl; }
   ~B(){ cout <<"Calling Destructor for Class B :" << endl; }
  
    void process();
};

vector<shared_ptr<B> > processB;
void B::process(){
     // Inside same class we can insert multiple time : this  
     // To Avoid Multiple repeatation of this pointer inside 
     // container leading to undefined behavior use shared_from_this

     // processB.emplace_back(this);
     // processB.emplace_back(shared_from_this());
}

/*
template <typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts... params){
   return unique_ptr<T>(new T(forward<Ts>(params)));
}
*/

class C{ };

void func(shared_ptr<C> spw, int priority){

}

void customDeleter(C * ptr) { 
    cout << " Calling customDeleter : " << endl;    
    delete ptr;
}

int computePriority() {
    return 0;
}

int main(int argc, char * argv[]) {
    unique_ptr<A, decltype(loggingDel)> upA(new A{}, loggingDel);
    shared_ptr<A> ptrA1(new A{}, customDeleter1);
    shared_ptr<A> ptrA2(new A{}, customDeleter2);

    vector<shared_ptr<A> > vecptrA{ptrA1, ptrA2};

    // Here Call to Second Destructor would lead to UnDefined Behaviour.
    // Here ptrA3 and ptrA4 will have Diffrent Control Block but those control Block Pointer to Same Ptr 
    // when Shared_Ptr ptrA3 goes out of scope, it will Destroy the ptrA.
    // when Shared_Ptr ptrA4 goes out of scope, it will lead to un-defined Behaviour.
    auto ptrA = new A{};
    shared_ptr<A> ptrA3(ptrA, customDeleter3);
    shared_ptr<A> ptrA4(ptrA, customDeleter3);
   
    // Here Passing Shared ptr to contruct Another Shared Ptr will make 
    // Manager Block Shared between sptr1 and sptr2.
    shared_ptr<A> sptr1(new A{}, customDeleter2);
    shared_ptr<A> sptr2(sptr1);

    weak_ptr<A>   wptr(sptr1);
    auto  spw2 = wptr.lock();
    if (wptr.expired())
        cout << "Weak Ptr has got Expired : " << endl;

    sptr1 = nullptr;

    B obj;
    obj.process();
    
    auto makeunique(std::make_unique<A>());
    auto makeshared(std::make_shared<A>());

    auto makeshared1 = make_shared<A>();

    // Creating Vector with Initializer List Constructor
    auto initList = {10, 20};
    auto spv = make_shared<vector<int>>(initList);

    auto spv1 = make_unique<vector<int>>(10, 20);
    auto spv2 = make_shared<vector<int>>(10, 20);

    // Whats The diffrence between given Two Statement
    auto pBigObj1 = make_shared<C>();
    auto pBigObj2 = shared_ptr<C>(new C);

    shared_ptr<C> sharedptrtmp(new C{}, customDeleter);
    // Both Efficent and Exception-Safe
    func(move(sharedptrtmp) , computePriority());
    
    return 0;
}
