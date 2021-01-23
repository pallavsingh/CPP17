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

int main(int argc, char * argv[]) {
    const int ci = 42;
    auto func1 = [ci]() mutable { std::cout << "Value of ci : " << ci << '\n'; };
    func1();      // prints 42

    const int cii = 42;
    auto func2 = [cii]() mutable { std::cout << "Value of ++cii : "<< ++cii << '\n'; };  
    func2();   
    // error! can't modify copy of ci that's in f

    const int ciii = 42;
    auto func3 = [ciii = ciii]() mutable { std::cout << "Value of ++cii : Capture by copy : "  << ++cii << '\n'; };      
    func3();   

    const int ciiii = 42;
    auto f1 = [=]() mutable { std::cout << "Value of ciiii : "<< ++ciiii << '\n'; };   
    auto f2 = [ciiii]() mutable { std::cout << "Value of ++ciiii : " << ++ciiii << '\n'; }; 
    auto f3 = [ciiii = ciiii]() mutable { std::cout << "Value of ++ciiii : Capture by copy " << ++ciiii << '\n'; }; 

    f1();   
    f2();   
    f3();   

     return 0;
}
