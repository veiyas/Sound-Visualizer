#pragma once
#include <vector>
#include <algorithm>

#include "WaveReader.hpp"
#include "Row.hpp"


constexpr int ROW_RENDER_LIMIT = 10;

class Spectrum
{
public:
	Spectrum(const char* path);

	void create_row();
	void render();

	int fs = 0;

private:
	std::vector<fftw_complex*> freqs;
	std::vector<Row*> rows;
	
	int which_row = 0;
};