// C++14 Hearders
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

using namespace std;
using boost::typeindex::type_id_with_cvr;

class  Widget {
   public :
       Widget();
      ~Widget();

       Widget(Widget && rhs);
       Widget & operator=(Widget && rhs);

       Widget(const Widget & rhs);
       Widget & operator=(const Widget & rhs);

   private :
      struct Impl;
      // Impl * pImpl;
      unique_ptr<Impl> pImpl;
};

