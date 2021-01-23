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
    Base (T * arg) {
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
       //  delete[] string1;
    }

  private :
   T * string1;
   size_t length1;
};

template<typename T1>
class Derived : public Base<T1> {
public :
   Derived (T1 * arg1, char * arg2) : Base<T1>(arg1) {
       cout <<"Call Constructor for Template Derived --->> Normal Base "<< endl;
       length2 = strlen(arg2);
       string2 = new char[length2 + 1]; 
       strcpy(string2, arg2);
       string2[length2 + 1] = '\0';
   }

   Derived (const Derived & rhs): Base<T1>(rhs) {
       cout <<"Call Copy Constructor for Template Derived --->> Normal Base "<< endl;
       length2 = rhs.length2;
       string2 = new char[length2 + 1]; 
       strcpy(string2, rhs.string2);
       string2[length2 + 1] = '\0';
   }

   Derived (Derived && rhs): Base<T1>(move(rhs)) {
       cout <<"Call Move Constructor for Template Derived --->> Normal Base"<< endl;
       string2 = rhs.string2; 
       length2 = rhs.length2;
       rhs.string2 = nullptr;
       rhs.length2 = 0;
   }

   Derived & operator=(const Derived & rhs) {
      cout <<"Call Assignment Operator for Template Derived Class"<< endl;
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

   Derived & operator=(Derived && rhs) {
      cout <<"Call Move Assignment Operator for Template Derived Class"<< endl;
      if (this != &rhs) {
         Base<T1>::operator=(move(rhs));
         delete [] string2;

         string2 = rhs.string2;
         length2 = rhs.length2;

         rhs.string2 = nullptr;
         rhs.length2 = 0;
      }
      return *this;
   }

   ~Derived() {
        cout <<"Call Desstructor for Template Derived --->> Normal Base "<< endl;
        // ~Base<T1>::Base();
        delete[] string2;
   }

 private :
   char * string2;
   int    length2;
};


int main(int argc, char * argv[]) {
#if 1
    // Here we Check for Copy Const and  Assignment Operator
    Derived<char> obj1("pallav1", "puneet1");
    Derived<char> obj2("pallav2", "puneet2");
    Derived<char> obj3(obj2);
    obj3 = obj1;
#endif 

#if 1
    // Here we Check for Move Const and Move Assignment Operator
    Derived<char> obj11("pallav1", "puneet1");
    Derived<char> obj22("pallav2", "puneet2");
    Derived<char> obj33(move(obj22));
    obj33 = move(obj11);
#endif 

    return 0;
};

