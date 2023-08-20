#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "shader.h"

bool bUseUniform = false;

static void errorCallback(int error, const char* description)
{
	std::cout << "AN ERROR HAS OCCURED" << std::endl;
}

static void windowCloseCallback(GLFWwindow* window)
{
	// Closing window
	glfwSetWindowShouldClose(window, GLFW_TRUE);
	std::cout << "WINDOW CLOSED" << std::endl;
}

static void windowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Checks if user presses the escape key
	if ((key == GLFW_KEY_ESCAPE) && (action == GLFW_PRESS))
	{
		// Sets window close flag
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		std::cout << "WINDOW CLOSED" << std::endl;
	}

	// Checks if user presses the space key
	if ((key == GLFW_KEY_SPACE) && (action == GLFW_PRESS))
	{
		// Sets the flag for using the uniform
		bUseUniform = !bUseUniform;

		if (bUseUniform)
		{
			std::cout << "ANIMATION ON" << std::endl;
		}
		else
		{
			std::cout << "ANIMATION OFF" << std::endl;
		}
	}
}

static void windowFramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	// Changes viewport size to match framebuffer size
	glViewport(0, 0, width, height);
	std::cout << "NEW VIEWPORT SIZE" << std::endl;
	std::cout << "Width: " << width << std::endl;
	std::cout << "Height: " << height << std::endl;
}

void performanceStatsOutput(int& frame, float& lastTime, float& timePassed)
{
	// Gets the frame time (Time between frames)
	float currentTime = glfwGetTime();
	float frameTime = currentTime - lastTime;
	lastTime = currentTime;

	// Accumulates frame time
	timePassed += frameTime;

	// Check if one second has passed
	if (timePassed >= 1.0f)
	{
		// Prints number of frames since last print
		std::cout << "FPS: " << frame << std::endl;
		std::cout << "Frame Time (ms): " << frameTime * 1000.0f << std::endl;

		// Resets
		frame = 0;
		timePassed = 0.0f;
	}

	// Increments frame
	frame += 1;
}

int main()
{
	// Initiating glfw
	if (!glfwInit())
	{
		// Initialization fails
		return(1);
	}

	// Initial colors stored in vector
	std::vector<float> clearColor {
		102.0f / 255.0f, 
		255.0f / 255.0f, 
		255.0f / 255.0f, 
		255.0f / 255.0f
	};

	// Vector of verticies
	float vertices[]{
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f
	};

	// Setting minimum version of OpenGL to use (3.3) and saying we want to use the core profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creating first window
	GLFWwindow* window = glfwCreateWindow(640, 480, "My First Window", NULL, NULL);

	// Checking if window wasn't properly created
	if (!window)
	{
		std::cout << "ERROR: WINDOW CREATION FAILED" << std::endl;
		return(1);
	}

	// Making the context current
	glfwMakeContextCurrent(window);

	// Setting the window callbacks
	glfwSetErrorCallback(errorCallback);
	glfwSetWindowCloseCallback(window, windowCloseCallback);
	glfwSetKeyCallback(window, windowKeyCallback);
	glfwSetFramebufferSizeCallback(window, windowFramebufferSizeCallback);

	// Initializing glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "ERROR: FAILED TO INITIALIZE GLAD" << std::endl;
		return(1);
	}

	Shader triangleShader("triangleVertexShader.vs", "triangleVertexShader.fs");

	// Setting up vertex array object
	unsigned int vertexArrayObj;
	glGenVertexArrays(1, &vertexArrayObj); /* Creating a vertex array object */

	// Setting up vertex buffer object
	unsigned int vertexBufferObj;
	glGenBuffers(1, &vertexBufferObj); /* Creates the vertex buffer object */

	// Bind vertex array to the context
	glBindVertexArray(vertexArrayObj);

	// Binds vertex buffer and copies data into it
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObj);							   
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

	// Setting up the vertex attribute pointer for position and color
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// We can unbind the VBO because the vertex attribute pointer is registered to it now
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// We can also unbind the VAO so that we don't accidently modify it
	glBindVertexArray(0);

	// Gets the window's framebuffer size and set viewport
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// Initial variables for calculating performance matrics
	int frame = 0;
	float timePassed = 0.0f;
	float lastTime = 0.0f;

	// Sets the swap interval
	glfwSwapInterval(0);

	// Getting the max number of vertex attributes
	int maxAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxAttributes);
	std::cout << "Max number of attributes suppoerted = " << maxAttributes << std ::endl;

	// Looping while window close flag isn't set
	while (!glfwWindowShouldClose(window))
	{
		// START RENDERING

		// Setting clear color and clearing color buffer
		glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
		glClear(GL_COLOR_BUFFER_BIT);
 
		// Changing RGB value with time
		float shift;
		if (bUseUniform)
		{
			shift = sin(glfwGetTime()) * 0.5f + 0.5f;
		}
		else
		{
			shift = 0.0f;
		}

		// Using the shader program
		triangleShader.activate();

		// Getting location of vertex color uniform and setting values
		triangleShader.setFloat("colorShift", shift);

		// Binding the vertex array and drawing triangle
		glBindVertexArray(vertexArrayObj);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// END RENDERING

		// Swaps the buffers
		glfwSwapBuffers(window);

		// Polls for all events
		glfwPollEvents();

		// Calculates frame information and prints it to console
		performanceStatsOutput(frame, lastTime, timePassed);
	}

	// Deallocates all objects and buffers
	glDeleteVertexArrays(1, &vertexArrayObj);
	glDeleteBuffers(1, &vertexBufferObj);
	//glDeleteProgram(shaderProgramObj);

	// Stops using glfw
	glfwTerminate();
	return(0);
}