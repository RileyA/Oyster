#ifndef OYSTER_LAYER_H
#define OYSTER_LAYER_H

#include "OysterStdHeaders.h"
#include "OysterText.h"
#include "OysterRectangle.h"

namespace Oyster
{
	class Layer
	{
	public:

		Layer()
		{

		}
		//-------------------------------------------------------------------

		~Layer()
		{

		}
		//-------------------------------------------------------------------	

		DirtyFlags needsUpdate()
		{
			DirtyFlags out = 0;
			for(int i = 0; i < mDrawables.size(); ++i)
				out |= mDrawables[i]->getStatus();
			return out;
		}
		//-------------------------------------------------------------------	

		void update(DirtyFlags flag, Mesh& mesh)
		{
			for(int i = 0; i < mDrawables.size(); ++i)
				mDrawables[i]->update(flag, mesh);
		}
		//-------------------------------------------------------------------	

		Rectangle* createRectangle(int x, int y, int w, int h, int r = 0, int g = 0, int b = 0)
		{
			Rectangle* rect = new Rectangle();

			rect->setPosition(x,y);
			rect->setScale(w,h);

			mDrawables.push_back(rect);
			return rect;
		}

	private:

		std::vector<Drawable*> mDrawables;

	};
}

#endif
