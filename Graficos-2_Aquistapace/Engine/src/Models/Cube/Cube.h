#ifndef CUBE_H
#define CUBE_H

#include "..\..\Export\Export.h"
#include "..\..\Renderer\Renderer.h"
#include "..\..\Entity\Entity.h"
#include "..\..\TextureImporter\TextureImporter.h"

namespace Engine
{
	const int CUBE_VERTEX_COMPONENTS = 288;
	const int CUBE_INDICES = 36;
	//const int CUBE_VERTICES = 8;

	class EXPORT_API Cube : public Entity
	{
	private:
		static float _vertex[CUBE_VERTEX_COMPONENTS];
		static unsigned int _index[CUBE_INDICES];

		unsigned int _vao; // Vertex Array Obj
		unsigned int _vbo; // Vertex Buffer Obj
		unsigned int _ebo; // Index Buffer Obj

		int _vertexSize;
		unsigned int _texture;

		unsigned int _modelUniform;

		TextureImporter* _textureImporter;
		Renderer* _renderer;

	public:
		Cube(Renderer* renderer);
		~Cube();

		void InitTexture(const char* name);
		void Draw();
		void SetColor(ENTITY_COLOR color);
		void SetColor(float r, float g, float b);
		void TriggerCollision(Entity* other);
	};
}
#endif