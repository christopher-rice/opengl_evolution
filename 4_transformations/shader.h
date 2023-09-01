#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
	public:
		// Program ID
		unsigned int ID;

		// Shader constructor
		Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

		// Activates the shader
		void activate();

		// Utility uniform functions
		void setBool(const std::string &name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;
};

// Shader constructor
Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	// String containing the code for the shaders
	std::string vertexShaderCode;
	std::string fragmentShaderCode;

	// File streams for files containing shader code
	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;

	// Enables exceptions for file streams
	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// Opens the two shader files
		vertexShaderFile.open(vertexShaderPath);
		fragmentShaderFile.open(fragmentShaderPath);

		// Creates string stream objects for two shaders
		std::stringstream vertexShaderSS;
		std::stringstream fragmentShaderSS;

		// Reading the file buffer contents into the string streams
		vertexShaderSS << vertexShaderFile.rdbuf();
		fragmentShaderSS << fragmentShaderFile.rdbuf();

		// Converts the string stream into a string
		vertexShaderCode = vertexShaderSS.str();
		fragmentShaderCode = fragmentShaderSS.str();
	}
	catch(std::ifstream::failure e)
	{
		std::cout << "ERROR: SHADER FILE FAILED TO READ" << std::endl;
	}

	// Converting c++ strings to c string
	const char* vertexShaderCodeC = vertexShaderCode.c_str();
	const char* fragmentShaderCodeC = fragmentShaderCode.c_str();

	// Setting up vertex shader object
	int success;
	char infoLog[512];
	unsigned int vertexShaderObj = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderObj, 1, &vertexShaderCodeC, NULL);
	glCompileShader(vertexShaderObj);
	glGetShaderiv(vertexShaderObj, GL_COMPILE_STATUS, &success);

	// Checks if vertex compilation was successful
	if (!success)
	{
		// Gets the compilation error message from shader message
		glGetShaderInfoLog(vertexShaderObj, 512, NULL, infoLog);

		// Prints out error message
		std::cout << "ERROR: VERTEX SHADER COMPILATION FAILED" << std::endl;
		std::cout << infoLog << std::endl;
	}

	// Setting up fragment shader object
	unsigned int fragmentShaderObj = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderObj, 1, &fragmentShaderCodeC, NULL);
	glCompileShader(fragmentShaderObj);
	glGetShaderiv(fragmentShaderObj, GL_COMPILE_STATUS, &success);

	// Checks if fragment compilation was successful
	if (!success)
	{
		// Gets the compilation error message from shader message
		glGetShaderInfoLog(fragmentShaderObj, 512, NULL, infoLog);

		// Prints out error message
		std::cout << "ERROR: FRAGMENT SHADER COMPILATION FAILED" << std::endl;
		std::cout << infoLog << std::endl;
	}

	// Setting up a shader program object
	unsigned int shaderProgramObj = glCreateProgram();
	glAttachShader(shaderProgramObj, vertexShaderObj);
	glAttachShader(shaderProgramObj, fragmentShaderObj);
	glLinkProgram(shaderProgramObj);
	glGetProgramiv(shaderProgramObj, GL_LINK_STATUS, &success);

	// Checks if shader linking was successful
	if (!success)
	{
		// Gets the compilation error message from shader message
		glGetProgramInfoLog(shaderProgramObj, 512, NULL, infoLog);

		// Prints out error message
		std::cout << "ERROR: SHADER LINKING FAILED" << std::endl;
		std::cout << infoLog << std::endl;
	}

	// Deletes the vertex and fragment shader objects as they are no longer needed
	glDeleteShader(vertexShaderObj);
	glDeleteShader(fragmentShaderObj);

	// Sets the ID
	ID = shaderProgramObj;
}

// Activates the shader
void Shader::activate()
{
	glUseProgram(ID);
}

// Utility uniform functions
void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

#endif
