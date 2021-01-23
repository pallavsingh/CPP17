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

using  namespace  std::chrono;
using  namespace  std::literals;
using  namespace  std::placeholders;
using  Time       = std::chrono::steady_clock::time_point;
using  Duration   = std::chrono::steady_clock::duration;
enum   class Sound  {Beep, Siren, Whistle};
enum   class Volume {Normal, Loud, LoudPlusPlus}; 

void   setAlarm (Time t, Sound s, Duration d) {
       cout << "Calling Function setAlarm(Time t, Sound s, Duration d) : \n" << endl;
}

void   setAlarm(Time t, Sound s, Duration d, Volume v) {
       cout << "Calling Function setAlarm(Time t, Sound s, Duration d, Volume v) : \n" << endl;
}

using  SetAlarmParamType = void (*)(Time t, Sound s, Duration d);

auto setSoundLambda1 = [] (Sound s) {
                           setAlarm(steady_clock::now() + hours(1), s, seconds(30));
                       };

auto setSoundLambda2 = [] (Sound s) {
                           setAlarm(steady_clock::now() + hours(1),  s, 30s);
                       };

// auto   setSoundB1 = bind (setAlarm, steady_clock::now() + hours(1),  _1 , 30s);
// auto   setSoundB2 = bind (setAlarm, bind (plus<>(), steady_clock::now(),  hours(1)),  _1, 30s);
// auto   setSoundB3 = bind (setAlarm, bind (plus<steady_clock::time_point>(), steady_clock::now(), hours(1)),  _1,  30s);

auto   SetSoundL = [] (Sound s) {
                       setAlarm(steady_clock::now() + hours(1),  s, 30s);
                   };

// auto   setSoundB11 = bind(setAlarm, bind(plus<>(), steady_clock::now(), 1h),  _1, 30s);
auto   SetSoundB = bind(static_cast<SetAlarmParamType>(setAlarm), bind(plus<>(), steady_clock::now(), 1h), _1, 30s);

class A { };
enum class CompLevel {Low, Normal, High};
A compress(const A & rhs, CompLevel level) {
    cout << "Calling Function : compress(const A & rhs, CompLevel level) : " << endl;
}

class PolyWidget {
    public :
      template <typename T>
      void operator() (const T & param){}
};

int main(int argc, char * argv[]) {
   SetSoundL(Sound::Siren);
   SetSoundB(Sound::Siren);
     
   A obj;
   auto compressRateB = bind(compress, obj, _1);
   auto compressRateL = [obj] (CompLevel level) {
                            return  compress(obj, level);
                         };
    
   int  lowVal = 10, highVal = 20;
   auto betweenL14 = [lowVal, highVal] (const auto & val) {
                          return lowVal <= val && val <= highVal;
                      };

   auto betweenL11 = [lowVal, highVal] (int val) {
                          return lowVal <= val && val <= highVal;
                      };

   auto betweenB14 = bind (logical_and<>(), bind(less_equal<>(),  lowVal, _1), bind(less_equal<>(),  _1, highVal));
   auto betweenB11 = bind (logical_and<bool>(), bind(less_equal<int>(), lowVal, _1), bind(less_equal<int>(), _1, highVal));

   compressRateL(CompLevel::High);
   compressRateB(CompLevel::High);

   PolyWidget obj1;  
   auto boundPW = bind(obj1, _1);

   boundPW(1930);
   boundPW(nullptr);
   boundPW("Pallav Singh");

   return 0;
}
