#include <iostream>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "callbacks.h"
#include "input.h"

int main()
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
	} else {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// opengl state changes
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



	/*
		render loop
	*/
	while (!glfwWindowShouldClose(window)) 
	{	
		// execute every frame
		process_input(window);

		// rendering commands
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// end every frame
		glfwSwapBuffers(window);
		glfwPollEvents();
	}



	/*
		cleanup
	*/
	glfwTerminate();
	return 0;
}