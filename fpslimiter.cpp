#include "fpslimiter.h"

fpslimiter::fpslimiter()
{
	m_times[sampleSize - 2] = glfwGetTime();
}
void fpslimiter::limitFPS(){
	const double currentTime = glfwGetTime();
	std::this_thread::sleep_for(std::chrono::nanoseconds((int64_t)((m_times[sampleSize - 1] + (1/ fps) - currentTime) * 1000000000)));	
	std::rotate(m_times, m_times + 1, m_times + sampleSize);
	m_times[sampleSize - 1] = glfwGetTime();
}
