#ifndef TIMER_H
#define TIMER_H
#include "defines.h"
#include <iostream>
class Timer
{
    //The clock time when the timer started
    Uint32 _start_ticks;
    //The timer status
    bool _is_started;
    Uint32 _timeout_time;
public:
	Timer(Uint32 timeout);
    ~Timer();
    bool isStarted();
    bool isTimedOut();
    int getTicks();
    void start();
    void stop();

};
#endif
