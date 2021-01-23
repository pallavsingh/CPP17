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
#include "PimpleIdom-UniquePtr.h"

// Boost Library Hearders
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

class  Widget::Impl {
      string name;
      vector<double> data;
};

Widget::Widget() : pImpl(std::make_unique<Impl>()) { 
    cout <<"Constructor for widget  : " << endl; 
}


Widget::~Widget() = default; 
Widget::Widget(Widget && rhs) = default; 
Widget & Widget::operator=(Widget && rhs) = default; 

Widget::Widget(const Widget & rhs) : pImpl(std::make_unique<Impl>()) { }
Widget & Widget::operator=(const Widget & rhs) {
   *pImpl = *rhs.pImpl;
   return *this;
}

int main(int argc, char * argv[]) {
    return 0;
}
