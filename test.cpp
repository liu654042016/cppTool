#include <iostream>
#include "RuningTime.hpp"


#define TIMER_START(_TimerName) \
RuningTimer _TimerName; \
_TimerName.Start(); 

#define TIMER_END(_TimerName) \
_TimerName.Stop(); \
_TimerName.ShowCostTime();


int main() {
  TIMER_START(_print)
    Sleep(3000);
    std::cout << "Hello, world!\n";
  TIMER_END(_print)
    Sleep(3000);
    std::cout<<"end"<<std::endl;
    return 1;
}
