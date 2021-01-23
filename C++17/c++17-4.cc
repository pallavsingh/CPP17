#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cassert>
#include <any>
#include <variant>
#include <algorithm>
#include <functional>
#include <tuple>
#include <type_traits>
#include <memory>
#include <mutex>
#include <thread>

using namespace std;

int Func(int a, int b){
    return a + b;
}

struct comp {
  void operator() (int a) {
       cout << "Functor invoked : " << a << '\n';
  }
};

void func1(char x, int y, double z){
     cout << "value of x : " << x << "  " 
	  << "value of y : " << y << "  "
	  << "value of z : " << z << endl;
}

struct S {
    char    m_x;
    int     m_y;
    double  m_z;
    S(char x, int y, double z) : m_x(x), m_y(y), m_z(z) {}
};


void mapNodeHandle(){
     // Access to containers nodes (Node handle)
     // In C++17, you can now move a node directly from one container to another

     map<int, string> myMap1{{ 1, "aa" },
			     { 2, "bb" },
			     { 3, "cc" }};

     map<int, string> myMap2{{ 4, "dd" },
			     { 5, "ee" },
			     { 6, "ff" }};

     auto node = myMap1.extract(2);
     myMap2.insert(std::move(node));
 
     // myMap1: {{1, "aa"}, {3, "cc"}}
     // myMap2: {{2, "bb"}, {4, "dd"}, {5, "ee"}, {6, "ff"}}
     return;
}

void  mapMerge()
{
   map<int, string> myMap1{{1, "aa"},
			   {2, "bb"},
		           {3, "cc"}};
                                     
   map<int, string> myMap2{{4, "dd"},
			   {5, "ee"},
			   {6, "ff"}};

   myMap1.merge(myMap2);
   // myMap1: { {1, "aa"},
   //           {2, "bb"},
   //           {3, "cc"},
   //           {4, "dd"},
   //           {5, "ee"},
   //           {6, "ff"} }
   // myMap2: {}

   return;
}

int mapKeyChange()
{
   map<int, string> myMap{{1, "Tommy"},
			  {2, "Peter" },
                          {3, "Andrew"}};

  auto node = myMap.extract(2);
  node.key() = 42;
  myMap.insert(std::move(node));

  // myMap: {{1, "Tommy"}, {42, "Peter"}, {3, "Andrew"}};

  return 0;
}

// std::shared_ptr for arrays
int sharedPtrArrays()
{
  // C++14  : std::shared_ptr<int[]> arr(new int[7],
  //  std::default_delete<int[]>());

  // C++17
  shared_ptr<int[]> arr(new int[7]);

  arr.get()[0] = 1;
  arr.get()[1] = 2;
  arr.get()[2] = 3;

  return 0;
}


int var;
mutex varMtx;

/******************************************************************

LOCK_GUARD VS SCOPED_LOCK diff.

The single and important difference is that std::scoped_lock has a variadic constructor taking more than one mutex. 
This allows to lock multiple mutexes in a deadlock avoiding way as if std::lock was used.
     std::scoped_lock<std::mutex, std::mutex> lock(mutex1, mutex2);

*********************************************************************/     

void ThreadFunc() {
   scoped_lock lck { varMtx };
   var++;
   cout << this_thread::get_id() << " : " << var << endl;
} // <= varMtx automatically frees when exiting block

///////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
  thread t1(ThreadFunc);
  thread t2(ThreadFunc);

  t1.join();
  t2.join();

  sharedPtrArrays();

   // static_assert ( constant-expression ) ;
   // static_assert ( constant-expression , string-literal ) 
   constexpr int arg = 42;
   static_assert(arg == 42, "arg must be equal to 42");
   static_assert(arg == 42); // Now you write like this

   // Access to containers nodes (Node handle)
   // In C++17, you can now move a node directly from one container to another. 
   //    --- There is no additional allocations or copying occur
    mapNodeHandle();
    mapMerge();
    mapKeyChange();


    tuple args{ 'c', 42, 3.14 };
    apply(func1, args);

    cout << std::invoke(Func, 10, 20) << '\n'; // 30
    invoke(comp(), 42); // 42
    invoke([]() { cout << "Lambda Function invoked \n";}); 

    tuple args1{ 'c', 42, 3.14 };
    S s = make_from_tuple<S>(args1);
    cout << "value of s.m_x : " << s.m_x << " " 
         << "value of s.m_y : " << s.m_y << " "
         << "value of s.m_z : " << s.m_z << '\n';

   // std::not_fn (Universal negator not_fn)
   // In C++17, there is now a std::not_fn function that returns a predicate-negation
    vector vct = { 1, 6, 3, 8, 14, 42, 2 };
    auto n = count_if(vct.begin(), vct.end(), not_fn([](int a){ return a < 10; }));
    cout << "value of n : " << n << endl;


#if 0
    vector<int> myvec = {1, 2, 3, 4, 5};	
    for (const auto & x : myvec)
	 cout << "value : " << x << endl;

    for_each(std::execution::par, myvec.begin(), myvec.end(), [](auto &e) { 
		                                                    e += 42; 
								    });
    cout << "..........................................." << endl;
    for (const auto & x : myvec)
	 cout << "value ater 42 addition : " << x << endl;
#endif

    return 0;
}

