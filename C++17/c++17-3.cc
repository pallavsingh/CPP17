#include <iostream>
#include <string>
#include <map>
#include <cassert>
#include <any>
#include <variant>
#include <algorithm>

using namespace std;

void  mapTryEmplace();
void  mapInsertOrAssign();

int main(int argc, char *argv[]) 
{
    // Non-constant string::data
    // C++17 string has the data() method, which 
    //       --- returns a non-constant pointer to internal string data:
    string str = "hello";
    char * p = str.data();
    p[0] = 'H';
    cout << str << '\n'; // Hello


    // An object of std::any class can store any type of information. 
    // Thus, the same variable of std::any type can first store int, then float, and then a string.
    any a = 42;
    cout << "Type : " << a.type().name() << "  value : "  << any_cast<int>(a) << endl;

    a = 11.34f;
    cout << "Type : " << a.type().name() << "  value : "  << any_cast<float>(a) << endl;

    a = string("Hello"); 
    cout << "Type : " << a.type().name() << "  value : "  << any_cast<string>(a) << endl;


    // stores either int, or float or char.
    variant<int, float, char> v;
    v = 42;
    cout << "get<int> from variant : "  << get<int>(v) << endl;
 // cout << get<float>(v); // std::bad_variant_access
 // cout << std::get<char>(v);  // std::bad_variant_access
    v = 3.14f;
    cout << "get<float> from variant : "  << get<float>(v) << endl;
    v = 'P';
    cout << "get<char> from variant : "  << get<char>(v) << endl;
    // cout << "get<int> from variant"  << get<double>(v) << endl; // compile-error

   // std::get_if function, which takes a pointer to std::variant and returns a pointer 
   // to the current value, if the type was specified correctly, or, otherwise, nullptr
    variant<int, float, char> v1;
    v1 = 42;
    auto ptr = get_if<int>(&v1);
    if (ptr != nullptr) {
       cout << "get_if<int>(&v1) value: " << *ptr << endl; // int value: 42
    }


    // more convenient way of working with std::variant is std::visit:
    visit([](auto& arg) {
             using Type = std::decay_t<decltype(arg)>;
             if constexpr (std::is_same_v<Type, int>){
                 cout << "int value: " << arg << '\n';
             }
             else if constexpr (std::is_same_v<Type, float>)
             {
                cout << "float value: " << arg << '\n';
             }
             else if constexpr (std::is_same_v<Type, char>)
             {
                cout << "char value: " << arg << '\n';
             }
         }, v);

     mapTryEmplace();
     mapInsertOrAssign();

     return 0;
}


// Unlike emplace, try_emplace function doesn't 'steal' move-only argument 
// in a case where the insertion of the element didn't occur.
void mapTryEmplace()
{
  string s1("hello");
  map<int, string> myMap;
  myMap.emplace(1, "aaa");
  myMap.emplace(2, "bbb");
  myMap.emplace(3, "ccc");

  // cout << s1.empty() << '\n'; // 0
  // myMap.emplace(3, std::move(s1));
  // cout << s1.empty() << '\n'; // 1

  // cout << s1.empty() << '\n'; // 0
  // myMap.try_emplace(3, std::move(s1));
  // cout << s1.empty() << '\n'; // 0

  cout << s1.empty() << '\n'; // 0
  myMap.try_emplace(4, move(s1));
  cout << s1.empty() << '\n'; // 1

  return;
}


void mapInsertOrAssign()
{
  map<int, string> m;
  m.emplace(1, "aaa");
  m.emplace(2, "bbb");
  m.emplace(3, "ccc");

  auto[iter, retval] = m.insert_or_assign(3, "ddd");
  if (retval == true){
      cout << "key value pair was inserted successfully" << endl; 
  } else {
      cout << "Value got assigned successfully" << endl; 
  }

  auto[iter1, retval1] = m.insert_or_assign(4, "eee");
  if (retval1 == true){
      cout << "key value pair was inserted successfully" << endl; 
  } else {
      cout << "Value got assigned successfully" << endl; 
  }

  return;
}
