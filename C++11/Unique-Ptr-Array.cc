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
#include <algorithm>
#include <iterator>
#include <unordered_map>

// Boost Library Hearders
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

////////////////////////////////////////////////////////////////////

//	unique_ptr
//	Case 1:	Array of type
//	Case 2:	Array of pointer to type

class Bar {
   public:
     Bar(float b) : bb(b) {
	std::cout << "Bar" << std::endl;
     }
    ~Bar() {
        std::cout << "~Bar" << std::endl;
     }

     float bb;
};

int main() {
	// Case 1
	std::unique_ptr<int []> foo(new int[10]);
	for (int i = 0; i < 10; ++i) {
  	     foo[i] = i*i;
	}

	for (int i = 0; i < 10; ++i) {
	     std::cout << "foo[" << i << "] = " << foo[i] << std::endl;
	}
	
	// Case 2 : Bar** boo = new Bar* [10]
	std::unique_ptr<Bar* [], void(*)(Bar**)> boo(new Bar*[10], [](Bar** boo_ptr) {
	     for(int i = 0; i < 10; ++i) {
	 	 delete boo_ptr[i];
	     }
	     delete [] boo_ptr;
	});
	
	for(int i = 0; i < 10; ++i) {
	    boo[i] = new Bar(i * 0.5f);
	}

	for(int i = 0; i < 10; ++i) {
	    std::cout << "bar[" << i << "] = " << boo[i]->bb << std::endl;
	}

	return 0;
}
