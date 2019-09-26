#include "Row.hpp"

void render_freqbar(Freqbar& temp)
{
	temp.render();
}

Row::Row()
{
	for (int i = 0; i < NUM_BARS; i++)
	{
		bars.push_back(Freqbar(BAR_WIDTH, 0, BAR_LENGTH - i));
	}
}

void Row::render()
{
	std::for_each(std::begin(bars), std::end(bars), render_freqbar);

	//for (size_t i = 0; i < bars.size(); i++)
	//{
	//	bars[i].render();
	//}
}