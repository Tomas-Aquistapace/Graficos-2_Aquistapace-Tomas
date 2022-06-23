#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "..\..\Renderer\Renderer.h"
#include "..\..\Entity\Entity.h"
#include "..\..\Export\Export.h"

using namespace std;

namespace Engine 
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};
	
	struct Texture 
	{
		unsigned int id;
		string type;
		string path;
	};

	class EXPORT_API Mesh : public Entity
	{
	private:
		unsigned int _vao;
		unsigned int _vbo;
		unsigned int _ebo;
		unsigned int _positionAttrib;
		unsigned int _normalAttrib;
		unsigned int _textureAttrib;

		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<Texture> textures;
		
		Renderer* _renderer;

		void SetUpMesh();

	public:
		
		Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, Renderer* renderer);
		~Mesh();
		void Draw();

		// --------------------------------
		// Virtual Functions:

		void SetColor(ENTITY_COLOR color);
		void SetColor(float r, float g, float b);
		void TriggerCollision(Entity* other);
	};
}

#endif