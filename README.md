# OpenGL Evolution
## 1: Hello Triangle

## Contributors
- Christopher Rice

## Controls
- Esc (Closes window)

## Description
This is the first project in my OpenGL Evolution series. Hello Triangle is known in the graphics programming community as the Hello World of graphics programming. This may seem like a simple image but graphics programming is very front heavy and requires a lot of knowledge of how the graphics pipeline works. I will try my best to explain the important part of the project below.

### GLFW
GLFW is a multi-platform library that allows for programmers to write code to open and manage windows, handle events and inputs, and create OpenGL contexts with ease. You can do a lot with GLFW without having to know any of the implementation of your OS's API. In this project, I use GLFW to create a small window with an OpenGL context. The window will react to certain events like resizing, closing the window, and keyboard input.

### Vertex Buffer Object
A vertex buffer object or VBO is an object used by OpenGL for giving vertex data to the GPU. Sending data to from the CPU to the GPU would be too expensive so OpenGL provides us with VBOs which allows us to send data to the GPU in one large go. In this project, we fill a single VBO with the three vertices of our triangle.

### Vertex Attribute
A vertex attribute is the argument we supply to our vertex shader. We need to define the vertex argument and tell it exactly how to read the date from the VBO. In this project, we told the vertex attribute that the vertices that we send are floats that should be read three at a time. 

### Vertex Array Object
A vertex array object is another object in OpenGl that helps to remember vertex data. When bound, the VAO will store vertex attribute information. We can then unbind the VAO and bind it again whenever we want to use that vertex data. 

### Vertex and Fragment Shaders
The vertex and fragment shaders are the two shaders that OpenGL needs defined by the user. The vertex shaders accepts a vertex and outputs a vertex while the fragment shader takes in fragments and outputs final colors. The vertex and fragment shaders need to be defined in OpenGL's shader language GLSL the compiled and linked together into a shader program which will be used for rendering.

## Sources
- https://learnopengl.com/
    - Used their website and online textbook to learn OpenGL
- https://www.khronos.org/opengl/wiki/Main_Page
    - Used to research all of the different OpenGL functions and objects
- https://www.glfw.org/
    - Used for creating windows, registering input, and easy integration with OpenGL
- https://www.youtube.com/watch?v=pSirBt4OgXQ&t=607s&ab_channel=Code%2CTech%2CandTutorials
    - A great tutorial for setting up vcpkg manager