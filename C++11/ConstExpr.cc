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
#include <unordered_map>

// Boost Library Hearders
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;


namespace Arnav1 {
#if 0
  int sz;
  constexpr auto arraySize1 = sz; // Its an Error as sz's Value is not Know at Compile Time.
  array<int, sz> data1;

  const     auto arraySize3 = sz;
  array<int, arraySize3> data3;
#endif

  constexpr auto arraySize2 = 10;
  array<int, arraySize2> data2;
}

namespace Arnav2 {
   class Point {
     public :
       constexpr Point(double xVal = 0, double yVal = 0) noexcept 
                 :x(xVal), y(yVal) {}
       constexpr double xValue() const noexcept { return x; }
       constexpr double yValue() const noexcept { return y; }

       constexpr void setX(double newX) noexcept { x = newX; }
       constexpr void setY(double newY) noexcept { y = newY; }

     private:
       double x, y;
   };

   constexpr Point midpoint(const Point & p1, const Point & p2) noexcept {
       return {(p1.xValue() + p2.xValue()) / 2,
               (p2.yValue() + p2.yValue()) / 2 };
   }

   constexpr Point reflection(const Point & p) noexcept {
       Point result{10, 10};

       result.setX(-p.xValue());   
       result.setY(-p.yValue());   

       return result;
   }

}

int main(int argc, char * argv[]) {
  using namespace Arnav1;
  using namespace Arnav2;

  constexpr Point p1(9.4, 27.7);
  constexpr Point p2(28.8, 5.3);

  constexpr auto mid = midpoint(p1, p2);

  constexpr auto reflectionmid = reflection(mid);

  return 0;
}

