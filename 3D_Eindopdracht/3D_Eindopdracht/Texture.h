#pragma once

#include <string>
#include <windows.h>
#include <gl/GL.h>

class Texture
{
	GLuint textureId;
public:
	Texture(const std::string &fileName);
	Texture();
	~Texture();
	void bind();
};