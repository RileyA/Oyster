#ifndef OYSTER_RECTANGLE_H
#define OYSTER_RECTANGLE_H

#include "OysterStdHeaders.h"
#include "OysterDrawable.h"

namespace Oyster
{
	typedef unsigned char DirtyFlags;

	/** A simple rectangle */
	class Rectangle : public Drawable
	{
	public:

		Rectangle(Atlas* atlas)
			:Drawable(atlas)
		{
			for(int i = 0; i < 4; ++i)
				vertColors[i] = mColor;
			setSolidColor();
		}
		//-------------------------------------------------------------------

		virtual ~Rectangle()
		{

		}
		//-------------------------------------------------------------------	

		virtual void update(DirtyFlags flag, Mesh& out)
		{
			bool updatePos = flag & (1<<3) || flag & (1);
			bool updateTex = flag & (1<<3) || flag & (1<<1);
			bool updateCol = flag & (1<<3) || flag & (1<<2);
			bool updateAll = flag & (1<<3);
			
			// positions
			if(updatePos)
			{
				out.vertex(mPosX, mPosY);
				out.vertex(mPosX + mScaleX, mPosY);
				out.vertex(mPosX + mScaleX, mPosY + mScaleY);
				out.vertex(mPosX, mPosY + mScaleY);
			}

			// indices
			if(updateAll)
			{
				uint16_t startInd = out.vertices.size()/3 - 4;
				
				// tri 1
				out.indices.push_back(startInd);
				out.indices.push_back(startInd+1);
				out.indices.push_back(startInd+2);
				// tri 2
				out.indices.push_back(startInd);
				out.indices.push_back(startInd+2);
				out.indices.push_back(startInd+3);
			}

			if(updateTex)
			{
				for(int i = 0; i < 4; ++i)
					out.texcoord(static_cast<int>(u[i]), 
						static_cast<int>(v[i]));
			}

			if(updateCol)
			{
				for(int i = 0; i < 4; ++i)
					out.color(vertColors[i]);
			}

			mFlags = 0;
		}
		//-------------------------------------------------------------------	
		
		void setColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
		{
			mFlags |= 1<<2;
			Color c = Color(r,g,b,a);
			for(int i = 0; i < 4; ++i)
				vertColors[i] = c;
		}
		//-------------------------------------------------------------------	
		
		void setColor(unsigned int index, unsigned int r, unsigned int g, unsigned int b, unsigned int a)
		{
			mFlags |= 1<<2;
			vertColors[index] = Color(r,g,b,a);
		}
		//-------------------------------------------------------------------	

		void setSprite(String name)
		{
			Sprite* temp = mAtlas->getSprite(name);
			u[0] = temp->x;
			u[1] = temp->x + temp->w;
			u[2] = temp->x + temp->w;
			u[3] = temp->x;
			v[0] = temp->y;
			v[1] = temp->y;
			v[2] = temp->y + temp->h;
			v[3] = temp->y + temp->h;
			mFlags |= 2;
		}
		//-------------------------------------------------------------------	

		void setSolidColor()
		{
			Sprite* temp = mAtlas->getWhitePixel();
			u[0] = temp->x;
			u[1] = temp->x + temp->w;
			u[2] = temp->x + temp->w;
			u[3] = temp->x;
			v[0] = temp->y;
			v[1] = temp->y;
			v[2] = temp->y + temp->h;
			v[3] = temp->y + temp->h;
			mFlags |= 2;
		}

	protected:

		Color vertColors[4];
		size_t u[4];
		size_t v[4];

	};
}

#endif
