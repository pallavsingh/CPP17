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

using  namespace std;
using  boost::typeindex::type_id_with_cvr;

template<typename T>
class Base {
   public :
    // Base () = default;

    Base (T * arg = "default") {
         cout <<"Call Template Constructor :  Base Class "<< endl;
         length1 = strlen(arg);
         string1 = new char[length1 + 1]; 
         strcpy(string1, arg);
         string1[length1 + 1] = '\0';
    }

    Base (const Base & rhs)  {
         cout <<"Call Copy Constructor : Base Class "<< endl;
         length1 = rhs.length1;
         string1 = new char[length1 + 1]; 
         strcpy(string1, rhs.string1);
         string1[length1 + 1] = '\0';
    }

    Base (Base && rhs): string1(rhs.string1), length1(rhs.length1) {
         cout <<"Call Move Constructor for Normal Base Class : Base "<< endl;
         rhs.string1 = nullptr;
         rhs.length1 = 0;
    }

    Base & operator=(const Base & rhs){
      cout <<"Call Assignment Operator for Normal Base Class : A "<< endl;
      if (this != &rhs) {
         delete[]  string1;

         string1 = new char[rhs.length1 + 1];
         strcpy(string1, rhs.string1);
         length1 = rhs.length1;
         string1[length1 + 1] = '\0';
      }
      return *this;
   }

   Base & operator=(Base && rhs){
      cout <<"Call Move Assignment Operator for Normal Base Class : Base "<< endl;
      if (this != &rhs) {
         delete[]  string1;
         string1 = rhs.string1;
         length1 = rhs.length1;
         rhs.string1 = nullptr;
         rhs.length1 = 0;
      }
      return *this;
   }

   ~Base() {
        cout <<"Call Destructor for Normal Base Class : Base "<< endl;
        delete[] string1;
    }

  private :
   T * string1;
   size_t length1;
};


template<typename T1, typename T2>
class Derived1 : virtual public Base<T1> {
public :
   Derived1 (T1 * arg1, T2 * arg2) : Base<T1>(arg1) {
       cout <<"Call Constructor for Template Derived1 --->> Base<T1> "<< endl;
       length2 = strlen(arg2);
       string2 = new char[length2 + 1]; 
       strcpy(string2, arg2);
       string2[length2 + 1] = '\0';
   }

   Derived1 (const Derived1 & rhs): Base<T1>(rhs) {
       cout <<"Call Copy Constructor for Template Derived1 --->> Base<T1> "<< endl;
       length2 = rhs.length2;
       string2 = new char[length2 + 1]; 
       strcpy(string2, rhs.string2);
       string2[length2 + 1] = '\0';
   }

   Derived1 (Derived1 && rhs): Base<T1>(move(rhs)) {
       cout <<"Call Move Constructor for Template Derived1 --->> Base<T1>"<< endl;
       string2 = rhs.string2; 
       length2 = rhs.length2;
       rhs.string2 = nullptr;
       rhs.length2 = 0;
   }

   Derived1 & operator=(const Derived1 & rhs) {
      cout <<"Call Assignment Operator for Template Derived1 Class"<< endl;
      if (this != &rhs) {
         Base<T1>::operator=(rhs);
         delete [] string2;

         string2 = new char[rhs.length2 + 1];
         strcpy(string2, rhs.string2);
         string2[length2 + 1] = '\0';

         length2 = rhs.length2;
      }
      return *this;
   }

   Derived1 & operator=(Derived1 && rhs) {
      cout <<"Call Move Assignment Operator for Template Derived1 Class"<< endl;
      if (this != &rhs) {
         Base<T1>::operator=(move(rhs));
         delete [] string2;

         string2 = rhs.string2;
         length2 = rhs.length2;

         rhs.string2 = nullptr ;
         rhs.length2 = 0;
      }
      return *this;
   }

   ~Derived1() {
        cout <<"Call Desstructor for Template Derived1 "<< endl;
        // ~Base<T1>::Base();
        delete[] string2;
   }

 private :
   T2 * string2;
   int  length2;
};


template<typename T1, typename T2>
class Derived2 : virtual public Base<T1> {
public :
   Derived2 (T1 * arg1, T2 * arg2) : Base<T1>(arg1) {
       cout <<"Call Constructor for Template Derived 2 --->> Base<T1> "<< endl;
       length2 = strlen(arg2);
       string2 = new char[length2 + 1]; 
       strcpy(string2, arg2);
       string2[length2 + 1] = '\0';
   }

   Derived2 (const Derived2 & rhs): Base<T1>(rhs) {
       cout <<"Call Copy Constructor for Template Derived 2 --->> Base<T1> "<< endl;
       length2 = rhs.length2;
       string2 = new char[length2 + 1]; 
       strcpy(string2, rhs.string2);
       string2[length2 + 1] = '\0';
   }

