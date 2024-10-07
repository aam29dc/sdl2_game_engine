#pragma once
#ifndef TIME_H
#define TIME_H

#include <SDL.h>

class Time {
private:
	static Time* instance;
public:
	Time();
	static Time* getTime();
	Uint64 _start;
	Uint64 _elapsed;

	Uint32 _current;
	Uint32 _last;
	float _dt;
};

#endif