#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include "..\Export\Export.h"
#include "..\Shader\Shader.h"
#include "..\Camera\Camera.h"
#include "glm\glm\mat4x4.hpp"

namespace Engine
{
	enum class TypeOfShape {
		Triangle,
		Quad
	};

	class EXPORT_API Renderer
	{
	private:
		Shader* _shader;
		Camera* _camera;

	public:
		Renderer();
		~Renderer();
		
		int InitGlew();
		void SetVertexBuffer(int size, float* vertex, unsigned int &vao, unsigned int &vbo);
		void SetIndexBuffer(int size, unsigned int* index, unsigned int &ebo);
		void SetVertexAttribPointer(bool shape, unsigned int &model);
		void CreateShader();
		void BindTexture(unsigned int& texture);
		void DisableTexture();
		void Draw(unsigned int& vao, unsigned int& vbo, unsigned int& ebo, float* vertex, float vertexSize, int vertexCount);
		void UpdateModel(glm::mat4 model, unsigned int updateShape);

		void StopShader();
		void DeleteBuffers(unsigned int& vao, unsigned int& vbo, unsigned int& ebo);

		void SetCameraValues(CameraType type, float near, float far);
		void SetCameraPosition(float x, float y, float z);
		unsigned int GetShader();
	};
}
#endif