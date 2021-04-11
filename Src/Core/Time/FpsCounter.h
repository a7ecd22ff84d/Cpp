#ifndef __FPS_COUNTER_H
#define __FPS_COUNTER_H

#include <chrono>
#include <vector>

#include "Core/Containers/LoopIterator.h"

namespace Time
{
class FpsCounter
{
	using Data = std::vector<std::chrono::milliseconds>;

public:
	FpsCounter(unsigned framesCount, unsigned refreshRate = 1);

	void tick();
	double getFps();

private:
	Data data;
	Containers::LoopIterator<Data> currentItem;

	unsigned refreshRate;
	unsigned framesCount{0};
	double currFps;
};

} // namespace Time

#endif