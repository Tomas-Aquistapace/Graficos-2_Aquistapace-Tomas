#include "Cube.h"

namespace Engine
{
	int _vertexSize;

	float Cube::_vertex[] =
	{
		//Position              //Normal               //UV       
		//-----------------
		-0.5f, -0.5f, -0.5f,  	0.0f,  0.0f, -1.0f,    0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  	0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  	0.0f,  0.0f, -1.0f,    1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  	0.0f,  0.0f, -1.0f,    1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  	0.0f,  0.0f, -1.0f,    0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  	0.0f,  0.0f, -1.0f,    0.0f, 1.0f,

		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  	0.0f,  0.0f,  1.0f,    1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  	0.0f,  0.0f,  1.0f,    1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  	0.0f,  0.0f,  1.0f,    0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  	0.0f,  0.0f,  1.0f,    0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,

		 0.5f,  0.5f,  0.5f,  	1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  	1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  	1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  	1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  	1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  	1.0f,  0.0f,  0.0f,    0.0f, 1.0f,

		-0.5f, -0.5f, -0.5f,  	0.0f, -1.0f,  0.0f,    0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  	0.0f, -1.0f,  0.0f,    1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  	0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  	0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  	0.0f, -1.0f,  0.0f,    0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  	0.0f, -1.0f,  0.0f,    0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  	0.0f,  1.0f,  0.0f,    0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  	0.0f,  1.0f,  0.0f,    1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  	0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  	0.0f,  1.0f,  0.0f,	   1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  	0.0f,  1.0f,  0.0f,    0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  	0.0f,  1.0f,  0.0f,    0.0f, 1.0f
	};

	unsigned int Cube::_index[] =
	{
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		9, 10, 11,
		12, 13, 14,
		15, 16, 17,
		18, 19, 20,
		21, 22, 23,
		24, 25, 26,
		27, 28, 29,
		30, 31, 32,
		33, 34, 35
	};

	// -------------------------------------------

	Cube::Cube(Renderer* renderer)
	{
		_textureImporter = new TextureImporter();

		_renderer = renderer;
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
			_renderer->UpdateModel(_generalMatrix.model, _modelUniform);

			_renderer->BindTexture(_texture);

			_renderer->Draw(_vao, _vbo, _ebo, _vertex, _vertexSize, sizeof(_index) / sizeof(float));

			_renderer->DisableTexture();
		}
	}

	// ------------------------------------

	void Cube::SetColor(ENTITY_COLOR color) { }
	void Cube::SetColor(float r, float g, float b) { }
	void Cube::TriggerCollision(Entity* other) { }
}