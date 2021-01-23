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

using  namespace std;
using  boost::typeindex::type_id_with_cvr;

class Widget {
  public :
      Widget() { cout <<"Calling Constructor for Widget : "<< endl ;}
      Widget(const Widget & rhs) {  cout <<"Calling Copy Constructor for Widget : "<< endl ;}
      Widget(Widget && rhs) { cout <<"Calling Move  Constructor for Widget : "<< endl ;}
     ~Widget() { cout <<"Calling Destructor for Widget : "<< endl ;}

      bool isValidated() const { cout << "Widget :: isValidated() :" << endl; }
      bool isProcessed() const { cout << "Widget :: isProcessed() :" << endl; }
      bool isArchived()  const { cout << "Widget :: isArchived() :" << endl; }
};

using DataType = unique_ptr<Widget>;

class IsValAndArch {
     public :
      IsValAndArch(DataType && ptr) : pw(move(ptr)) { cout <<" Calling Move Cons : IsValAndArch :: "<< endl;  }
      IsValAndArch(const DataType & ptr) : pw(ptr)  { cout <<"Calling Cons : IsValAndArch :: "<< endl; }

      bool operator()() const {
         return pw->isValidated() && pw->isArchived();
      };

     private :
      DataType pw;
};

int main(int argc, char * argv[]) {
   auto pw    =  make_unique<Widget>();

   auto func1 =  [pw = move(pw)] { 
                     return pw->isValidated() && pw->isArchived();
                 };

   auto func2 =  [pw = make_unique<Widget>(pw)] { 
                     return pw->isValidated() && pw->isArchived();
                 };

    auto func3 = IsValAndArch(make_unique<Widget>());
    vector<double> data;

    auto func4 = bind([](const vector<double> & data) { cout << " Calling func2 : " << endl; }, move(data));
    auto func5 = bind([](const vector<double> & data) mutable { cout <<"Calling func3 : "<< endl;}, move(data));

    return 0;
}
