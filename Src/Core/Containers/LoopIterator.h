#ifndef __LOOP_ITERATOR
#define __LOOP_ITERATOR

#include <iterator>

namespace Containers
{
template<typename T>
class LoopIterator
{
public:
	LoopIterator(T& container) : container(container)
	{
		currentItemIt = container.begin();
	}

	typename T::value_type& operator*()
	{
		return *currentItemIt;
	}

	void operator++(int)
	{
		currentItemIt++;

		if (currentItemIt == container.end())
			currentItemIt = container.begin();
	}

	void operator+=(int steps)
	{
		for (int i = 0; i < steps; i++)
			operator++(1);
	}

	void operator--(int)
	{
		if (currentItemIt == container.begin())
			currentItemIt = container.end();

		currentItemIt--;
	}

	void operator-=(int steps)
	{
		for (int i = 0; i < steps; i++)
			operator--(1);
	}

private:
	T& container;
	typename T::iterator currentItemIt;
};

} // namespace Containers

#endif