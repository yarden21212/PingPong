/* https://cplusplus.com/forum/beginner/280938/ */

#include "Timer.h"
#include <iostream>
#include <thread>

void Timer::reset()
{
	m_beg = Clock::now();
}

double Timer::elapsed() const
{
	return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
}
void Timer::wait(int duration)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(duration));
}