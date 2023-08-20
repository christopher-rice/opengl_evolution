# OpenGL Evolution
## 2: Rainbow Triangle

## Contributors
- Christopher Rice

## Controls
- Esc (Closes window)
- Space (Toggle animation)

## Description
This is the second project in my OpenGL Evolution series. The goal of this project is to use shaders to create a multi-colored triangle. Color data is added to each vertex by placing it alongside the position data of each vertex in the vertex buffer. I configured two vertex attributes, one for position data and another for color data, that passes the data to the vertex shader. The vertex shader receives the position data from the vertex attribute and passes along the color data to the fragment shader. The fragment shader takes the color data and outputs it. This results in a multicolored triangle with each vertex having its respect colors. The colors in the middle are the result of interporlation that automatically occurs within the vertex shader. I also added a uniform to the shader to pass in a constantly changing value that allows for the color of the vertices to change over time. The uniform can be toggled on and off with the space bar. The final aspect of the project that I would like to highlight is the shader class that makes it easier to program and use shaders. With the shader class, you can write shader programs in other files and the class will read the code from the files, copy them to strings, compile, and link them. Being able to write shaders within a serparate file instead of a string within your code makes programming shaders easier and more efficient.   

## Sources
- https://learnopengl.com/
    - Used their website and online textbook to learn OpenGL
- https://www.khronos.org/opengl/wiki/Main_Page
    - Used to research all of the different OpenGL functions and objects
- https://www.glfw.org/
    - Used for creating windows, registering input, and easy integration with OpenGL
- https://www.youtube.com/watch?v=pSirBt4OgXQ&t=607s&ab_channel=Code%2CTech%2CandTutorials
    - A great tutorial for setting up vcpkg manager
