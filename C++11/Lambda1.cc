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

    int  int_var_copy = 42;
    auto lambdafunc_passbycopy = [int_var_copy]() {
                    cout << "This lambda has a copy of int_var when created: " << int_var_copy << endl;
                };

    for (int i = 0; i < 3; i++) {
         int_var_copy++;
         lambdafunc_passbycopy();
    }

    int  int_var_ref = 42;
    auto lambdafunc_passbyref = [&int_var_ref] () {
                     cout << "This lambda captures int_var by reference: " << int_var_ref << endl;
                 };

    for (int i = 0; i < 3; i++) {
         int_var_ref++;
         lambdafunc_passbyref();
    }

///////////////////////////////////////////////////////////////////////////////////////////////

    // generic lambda, operator() is a template with two parameters
    auto glambda = [](auto a, auto&& b) { return a < b; };
    bool b1 = glambda(3, 3.14); // ok
 
    // generic lambda, operator() is a template with one parameter
    auto vglambda = [](auto printer) {
         return [=](auto&&... ts) {
            // generic lambda, ts is a parameter pack
            printer(std::forward<decltype(ts)>(ts)...);
            return [=] { printer(ts...); }; // nullary lambda (takes no parameters)
         };
    };

    auto p = vglambda([](auto v1, auto v2, auto v3) { std::cout << v1 << v2 << v3; });
    auto q = p(1, 'a', 3.14); // outputs 1a3.14
    q();                      // outputs 1a3.14

//////////////////////////////////////////////////////////////////////////////////////////////////

    int a = 1, b = 1, c = 1;

    auto m1 = [a, &b, &c]() mutable {
        auto m2 = [a, b, &c]() mutable {
             std::cout << a << b << c << '\n';
             a = 4; b = 4; c = 4;
        };
 
        a = 3; b = 3; c = 3;
        m2();
    };

    a = 2; b = 2; c = 2;
    m1();              

    std::cout << a << b << c << '\n'; 

////////////////////////////////////////////////////////////////////////////////////////////////////

    std::vector<int> param = {1, 2, 3, 4, 5, 6, 7};
    int x = 5;
    param.erase(std::remove_if(param.begin(), param.end(), [x](int n) { return n < x; }), param.end());
 
    std::cout << "param : ";
    std::for_each(param.begin(), param.end(), [](int i){ std::cout << i << ' '; });
    std::cout << '\n';
 
    // the type of a closure cannot be named, but can be inferred with auto
    auto func1 = [](int i) { return i + 4; };
    std::cout << "func1 : " << func1(6) << '\n';
 
    // like all callable objects, closures can be captured in std::function
    // (this may incur unnecessary overhead)
    std::function<int(int)> func2 = [](int i) { return i + 4; };
    std::cout << "func2 : " << func2(6) << '\n';

    return 0;
}
