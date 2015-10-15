#include "GLInit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#define VERTEX_PATH "C:\\Users\\guga\\Documents\\Visual Studio 2015\\Projects\\OpenGlProject\\ShadersSources\\vertexShader.vs"
#define FRAGMENT_PATH "C:\\Users\\guga\\Documents\\Visual Studio 2015\\Projects\\OpenGlProject\\ShadersSources\\fragmentShader.fsh"
using namespace std;

static GLuint loadShader(const char *path, GLenum type);

GLuint createScreenVao() {
	//Vertices of a square that will represent the screen
	GLfloat vertices[] = {
		-1.0f ,  1.0f,  //top left
		-1.0f , -1.0f,  //bottom left
		 1.0f , -1.0f,  //bottom right
		 1.0f ,  1.0f   //top right
	};
	
	GLuint screenVao;
	//Create a vao to store attributes (vertices and other informations) to be used
	//by shaders
	glGenVertexArrays(1, &screenVao);
	//Bind the vao to openGL so we can set attributes
	glBindVertexArray(screenVao);
	//Create a Vertex Buffer Object to store vertices
	GLuint screenVbo;
	glGenBuffers(1, &screenVbo);
	glBindBuffer(GL_ARRAY_BUFFER, screenVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	//Create indexes to be used by a Index Buffer Object (IBO)
	GLuint indexes[] = {
		0,1,2, //leftBottom triangle
		0,3,2  //rightTop triangle
	};

	GLuint screenIbo;
	glGenBuffers(1, &screenIbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, screenIbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

	//Pass data to shaders
	//AttribId, vec2 type, type of data, not normilize, stride, offset 
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);
	//Unbind the vao
	glBindVertexArray(0);
	return screenVao;
}

static std::string getSource(const char *path) {
	std::string code;
	std::ifstream shaderFile;
	// ensures ifstream objects can throw exceptions:
	shaderFile.exceptions(std::ifstream::badbit);
	try
	{
		// Open files
		shaderFile.open(path);
		
		std::stringstream shaderStream;
		// Read file's buffer contents into streams
		shaderStream << shaderFile.rdbuf();
		// close file handlers
		shaderFile.close();
		
		// Convert stream into GLchar array
		code = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	
	return code;
}

GLuint loadPrograms() {
	std::string vSource = getSource(VERTEX_PATH);
	const GLchar *vertexSource = vSource.c_str();
	std::string fSource = getSource(FRAGMENT_PATH);
	const GLchar *fragmentSource = fSource.c_str();
	//getSources
	GLuint vertexShader = loadShader(vertexSource, GL_VERTEX_SHADER);
	GLuint fragmentShader = loadShader(fragmentSource, GL_FRAGMENT_SHADER);
	GLint status;
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	return program;
}

static GLuint loadShader(const char *source, GLenum type) {
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	return shader;
}

