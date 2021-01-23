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

/////////////////////////////////////////////////////////////////////////////

namespace aligned {
   namespace details {
       /// Deleter for single object in aligned memory, used by aligned::unique_ptr
       template <class T> struct Deleter {
         void operator()(T *data) const {
             // Single object, was created by placement-new => destruct explicitly
             data->~T();
             free(data);
             }
       };

       /// Specialization of Deleter for array of objects, used by aligned::unique_ptr
       template <class T> struct Deleter<T[]> {
          void operator()(T *data) const {
             free(data);
          }
};

/// Allocation function for aligned memory, used by aligned::make_unique
template <typename T, std::size_t alignment>
inline typename std::remove_extent<T>::type *alloc(std::size_t num) {
      // Ensure minimum alignment for given type
      std::size_t align = std::max(std::alignment_of<T>::value, alignment);
      // If T is an array type, we remove the "[]"
      using TYPE = typename std::remove_extent<T>::type;
      TYPE *mem = 0;

      int error = posix_memalign((void **)&mem, align, sizeof(TYPE) * num);
      if (error == EINVAL)
          throw std::logic_error("Error: Alignment must be a power of two (posix_memalign returned EINVAL)");
      else if (error != 0)
          throw std::bad_alloc();

      return mem;
}

/// Default alignment is set to 64 Byte, i.e., the most common cache-line size.
constexpr std::size_t default_alignment = 64;

} // namespace details

/// Typedef providing aligned::unique_ptr
template <class T> using unique_ptr = std::unique_ptr<T, details::Deleter<T>>;

/// For internal use only!
namespace details {
     template <typename T> struct MakeUniq { typedef unique_ptr<T> single_object; };
     template <typename T> struct MakeUniq<T[]> { typedef unique_ptr<T[]> array; };
     template <typename T, std::size_t Bound> struct MakeUniq<T[Bound]> {
         struct invalid_type {};
     };
} // namespace details

/// aligned::make_unique for single objects
template <typename T, std::size_t alignment = details::default_alignment, typename... Args>
inline typename details::MakeUniq<T>::single_object make_unique(Args &&... args) {
  // Placement-new into aligned memory
  // We use constructor with "{}" to prevent narrowing
  return unique_ptr<T>(new (details::alloc<T, alignment>(1))
                           T{std::forward<Args>(args)...});
}

/// aligned::make_unique for arrays of unknown bound
template <typename T, std::size_t alignment = details::default_alignment>
inline typename details::MakeUniq<T>::array make_unique(std::size_t num) {
  // We are not using "new", which would prevent allocation of
  // non-default-constructible types, so we need to verify explicitly
  static_assert(std::is_default_constructible< typename std::remove_extent<T>::type>::value,
                "Error: aligned::make_unique<T[]> supports only default-constructible types");
  static_assert(std::is_pod< typename std::remove_extent<T>::type>::value,
                "Error: aligned::make_unique<T[]> supports only pod types");
  return unique_ptr<T>(details::alloc<T, alignment>(num));
}

/// Disable aligned::make_unique for arrays of known bound
template <typename T, typename... Args>
inline typename details::MakeUniq<T>::invalid_type
make_unique(Args &&...) = delete;

} // namespace aligned


////////////////////////////////////////////////////////////////////////////

struct Foo {
  Foo(int x, int y) : x(x), y(y){};
  int x;
  int y;
};

////////////////////////////////////////////////////////////////////////////

int main() {

  // Single object
  auto x = aligned::make_unique<double>(16.0);

  // Forbidden thanks to "{}" --- did the user want to write
  // aligned::make_unique<double[]>(16)?
  // auto x = aligned::make_unique<double>(16);
  auto foo = aligned::make_unique<Foo>(3, 4);

  // Array
  auto y = aligned::make_unique<double[]>(16);

  // Disabled for arrays of known bounds:
  // auto y = aligned::make_unique<double[16]>(16);

  // Forbidden --- there is no default constructor:
  // auto foo = aligned::make_unique<Foo[]>(16);

  // Forbidden --- calling constructor & destructors on each array element is
  // not implemented:
  // auto s = aligned::make_unique<std::string[]>(16);
}
