#pragma once
#include <GL/glew.h>  
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Constants.hpp"

#include <vector>
#include <memory>
#include <iostream>

class Bar
{
public:
	Bar(GLfloat x_coord, GLfloat height, GLfloat z_coord);
	~Bar();

	void render();

private:
	//OpenGL magic
	GLuint vao = 0; // Vertex array object, the main handle for geometry
	const int nverts; // Number of vertices in the vertex array
	const int ntris;  // Number of triangles in the index array (may be zero)
	GLuint vertexbuffer; // Buffer ID to bind to GL_ARRAY_BUFFER
	GLuint indexbuffer;  // Buffer ID to bind to GL_ELEMENT_ARRAY_BUFFER
};