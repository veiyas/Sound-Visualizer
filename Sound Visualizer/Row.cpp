#include "Row.hpp"

Row::Row()
{
	std::default_random_engine r;

	for (int i = 0; i < NUM_BARS; i++)
	{
		bars.push_back(Bar(BAR_WIDTH * (1 + i), 10, BAR_LENGTH));
	}
}

void Row::render()
{
	for (size_t i = 0; i < bars.size(); i++)
	{
		bars[i].render();
	}
}