// C++14 Hearders
#include <iostream>
#include <memory>
#include <atomic>
#include <initializer_list>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>
#include <string>
#include <unordered_map>

// Boost Library Hearders
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

class A{
  private :
    // when should we use uniform initialization inside class
    // Used to initialize Non-Static data member of class  
    int x {1};
    int y = 1;
    // int z(1);
  public :
    void showdata() {
        cout <<"Value of A::x  : " << x  << endl;
        cout <<"Value of A::y  : " << y  << endl;
        // cout <<"Value of A::z  : " << z  << endl;
    }
};

class B {
   public :
     B(int x, bool   y): p(x), q(y) { cout << "Calling Constructor of B(int, bool)  :" << endl; }
     B(int x, double y): p(x), q(y) { cout << "Calling Constructor of B(int, double) :" << endl; }
     // Initialzer List main usage is to Initialize Containers {vector, list, set, map}
     // with homogenous data.
     B(initializer_list<long double> args) { 
        // for (auto iter = args.begin(); iter != args.end(); ++iter) 
        // p = args.begin();  It will Call Constructor, but will Face conversion Issues
        // q = args.end(); 

        cout << "Calling Constructor of B(initializer_list) :" << endl; 
     }

     B (const B & rhs) { 
        cout <<"Calling Copy Constructor for B "<< endl; 
     }

     B (B && rhs) { 
        cout <<"Calling Move Constructor for B "<< endl; 
     }

     operator float() const {}

   private :
     int p, q;
};


class C {
   public :
     C(int x, bool   y): p(x), q(y) { cout << "Calling Constructor of C(int, bool)  :" << endl; }
     C(int x, double y): p(x), q(y) { cout << "Calling Constructor of C(int, double) :" << endl; }
     C(initializer_list<bool> args) { 
        cout << "Calling Constructor of C(initializer_list) :" << endl; 
     }
   private :
     int p, q;
};


class D {
   public :
     D(int x, bool   y): p(x), q(y) { cout << "Calling Constructor of D(int, bool)  :" << endl; }
     D(int x, double y): p(x), q(y) { cout << "Calling Constructor of D(int, double) :" << endl; }
     D(initializer_list<string> args) { 
        cout << "Calling Constructor of D(initializer_list) :" << endl; 
     }
   private :
     int p, q;
};

class E {
   public :
     E() { cout << "Calling Constructor of E() :" << endl; }
     E(initializer_list<string> args) { 
        cout << "Calling Constructor of E(initializer_list) :" << endl; 
     }
};



int main(int argc, char * argv[]) {
   int x(1);
   int y = 1;
   int z1{1};
   int z2 = {1};

   cout <<"Value of x  : " << x  << endl;
   cout <<"Value of y  : " << y  << endl;
   cout <<"Value of z1 : " << z1 << endl;
   cout <<"Value of z2 : " << z2 << endl;

   // Used to initialize Non-Copyable object
   atomic<int> ai1{1};
   atomic<int> ai2(1);
   // atomic<int> ai3 = 1;

   double p, q, r;
   int sum1{p + q + r}; // Donot allow Implicit Type Conversion

   // Here sum2 and sum3 allow implicit type conversions
   int sum2(p + q + r);
   int sum3 = p + q + r;

   A obj1;
   obj1.showdata();

   // Used to call Constructor when object is created on Stack.
   // It was an Issue in C++98
   A obj2{};
   obj2.showdata();
 
   B b1(10, true);
   B b2{10, true};
   B b3(10, 5.0);
   B b4{10, true};

   B b5(b4);
   B b6{b4};
   B b7(move(b4));
   B b8{move(b4)};

   C c1{10, 5.0};

   D d1(10, true);
   D d2{10, true};
   D d3(10, 5.0);
   D d4{10, true};

   E e1;
   E e2{};
   // E e3(); // Most vexing parsing declare a function
   E e3({});
   E e4{{}};

   return 0;
}

