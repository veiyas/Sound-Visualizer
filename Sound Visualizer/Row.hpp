#pragma once
#include "Bar.hpp"
#include "Constants.hpp"
#include "FFTW/fftw3.h"

#include <vector>
#include <algorithm>
#include <random>
#include <cmath>

#define REAL 0
#define IMAG 1

class Row
{
public:
	Row(fftw_complex* data, int depth);
	Row(const Row&) = default;
	Row& operator=(const Row&) = default;
	~Row();

	//Methods
	void render();

	void create_row();

private:
	std::vector<Bar*> bars;	
};
