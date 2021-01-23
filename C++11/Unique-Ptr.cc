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

////////////////////////////////////////////////////////////////////

/*
Only non-const unique_ptr can transfer the ownership of the managed object 
to another unique_ptr. The lifetime of an object managed by const std::unique_ptr 
is limited to the scope in which the pointer was created.
*/
 
struct Foo {
    Foo()      { std::cout << "Foo::Foo\n";  }
    ~Foo()     { std::cout << "Foo::~Foo\n"; }
    void bar() { std::cout << "Foo::bar\n";  }
};
 
void func1 (const Foo & param) {
     std::cout << "f(const Foo&) \n";
}
 
void func2 (const unique_ptr<Foo>  & p) {
    cerr << "Sink owns Foo [" << p.get() << "]\n";
}

int main(int argc, char * argv[]) {
    // C++ Has deleted the Implementation of Copy Constructor and Assignment Operator 
    // unique_ptr(const unique_ptr&) = delete;
    // unique_ptr& operator=(const unique_ptr&) = delete;
    unique_ptr<Foo> fp(new Foo());
    unique_ptr<Foo> fp3;
    // unique_ptr<Foo> fp2(fp);    // ERROR! can't copy unique_ptr
    // fp3 = fp;                   // ERROR! can't assign unique_ptr

    std::unique_ptr<Foo> p1(new Foo);  // p1 owns Foo

    if (p1) {
        p1->bar();
    }
 
    // for Auto_ptr we have copy constructor and Assignment Operator implemented
    // Hence we can pass-by-value Auto Ptr but not Unique Ptr.
    std::unique_ptr<Foo> p2(std::move(p1));  // now p2 owns Foo
    func1(*p2);
    func2(p2);

    p1 = std::move(p2);  // ownership returns to p1
    std::cout << "destroying p2...\n";

    // Foo instance is destroyed when p1 goes out of scope
    if (p1) { 
        p1->bar();
        std::cout << "destroying p1...\n";
    }

    // If you need the raw pointer. But do not call delete on pRawPtr your self. 
    unique_ptr<Foo> pObj(new Foo());
    Foo * pRawPtr = pObj.get();

    // If you want to remove a pointer from the smart pointer, you need to release the ownership of it.
    // The std::unique_ptr will now not delete the pointer. And pObj is now also invalid for usage.
    pObj.release();

    return 0;
}

