#include <iostream>
#include <cassert>
#include <mutex>
#include <atomic>
#include <vector>
#include <list>
#include <set>
#include <map>

using namespace std;

int  keywords1(int i);
int  ifSwitchVarInit();

static int  unsedFunc2(long i);
[[maybe_unused]] static int  unsedFunc1([[maybe_unused]]long i);

// Here we force compiler to aligas object of struct to 32 byte word boundary
// Use g++-7 with -faligned-new
struct alignas(32) S {
    int  a;
    char c;
};

// consexpr can be used in the context of lambdas.
void lambdaConstExpr();

// Lambda capture of *this
struct S1 {
   int x ;
   void f() {
      // The following lambda captures are currently identical
      auto a = [&]() { x = 42 ; }; // OK: transformed to (*this).x
      auto b = [=]() { x = 43 ; }; // OK: transformed to (*this).x
      a();
      assert( x == 42 );
      b();
      assert( x == 43 );
   }
};

// Make exception specifications part of the type system
void exceptionTypeSystemPart();
void copyDirectInitialization();

struct base { int a1, a2; };
struct derived : base { int b1; };

////////////////////////////////////////////////////////////////////

int main(int argc, char * argv[])
{
    auto a = keywords1(4);
    cout << "Value of return type : " << a << endl;

    [[maybe_unused]]S * objects = new S[10];

    ifSwitchVarInit();
    lambdaConstExpr();

    S1 obj;
    obj.f();

    exceptionTypeSystemPart();
    copyDirectInitialization();

    [[maybe_unused]]derived d1{{1, 2}, 3};  // full explicit initialization
    [[maybe_unused]]derived d2{{}, 1};      // the base is value initialized

    return 0;
}


///////////////////////////////////////////////////////////////////

void exceptionTypeSystemPart()
{
#if 0
    // Make exception specifications part of the type system
    void (*p)();
    void (**pp)() noexcept = &p;   // error: cannot convert to pointer to noexcept function

    struct S { typedef void (*p)(); operator p(); };
    void (*q)() noexcept = S();   // error: cannot convert to pointer to noexcept function
#endif
}

int foo() { 
  return 100;
}

// For a braced-init-list with only a single element, auto deduction will deduce from that entry;
// For a braced-init-list with more than one element, auto deduction will be ill-formed.
// Basically, auto x { 1 }; will be now deduced as int, but before it was an initializer list.
void copyDirectInitialization()
{
     [[maybe_unused]] auto x1 = foo(); // copy-initialization
     [[maybe_unused]] auto x2{foo};    // direct-initialization, initializes an initializer_list
     [[maybe_unused]] int x3 = foo();  // copy-initialization
     // [[maybe_unused]] int x4{foo};     // direct-initialization
}

constexpr int AddEleven(int n){
    return [n]{return n + 11;}();
}

void lambdaConstExpr()
{
   // consexpr can be used in the context of lambdas.
   constexpr auto constexprlambda = [](int n) { 
	                                   return n;
                                    };

   constexpr int I = constexprlambda(3);
   static_assert(I == 3);
   static_assert(AddEleven(5) == 16);
}	

static int  unsedFunc2(long i){ 
    return 0;
}

[[maybe_unused]] static int  unsedFunc1([[maybe_unused]]long i) {
    // The warning will be suppressed
    [[maybe_unused]] int someUnusedVar = 42;
    return 0;
}

[[nodiscard]] int  keywords1(int i)
{
    switch (i)
    {
       case 1:
          cout << "switch case -1" << endl;
          break;
       case 2:
          cout << "switch case -2" << endl;
          break;
       case 3:
          cout << "switch case -3" << endl;
          break;
       case 4:
          cout << "switch case -4" << endl;
          // [[fallthrough]]; // The warning will be suppressed
       case 5:
          cout << "switch case -5" << endl;
          break;
       default :
          break;
    }

    return 2;
}

int  ifSwitchVarInit()
{
    if (auto val = 5; val > 6)
       cout << "If part executed" << endl;
    else
      cout << "Else part executed" << endl;

    switch (auto val = 1; val)
    {
       case 1:
          cout << "switch case -1" << endl;
          break;
       default:
	  break;
    }

    return 0;
}
