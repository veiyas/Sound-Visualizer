#pragma once

class Geometry
{
public:
	Geometry() = default;
	Geometry(const Geometry&) = default; //May need to implement deep copy constructor if need arises
	Geometry& operator=(const Geometry&) = default;

	//Methods
	void render();
	Geometry create_box(const int& x, const int& y, const int& z);

private:


};