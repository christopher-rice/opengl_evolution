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
float speedRot = 0.5f / 1000.0f;
float speedScale = 0.5f / 1000.0f;
float smileCount = 1.0f;
float blend = 0.2f;
float redFilter = 1.0f;
float greenFilter = 1.0f;
float blueFilter = 1.0f;
bool bUseColor = false;
bool bTurnRight = false;
bool bTurnLeft = false;
bool bScaleUp = false;
bool bScaleDown = false;

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
	if ((key == GLFW_KEY_UP) && (action == GLFW_PRESS))
	{
		smileCount += 1.0f;
	}

	// Checks if user presses down arrow key
	if ((key == GLFW_KEY_DOWN) && (action == GLFW_PRESS))
	{
		smileCount -= 1.0f;
	}

	// Checks if user presses left arrow key
	if ((key == GLFW_KEY_LEFT) && (action == GLFW_PRESS))
	{
		if ((blend - 0.01f) >= 0.0f)
		{
			blend -= 0.1;
		}
	}

	// Checks if user presses right arrow key
	if ((key == GLFW_KEY_RIGHT) && (action == GLFW_PRESS))
	{
		if ((blend + 0.01f) <= 1.0f)
		{
			blend += 0.1;
		}
	}

	// Checks if user presses z key
	if ((key == GLFW_KEY_Z) && (action == GLFW_PRESS))
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
	if ((key == GLFW_KEY_X) && (action == GLFW_PRESS))
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
	if ((key == GLFW_KEY_C) && (action == GLFW_PRESS))
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
	if ((key == GLFW_KEY_SPACE) && (action == GLFW_PRESS))
	{
		bUseColor = !bUseColor;
	}

	// Check if user presses d key
	if ((key == GLFW_KEY_D) && ((action == GLFW_PRESS) || (action == GLFW_REPEAT)))
	{
		bTurnRight = true;
	}
	else if ((key == GLFW_KEY_D) && (action == GLFW_RELEASE))
	{
		bTurnRight = false;
	}

	// Check if user presses a key
	if ((key == GLFW_KEY_A) && ((action == GLFW_PRESS) || (action == GLFW_REPEAT)))
	{
		bTurnLeft = true;
	}
	else if ((key == GLFW_KEY_A) && (action == GLFW_RELEASE))
	{
		bTurnLeft = false;
	}

	// Check if user presses w key
	if ((key == GLFW_KEY_W) && ((action == GLFW_PRESS) || (action == GLFW_REPEAT)))
	{
		bScaleUp = true;
	}
	else if ((key == GLFW_KEY_W) && (action == GLFW_RELEASE))
	{
		bScaleUp = false;
	}

	// Check if user presses s key
	if ((key == GLFW_KEY_S) && ((action == GLFW_PRESS) || (action == GLFW_REPEAT)))
	{
		bScaleDown = true;
	}
	else if ((key == GLFW_KEY_S) && (action == GLFW_RELEASE))
	{
		bScaleDown = false;
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
	// Initial colors stored in vector
	std::vector<float> clearColor {
		102.0f / 255.0f,
			255.0f / 255.0f,
			255.0f / 255.0f,
			255.0f / 255.0f
	};

	// Array of verticies
	float vertices[]{
		  0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
		  0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
		 -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
		 -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
	};

	// Array of indexes
	unsigned int indices[]{
		0, 1, 3,
		1, 2, 3
	};

	// Initiating glfw
	if (!glfwInit())
	{
		// Initialization fails
		return(1);
	}

	// Setting minimum version of OpenGL to use (3.3) and saying we want to use the core profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creating first window
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Textured Square", NULL, NULL);

	// Checking if window wasn't properly created
	if (!window)
	{
		std::cout << "ERROR: WINDOW CREATION FAILED" << std::endl;
		glfwTerminate();
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

	// Setting up element buffer object
	unsigned int elementBufferObj;
	glGenBuffers(1, &elementBufferObj);

	// Bind vertex array to the context
	glBindVertexArray(vertexArrayObj);

	// Binds vertex buffer and copies data into it
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObj);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Binds element buffer and copies data into it
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObj);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Setting up the vertex attribute pointer for position, color, and texture coordinates
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Creating a texture object
	unsigned int textureObj1, textureObj2;
	glGenTextures(1, &textureObj1);
	glGenTextures(1, &textureObj2);

	// Binding first texture
	glBindTexture(GL_TEXTURE_2D, textureObj1);

	// Parameters for out of bound texture coordinates
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Parameters for texture filtering and mipmap filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Loads crate texture
	int textureWidth, textureHeight, textureColors;
	unsigned char* textureData = stbi_load("crate.png", &textureWidth, &textureHeight, &textureColors, 3);

	if (textureData)
	{
		// Generating texture image
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);

		// Generating texture mipmap
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR: TEXTURE FAILED TO LOAD" << std::endl;
	}

	// Freeing the texture data
	stbi_image_free(textureData);

	// Binding second texture
	glBindTexture(GL_TEXTURE_2D, textureObj2);

	// Parameters for out of bound texture coordinates
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Parameters for texture filtering and mipmap filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Loads smile texture
	stbi_set_flip_vertically_on_load(true);
	textureData = stbi_load("awesomeface.png", &textureWidth, &textureHeight, &textureColors, 4);

	if (textureData)
	{
		// Generating texture image
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);

		// Generating texture mipmap
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR: TEXTURE FAILED TO LOAD" << std::endl;
	}

	// Setting uniforms
	triangleShader.activate();
	triangleShader.setInt("crateTexture", 0);
	triangleShader.setInt("smileTexture", 1);


	// We can unbind the VBO because the vertex attribute pointer is registered to it now
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// We can also unbind the VAO so that we don't accidently modify it
	glBindVertexArray(0);

	// Initial variables for calculating performance matrics
	int frame = 0;
	float timePassed = 0.0f;
	float lastTime = 0.0f;

	// Sets the swap interval
	glfwSwapInterval(0);

	// Getting the max number of vertex attributes
	int maxAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxAttributes);
	std::cout << "Max number of attributes suppoerted = " << maxAttributes << std::endl;

	float currRot = 0.0f;
	float currScale = 1.0f;

	// Looping while window close flag isn't set
	while (!glfwWindowShouldClose(window))
	{
		// Applying rotation with input
		if (bTurnRight)
		{
			currRot -= speedRot * timePassed;
		}

		if (bTurnLeft)
		{
			currRot += speedRot * timePassed;
		}

		// Applying scale with input
		if (bScaleUp)
		{
			currScale += speedScale * timePassed;
		}

		if (bScaleDown)
		{
			currScale -= speedScale * timePassed;
		}

		// Creating transformation matrix (scales by 0.5, rotates 90 degrees, then translates)
		glm::mat4 transMat(1.0f);
		//transMat = glm::translate(transMat, glm::vec3(0.25f, 0.25f, 0.0f));
		transMat = glm::rotate(transMat, currRot, glm::vec3(0.0f, 0.0f, 1.0f));
		transMat = glm::scale(transMat, glm::vec3(currScale, currScale, currScale));

		// START RENDERING

		// Setting clear color and clearing color buffer
		glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
		glClear(GL_COLOR_BUFFER_BIT);

		// Binding the texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureObj1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureObj2);

		// Using the shader program
		triangleShader.activate();

		// Setting uniforms
		triangleShader.setFloat("smileCount", smileCount);
		triangleShader.setFloat("blend", blend);
		triangleShader.setFloat("redFilter", redFilter);
		triangleShader.setFloat("greenFilter", greenFilter);
		triangleShader.setFloat("blueFilter", blueFilter);
		triangleShader.setBool("bUseColor", bUseColor);

		// Setting matrix uniform
		unsigned int transMatLoc = glGetUniformLocation(triangleShader.ID, "transMat");
		glUniformMatrix4fv(transMatLoc, 1, GL_FALSE, glm::value_ptr(transMat));

		// Binding the vertex array and drawing triangle
		glBindVertexArray(vertexArrayObj);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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