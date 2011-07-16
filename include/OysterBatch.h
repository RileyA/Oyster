#ifndef OYSTER_BATCH_H
#define OYSTER_BATCH_H

#include "OysterStdHeaders.h"
#include "OysterAtlas.h"
#include "OysterLayer.h"
#include "OysterMesh.h"

namespace Oyster
{
	class Batch
	{
	public:

		Batch(Atlas* atlas, size_t w, size_t h)
			:mAtlas(atlas),mMesh(w, h, mAtlas->getAtlasWidth(),mAtlas->getAtlasHeight())
		{

		}
		//-------------------------------------------------------------------------

		~Batch()
		{
			for(std::map<int, Layer*>::iterator it = mLayers.begin(); it != 
				mLayers.end(); ++it)
				delete it->second;
		}
		//-------------------------------------------------------------------------

		Layer* createLayer(int index)
		{
			if(mLayers.find(index) != mLayers.end())
				throw std::runtime_error("A Layer already exists at that index!");
			mLayers[index] = new Layer(mAtlas);
			return mLayers[index];
		}
		//-------------------------------------------------------------------------

		Layer* getLayer(int index)
		{
			std::map<int, Layer*>::iterator search = mLayers.find(index);
			return search == mLayers.end() ? 0 : search->second;
		}
		//-------------------------------------------------------------------------

		/** Updates this batch (to be called every frame), returns a bitfield of
		 *		info about what needs to be updated */
		void update()
		{
			DirtyFlags flag = 0;

			// figure out what needs updating
			for(std::map<int,Layer*>::iterator it = mLayers.begin(); it != 
				mLayers.end(); ++it)
			{
				flag |= it->second->needsUpdate();
			}

			// does any necessary updates
			if(flag)
			{
				for(std::map<int,Layer*>::iterator it = mLayers.begin(); it != 
					mLayers.end(); ++it)
					it->second->update(flag, mMesh);
			}
		}
	
		const Mesh& getMesh()
		{
			return mMesh;
		}
		//-------------------------------------------------------------------------

	private:

		Atlas* mAtlas;
		Mesh mMesh;
		std::map<int, Layer*> mLayers;

	};
}

#endif
