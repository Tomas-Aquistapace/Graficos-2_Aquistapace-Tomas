#include "TextureImporter.h"

#include "GL\glew.h"
#include "glm\glm.hpp"

//#define STB_IMAGE_IMPLEMENTATION
#include "..\TextureImporter\stb_image.h"

#include <iostream>

using namespace std;

namespace Engine
{
	TextureImporter::TextureImporter()
	{

	}

	TextureImporter::~TextureImporter()
	{

	}

	void TextureImporter::ImportTexture(Renderer* renderer, const char* name, unsigned int& texture)
	{
		stbi_set_flip_vertically_on_load(true);

		_data = stbi_load(name, &_width, &_height, &_nrChannels, 0);

		if (!_data)
		{
			cout << "failed to load texture" << endl;
			return;
		}

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (_nrChannels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _data);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _data);
		}

		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(_data);

		glUseProgram(renderer->GetShader());
		glUniform1i(glGetUniformLocation(renderer->GetShader(), "ourTexture"), 0);
	}
}