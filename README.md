# OpenGL Evolution
## 3: Textured Triangle

## Contributors
- Christopher Rice

## Controls
- Esc (Closes window)
- Left and Right Arrow Keys (Adjust texture blend)
- Up and Down Arrow Keys (Increments or decrements amount of smiley faces on x and y axes)
- Space (Toggles vertex colors on and off)
- z (Toggles red vertex color)
- x (Toggles green vertex color)
- c (Toggles blue vertex color)

## Description
This is the third project in my OpenGL Evolution series. The goal of this project is to learn how to apply textures to polygons. The first noticable difference between this project and the previous project is that instead of a triangle, we are rendering a square. In order to render the square efficiently, I introduced an element buffer object (EBO) to the pipeline. The element buffer object allows the user to list the indices of vertices in drawing order instead of having to repeat the same vertices in the VBO. Textures are images that we can place onto polygons to give details to the flat shapes. In order to get the image data into the program, I used the stb_image header which includes many useful function for loading and formatting image data. After the image data is loaded, I copy and format it into a texture object which is then binded to the pipeline for use in the final image. In this project, I use two textures, a crate texture and a smiley face texture. In order to use both of them, I assigned each texture to a unique space in memory called a texture unit. Along with each vertex's position and color data, texture coordinate data is packed in so the fragment shader knows which section of the texture to sample from. The texture coordinates range from 0 to 1 in the x and y axes with any values outside the cause a predefined behavior which in this project causes the texture to repeat. In this project, I blend the two textures together within the fragment shader to get the final image. I added several uniforms to allow the user to control the image. Pressing the left and right arrow keys will change the blend value and adjust which texture has more of a priority. Pressing the up and down arrow keys will adjust the scale of the texture coordinates for the smiley face texture which results in more smiley faces being repeated along the x and y axes. The spacebar is used to toggle the color data within the vertices on and off with the z, x, and c keys being used to toggle the respective RGB color channels.

## Sources
- https://learnopengl.com/
    - Used their website and online textbook to learn OpenGL
    - Supplied the textures used in the project
- https://www.khronos.org/opengl/wiki/Main_Page
    - Used to research all of the different OpenGL functions and objects
- https://www.glfw.org/
    - Used for creating windows, registering input, and easy integration with OpenGL
- https://www.youtube.com/watch?v=pSirBt4OgXQ&t=607s&ab_channel=Code%2CTech%2CandTutorials
    - A great tutorial for setting up vcpkg manager