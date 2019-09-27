#include "Row.hpp"

Row::Row()
{
	//TODO implement height based on frequency amplitude, remove random generator
	std::default_random_engine r;

	for (int i = 0; i < NUM_BARS; i++)
	{
		bars.push_back(Bar(BAR_WIDTH * (i + 1), r() % 15, BAR_LENGTH));
	}
}

void Row::render()
{
	for (size_t i = 0; i < bars.size(); i++)
	{
		bars[i].render();
	}
}