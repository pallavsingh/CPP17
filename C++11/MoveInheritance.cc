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

using  namespace std;
using  boost::typeindex::type_id_with_cvr;

class Base {
public:
    explicit Base(char * str = "Base default")  : mData1(str), mLength1(strlen(str)){}
    Base(const Base & rhs) : mData1(rhs.mData1) , mLength1(rhs.mLength1) {
	 std::cout << "Base (const Base &).  = " << std::endl;
    }

    Base (Base && rhs) : mData1(rhs.mData1), mLength1(rhs.mLength1) {
        std::cout << "Base (Base &&) ::  Moving resource.\n";
        rhs.mData1   =  NULL;
        rhs.mLength1 =  0;
    }

    ~Base() { 
	if (mData1 != NULL) {
	    delete[] mData1; 
	}
    }

    Base & operator=(const Base & rhs) {
	std::cout << "Base Assignement operator=(const Base &). length1 = " << std::endl;
	if (this != &rhs) {
	    delete[] mData1; 
	    mLength1 = rhs.mLength1;
            mData1   = new char[mLength1 + 1];
            strcpy(mData1, rhs.mData1);
            mData1[mLength1 + 1] = '\0';
	}
	return *this;
    }


    Base & operator=(Base && rhs) {
        std::cout << "operator=(Base &&). length1 = " << std::endl;
        if (this != &rhs) {
          delete[] mData1;
          mData1         = rhs.mData1;
          mLength1       = rhs.mLength1;
          rhs.mData1   = NULL;
          rhs.mLength1 = 0;
       }
       return *this;
    }

    size_t Length() const { return mLength1; }

private:
    size_t   mLength1; 
    char *   mData1;  
};


class Derived : public Base {
public:
    explicit Derived (char * strderived = "Derived default")  : mData2(strderived), mLength2(strlen(strderived)){}
    Derived(const Derived & rhs) : Base(rhs), mData2(rhs.mData2) , mLength2(rhs.mLength2) {
	 std::cout << "Derived (const Derived &).  = " << std::endl;
    }

    Derived (Derived && rhs) : Base(move(rhs)), mData2(rhs.mData2), mLength2(rhs.mLength2) {
        std::cout << "Derived (Derived &&) ::  Moving resource.\n";
        rhs.mData2   =  NULL;
        rhs.mLength2 =  0;
    }

    ~Derived() { 
	if (mData2 != NULL) {
	    delete [] mData2; 
	}
    }

    Derived & operator=(const Derived & rhs) {
	std::cout << "Derived Assignement operator=(const Derived &). length1 = " << std::endl;
	if (this != &rhs) {
	    delete[] mData2; 
	    mLength2 = rhs.mLength2;
            mData2   = new char[mLength2];
            strcpy(mData2, rhs.mData2);
            mData2[mLength2 + 1] = '\0';
	}
	return *this;
    }


    Derived & operator=(Derived && rhs) {
        std::cout << "operator=(Base &&). length1 = " << std::endl;
        if (this != &rhs) {
          delete[] mData2;
          mData2         = rhs.mData2;
          mLength2       = rhs.mLength2;
          rhs.mData2     = NULL;
          rhs.mLength2   = 0;
       }
       return *this;
    }

    size_t Length() const { return mLength2; }

private:
    size_t   mLength2; 
    char *   mData2;  
};



/////////////////////////////////////////////////////////////////////////

int main(int argc, char * argv[]) {

     return 0;
}
