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

		Rectangle()
		{
		
		}
		//-------------------------------------------------------------------

		virtual ~Rectangle()
		{

		}
		//-------------------------------------------------------------------	

		virtual void update(DirtyFlags flag, Mesh& out)
		{
			// do update
		}
		//-------------------------------------------------------------------	

		

	private:

		

	};
}

#endif
