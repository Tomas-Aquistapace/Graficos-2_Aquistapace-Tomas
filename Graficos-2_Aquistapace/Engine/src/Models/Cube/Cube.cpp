#include "Cube.h"

namespace Engine
{
	int _vertexSize;

	float Cube::_vertex[] =
	{
		//Position              //Normal               //UV       
		//-----------------
		-0.5f,  0.5f, -0.5f,  	0.0f,  0.0f, -1.0f,    0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  	0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  	0.0f,  0.0f, -1.0f,    1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  	0.0f,  0.0f, -1.0f,    1.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  	0.0f,  0.0f,  1.0f,    1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  	0.0f,  0.0f,  1.0f,    1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    1.0f, 0.0f,

		-0.5f,  0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,

		 0.5f,  0.5f, -0.5f,  	1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  	1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  	1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  	1.0f,  0.0f,  0.0f,    1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  	0.0f, -1.0f,  0.0f,    0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  	0.0f, -1.0f,  0.0f,    1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  	0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  	0.0f, -1.0f,  0.0f,    1.0f, 0.0f,

		-0.5f,  0.5f, -0.5f,  	0.0f,  1.0f,  0.0f,    0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  	0.0f,  1.0f,  0.0f,    1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  	0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  	0.0f,  1.0f,  0.0f,	   1.0f, 0.0f
	};

	unsigned int Cube::_index[] =
	{
		0, 1, 2,
		0, 3, 2,
		4, 5, 6,
		4, 7, 6,
		8, 9, 10,
		8, 11, 10,
		12, 13, 14,
		12, 15, 14,
		16, 17, 18,
		16, 19, 18,
		20, 21, 22,
		20, 23, 22
	};

	// -------------------------------------------

	Cube::Cube(Renderer* renderer)
	{
		_textureImporter = new TextureImporter();

		_renderer = renderer;

		_material._ambient = glm::vec3(0.6f, 0.2f, 0.31f);
		_material._diffuse = glm::vec3(0.6f, 0.2f, 0.31f);
		_material._specular = glm::vec3(0.5f, 0.5f, 0.5f);
		_material._shininess = 32.0f;
	}

	Cube::~Cube()
	{
		_renderer->DeleteBuffers(_vao, _vbo, _ebo);

		if (_textureImporter != NULL)
		{
			delete _textureImporter;
			_textureImporter = NULL;
		}
	}

	void Cube::InitTexture(const char* name)
	{
		_vertexSize = sizeof(_vertex);

		_renderer->SetVertexBuffer(_vertexSize, _vertex, _vao, _vbo);
		_renderer->SetIndexBuffer(_vertexSize, _index, _ebo);

		_renderer->SetCubeVertexAttribPointer(_modelUniform);

		_textureImporter->ImportTexture(_renderer, name, _texture);
	}

	void Cube::Draw()
	{
		if (GetHableToDraw())
		{
			_renderer->UpdateMaterial(_material);
			_renderer->UpdateModel(_generalMatrix.model, _modelUniform);

			_renderer->BindTexture(_texture);

			_renderer->Draw(_vao, _vbo, _ebo, _vertex, _vertexSize, sizeof(_index) / sizeof(float));

			_renderer->DisableTexture();
		}
	}

	// ------------------------------------

	void Cube::SetMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
	{
		_material._ambient = ambient;
		_material._diffuse = diffuse;
		_material._specular = specular;
		_material._shininess = shininess;
	}

	void Cube::SetColor(float r, float g, float b) 
	{
		_material._diffuse = glm::vec3(r,g,b) * glm::vec3(0.5f);
		_material._ambient = _material._diffuse * glm::vec3(0.2f);
	}

	void Cube::SetColor(ENTITY_COLOR color) { }
	void Cube::TriggerCollision(Entity* other) { }
}