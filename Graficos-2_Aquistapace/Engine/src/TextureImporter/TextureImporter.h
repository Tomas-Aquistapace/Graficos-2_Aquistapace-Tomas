#ifndef TEXTURE_IMPORTER_H
#define TEXTURE_IMPORTER_H

#include "..\Export\Export.h"
#include "..\Renderer\Renderer.h"

namespace Engine
{
	class EXPORT_API TextureImporter
	{
		int _width, _height, _nrChannels;

		unsigned char* _data;

	public:
		TextureImporter();
		~TextureImporter();

		void ImportTexture(Renderer* renderer, const char* name, unsigned int& texture);
	};
}

#endif