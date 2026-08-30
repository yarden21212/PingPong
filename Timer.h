#include <chrono> // for std::chrono functions
#include <iostream>
#include <thread>
class Timer
{
private:
	// Type aliases to make accessing nested type easier
	using Clock = std::chrono::steady_clock;
	using Second = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<Clock> m_beg{ Clock::now() };

public:
	void reset();
	double elapsed() const;
	void wait(int duration);
};