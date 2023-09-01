#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "stb_image.h"

int screenWidth = 800;
int screenHeight = 800;
float smileCount = 1.0f;
float blend = 0.2f;
float redFilter = 1.0f;
float greenFilter = 1.0f;
float blueFilter = 1.0f;
bool bUseColor = false;

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

	// Checks if user presses up arrow key
	if ((key == GLFW_KEY_UP) && (action == GLFW_TRUE))
	{
		smileCount += 1.0f;
	}

	// Checks if user presses down arrow key
	if ((key == GLFW_KEY_DOWN) && (action == GLFW_TRUE))
	{
		smileCount -= 1.0f;
	}

	// Checks if user presses left arrow key
	if ((key == GLFW_KEY_LEFT) && (action == GLFW_TRUE))
	{
		if ((blend - 0.01f) >= 0.0f)
		{
			blend -= 0.1;
		}
	}

	// Checks if user presses right arrow key
	if ((key == GLFW_KEY_RIGHT) && (action == GLFW_TRUE))
	{
		if ((blend + 0.01f) <= 1.0f)
		{
			blend += 0.1;
		}
	}

	// Checks if user presses z key
	if ((key == GLFW_KEY_Z) && (action == GLFW_TRUE))
	{
		if (redFilter == 1.0f)
		{
			redFilter = 0.0f;
		}
		else
		{
			redFilter = 1.0f;
		}
	}

	// Checks if user presses x key
	if ((key == GLFW_KEY_X) && (action == GLFW_TRUE))
	{
		if (greenFilter == 1.0f)
		{
			greenFilter = 0.0f;
		}
		else
		{
			greenFilter = 1.0f;
		}
	}

	// Checks if user presses c key
	if ((key == GLFW_KEY_C) && (action == GLFW_TRUE))
	{
		if (blueFilter == 1.0f)
		{
			blueFilter = 0.0f;
		}
		else
		{
			blueFilter = 1.0f;
		}
	}

	// Checks if user presses space bar
	if ((key == GLFW_KEY_SPACE) && (action == GLFW_TRUE))
	{
		bUseColor = !bUseColor;
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

void printVector(glm::vec4 vector)
{
	std::cout << "-" << std::endl;
	std::cout << vector.x << std::endl;
	std::cout << vector.y << std::endl;
	std::cout << vector.z << std::endl;
	std::cout << vector.w << std::endl;
	std::cout << "-" << std::endl << std::endl;
}

int main()
{
	// Initializes a homogenous vector <1, 0, 0>
	glm::vec4 pos1(1.0f, 0.0f, 0.0f, 1.0f);

	// Initializes an identity matrix
	glm::mat4 transMat(1.0f);

	// Creating a translation matrix
	transMat = glm::translate(transMat, glm::vec3(1.0f, 1.0f, 0.0f));

	// Translating the position with the translation matrix
	glm::vec4 pos2 = transMat * pos1;

	// Printing the vectors
	std::cout << "Old Position = " << std::endl;
	printVector(pos1);
	std::cout << "New Position = " << std::endl;
	printVector(pos2);
}