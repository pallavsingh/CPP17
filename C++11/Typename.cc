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
#include <string.h>
#include <algorithm>
#include <iterator>
#include <unordered_map>
// Boost Library Hearders
#include <boost/type_index.hpp>
#include <boost/scoped_array.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/assert.hpp>

using  namespace boost::mpl; // brings boost::mpl:: in scope
using  namespace std;
using  boost::typeindex::type_id_with_cvr;

class Widget {
  public :
     Widget() { cout << "Calling Constructor for Widget " << endl; }
     Widget(const Widget & rhs) { cout << "Calling  Copy Constructor for Widget " << endl; }
     virtual ~Widget() { cout << "Calling Destructor for Widget " << endl; }
     virtual size_t size() const { constexpr int x = 20; return  x; }
     virtual void   normalize()  { cout << "Calling Func :: normalize() " << endl; }
     void swap(Widget & other)   { cout << "Calling Func :: sawp() " << endl; }
};

// Here Compiler will do Static Ananlysis and will Give error for Data Types ( Compiler/User defined )
// which donot Implement function required for Type of Class being passed.
template <typename T>
void doProcessing(T & w){
     if ((w.size() > 10)) {
          T temp{};
          // Since Virtual Function and Template donot work Togather.
          temp.normalize();
          temp.swap(w);

          // Calling Unimplemeted Function will cause Error
          // temp.UnImpleted_Func(w);
     }
}

//////////////////////////////////////////////////////////////////////////////

template <typename C>
void func1(const C & arg){
     if (arg.size() >= 2)
        typename C::const_iterator iter(arg.begin());
}

template<typename C>
void func2(const C & arg, typename C::iterator) {
}

// Typename should be used to Identify only nested dependent Names
// Others Name should not have it.

template<typename T>
class Base{
   public :
      class Nested { };
};

// Why Base Class List donot have TypeName Allowed
template<typename T>
class Derived : public Base<T>::Nested {
    public :
      // Base Class Identifier mem.init.list : Typename not Allowed
      explicit Derived(int x) : Base<T>::Nested(x) {
           typename Base<T>::Nested temp;
      }
};

template <typename IterT>
void func3(IterT iter){
   typename std::iterator_traits<IterT>::value_type temp(*iter);
}

template <typename IterT>
void func4(IterT iter){
   typename std::iterator_traits<IterT>::value_type value_type1;
   // value_type1 temp(*iter);
}

///////////////////////////////////////////////////////////////////////////////

namespace Arnav {
    class A { };
    
    template <typename T>
    class Base1 {
       public :
          void func(const A & rhs) {
               cout << " Calling Func() Inside Base Class " << endl;
          } 
    
          void func1() {
               cout << " Calling Func1() Inside Base Class " << endl;
          } 
    };
    
    template < >
    class Base1<A> {
       public :
          void func1() {
               cout << " Calling Specialization Template<> Base<A> Func1() Base Class " << endl;
          } 
    };
    

    template <typename T>
    class Derived1 : public Base1<T> {
       public :
          // How to Explicitly Call Function of Base Class
          // when Base and Derived Class have Same Name.

          // using Base1<T>::func1;  // Case - 2 
          void func2() {
               cout << " Calling Func2() Inside Derived Class " << endl;
                // this->func1();    // Case - 1
               Base1<T>::func1();    // Case - 3
          } 

          void func1() {
               cout << " Calling Func1() Inside Derived Class " << endl;
          } 
    };
}

/////////////////////////////////////////////////////////////////////////////////////

// Code Bloating Example in Templates

// 1. Code Bloat by Non-Type Parameter.
template <typename T, size_t n>
class P {
   public :
      void invert() { cout << "Calling P :: invert() Func : " << endl; }
};

template<typename T>
class P1{
   public :
      void invert(int arg) { cout << "Calling P1 :: invert() Func : " << endl; }
};

template<typename T, size_t n>
class P2 : private P1<T> {
   public :
      using P1<T>::invert;
      void invert() { this->invert(10);  cout << "Calling P2 :: invert() Func : " << endl; }
};

// 2. Code Bloat by Non-Type Parameter.
template <typename T>
class Q {
   protected :
      Q(size_t n, T * pMem) : size(n), pData(pMem) {}
      void setDataPtr(T * ptr) { pData = ptr; }
   private :
      size_t size;
      T * pData;
};

template<typename T, size_t n>
class Q1 : private Q<T> {
   public :
      Q1():Q<T>(n, data){}
   private :
      T data[n*n];
}; 

template<typename T, size_t n>
class Q2 : private Q<T> {
   public :
      Q2():Q<T>(n, 0), pData(new T[n*n]) { this->setDataPtr(pData.get()); }
   private :
      boost::scoped_array<T> pData;
}; 

///////////////////////////////////////////////////////////////////////////

// Use Member Function template to accept "All Compatible Types"

class Top { };
class Middle : public Top { };
class Bottom : public Middle { };

// How Generated Copy Constructor Help to Assign Base * ==>> Derived *
template<typename T>
class shared_ptrT {
   public :
      template<typename Y>
      explicit shared_ptrT(Y * ptr) { } 

      template<typename Y>
      explicit shared_ptrT(shared_ptrT<Y> const & other) { } 

      template<typename Y>
      explicit shared_ptrT(weak_ptr<Y> const & other) { } 

      template<typename Y>
      explicit shared_ptrT(auto_ptr<Y> & other) { } 

      template<typename Y>
      shared_ptrT & operator= (shared_ptrT<Y> const & rhs) { }

      template<typename Y>
      shared_ptrT & operator= (auto_ptr<Y> & rhs) { }
};

//////////////////////////////////////////////////////////////////////

template<typename T>
class Z;

template<typename T>
const Z<T> HelperFunc(const Z<T> & lhs, const Z<T> & rhs) {
   return Z<T>(lhs.getx() * rhs.getx() , lhs.gety() * rhs.gety());
}

template <typename T>
class Z {
  public :
      Z(const T & p = 0, const T & q = 0) :x(p), y(q) { }
      const T getx() const {return x; }
      const T gety() const {return y; }

      friend const Z<T> operator* (const Z<T> & lhs, const Z<T> & rhs) {
             return HelperFunc(lhs, rhs);
      }

  private:
     int x, y;
};


int main(int argc, char * argv[]) {
    Widget obj1{};
    doProcessing<Widget>(obj1);

    using namespace Arnav;
    Derived1<A> obj{};
    obj.func2();

    // Code Bloating Example in Templates
    P< double, 5>  p1{};  p1.invert();
    P< double, 10> p2{};  p1.invert();

    P2< double, 10> p22{};  p22.invert();

    Top * pt1 = new Middle;
    Top * pt2 = new Bottom;
    const Top * pct2 = pt1;

#if 0
    shared_ptrT<Top> pt11 = shared_ptrT<Middle>(new Middle);
    shared_ptrT<Top> pt22 = shared_ptrT<Bottom>(new Bottom);
    shared_ptrT<const Top> pct22 = pt11;
#endif

    Z<int> oneHalf(1,2);
    Z<int> result = oneHalf*2;


    return 0;
};

