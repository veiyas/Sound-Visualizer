#include <iostream>
#include <fstream>
#include <string>

#include <GL/glew.h>  
#include <GLFW/glfw3.h>

#include "Row.hpp"
#include "Freqbar.hpp"

void window_resized(GLFWwindow* window, int width, int height);
void key_pressed(GLFWwindow* window, int key, int scancode, int action, int mods);
void show_glfw_error(int error, const char* description);
void create_perspective_matrix(float M[], const float& vfov, const float& aspect, const float& znear, const float& zfar);
void create_translate_matrix(float M[], const float& x, const float& y, const float& z);
GLFWwindow* initialize_all_libraries(int height, int width);

bool load_shaders(GLuint& program);

int main()
{
	auto window = initialize_all_libraries(1920 / 2, 1080 / 2);

	//Shader initialization
	GLuint core_program;
	if (!load_shaders(core_program))
	{
		std::cout << "Core program could not be loaded\n";
		glfwTerminate();
	}
	// Shader uniforms
	GLint location_time, location_MV, location_P;
	location_MV = glGetUniformLocation(core_program, "MV");
	location_P = glGetUniformLocation(core_program, "P");
	location_time = glGetUniformLocation(core_program, "time");

	//GLfloat time = 0.0f;
	//GLfloat P[16];
	//GLfloat MV[16];
	//create_perspective_matrix(P, 1.0f, 1.0f, 0.0f, 100.0f);
	//create_translate_matrix(MV, 0.0f, 0.0f, -1.0f);

	//Background color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	/********************************************************
						TEST AREA
	********************************************************/
	
	//Row test{};

	Freqbar test{ 0, 0, -3 };

	/********************************************************
	********************************************************/


	/**********		MAIN LOOP	  **********/	
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		test.render();

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	glDeleteProgram(core_program);

	return 0;
}

void key_pressed(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//Hack away warnings B)
	window; scancode; mods;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwTerminate();
		exit(0);
	}
}

void window_resized(GLFWwindow* window, int width, int height)
{
	std::cout << "Window resized, new window size: " << width << " x " << height << '\n';

	glClearColor(0, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);
}

void show_glfw_error(int error, const char* description)
{
	std::cerr << "Error: " << description << '\n';
	//Hack away warnings B)
	error;
}

GLFWwindow* initialize_all_libraries(int height, int width)
{
	glfwSetErrorCallback(show_glfw_error);

	if (!glfwInit()) {
		std::cerr << "GLFW was not initialized properly" << '\n';
		exit(-1);
	}

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(
		height,
		width,
		"Sound Visualizer",
		NULL, NULL);
	if (!window)
	{
		std::cerr << "Window could not be created" << '\n';
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
	glfwSetWindowSizeCallback(window, window_resized);
	glfwSetKeyCallback(window, key_pressed);
	glfwSwapInterval(1);
	glewExperimental = GL_TRUE;

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cerr << "GLEW not ok " << glewGetErrorString(err) << '\n';
		glfwTerminate();
		exit(-1);
	}

	std::cout << glGetString(GL_VERSION) << '\n';

	int nr_extensions = 0;
	glGetIntegerv(GL_NUM_EXTENSIONS, &nr_extensions);

	//for (int i = 0; i < nr_extensions; ++i) {
	//	std::cout << glGetStringi(GL_EXTENSIONS, i) << '\n';
	//}

	return window;
}

bool load_shaders(GLuint& program)
{
	bool load_success = true;
	char info_log[512];
	GLint success;

	std::string temp = "";
	std::string src = "";

	std::ifstream in_file;

	////Vertex
	in_file.open("vertex_shader.glsl");

	if (in_file.is_open())
	{
		while (std::getline(in_file, temp))
			src += temp + "\n";
	}
	else
	{
		std::cout << "Error (load_shaders()) - could not open vertex file";
		load_success = false;
	}

	in_file.close();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertSrc = src.c_str();
	glShaderSource(vertexShader, 1, &vertSrc, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, info_log);
		std::cout << "Error load_shaders() - could not compile vertex file";
		std::cout << info_log << "\n";
		load_success = false;
	}

	temp = "";
	src = "";

	//Fragment
	in_file.open("fragment_shader.glsl");

	if (in_file.is_open())
	{
		while (std::getline(in_file, temp))
			src += temp + "\n";
	}
	else
	{
		std::cout << "Error (load_shaders()) - could not open fragment file";
		load_success = false;
	}

	in_file.close();

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragSrc = src.c_str();
	glShaderSource(fragmentShader, 1, &fragSrc, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, info_log);
		std::cout << "Error load_shaders() - could not compile fragment file";
		std::cout << info_log << "\n";
		load_success = false;
	}

	//Program
	program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, info_log);
		std::cout << "Error load_shaders() - could link program";
		std::cout << info_log << "\n";
		load_success = false;
	}

	//End
	glUseProgram(0);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return load_success;
}

void create_perspective_matrix(float M[], const float& vfov, const float& aspect, const float& znear, const float& zfar)
{
	float f = (cos(vfov / 2)) / (sin(vfov / 2));
	float z1 = -1 * ((zfar + znear) / (zfar - znear));
	float z2 = -1 * ((2 * znear * zfar) / (zfar - znear));

	float MTemp[16] = {
		(f / aspect) , 0.0f     , 0.0f    , 0.0f ,
		0.0f       , f        , 0.0f    , 0.0f ,
		0.0f       , 0.0f     , z1      ,-1.0f ,
		0.0f       , 0.0f     , z2      , 1.0f
	};

	for (int i = 0; i < 16; i++) {
		M[i] = MTemp[i];
	}
}

void create_translate_matrix(float M[], const float& x, const float& y, const float&z)
{

	float MTemp[16] = {
		1.0f		,0.0f		, 0.0f		, x ,
		0.0f		, 1.0f      , 0.0f		, y ,
		0.0f		, 0.0f		, 1.0f      , z ,
		0.0f		, 0.0f		, 0.0f      , 1.0f
	};

	for (int i = 0; i < 16; i++) {
		M[i] = MTemp[i];
	}
}

