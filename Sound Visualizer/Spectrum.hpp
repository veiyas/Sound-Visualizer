#pragma once
#include <vector>

#include "FFTW/fftw3.h"

#include "WaveReader.hpp"
#include "Row.hpp"

class Spectrum
{
public:
	Spectrum(const char* _path);

	void create_row();
	void render();

private:
	std::vector<fftw_complex*> freqs;
	std::vector<Row*> rows;
	unsigned which_row = 0;
};