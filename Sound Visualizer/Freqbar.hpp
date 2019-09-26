#pragma once

#include "Constants.hpp"
#include <GL/glew.h>  
#include <GLFW/glfw3.h>

class Freqbar
{
public:
	Freqbar();		

	Freqbar(int _x, int _y, int _z);

	~Freqbar() = default;

	void render();

private:
	const int x_coord, y_coord, z_coord;

	void create_geometry();

	//OpenGL stuff
	GLuint vao = 1; // Vertex array object, the main handle for geometry
	GLint nverts = 0; // Number of vertices in the vertex array
	GLint ntris = 0;  // Number of triangles in the index array (may be zero)
	GLuint vertexbuffer{ 0 }; // Buffer ID to bind to GL_ARRAY_BUFFER
	GLuint indexbuffer{ 0 };  // Buffer ID to bind to GL_ELEMENT_ARRAY_BUFFER
	GLfloat* vertexarray{ nullptr }; // Vertex array on interleaved format: x y z nx ny nz s t
	GLuint* indexarray{ nullptr };   // Element index array
};