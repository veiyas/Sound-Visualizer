#pragma once
#include "Bar.hpp"
#include "Constants.hpp"

#include <vector>
#include <algorithm>
#include <random>

class Row
{
public:
	Row();
	Row(const Row&) = delete;
	Row& operator=(const Row&) = delete;

	//Methods
	void render();

private:
	std::vector<Bar> bars;
};
