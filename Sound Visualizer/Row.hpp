#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <GL/glew.h>  
#include <GLFW/glfw3.h>
#include <aubio/aubio.h>

#include "Freqbar.hpp"
#include "Constants.hpp"

class Row
{
public:
	Row();
	Row(const Row&) = delete;
	Row& operator=(const Row&) = delete;

	//Methods
	void render();

private:
	std::vector<Freqbar> bars;
};
