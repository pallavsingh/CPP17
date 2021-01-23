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
#include <string.h>
#include <algorithm>
#include <iterator>
#include <unordered_map>
// Boost Library Hearders
#include <boost/type_index.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/assert.hpp>

using  namespace boost::mpl; // brings boost::mpl:: in scope
using  namespace std;
using  boost::typeindex::type_id_with_cvr;

///////////////// Example of Numeric Computation //////////////////
template <unsigned int N>
struct factorial{
   enum { value =  N * factorial<N - 1>::value };
};

template < >
struct factorial<1> {
   enum { value = 1 };
};

////////////////  Example of Type Computation //////////////////////
template <typename T>
struct permutation_holder {
  typedef T type[1][1];
};

template <typename T, unsigned  N>
struct permutation_holder <T[N]> {
  typedef T type[factorial<N>::value][N];
};

//////////////////////// Example of Type Sequences /////////////////
// C++ provide NO way to know the Members at Compile Time 
struct types {
   int  t1;
   long t2;
   vector<double> t3;

};

template <typename First, typename Rest>
struct cons {
   typedef First  first;
   typedef Rest   rest;
};

struct nil {};

typedef cons< int, cons< long, cons<vector<double>, nil> > > my_types;

template<typename T1, typename T2, bool choose1 = (sizeof(T1) > sizeof(T2))>
struct choose_larger {typedef T1 type; };
template<typename T1, typename T2> 
struct choose_larger<T1, T2, false> {
   typedef T2 type;
};
template<typename T>
struct largest;

template<typename First, typename Rest>
struct largest < cons<First, Rest> > : choose_larger<First, typename largest<Rest>::type > {
   // Type Inherited from Base.
};

template <typename First>
struct largest< cons<First, nil> > {
   typedef First type;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct wrapper { T x; };

template <typename T>
wrapper<typename permutation_holder<T>::type>
all_permutations(T const & in) {
   wrapper<typename permutation_holder<T>::type> result;
   unsigned const N = sizeof(T) / sizeof(**result.x);
   copy(&*in, &*in + N, result.x[0]);

   unsigned const result_size = sizeof(result.x) / sizeof(T);

   for (T * dst = result.x + 1; dst != result.x + result_size; ++dst){
       T * src = dst - 1;
       copy(*src, *src + N, *dst);
       next_permutation(*dst, *dst + N);
   }
   return result;
}

//////////////////////////////////////////////////////////////////////////////////

typedef  if_ <true_,  char, long>::type t1;
typedef  if_ <false_, char, long>::type t2;

BOOST_MPL_ASSERT((is_same< t1, char>));
BOOST_MPL_ASSERT((is_same< t2, long>));

//////////////////////////////////////////////////////////////////////////////////

#if 0
namespace aux {
   template<typename T>
   struct element_type { typedef typename T::element_type type; };

   template<typename T>
   struct pointed_type {
      private :
      typedef typename if_ < is_pointer<T> ,
                             remove_pointer<T>,
                             aux::element_type<T>
                           >::type_func_;
      public:
      typedef typename func_::type type;
   };
}
#endif

//////////////////////////////////////////////////////////////////////////////////

template<typename T1, typename T2>
struct derive {
   struct type : T1, T2 { };
};

template< >
struct derive<void, void> {
   typedef  int type;
};

//////////////////////////////////////////////////////////////////////////////////

template <template <typename, typename> class F,
          typename T1,
          typename T2,
          typename T3
         >

struct apply_twice {
   typedef typename F<T1, typename F<T2, T3>::type>::type type;
};

template<typename T1, typename T2, typename T3>
struct derive3: apply_twice<derive, T1, T2, T3> { };

template< template<typename, typename> class F>
struct compose_self {
    template <typename T1, typename T2, typename T3>
       struct type : apply_twice<F, T1, T2, T3> { };
};

//////////////////////////////////////////////////////////////////////////////////

struct derive1 {
   template <typename N1, typename N2>
   struct apply {
      struct type : N1, N2 { };
   };
};

template <typename T>
T add(T x, T y) { return x + y; }

struct add {
    template <typename T>
    T operator() (T x, T y) { return x + y; }
};

//////////////////////////////////////////////////////////////////////////////////

template <typename TinyList, long Pos>
struct tiny_list_item;

template <typename TinyList, long Pos>
struct tiny_list_iterator {
   typedef typename tiny_list_item<TinyList, Pos>::type type;
   typedef tiny_list_iterator<TinyList, Pos - 1> prior;
   typedef tiny_list_iterator<TinyList, Pos + 1> next;
};

template<typename T0, typename T1, typename T2>
struct tiny_list {
   typedef tiny_list_iterator<tiny_list, 0> begin;
   typedef tiny_list_iterator<tiny_list, 3> end;
   typedef T0 type0;
   typedef T1 type1;
   typedef T2 type2;
};

template<typename TinyList>
struct tiny_list_item<TinyList, 0> {
   typedef typename TinyList::type0 type; 
};

template<typename TinyList>
struct tiny_list_item<TinyList, 1> {
   typedef typename TinyList::type1 type; 
};

template<typename TinyList>
struct tiny_list_item<TinyList, 2> {
   typedef typename TinyList::type2 type; 
};

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char * argv[]) {
    constexpr int i =  factorial<5>::value; 

    cout <<"Output of i = " << i << endl;
    cout << " Value of typeid(largest<my_types>::type).name() :: " << typeid(largest<my_types>::type).name() << endl;

    return 0;
};

