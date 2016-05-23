#version 420 //does vulkan respect GLSL standards?
in vec4 position;
in vec2 uv;

void main()
{
	gl_Position = position;
}
