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

class Base {
   public :
    Base (char * str1) {
         cout <<"Call Constructor for Normal Base Class : Base "<< endl;
         length1 = strlen(str1);
         string1 = new char[length1 + 1]; 
         strcpy(string1, str1);
         string1[length1 + 1] = '\0';
    }

    Base (const Base & rhs)  {
         cout <<"Call Constructor for Normal Base Class : Base "<< endl;
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
         delete [] string1;

         length1 = rhs.length1;
         string1 = new char[length1 + 1];
         strcpy(string1, rhs.string1);
         string1[length1 + 1] = '\0';
      }
      return *this;
   }

   Base & operator=(Base && rhs){
      cout <<"Call Move Assignment Operator for Normal Base Class : Base "<< endl;
      if (this != &rhs) {
         delete [] string1;
         
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
   char * string1;
   size_t length1;
};


template<typename T>
class Derived : public Base {
public :
   Derived (char * str1, T * str2) : Base(str1) {
       cout <<"Call Constructor for Template Derived --->> Normal Base "<< endl;
       length2 = strlen(str2);
       string2 = new char[length2 + 1]; 
       strcpy(string2, str2);
       string2[length2 + 1] = '\0';
   }

   Derived (const Derived & rhs): Base(rhs) {
       cout <<"Call Copy Constructor for Template Derived --->> Normal Base "<< endl;
       length2 = rhs.length2;
       string2 = new char[length2 + 1]; 
       strcpy(string2, rhs.string2);
       string2[length2 + 1] = '\0';
   }

   Derived (Derived && rhs): Base(move(rhs)) {
       cout <<"Call Move Constructor for Template Derived --->> Normal Base"<< endl;
       string2 = rhs.string2; 
       length2 = rhs.length2;
       rhs.string2 = nullptr;
       rhs.length2 = 0;
   }

   Derived & operator=(const Derived & rhs) {
      cout <<"Call Assignment Operator for Template Derived Class"<< endl;
      if (this != &rhs) {
         Base::operator=(rhs);
         delete [] string2;

         length2 = rhs.length2;
         string2 = new char[length2 + 1];
         strcpy(string2, rhs.string2);
         string2[length2 + 1] = '\0';
      }
      return *this;
   }

   Derived & operator=(Derived && rhs) {
      cout <<"Call Move Assignment Operator for Template Derived Class"<< endl;
      if (this != &rhs) {
         Base::operator=(move(rhs));
         delete [] string2;

         string2 = rhs.length2;
         length2 = rhs.length2;

         rhs.string2 = nullptr ;
         rhs.length2 = 0;
      }
      return *this;
   }

   ~Derived() {
        cout <<"Call Desstructor for Template Derived --->> Normal Base "<< endl;
        ~Base::Base();
        delete[] string2;
   }

 private :
   T * string2;
   int length2;
};


int main(int argc, char * argv[]) {
    Derived<char> obj1("pallav", "puneet");

    return 0;
};

