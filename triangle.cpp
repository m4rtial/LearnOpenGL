#pragma once
#include <iostream>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "callbacks.h"
#include "input.h"

int WelcomeTriangle()
{
	/*
		initialisation
	*/
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create and initialise a glfw window, opengl context, and glad
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window != NULL) {
		glfwMakeContextCurrent(window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialise GLAD" << std::endl;
			return -1;
		}
	}
	else {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// opengl state changes
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/*
		project variables
	*/
	// vertex array
	float verticesOne[] = {
		-0.9f, -0.5f, 0.0f,  // left 
		-0.0f, -0.5f, 0.0f,  // right
		-0.45f, 0.5f, 0.0f,  // top 
	};
	float verticesTwo[] = {
		0.0f, -0.5f, 0.0f,  // left
		0.9f, -0.5f, 0.0f,  // right
		0.45f, 0.5f, 0.0f   // top 
	};

	// vertex buffer object
	unsigned int VBOs[2];
	unsigned int VAOs[2];
	glGenBuffers(2, VBOs);
	glGenVertexArrays(2, VAOs);
	//
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesOne), verticesOne, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTwo), verticesTwo, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// vertex shader
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos, 1.0);\n"
		"}\0";
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// fragment shader
	const char* pinkFragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(0.769, 0.243, 0.612, 1.0);\n"
		"}\0";
	unsigned int pinkFragmentShader;
	pinkFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(pinkFragmentShader, 1, &pinkFragmentShaderSource, NULL);
	glCompileShader(pinkFragmentShader);

	// fragment shader
	const char* yellowFragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1, 0.984, 0, 1.0);\n"
		"}\0";
	unsigned int yellowFragmentShader;
	yellowFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(yellowFragmentShader, 1, &yellowFragmentShaderSource, NULL);
	glCompileShader(yellowFragmentShader);

	// shader programs
	unsigned int pinkShaderProgram;
	pinkShaderProgram = glCreateProgram();
	glAttachShader(pinkShaderProgram, vertexShader);
	glAttachShader(pinkShaderProgram, pinkFragmentShader);
	glLinkProgram(pinkShaderProgram);
	glUseProgram(pinkShaderProgram);
	glDeleteShader(pinkFragmentShader);

	unsigned int yellowShaderProgram;
	yellowShaderProgram = glCreateProgram();
	glAttachShader(yellowShaderProgram, vertexShader);
	glAttachShader(yellowShaderProgram, yellowFragmentShader);
	glLinkProgram(yellowShaderProgram);
	glUseProgram(pinkShaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(yellowFragmentShader);

	/*
		render loop
	*/
	while (!glfwWindowShouldClose(window))
	{
		// Process input every frame
		process_input(window);

		// Clear the screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Render the first triangle using vaoOne
		glUseProgram(pinkShaderProgram);

		glBindVertexArray(VAOs[0]);  // Bind the first VAO
		glDrawArrays(GL_TRIANGLES, 0, 3); // Draw only 3 vertices (one triangle)

		glUseProgram(yellowShaderProgram);

		glBindVertexArray(VAOs[1]);  // Bind the first VAO
		glDrawArrays(GL_TRIANGLES, 0, 3); // Draw only 3 vertices (one triangle)

		// End the frame
		glfwSwapBuffers(window);
		glfwPollEvents();

	}


	/*
		cleanup
	*/
	glfwTerminate();
}