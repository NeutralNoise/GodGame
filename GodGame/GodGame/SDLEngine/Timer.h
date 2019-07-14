#pragma once

class  SimpleTimer
{
public:
	 SimpleTimer();
	~ SimpleTimer();
	void StartTimer();
	void StopTimer();
	float GetTime();
	float GetTimeRestart();

private:
	float m_startTime;
	float m_endTime;
	bool m_isStoped;
};

class Timer
{
public:
	Timer();
	~Timer();

	static unsigned int GetTicks();

};

