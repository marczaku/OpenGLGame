
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "Triangle.h"

using namespace std;

void processInput(GLFWwindow*);

int main() {

	Window window{ 800,600 };

	float vertices[]{
		   -1.0f, -0.5f, 0.0f,
			0.0f, -0.5f, 0.0f,
		   -0.5f,  0.5f, 0.0f,
		   - 1.0f, -0.5f, 0.0f,
		   -0.5f,  0.5f, 0.0f,
		   -1.0f, 0.5f, 0.0f
	};

	Mesh mesh1{vertices, size(vertices)};

	float vertices2[]{
		0.0f, -0.5f, 0.0f,
		1.0f, -0.5f, 0.0f,
		0.5f,  0.5f, 0.0f
	};

	Mesh mesh2{ vertices2, size(vertices2) };

	Shader vertexShader{"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0", GL_VERTEX_SHADER };
	
	Shader orangeShader{
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f,sdasdasd 0.5f, 0.2f, 1.0f);\n"
		"} \0", GL_FRAGMENT_SHADER
	};

	Shader yellowShader{
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
		"} \0", GL_FRAGMENT_SHADER
	};

	// -------- Create Orange Shader Program (Render Pipeline) ---------
	Material orange{vertexShader, orangeShader};
	Material yellow{ vertexShader, yellowShader };

	Triangle a{ &orange, &mesh1 };
	Triangle b{ &orange, &mesh2 };

	// While the User doesn't want to Quit (X Button, Alt+F4)
	while (!window.shouldClose()) // window -> window.window
	{
		window.processInput();

		window.clear();

		a.render();
		b.render();

		window.present();
	}
	// Cleans up all the GLFW stuff
	glfwTerminate();
	return 0;
}