#include <iostream>
#include <memory>
#include <atomic>
#include <initializer_list>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

class A {};

A getClassA() {
  return A{};
}

template <typename T>
void func(T && param) {
     cout <<"Reference Collapsing Template Instantiation : T = " << type_id_with_cvr<T>().pretty_name() << '\n';
     cout <<"Reference Collapsing Template Instantiation : Param = "<<type_id_with_cvr<decltype(param)>().pretty_name() << '\n';
}


template <typename T>
class B {
   public :
      typedef T && RvalueRef;
};

int main(int argc, char * argv[]) {
    A obj1{};
    func (obj1);
    func (getClassA());

    auto && obj2 = obj1;
    cout << "Reference Collapsing Auto : obj2 = " <<  type_id_with_cvr<decltype(obj2)>().pretty_name() << '\n';
    auto && obj3 = getClassA();
    cout <<"Reference Collapsing  Auto : obj3 = " <<  type_id_with_cvr<decltype(obj3)>().pretty_name() << '\n';

    B<int &> obj4{};

    return 0;
}

