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
public:
    int i{10}, j{20};
};

ostream & operator<< (ostream& out, const A & rhs){
    out << "Value of i = " << rhs.i << endl;
    out << "Value of j = " << rhs.j << endl;
    return out;
}

shared_ptr<A> find_some_thing(){
     shared_ptr<A> p;
     return p;
}

shared_ptr<A> do_something_with(shared_ptr<A> p) {
     return p;
}

int main(int argc, char * argv[]) {
     shared_ptr<A> p1(new A);
     shared_ptr<A> p2 = p1; // p1 and p2 now share ownership of the A
     shared_ptr<A> p3(new A); // another A
     p1 = find_some_thing(); // p1 may no longer point to first A

     do_something_with(p2);

     cout << *p2 << endl; // dereference like built-in pointer

     // reset with a member function or assignment to nullptr:
     p1.reset(); // decrement count, delete if last
     p2 = nullptr; // convert nullptr to an empty shared_ptr, and decrement count;


     shared_ptr<A> sp(new A);
     weak_ptr<A> wp1(sp); // construct wp1 from a shared_ptr
     weak_ptr<A> wp2; // an empty weak_ptr - points to nothing
     wp2 = sp; // wp2 now points to the new A
     weak_ptr<A> wp3 (wp2); // construct wp3 from a weak_ptr
     weak_ptr<A> wp4;
     wp4 = wp2; // wp4 now points to the new A.

     return 0;
}
