#include "libs.hpp"

void window_resized(GLFWwindow* window, int width, int height);
void key_pressed(GLFWwindow* window, int key, int scancode, int action, int mods);
void show_glfw_error(int error, const char* description);
GLFWwindow* initialize_all_libraries(int height, int width);

bool load_shaders(GLuint& program);

const double ROWS_PER_SEC = (double)BUFFER / (double)SAMPLERATE;
const char *PATH = "soundfiles/susann_vega.wav";

int main()
{
	/********************************************************
					TEST AREA
	********************************************************/

	Spectrum spec{ PATH };

	/********************************************************
	********************************************************/


	auto window = initialize_all_libraries(1920 / 2, 1080 / 2);
	int frame_buffer_width = 0;
	int frame_buffer_height = 0;
	glfwGetFramebufferSize(window, &frame_buffer_width, &frame_buffer_height);

	//Shader initialization
	GLuint core_program;
	if (!load_shaders(core_program))
	{
		std::cout << "Core program could not be loaded\n";
		glfwTerminate();
	}
	// Shader uniforms
	GLint location_V, location_M, location_P, location_scale;
	location_M = glGetUniformLocation(core_program, "M");
	location_P = glGetUniformLocation(core_program, "P");
	location_V = glGetUniformLocation(core_program, "V");
	location_scale = glGetUniformLocation(core_program, "scale");

	//OpenGL options
	glEnable(GL_DEPTH_TEST);	//Z buffer
	glEnable(GL_CULL_FACE);		//Cull faces (on the back)
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Model translation, rotation and scale
	glm::mat4 Model_Matrix(1.f);
	Model_Matrix = glm::translate(Model_Matrix, glm::vec3(-45.f, -30.f, -60.f));
	Model_Matrix = glm::rotate(Model_Matrix, glm::radians(25.f), glm::vec3(1.f, 0.f, 0.f)); //X-axis
	Model_Matrix = glm::rotate(Model_Matrix, glm::radians(0.f), glm::vec3(0.f, 1.f, 0.f)); //Y-axis
	Model_Matrix = glm::rotate(Model_Matrix, glm::radians(0.f), glm::vec3(0.f, 0.f, 1.f));	//Z-axis
	Model_Matrix = glm::scale(Model_Matrix, glm::vec3(1.f));

	//View
	glm::vec3 world_up(0.f, 1.f, 0.f);
	glm::vec3 cam_front(0.f, 0.f, -1.f);
	glm::vec3 cam_position(0.f);
	glm::mat4 View_Matrix(1.f);
	View_Matrix = glm::lookAt(cam_position, cam_position + cam_front, world_up);

	//Perspective
	float fov = 90.f;
	float near_plane = 0.1f;
	float far_plane = 1000.f;
	glm::mat4 Projection_Matrix(1.f);
	Projection_Matrix = glm::perspective(glm::radians(fov), static_cast<float>(frame_buffer_width/frame_buffer_height), near_plane, far_plane);
	glUseProgram(core_program);
	glUniformMatrix4fv(location_V, 1, GL_FALSE, glm::value_ptr(View_Matrix));
	glUniform1f(location_scale, scale);
	
	
	double current_time = 0.0;
	double last_time = 0.0;
	double render_time = 1.0;
	glfwSetTime(0);

	/**********		MAIN LOOP	  **********/	
	PlaySound(TEXT(PATH), NULL, SND_ASYNC);
	while (!glfwWindowShouldClose(window))
	{
		current_time = glfwGetTime();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//glClearColor(sin(current_time), sin(current_time), cos(current_time), 1.0f);

		spec.create_row();
		spec.render();

		glfwSwapBuffers(window);

		glfwPollEvents();

		Model_Matrix = glm::translate(Model_Matrix, glm::vec3(0.f, 0.f, -1.f)); //Move the rows
		glUniformMatrix4fv(location_M, 1, GL_FALSE, glm::value_ptr(Model_Matrix));
		glUniformMatrix4fv(location_V, 1, GL_FALSE, glm::value_ptr(View_Matrix));
		glUniformMatrix4fv(location_P, 1, GL_FALSE, glm::value_ptr(Projection_Matrix));
		
		//std::cout << "FPS: " << 1 / render_time << "\n";

		last_time = glfwGetTime();
		render_time = last_time - current_time;

		
		//Pausa loopen i så lång tid det krävs till nästa row ska visas för att behålla synk (ms)
		Sleep(std::max((ROWS_PER_SEC - render_time) * 1000, 0.0));
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
	std::cout << "Initializing openGL...";
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
	
	std::cout << " done!\n";
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