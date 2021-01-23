// C++14 Hearders
#include <iostream>
#include <memory>
#include <atomic>
#include <mutex>
#include <initializer_list>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <list>
#include <string>
#include <unordered_map>

// Boost Library Hearders
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

// 1. ALways use scope enums. as they are enclosed under scope , use Scope Resolution Operator 
// 2. Use statis_cast for typeconversion. It donot offer Implicit Casts

//C++98 Style : Name used inside enum cannot be used again in same scope
namespace arnav1 {
   enum Color98 {black, white, red};
   // auto white = false;
}

//C++11 Style : Name used inside enum can be used again in same scope
namespace arnav2 {
   enum class Color {black, white, red};
   auto white = false;
   // Color c1 = white; -- Cannot convert bool to Color type
   Color c2 = Color::white;
   auto  c3 = Color::white;
}

// C++11 allow fwd-decleration of scoped enums as compared to unscoped in C++98
//enum Color1;
enum class Color2;

// How complier choose Type for Enums

enum class Status1;                 // Here underline type is int
enum class Status2: std::uint32_t;  // Here underline type is uint32
enum class Status3: std::uint8_t;   // Here underline type is uint8
enum class Status4: std::uint32_t {
    good = 0,
    failed = 1,
    incomplete = 100,
    corrupt = 200,
    audited = 500,
    indeterminate = 0xFFFFFF
};


int main(int argc, char * argv[]) {
  // if (arnav2::c2 < 14.5) {cout <<"Failed to compare enum to double" << endl; }
  if (static_cast<double>(arnav2::c2) < 14.5) {cout <<"use Static_cast : Compare enum to double" << endl; }

  return 0;
}

