#pragma once
#include <vector>
#include <algorithm>

#include "FFTW/fftw3.h"

#include "WaveReader.hpp"
#include "Row.hpp"

class Spectrum
{
public:
	Spectrum(const char* _path);

	void create_row();
	void render();

	int fs = 0;

private:
	std::vector<fftw_complex*> freqs;
	std::vector<Row*> rows;
	
	int which_row = 0;
};