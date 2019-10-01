#include "Spectrum.hpp"

Spectrum::Spectrum(const char* _path)
{
	WaveReader temp{ _path };

	freqs = temp.freq_data;
}

void Spectrum::create_row()
{
	if (which_row != freqs.size())
	{
		rows.resize(freqs.size());
		rows[which_row] = new Row(freqs[which_row], which_row);
		++which_row;

		if (which_row > 30)
		{
			auto *ptr = rows[which_row - 30];
			delete rows[which_row - 30];
			ptr = nullptr;
		}
	}
	else
		std::cout << "No more frequency data\n";
}

void Spectrum::render()
{
	if (which_row > 30)
	{
		for (size_t i = which_row - 20; rows[i] != nullptr && i < rows.size() - 1; i++)
		{
			rows[i]->render();
		}
	}
	else
	{
		for (size_t i = 0; rows[i] != nullptr && i < rows.size() - 1; i++)
		{
			rows[i]->render();
		}
	}
}
