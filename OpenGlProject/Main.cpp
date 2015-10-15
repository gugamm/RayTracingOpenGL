#include "GLInit.h"

#include <GLFW\glfw3.h>

#include <iostream>

#define WIDTH 800
#define HEIGHT 600

using namespace std;

int main(void) {

	if (glfwInit() == GLFW_FALSE) {
		printf("Could not initialize glfw\n");
		exit(EXIT_FAILURE);
	}
	glViewport(0, 0, WIDTH, HEIGHT);

	//hints for the window that will be created
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	//Create a window and set the context of openGL to her
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Ray Tracing :: Gustavo Martins", NULL, NULL);
	glfwMakeContextCurrent(window);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	

	//Initialize glew
	glewExperimental = GL_TRUE;
	if (glewInit()) {
		printf("Could not initialize glew\n");
		getchar();
		exit(EXIT_FAILURE);
	}

	GLuint screenVao = createScreenVao();
	GLuint program = loadPrograms();
	
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(program);
		glBindVertexArray(screenVao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid *)0);
		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}
