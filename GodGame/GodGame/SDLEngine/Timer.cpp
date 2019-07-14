#include "Timer.h"
#include <SDL2/SDL.h>

SimpleTimer::SimpleTimer()
{
	m_isStoped = false;
}

SimpleTimer::~SimpleTimer()
{
}

void SimpleTimer::StartTimer() {
	m_startTime = (float)Timer::GetTicks();
	m_isStoped = false;
}

void SimpleTimer::StopTimer() {
	m_endTime = (float)Timer::GetTicks();
	m_isStoped = true;
}

float SimpleTimer::GetTime() {
	if (m_isStoped) {
		return m_endTime - m_startTime;
	}
	else {
		return (float)Timer::GetTicks() - m_startTime;
	}
}

float SimpleTimer::GetTimeRestart() {
	if (m_isStoped) {
		float rtn = m_endTime - m_startTime;
		StartTimer();
		return rtn;
	}
	else {
		float rtn = (float)Timer::GetTicks() - m_startTime;
		StartTimer();
		return rtn;
	}
}

Timer::Timer()
{
}


Timer::~Timer()
{
}

unsigned int Timer::GetTicks() {
	return SDL_GetTicks();
}