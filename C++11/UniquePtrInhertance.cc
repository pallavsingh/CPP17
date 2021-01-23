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

// How to solve Issues with Unique_ptr for Inheritance Hirarcy,
// when base class Destructor is Not Virtual.

class Base {
public:
      Base() { cout << "Base:<init>" << endl; }
     ~Base() { cout << "Base::<destroy>" << endl; }
      virtual string message() const { return "Message from Base!"; }
};

class Derived : public Base {
public:
      Derived() { cout << "Derived::<init>" << endl; }
     ~Derived() { cout << "Derived::<destroy>" << endl; }
      virtual string message() const { return "Message from Derived!"; }
};

////////////////////////////////////////////////////////////////////////

class BoundDeleter {
private:
    typedef void (*DeleteFunc) (void* p);

    DeleteFunc  deleteFunc_;
    void*       pObject_;

    template <class Type>
    static void deleteFuncImpl (void * p) {
         delete static_cast< Type* >(p);
    }

public:
    template< class Type >
    BoundDeleter(Type * pObject) : deleteFunc_( &deleteFuncImpl<Type>) , pObject_(pObject) { }
    BoundDeleter(BoundDeleter && other) : deleteFunc_(move( other.deleteFunc_ )) , pObject_( move( other.pObject_) ){ }
    void operator() (void*) const {
         deleteFunc_( pObject_ );
    }
};

template< class Type >
class SafeCleanupUniquePtr : protected unique_ptr<Type, BoundDeleter> {
public:
    typedef unique_ptr<Type, BoundDeleter>  Base;

    using Base::operator->;
    using Base::operator*;

    template< class ActualType >
    SafeCleanupUniquePtr( ActualType* p ) : Base( p, BoundDeleter(p)) { }

    template< class Other >
    SafeCleanupUniquePtr(SafeCleanupUniquePtr<Other> && other) : Base(move(other)) { }
};

////////////////////////////////////////////////////////////////////////

int main() {
    // SafeCleanupUniquePtr< Base >  p( new Derived );
    unique_ptr<Base>  p(new Derived);
    cout << p->message() << endl;

    return 0;
}
