#pragma once

#include <libsndfile/sndfile.hh>
#include <libsndfile/sndfile.h>
#include <FFTW/fftw3.h>

#include <vector>
#include <array>
#include <iostream>
#include <cmath>

#include "Constants.hpp"

class WaveReader
{
public:
	WaveReader(const char * _path);

	std::vector<double> frames;
	std::vector<fftw_complex*> freq_data;

	unsigned fs = 0;
};