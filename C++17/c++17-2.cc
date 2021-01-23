#include <iostream>
#include <string>
#include <cassert>
#include <mutex>
#include <atomic>
#include <vector>
#include <list>
#include <set>
#include <map>

using namespace std;

//  https://www.viva64.com/en/b/0533/#ID0EPFCM

/****************************************************************
pack is an expression containing an undisclosed parameter pack
init - initial value

(pack op ...)  A unary right associative fold
(... op pack)  A unary left associative fold
(pack op ... op init) A binary right associative fold
(init op ... op pack) A binary left associative fold

op are binary operators:
    + - * / % ^ & | ~ = < > << >> += -= *= /= %=
    ^= &= |= <<= >>= == != <= >= && || , .* ->*

****************************************************************/

// C++17
template<typename... Args>
auto Sum1(Args... args) {
     return (args + ...);
}

// C++17
template<typename... Args>
auto Sum2(Args... args){
     return (args + ... + 100);
}

//C++14 Recursion
auto Sum3(){
     return 0;
}

template<typename Arg, typename... Args>
auto Sum3(Arg first, Args... rest) {
     return first + Sum3(rest...);
}

//////////////////////////////////////////////////////////////

// C++17 : Lambda are allowed inside constexpr Functions
constexpr int Func(int x)
{
   auto f = [x]() { return x * x; };
   return x + f();
}

// Inline Variable has been Supported Now
inline int MyVar = 4 + 2 + 1;
    
// decomposition of types that contain only non-static public members
struct S
{
  char x{ 'c' };
  int y{ 42 };
  double z{ 3.14 };
};

[[nodiscard]]int structuredBinding() {
    // structured binding can be used with arrays
    [[maybe_unused]]int arr[] = { 1, 2, 3, 4 };
    auto[a, b, c, d] = arr;
   
    std::cout << a << b << c << d << '\n';

    S s;
    auto[a1, b1, c1] = s;
    std::cout << a1 << ' ' << b1 << ' ' << c1 << ' ' << '\n';

    return 0;
}

// structured binding is its usage in range-based loops
[[nodiscard]]int structuredBinding1() {
   
    map<int, string> myMap;
    myMap.insert(make_pair(1, "Arnav1"));
    myMap.insert(make_pair(2, "Arnav2"));
    myMap.insert(make_pair(3, "Arnav3"));
    myMap.insert(make_pair(4, "Arnav4"));
    myMap.insert(make_pair(5, "Arnav5"));

    if (auto[iter, retval] = myMap.insert({ 6, "hello" }); retval) {
        cout << "key: auto[iter, retval]  " << iter->first << ' ' 
	     << "value: auto[iter, retval] :" << iter->second << endl;
    }

    for(const auto &[key, value] : myMap)
        cout << "key: " << key << ' ' << "value: " << value << endl;

    return 0;
}

// C++17 gives us the ability to perform compile-time conditional branching
template <typename T>
auto GetValue(T t){
   if constexpr (std::is_pointer<T>::value) {
      return *t;
   } else {
      return t;
   }
}


// C++14
template<typename T>
typename std::enable_if<std::is_pointer<T>::value, std::remove_pointer_t<T>>::type
GetValueX(T t) {
  return *t;
}

template<typename T>
typename std::enable_if<!std::is_pointer<T>::value, T>::type 
GetValueX(T t) {
  return t;
}



int main(int argc, char *argv[])
{
    [[maybe_unused]]auto retval  = structuredBinding();
    [[maybe_unused]]auto retval1 = structuredBinding1();

    constexpr int retval2 = Func(10);
    static_assert(retval2 == 110);

    // C++17 Style
    int v = 10;
    cout << "GetValue : " << GetValue(v)  << endl; // 10
    cout << "GetValue : " << GetValue(&v) << endl; // 10

    // C++14 Style
    cout << "GetValueX : " << GetValueX(v)  << endl; // 10
    cout << "GetValueX : " << GetValueX(&v) << endl; // 10

    cout << "Sum1 :  " << Sum1(1, 2, 3, 4, 5) << endl; // 15
    cout << "Sum2 :  " << Sum2(1, 2, 3, 4, 5) << endl; // 115
    cout << "Sum3 :  " << Sum3(1, 2, 3, 4, 5) << endl; // 15

    return 0;

}

