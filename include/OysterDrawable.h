#ifndef OYSTER_DRAWABLE_H
#define OYSTER_DRAWABLE_H

#include "OysterStdHeaders.h"
#include "OysterMesh.h"

namespace Oyster
{
	/** Abstract drawable object, occupies a rectangle of pixels */
	class Drawable
	{
	public:

		Drawable()
			:mFlags(1<<3)
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
		}
		//-------------------------------------------------------------------	

		/** Set scale in pixels */
		void setScale(int x, int y)
		{
			mScaleX = x;
			mScaleY = y;
		}
		//-------------------------------------------------------------------	

	private:

		DirtyFlags mFlags;

		// these are in pixels
		int mPosX;
		int mPosY;
		int mScaleX;
		int mScaleY;

	};
}

#endif
