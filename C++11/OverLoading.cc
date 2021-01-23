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
#include <unordered_map>

// Boost Library Hearders
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

namespace Arnav1 {
    class A {
      public :
        void func(void) &  { cout << " Inside Class A:: func(void) &  : " << endl; }
        void func(void) && { cout << " Inside Class A:: func(void) && : " << endl; }
    };

    A  getRvalueA(void) {
      return A{ };
    }
}
  
namespace Arnav2 {
    class Base {
        virtual void mfunc1() const;
        virtual void mfunc2(int x);
        virtual void mfunc3() &;
        void mfunc4() const;
    };

    class Derived1 : public Base {
        virtual void mfunc1() const;
        virtual void mfunc2(unsigned int x);
        virtual void mfunc3() &&;
        void mfunc4() const;
    };

#if 0
    class Derived2 : public Base {
        virtual void mfunc1() const override;
        virtual void mfunc2(unsigned int x) override;
        virtual void mfunc3() && override;
        void mfunc4() const override;
    };
#endif

}

namespace Arnav3{
    class B{ };

    B getRvalueB(void) {
      return B{ };
    }
  
    void func (B &  param) { cout <<"Calling func(B &  param) with reference" << endl; }
    void func (B && param) { cout <<"Calling func(B && param) with universal reference" << endl; }
}

namespace Arnav4{
    class C { 
       public :
         using DataType = vector<int>;

         DataType & func () &  {
              cout << "Calling Datatype & func() &  with reference" << endl; 
              return values;
         }

         DataType   func () && { 
              cout << "Calling Datatype   func() && with reference" << endl; 
              return move(values);
         }

       private :
         DataType values;
    };

    C getRvalueC(void) {
      return C{ };
    }
}

int main(int argc, char * argv[]) {
  using namespace Arnav1;
  using namespace Arnav2;
  using namespace Arnav3;
  using namespace Arnav4;

  A obj;
  obj.func();
  getRvalueA().func();

  B obj1;
  func(obj1);
  func(getRvalueB());

  C obj2;
  auto val1 = obj2.func();
  auto val2 = getRvalueC().func();

  return 0;
}

