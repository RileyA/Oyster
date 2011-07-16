#ifndef OYSTER_MESH_H
#define OYSTER_MESH_H

#include "OysterStdHeaders.h"

namespace Oyster
{
	class Mesh
	{
	public:

		Mesh(size_t width, size_t height, size_t atlas_width, size_t atlas_height)
			:vertices(std::vector<float>())
			,texcoords(std::vector<float>())
			,colors(std::vector<float>())
			,indices(std::vector<uint16_t>())
		{
			mScreenWidth  = width;
			mScreenHeight = height;
			mAtlasWidth  = atlas_width;
			mAtlasHeight = atlas_height;
			mInvScreenWidth = 1.f / width;
			mInvScreenHeight = 1.f / height;
		}

		void vertex(int x, int y)
		{
			vertex((mInvScreenWidth * x * 2) - 1, 1 - (mInvScreenHeight * y * 2));
		}

		void vertex(float x, float y)
		{
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(0);// flat mesh
		}

		void texcoord(int u, int v)
		{
			texcoords.push_back(static_cast<float>(u) / mAtlasWidth);
			texcoords.push_back(static_cast<float>(v) / mAtlasWidth);
		}

		void texcoord(float u, float v)
		{
			texcoords.push_back(u);
			texcoords.push_back(v);
		}

		void color(float r, float g, float b, float a)
		{
			colors.push_back(r);
			colors.push_back(g);
			colors.push_back(b);
			colors.push_back(a);
		}

		void color(Color c)
		{
			colors.push_back(c.r/255.f);
			colors.push_back(c.g/255.f);
			colors.push_back(c.b/255.f);
			colors.push_back(c.a/255.f);
		}

		float* getVertices() const
		{
			return const_cast<float*>(&vertices[0]);
		}

		float* getTexcoords() const
		{
			return const_cast<float*>(&texcoords[0]);
		}

		float* getColors() const
		{
			return const_cast<float*>(&colors[0]);
		}

		uint16_t* getIndices() const
		{
			return const_cast<uint16_t*>(&indices[0]);
		}

		size_t getVertexCount() const
		{
			return vertices.size() / 3;
		}

		size_t getFaceCount() const
		{
			return indices.size() / 3;
		}

		std::vector<float> vertices;
		std::vector<float> texcoords;
		std::vector<float> colors;
		std::vector<uint16_t> indices;// 16 bit

	private:

		size_t mAtlasWidth;
		size_t mAtlasHeight;
		size_t mScreenWidth;
		size_t mScreenHeight;
		float mInvScreenHeight;
		float mInvScreenWidth;
		
	};
}

#endif
