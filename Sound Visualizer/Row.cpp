#include "Row.hpp"

Row::Row(fftw_complex* data, int depth)
{
	for (size_t i = 0; i < NUM_BARS; i++)
	{
		double mag = sqrt(pow(data[i][REAL], 2) + pow(data[i][IMAG], 2));
		
		if(mag < 1e-3)
			mag = 0.0;

		bars.push_back(Bar(BAR_WIDTH * i, mag, BAR_LENGTH * depth));

	}
}

void Row::render()
{
	for (size_t i = 0; i < bars.size(); i++)
	{
		bars[i].render();
	}
}

void Row::create_row()
{
	for (size_t i = 0; i < NUM_BARS; i++)
	{

	}
}
