#include "time.hpp"

Time* Time::instance = nullptr;

Time::Time() {
	_start = 0;
	_current = 0;
	_last = 0;
	_elapsed = 0;
	_dt = 0.0f;
}

Time* Time::getTime() {
	if (instance == nullptr) instance = new Time();
	return instance;
}