#version 330 core
in vec3 vertexColor;
out vec4 fragColor;
uniform float colorShift;
void main()
{
	float newRed = vertexColor.x + colorShift;
	float newGreen = vertexColor.y + colorShift;
	float newBlue = vertexColor.z + colorShift;
	if (newRed >= 1.0)
	{
		newRed = newRed - 1.0;
	}
	if (newGreen >= 1.0)
	{
		newGreen = newGreen - 1.0;
	}
	if (newBlue >= 1.0)
	{
		newBlue = newBlue - 1.0;
	}
	fragColor = vec4(newRed, newGreen, newBlue, 1.0);
}