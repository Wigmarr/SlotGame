#include "Timer.h"

Timer::Timer(Uint32 timeout)
{
	_is_started = false;
	_start_ticks = 0;
	_timeout_time = timeout;
}

Timer::~Timer()
{
	//std::cout << "~Timer" << std::endl;
}

bool Timer::isStarted()
{
	return _is_started;
}

bool Timer::isTimedOut()
{
    return getTicks() >= _timeout_time;
}

int Timer::getTicks()
{
	Uint32 time = 0;
	if (_is_started) {
		time = SDL_GetTicks() - _start_ticks;
	}
	return time;
}

void Timer::start()
{
	_is_started = true;
	_start_ticks = SDL_GetTicks();
}

void Timer::stop()
{
	_is_started = false;
	_start_ticks = 0;
}
