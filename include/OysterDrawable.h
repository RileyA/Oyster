#ifndef OYSTER_DRAWABLE_H
#define OYSTER_DRAWABLE_H

#include "OysterStdHeaders.h"
#include "OysterMesh.h"
#include "OysterAtlas.h"

namespace Oyster
{
	/** Abstract drawable object, occupies a rectangle of pixels */
	class Drawable
	{
	public:

		Drawable(Atlas* atlas)
			:mFlags(1<<3), mAtlas(atlas), mColor(255,255,255,255)
		{
		
		}
		//-------------------------------------------------------------------

		virtual ~Drawable()
		{

		}
		//-------------------------------------------------------------------	
		
		/** Gets whether or not various parts of this need updating */
		DirtyFlags getStatus()
		{
			return mFlags;
		}
		//-------------------------------------------------------------------	

		/** updates/draws this object */
		virtual void update(DirtyFlags flag, Mesh& out) = 0;

		/** Set position in pixels */
		void setPosition(int x, int y)
		{
			mPosX = x;
			mPosY = y;
			mFlags |= 1;
		}
		//-------------------------------------------------------------------	

		/** Set scale in pixels */
		void setScale(int x, int y)
		{
			mScaleX = x;
			mScaleY = y;
			mFlags |= 1;
		}
		//-------------------------------------------------------------------	

		virtual void setColor(int r, int g, int b, int a)
		{
			mColor = Color(r,b,g, a);
			mFlags |= 4;
		}
		//-------------------------------------------------------------------	

		void markDirty(DirtyFlags f)
		{
			mFlags = f;
		}
		//-------------------------------------------------------------------	

	protected:

		DirtyFlags mFlags;
		Atlas* mAtlas;

		// these are in pixels
		int mPosX;
		int mPosY;
		int mScaleX;
		int mScaleY;

		Color mColor;

	};
}

#endif
