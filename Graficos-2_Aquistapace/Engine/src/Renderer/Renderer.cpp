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
		_camera = NULL;

		DefaultCameraValues();
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

		//glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
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

	void Renderer::SetCubeVertexAttribPointer(unsigned int& model)
	{
		//Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		//Normal
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		//Texture coordinates
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);

		model = glGetUniformLocation(GetShader(), "model");
	}

	void Renderer::CreateShader()
	{
		_shader->SetShader("../Engine/shaders/Vertex.shader", "../Engine/shaders/Fragment.shader");
		glUseProgram(_shader->GetShader());

		DefaultCameraIndex(_shader->GetShader());

		glUniform1i(glGetUniformLocation(_shader->GetShader(), "u_material.diffuse"), 0);
		glUniform1i(glGetUniformLocation(_shader->GetShader(), "u_material.specular"), 1);
	}
	
	void Renderer::BindTexture(unsigned int& texture)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
	}
	
	void Renderer::BindTextures(unsigned int& texture1, unsigned int& texture2)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
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

		if(_camera != NULL)
			_camera->UpdateMVP(model);
		else
		{
			glUniformMatrix4fv(_defModelInd, 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(_defViewInd, 1, GL_FALSE, glm::value_ptr(_defView));
			glUniformMatrix4fv(_defProjectionInd, 1, GL_FALSE, glm::value_ptr(_defProjection));
		}

		glUseProgram(0);
	}
	
	void Renderer::UpdateMaterial(MaterialData& material)
	{
		glUseProgram(_shader->GetShader());

		//glUniform3fv(glGetUniformLocation(_shader->GetShader(), "material.specular"), 1, &material._specular[0]);
		//glUniform1i(glGetUniformLocation(_shader->GetShader(), "u_material.specular"), 1);
		glUniform1f(glGetUniformLocation(_shader->GetShader(), "u_material.shininess"), material._shininess);

		glUseProgram(0);
	}

	void Renderer::UpdateDirectionalLight(LightData& light, DirectionLightData& directional)
	{
		glUseProgram(_shader->GetShader());

		glm::vec4 u_color = { 0.5f, 0.5f, 0.5f, 0.5f };

		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "u_color"), 1, &u_color[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "u_viewPos"), 1, &_camera->GetPosition()[0]);

		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "u_directionLight.color"), 1, &light._color[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "u_directionLight.direction"), 1, &directional._direction[0]);

		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "u_directionLight.ambient"), 1, &light._ambient[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "u_directionLight.diffuse"), 1, &light._diffuse[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "u_directionLight.specular"), 1, &light._specular[0]);

		glUniform1i(glGetUniformLocation(_shader->GetShader(), "u_directionLight.isActive"), light._isActive);

		glUseProgram(0);
	}

	void Renderer::UpdatePointLight(LightData& light, PointLightData& point)
	{
		glUseProgram(_shader->GetShader());

		glm::vec4 u_color = { 0.5f, 0.5f, 0.5f, 0.5f };

		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "u_color"), 1, &u_color[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "u_viewPos"), 1, &_camera->GetPosition()[0]);

		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "u_pointLight.color"), 1, &light._color[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "u_pointLight.position"), 1, &point._position[0]);

		glUniform1f(glGetUniformLocation(_shader->GetShader(), "u_pointLight.constant"), point._constant);
		glUniform1f(glGetUniformLocation(_shader->GetShader(), "u_pointLight.linear"), point._linear);
		glUniform1f(glGetUniformLocation(_shader->GetShader(), "u_pointLight.quadratic"), point._quadratic);

		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "u_pointLight.ambient"), 1, &light._ambient[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "u_pointLight.diffuse"), 1, &light._diffuse[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "u_pointLight.specular"), 1, &light._specular[0]);

		glUniform1i(glGetUniformLocation(_shader->GetShader(), "u_pointLight.isActive"), light._isActive);

		glUseProgram(0);
	}

	void Renderer::UpdateSpotLight(LightData& light, SpotLightData& spot)
	{
		glUseProgram(_shader->GetShader());

		glm::vec4 u_color = { 0.5f, 0.5f, 0.5f, 0.5f };

		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "u_color"), 1, &u_color[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "u_viewPos"), 1, &_camera->GetPosition()[0]);

		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "u_spotLight.color"), 1, &light._color[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "u_spotLight.position"), 1, &spot._position[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "u_spotLight.direction"), 1, &spot._direction[0]);

		glUniform1f(glGetUniformLocation(_shader->GetShader(), "u_spotLight.cutOff"), spot._cutOff);
		glUniform1f(glGetUniformLocation(_shader->GetShader(), "u_spotLight.outerCutOff"), spot._outerCutOff);

		glUniform1f(glGetUniformLocation(_shader->GetShader(), "u_spotLight.constant"), spot._constant);
		glUniform1f(glGetUniformLocation(_shader->GetShader(), "u_spotLight.linear"), spot._linear);
		glUniform1f(glGetUniformLocation(_shader->GetShader(), "u_spotLight.quadratic"), spot._quadratic);

		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "u_spotLight.ambient"), 1, &light._ambient[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "u_spotLight.diffuse"), 1, &light._diffuse[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "u_spotLight.specular"), 1, &light._specular[0]);

		glUniform1i(glGetUniformLocation(_shader->GetShader(), "u_spotLight.isActive"), light._isActive);

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

	void Renderer::SetCameraInUse(Camera* camera)
	{
		if (camera == NULL)
		{
			std::cout << "Error:: the camera is NULL" << std::endl;
		}
		else
		{
			if (_camera != NULL)
				_camera = NULL;

			_camera = camera;
			_camera->SetIndex(_shader->GetShader());
		}
	}

	void Renderer::UnlockCamera()
	{
		if (_camera != NULL)
			_camera = NULL;
	}

	// ----------------------------

	unsigned int Renderer::GetShader()
	{
		return _shader->GetShader();
	}

	// ----------------------------
	// Private Functions:

	void Renderer::DefaultCameraValues()
	{
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		
		_defView = glm::lookAt(cameraPos, cameraTarget, up);
		_defProjection = glm::perspective(glm::radians(45.0f), 1366.0f / 768.0f, 0.1f, 100.0f);
	}
	
	void Renderer::DefaultCameraIndex(unsigned int shaderId)
	{
		_defModelInd = glGetUniformLocation(shaderId, "model");
		_defViewInd = glGetUniformLocation(shaderId, "view");
		_defProjectionInd = glGetUniformLocation(shaderId, "projection");
	}
}