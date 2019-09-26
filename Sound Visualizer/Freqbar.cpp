#include "Freqbar.hpp"

Freqbar::Freqbar()
	:x_coord{ BAR_WIDTH }, y_coord{ 0 }, z_coord{ BAR_LENGTH }
{
	create_geometry();
}

Freqbar::Freqbar(int _x, int _y, int _z)
	: x_coord{ _x }, y_coord{ _y }, z_coord{ _z }
{
	create_geometry();
}

void Freqbar::render()
{
	//Render
	glDrawElements(GL_TRIANGLES, 3 * ntris, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
	glBindBuffer(0, 0);
	glBindTexture(0, 0);
}

void Freqbar::create_geometry()
{
	//Ugly conversions to avoid warnings
	GLfloat x = (GLfloat)x_coord + BAR_WIDTH;
	GLfloat y = (GLfloat)y_coord + 10;
	GLfloat z = (GLfloat)z_coord;

	const GLfloat vertex_array_data[] = {
		//Back face
	   -x, -y, -z,   0.0f, 0.0f,-1.0f,   0.0f, 1.0f / 3.0f,  // Vertex 0
		x, -y, -z,   0.0f, 0.0f,-1.0f,   1.0f, 1.0f / 3.0f,  // Vertex 1
	   -x,  y, -z,   0.0f, 0.0f,-1.0f,   0.0f, 2.0f / 3.0f,  // Vertex 2
		x,  y, -z,   0.0f, 0.0f,-1.0f,   1.0f, 2.0f / 3.0f,  // Vertex 3
		//Front face
	   -x, -y,  z,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f / 3.0f,  // Vertex 4
		x, -y,  z,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f / 3.0f,  // Vertex 5
	   -x,  y,  z,   0.0f, 0.0f, 1.0f,   0.0f, 2.0f / 3.0f,  // Vertex 6
		x,  y,  z,   0.0f, 0.0f, 1.0f,   1.0f, 2.0f / 3.0f,  // Vertex 7
		//Right face
		x, -y,  z,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f / 3.0f,  // Vertex 5 - 8
		x, -y, -z,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f / 3.0f,  // Vertex 1 - 9
		x,  y,  z,   1.0f, 0.0f, 0.0f,   0.0f, 2.0f / 3.0f,  // Vertex 7 - 10
		x,  y, -z,   1.0f, 0.0f, 0.0f,   1.0f, 2.0f / 3.0f,  // Vertex 3 - 11
		//Left face
	   -x, -y, -z,  -1.0f, 0.0f, 0.0f,   0.0f, 1.0f / 3.0f,  // Vertex 0 - 12
	   -x, -y,  z,  -1.0f, 0.0f, 0.0f,   1.0f, 1.0f / 3.0f,  // Vertex 4 - 13
	   -x,  y, -z,  -1.0f, 0.0f, 0.0f,   0.0f, 2.0f / 3.0f,  // Vertex 2 - 14
	   -x,  y,  z,  -1.0f, 0.0f, 0.0f,   1.0f, 2.0f / 3.0f,  // Vertex 6 - 15
		//Top face
	   -x,  y,  z,   0.0f, 1.0f, 0.0f,   0.0f,  2.0f / 3.0f, // Vertex 6 - 16
		x,  y,  z,   0.0f, 1.0f, 0.0f,   1.0f,  2.0f / 3.0f, // Vertex 7 - 17
	   -x,  y, -z,   0.0f, 1.0f, 0.0f,   0.0f,  1.0f,      // Vertex 2 - 18
		x,  y, -z,   0.0f, 1.0f, 0.0f,   1.0f,  1.0f,      // Vertex 3 - 19
		//Bottom face
	   -x, -y, -z,   0.0f,-1.0f, 0.0f,   0.0f,  0.0f,      // Vertex 0 - 20
		x, -y, -z,   0.0f,-1.0f, 0.0f,   1.0f,  0.0f,      // Vertex 1 - 21
	   -x, -y,  z,   0.0f,-1.0f, 0.0f,   0.0f,  1.0f / 3.0f, // Vertex 4 - 22
		x, -y,  z,   0.0f,-1.0f, 0.0f,   1.0f,  1.0f / 3.0f, // Vertex 5 - 23
	};

	const GLuint index_array_data[] = {
		//Back face
		0,2,1,
		1,2,3,
		//Front face
		4,5,6,
		5,7,6,
		//Right face
		8,9,10,
		9,11,10,
		//Left face
		12,15,14,
		13,15,12,
		//Top face
		16,19,18,
		17,19,16,
		//Bottom face
		20,21,23,
		20,23,22
	};

	nverts = 24;
	ntris = 12;

	vertexarray = new GLfloat[8 * nverts];
	indexarray = new GLuint[3 * ntris];

	for (int i = 0; i < 8 * nverts; i++) {
		vertexarray[i] = vertex_array_data[i];
	}
	for (int i = 0; i < 3 * ntris; i++) {
		indexarray[i] = index_array_data[i];
	}

	// Generate one vertex array object (VAO) and bind it
	glGenVertexArrays(1, &(vao));
	glBindVertexArray(vao);

	// Generate two buffer IDs
	glGenBuffers(1, &vertexbuffer);
	glGenBuffers(1, &indexbuffer);

	// Activate the vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Present our vertex coordinates to OpenGL
	glBufferData(GL_ARRAY_BUFFER, 8 * nverts * sizeof(GLfloat), vertexarray, GL_STATIC_DRAW);
	// Specify how many attribute arrays we have in our VAO
	glEnableVertexAttribArray(0); // Vertex coordinates
	glEnableVertexAttribArray(1); // Normals
	glEnableVertexAttribArray(2); // Texture coordinates
	// Specify how OpenGL should interpret the vertex buffer data:
	// Attributes 0, 1, 2 (must match the lines above and the layout in the shader)
	// Number of dimensions (3 means vec3 in the shader, 2 means vec2)
	// Type GL_FLOAT
	// Not normalized (GL_FALSE)
	// Stride 8 floats (interleaved array with 8 floats per vertex)
	// Array buffer offset 0, 3 or 6 floats (offset into first vertex)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), nullptr); // xyz coordinates
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))); // normals
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat))); // texcoords

	// Activate the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	// Present our vertex indices to OpenGL
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * ntris * sizeof(GLuint), indexarray, GL_STATIC_DRAW);

	// Deactivate (unbind) the VAO and the buffers again.
	// Do NOT unbind the index buffer while the VAO is still bound.
	// The index buffer is an essential part of the VAO state.
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}