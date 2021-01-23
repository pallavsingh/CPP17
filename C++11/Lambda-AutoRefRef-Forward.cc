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
    auto func1 = [] (auto x) { 
                        return func(normalize(x)); 
                    };

    auto func2 = [] (auto && param) {
                        return func(normalize(forward<decltype(param)>(param)));
                    };

    auto func3 = [] (auto &&... param) {
                        return func(normalize(forward<decltype(param)>(param)...));
                    };


   return 0;
}
