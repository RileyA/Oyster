#include "OysterStdHeaders.h"

namespace Oyster
{
	class Batch
	{
	public:

		Batch::Batch(Atlas* atlas)
			:mAtlas(atlas)
		{

		}
		//-------------------------------------------------------------------------

		Batch::~Batch()
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
			mLayers[index] = new Layer();
		}
		//-------------------------------------------------------------------------

		Layer* getLayer(int index)
		{
			std::map<int, Layer*>::iterator search = mLayers.find(index);
			return search == mLayers.end() ? 0 : search->second;
		}
		//-------------------------------------------------------------------------

	private:

		Atlas* mAtlas;
		std::map<int, Layer*> mLayers;

	};
}
