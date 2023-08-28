#version 330 core

in vec3 vertexColor;
in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D crateTexture;
uniform sampler2D smileTexture;

uniform float smileCount;
uniform float blend;
uniform float redFilter;
uniform float greenFilter;
uniform float blueFilter;
uniform bool bUseColor;

void main()
{
	vec4 colorFilter = vec4(vertexColor.x * redFilter, 
							vertexColor.y * greenFilter, 
							vertexColor.z * blueFilter, 
							1.0);

	if (!bUseColor)
	{
		colorFilter = vec4(1.0, 1.0, 1.0, 1.0);
	}

	vec4 textureColor = mix(texture(crateTexture, texCoord), 
							texture(smileTexture, texCoord * smileCount), 
							blend);

	fragColor = textureColor * colorFilter;
}