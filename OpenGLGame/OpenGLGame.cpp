
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Window.h"
#include "Mesh.h"

using namespace std;

void processInput(GLFWwindow*);

// Removed two callback functions

int main() {

	Window window{ 800,600 };

	// Replaced all the code up to Initialization ends here with above code
	// ==================================================================
	// The Real Program starts here
	float red{};

	float vertices[]{
		   -1.0f, -0.5f, 0.0f,
			0.0f, -0.5f, 0.0f,
		   -0.5f,  0.5f, 0.0f,
		   - 1.0f, -0.5f, 0.0f,
		   -0.5f,  0.5f, 0.0f,
		   -1.0f, 0.5f, 0.0f
	};
	                                          // 9*float = 36  / 1*float (4)   = 9
	Mesh mesh1{vertices, size(vertices)};  // sizeof(vertices) / sizeof(float)

	float vertices2[]{
		0.0f, -0.5f, 0.0f,
		1.0f, -0.5f, 0.0f,
		0.5f,  0.5f, 0.0f
	};

	Mesh mesh2{ vertices2, size(vertices2) };

	// ----- Compile the Vertex Shader on the GPU -------

	

	// ------ Compile the Orange Fragment Shader on the GPU --------
	const char* orangeFragmentShaderSource{ "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"} \0" };
	unsigned int orangeFragmentShader{ glCreateShader(GL_FRAGMENT_SHADER) };
	glShaderSource(orangeFragmentShader, 1, &orangeFragmentShaderSource, nullptr);
	glCompileShader(orangeFragmentShader);

	// ------ Compile the Yellow Fragment Shader on the GPU --------
	const char* yellowFragmentShaderSource{ "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
		"} \0" };
	unsigned int yellowFragmentShader{ glCreateShader(GL_FRAGMENT_SHADER) };
	glShaderSource(yellowFragmentShader, 1, &yellowFragmentShaderSource, nullptr);
	glCompileShader(yellowFragmentShader);

	// -------- Create Orange Shader Program (Render Pipeline) ---------
	unsigned int orangeShaderProgram;
	orangeShaderProgram = glCreateProgram();
	glAttachShader(orangeShaderProgram, vertexShader);
	glAttachShader(orangeShaderProgram, orangeFragmentShader);
	glLinkProgram(orangeShaderProgram);

	// -------- Create Yellow Shader Program (Render Pipeline) ---------
	unsigned int yellowShaderProgram;
	yellowShaderProgram = glCreateProgram();
	glAttachShader(yellowShaderProgram, vertexShader);
	glAttachShader(yellowShaderProgram, yellowFragmentShader);
	glLinkProgram(yellowShaderProgram);

	// clean up shaders after they've been linked into a program
	glDeleteShader(vertexShader);
	glDeleteShader(orangeFragmentShader);
	glDeleteShader(yellowFragmentShader);



	// While the User doesn't want to Quit (X Button, Alt+F4)
	while (!window.shouldClose()) // window -> window.window
	{
		window.processInput();

		// ^^^   window.processInput();
		red += 0.001f;
		if (red > 1)
			red -= 1;

		// render (paint the current frame of the game)
		glClearColor(red, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// DRY Principle
		// Don't Repeat Yourself
		glUseProgram(orangeShaderProgram);
		mesh1.render();

		glUseProgram(yellowShaderProgram);
		mesh2.render();

		window.present();
	}
	// Cleans up all the GLFW stuff
	glfwTerminate();
	return 0;
}