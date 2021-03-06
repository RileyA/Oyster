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

		Layer(Atlas* atlas)
			:mAtlas(atlas),mFlags(0)
		{

		}
		//-------------------------------------------------------------------

		~Layer()
		{
			for(int i = 0; i < mDrawables.size(); ++i)
				delete mDrawables[i];
		}
		//-------------------------------------------------------------------	

		DirtyFlags needsUpdate()
		{
			DirtyFlags out = mFlags;
			for(int i = 0; i < mDrawables.size(); ++i)
				out |= mDrawables[i]->getStatus();
			return out;
		}
		//-------------------------------------------------------------------	

		void update(DirtyFlags flag, Mesh& mesh)
		{
			for(int i = 0; i < mDrawables.size(); ++i)
				mDrawables[i]->update(flag, mesh);
			mFlags = 0;
		}
		//-------------------------------------------------------------------	
		
		void removeDrawable(Drawable* d, bool kill = true)
		{
			for(int i = 0; i < mDrawables.size(); ++i)
			{
				if(mDrawables[i] == d)
				{
					if(kill)
						delete d;
					mDrawables.erase(mDrawables.begin() + i);
					mFlags |= 1<<3;
					return;
				}
			}
		}
		//-------------------------------------------------------------------	

		void addDrawable(Drawable* d)
		{
			mDrawables.push_back(d);
		}
		//-------------------------------------------------------------------	

		Rectangle* createRectangle(int x, int y, int w, int h, int r = 0, int g = 0, int b = 0)
		{
			Rectangle* rect = new Rectangle(mAtlas);

			rect->setPosition(x,y);
			rect->setScale(w,h);

			mDrawables.push_back(rect);
			return rect;
		}
		//-------------------------------------------------------------------	

		Text* createText(String caption, int x, int y, int w, int h, 
			int r = 0, int g = 0, int b = 0)
		{
			Text* t = new Text(mAtlas, caption);

			t->setPosition(x,y);
			t->setScale(w,h);

			mDrawables.push_back(t);
			return t;
		}
		//-------------------------------------------------------------------	

	private:

		Atlas* mAtlas;
		std::vector<Drawable*> mDrawables;
		DirtyFlags mFlags;

	};
}

#endif
