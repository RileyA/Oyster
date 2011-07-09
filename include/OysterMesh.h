#ifndef OYSTER_MESH_H
#define OYSTER_MESH_H

#include "OysterStdHeaders.h"

namespace Oyster
{
	class Mesh
	{
	public:

		Mesh(size_t width, size_t height)
			:vertices(std::vector<float>())
			,texcoords(std::vector<float>())
			,colors(std::vector<float>())
			,indices(std::vector<uint16_t>())
		{
			mScreenWidth  = width;
			mScreenHeight = height;
			mInvScreenWidth = 1.f / width;
			mInvScreenHeight = 1.f / width;
		}

		void vertex(int x, int y)
		{
			vertex(mInvScreenWidth * x, mInvSreenHeight* y);
		}

		void vertex(float x, float y)
		{
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(0);// flat mesh
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

		float* getVertices()
		{
			return &vertices[0];
		}

		float* getTexcoords()
		{
			return &texcoords[0];
		}

		float* getColors()
		{
			return &colors[0];
		}

		uint16_t* getIndices()
		{
			return &indices[0];
		}

		std::vector<float> vertices;
		std::vector<float> texcoords;
		std::vector<float> colors;
		std::vector<uint16_t> indices;// 16 bit

	private:

		size_t mScreenWidth;
		size_t mScreenHeight;
		float mInvScreenHeight;
		float mInvScreenWidth;
		
	};
}

#endif
