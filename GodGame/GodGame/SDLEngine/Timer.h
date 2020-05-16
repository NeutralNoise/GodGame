#pragma once

class  SimpleTimer
{
public:

	/**
	 * \brief Construct a new SimpleTimer object
	 * 
	*/

	 SimpleTimer();

	/**
	 * \brief Destroy the SimpleTimer object
	 * 
	*/

	~SimpleTimer();

	/**
	 * \brief Starts the timer.
	 * 
	*/

	void StartTimer();

	/**
	 * \brief Stops the timer.
	 * 
	*/

	void StopTimer();

	/**
	 * \brief Gets the time elapsed since the timer was started to when it was stoped.
	 * 
	 * \note If the timer was not stoped before calling this it will NOT stop the timer.
	 * 
	 * \return float 
	*/

	float GetTime();

	/**
	 * \brief Gets the time elapsed since the timer was started to when it was stoped then restarts the timer.
	 * 
	 * \return float 
	*/

	float GetTimeRestart();

private:
	float m_startTime; //!< Time the timer was started.
	float m_endTime; //!< Time the timer was stoped.
	bool m_isStoped; //!< True if the timer is not running.
};

class Timer
{
public:
	Timer();
	~Timer();

	/**
	 * \brief Get the number of milliseconds since the start the engine.
	 * 
	 * \note Really is the start of SDL2 but who really cares.
	 * \warning This will loop back around after 49 days.
	 * 
	 * \return unsigned int 
	*/

	static unsigned int GetTicks();

};

