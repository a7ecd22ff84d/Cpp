#include "Core/Time/FpsCounter.h"

namespace Time
{
FpsCounter::FpsCounter(unsigned framesCount, unsigned refreshRate)
	: data(framesCount)
	, currentItem(data)
	, refreshRate(refreshRate)
{
}

void FpsCounter::tick()
{
	auto currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch());

	*currentItem = currentTime;
	currentItem++;
	framesCount++;

	if (framesCount > refreshRate)
	{
		framesCount = 0;

		auto prevTime = *currentItem;
		currFps = 1000.0 * data.size() / (currentTime - prevTime).count();
	}
}

double FpsCounter::getFps()
{
	return currFps;
}

} // namespace Time