   Derived2 (Derived2 && rhs): Base<T1>(move(rhs)) {
       cout <<"Call Move Constructor for Template Derived 2 --->> Base<T1>"<< endl;
       string2 = rhs.string2; 
       length2 = rhs.length2;
       rhs.string2 = nullptr;
       rhs.length2 = 0;
   }

   Derived2 & operator=(const Derived2 & rhs) {
      cout <<"Call Assignment Operator for Template Derived 2 Class"<< endl;
      if (this != &rhs) {
         Base<T1>::operator=(rhs);
         delete [] string2;

         length2 = rhs.length2;
         string2 = new char[rhs.length2 + 1];
         strcpy(string2, rhs.string2);
         string2[length2 + 1] = '\0';

      }
      return *this;
   }

   Derived2 & operator=(Derived2 && rhs) {
      cout <<"Call Move Assignment Operator for Template Derived 2 Class"<< endl;
      if (this != &rhs) {
         Base<T1>::operator=(move(rhs));
         delete [] string2;

         string2 = rhs.string2;
         length2 = rhs.length2;

         rhs.string2 = nullptr ;
         rhs.length2 = 0;
      }
      return *this;
   }

   ~Derived2() {
        cout <<"Call Desstructor for Template Derived 2 --->> Base<T1> "<< endl;
        // ~Base<T1>::Base();
        delete[] string2;
   }

 private :
   T2 * string2;
   int  length2;
};

template<typename T1, typename T2, typename T3, typename T4>
class Derived3 : public Derived1<T1, T2>, Derived2<T1, T3> {
public :
   Derived3 (T1 * arg1, T2 * arg2, T3 * arg3, T4 * arg4) : Derived1<T1, T2>(arg1, arg2), Derived2<T1, T3>(arg1, arg3) {
       cout <<"Call Constructor for Template Derived 3--->> Derived 1, Derived 2  "<< endl;
       length3 = strlen(arg3);
       string3 = new char[length3 + 1]; 
       strcpy(string3, arg3);
       string3[length3 + 1] = '\0';
   }

   Derived3 (const Derived3 & rhs): Derived1<T1, T2>(rhs), Derived2<T1, T3>(rhs) {
       cout <<"Call Copy Constructor for Template Derived 3 --->> Derived 1, Derived 2 "<< endl;
       length3 = rhs.length3;
       string3 = new char[length3 + 1]; 
       strcpy(string3, rhs.string3);
       string3[length3 + 1] = '\0';
   }

   Derived3 (Derived3 && rhs): Derived1<T1, T2>(move(rhs)), Derived2<T1, T3>(move(rhs)) {
       cout <<"Call Move Constructor for Template Derived 3--->> Derived 1, Derived 2"<< endl;
       string3 = rhs.string3; 
       length3 = rhs.length3;
       rhs.string3 = nullptr;
       rhs.length3 = 0;
   }

   Derived3 & operator=(const Derived3 & rhs) {
      cout <<"Call Assignment Operator for Template Derived 3 --->> Derived 1, Derived 2 "<< endl;
      if (this != &rhs) {
         Derived1<T1, T2>::operator=(rhs);
         Derived2<T1, T3>::operator=(rhs);
         delete [] string3;

         length3 = rhs.length3;
         string3 = new char[rhs.length3 + 1];
         strcpy(string3, rhs.string3);
         string3[length3 + 1] = '\0';

      }
      return *this;
   }

   Derived3 & operator=(Derived3 && rhs) {
      cout <<"Call Move Assignment Operator for Template Derived3 --->> Derived 1, Derived 2 " << endl;
      if (this != &rhs) {
         Derived1<T1, T2>::operator=(move(rhs));
         Derived2<T1, T3>::operator=(move(rhs));
         delete [] string3;

         string3 = rhs.string3;
         length3 = rhs.length3;

         rhs.string3 = nullptr ;
         rhs.length3 = 0;
      }
      return *this;
   }

   ~Derived3() {
        cout <<"Call Desstructor for Template Derived 3 --->> Derived 1, Derived 2 " << endl;
        // ~Base<T1>::Base();
        delete[] string3;
   }

 private :
   T3 * string3;
   int  length3;
};


int main(int argc, char * argv[]) {
#if 0
    // Here we Check for Copy Const and  Assignment Operator
    Derived3<char, char, char, char> obj1("pallav1", "puneet1", "Pallav1", "Puneet1");
    Derived3<char, char, char, char> obj2("pallav2", "puneet2", "Pallav1", "Puneet1");
    Derived3<char, char, char, char> obj3(obj2);
    obj3 = obj1;
#endif 

#if 1
    // Here we Check for Move Const and Move Assignment Operator
    Derived3<char, char, char, char> obj11("pallav1", "puneet1", "pallav1", "puneet1");
    Derived3<char, char, char, char> obj22("pallav2", "puneet2", "pallav1", "puneet1");
    Derived3<char, char, char, char> obj33(move(obj22));
    obj33 = move(obj11);
#endif 

    return 0;
};

