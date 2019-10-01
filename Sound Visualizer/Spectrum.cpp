#include "Spectrum.hpp"

Spectrum::Spectrum(const char* _path)
{
	WaveReader temp{ _path };

	freqs = temp.freq_data;
}

void Spectrum::create_row()
{
	rows.resize(freqs.size());
	rows[which_row] = new Row(freqs[which_row], which_row);
	++which_row;

	if (which_row > 10)
	{
		delete rows[which_row - 10];
		rows[which_row - 10] = nullptr;
	}
}

void Spectrum::render()
{
	for (size_t i = 0; rows[i] != nullptr && i < rows.size(); i++)
	{
		rows[i]->render();
	}
}
