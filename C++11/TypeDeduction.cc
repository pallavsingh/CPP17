/////////////////////////////////////////////////
// C++14 Hearders
#include <iostream>
#include <memory>
#include <atomic>
#include <initializer_list>
#include <type_traits>
#include <typeinfo>
#include <utility>

/////////////////////////////////////////////////
// Boost Library Hearders
#include <boost/type_index.hpp>

/////////////////////////////////////////////////
// Intel TBB Concurrent Containers Hearders
#include "tbb/concurrent_vector.h"
#include "tbb/concurrent_unordered_map.h"
#include "tbb/concurrent_unordered_set.h"
#include "tbb/concurrent_hash_map.h"
#include "tbb/concurrent_queue.h"
#include "tbb/concurrent_priority_queue.h"

/////////////////////////////////////////////////
// Intel TBB  Memory Allocator Hearders
#include "tbb/tbb_allocator.h"
#include "tbb/scalable_allocator.h"
#include "tbb/cache_aligned_allocator.h"
#include "tbb/aligned_space.h"

/////////////////////////////////////////////////
// Intel TBB  Tasked Based Programming 
#include "tbb/task.h"
#include "tbb/task_group.h"
#include "tbb/task_scheduler_init.h"
#include "tbb/tbb_exception.h"
#include "tbb/task_arena.h"

//////////////////////////////////////////////////
#include "tbb/tbb_stddef.h"
#include "tbb/blocked_range.h"
#include "tbb/blocked_range2d.h"
#include "tbb/blocked_range3d.h"
#include "tbb/partitioner.h"
#include "tbb/parallel_for.h" 
#include "tbb/parallel_reduce.h"
#include "tbb/parallel_scan.h"
#include "tbb/parallel_do.h"
#include "tbb/parallel_for_each.h"
#include "tbb/pipeline.h"
#include "tbb/parallel_sort.h"
#include "tbb/parallel_invoke.h"

using namespace std;
using boost::typeindex::type_id_with_cvr;

template <typename T>
void func1(T  param) {
     cout <<"Pass by value : T = "     <<  type_id_with_cvr<T>().pretty_name() << '\n';
     cout <<"Pass by value : Param = " <<  type_id_with_cvr<decltype(param)>().pretty_name() << '\n';
}

template <typename T>
void func2(T & param) {
     cout <<"Pass by reference : T = "     <<  type_id_with_cvr<T>().pretty_name() << '\n';
     cout <<"Pass by reference : Param = " <<  type_id_with_cvr<decltype(param)>().pretty_name() << '\n';
}

template <typename T>
void func3(T && param) {
     cout <<"Pass by universal reference : T = "     <<  type_id_with_cvr<T>().pretty_name() << '\n';
     cout <<"Pass by universal refrence  : Param = " <<  type_id_with_cvr<decltype(param)>().pretty_name() << '\n';
}

template <typename T>
void func4(const T & param) {
     cout << "Pass by const-reference : T = "     <<  type_id_with_cvr<T>().pretty_name() << '\n';
     cout << "Pass by const-refrence  : Param = " <<  type_id_with_cvr<decltype(param)>().pretty_name() << '\n';
}

template <typename T>
void func5(T * param) {
     cout << "Pass by pointer : T = "     <<  type_id_with_cvr<T>().pretty_name() << '\n';
     cout << "Pass by Pointer : Param = " <<  type_id_with_cvr<decltype(param)>().pretty_name() << '\n';
}

void someFunc(int, double){}

int main(int argc, char * argv[]) {
   int x = 27;
   const int  cx = x;
   const int& rx = x;

   func1(x);
   func1(cx);
   func1(rx);

   const char * const str = "FireEye";
   func1(str);

   func2(x);
   func2(cx);
   func2(rx);

   const char name[] = "Array-Argument";
   const char * ptrToName = name;
   func1(name);
   func2(name);

   func1(someFunc);
   func2(someFunc);

   func3(x);
   func3(cx);
   func3(rx);
   func3(27);

   func4(x);
   func4(cx);
   func4(rx);

   int y = 100;
   const int * py = &y;

   func5(&y);
   func5(py);

   return 0;
}

