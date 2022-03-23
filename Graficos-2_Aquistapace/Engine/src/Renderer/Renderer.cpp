#include "Renderer.h"
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm\gtc\type_ptr.hpp"

namespace Engine
{
	Renderer::Renderer()
	{		
		_shader = new Shader();
		_camera = new Camera();
	}

	Renderer::~Renderer()
	{
		if (_shader != NULL)
		{
			delete _shader;
			_shader = NULL;
		}
		
		if (_camera != NULL)
		{
			delete _camera;
			_camera = NULL;
		}
	}

	int Renderer::InitGlew()
	{
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Error in Glew Init" << std::endl;
			return -1;
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Renderer::SetVertexBuffer(int size, float* vertex, unsigned int& vao, unsigned int& vbo)
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER, size, vertex, GL_STATIC_DRAW);
	}

	void Renderer::SetIndexBuffer(int size, unsigned int* index, unsigned int &ebo)
	{
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, index, GL_STATIC_DRAW);
	}

	void Renderer::SetVertexAttribPointer(bool shape, unsigned int& model)
	{
		if (shape)
		{
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
		}
		else
		{
			// position attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			// color attribute
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			// texture coord attribute
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
			glEnableVertexAttribArray(2);
		}

		model = glGetUniformLocation(GetShader(), "model");
	}

	void Renderer::CreateShader()
	{
		_shader->SetShader("../Engine/shaders/Vertex.shader", "../Engine/shaders/Fragment.shader");
		glUseProgram(_shader->GetShader());

		_camera->SetIndex(_shader->GetShader());
	}
	
	void Renderer::BindTexture(unsigned int& texture)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	void Renderer::DisableTexture()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDisable(GL_TEXTURE_2D);
	}

	void Renderer::Draw(unsigned int& vao, unsigned int& vbo, unsigned int& ebo, float* vertex, float vertexSize, int vertexCount)
	{
		glUseProgram(_shader->GetShader());
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ARRAY_BUFFER, vertexSize, vertex, GL_STATIC_DRAW);

		glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glUseProgram(0);
	}

	void Renderer::UpdateModel(glm::mat4 model, unsigned int modelUniform)
	{
		glUseProgram(_shader->GetShader());
		glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(model));

		_camera->UpdateMVP(model);

		glUseProgram(0);
	}
	
	void Renderer::StopShader()
	{
		if (_shader != NULL)
		{
			_shader->ClearShader();
		}
	}

	void Renderer::DeleteBuffers(unsigned int& vao, unsigned int& vbo, unsigned int& ebo)
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ebo);
	}

	void Renderer::SetCameraValues(CameraType type, float near, float far)
	{
		_camera->SetCameraValues(type, near, far);
	}

	void Renderer::SetCameraPosition(float x, float y, float z)
	{
		_camera->SetCameraPosition(x, y, z);
	}

	// ----------------------------

	unsigned int Renderer::GetShader() 
	{
		return _shader->GetShader();
	}
}