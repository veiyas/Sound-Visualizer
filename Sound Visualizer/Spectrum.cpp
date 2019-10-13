#include "Spectrum.hpp"

Spectrum::Spectrum(const char* _path)
{
	WaveReader temp{ _path };

	freqs = temp.freq_data;
	fs = temp.fs;
}

void Spectrum::create_row()
{
	if (which_row != freqs.size())
	{
		rows.resize(freqs.size());
		rows[which_row] = new Row(freqs[which_row], which_row);
		++which_row;

		if (which_row > ROW_RENDER_LIMIT)
		{
			delete rows[(__int64)which_row - (__int64)ROW_RENDER_LIMIT];
		}
	}
	else
		std::cout << "No more frequency data\n";
}

void Spectrum::render()
{
		for (size_t i = std::max(0, which_row - ROW_RENDER_LIMIT); rows[i] != nullptr && i < rows.size(); i++)
		{
			rows[i]->render();
		}	
}
