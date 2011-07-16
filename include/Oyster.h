#ifndef OYSTER_H
#define OYSTER_H

#include "OysterStdHeaders.h"
#include "OysterAtlas.h"
#include "OysterBatch.h"

namespace Oyster
{
	/** The root for everything */
	class Oyster
	{
	public:

		Oyster(size_t w, size_t h)
			:mWidth(w),mHeight(h)
		{

		}
		//-------------------------------------------------------------------

		~Oyster()
		{
			for(std::map<String,Batch*>::iterator it = mBatches.begin(); it != 
				mBatches.end(); ++it)
				delete it->second;
			for(std::map<String,Atlas*>::iterator it = mAtlases.begin(); it != 
				mAtlases.end(); ++it)
				delete it->second;
		}
		//-------------------------------------------------------------------

		/** Create an Atlas based on a .atlas definition file */
		Atlas* createAtlas(String name, String filename)
		{
			if(mAtlases.find(name) != mAtlases.end())
				throw std::runtime_error("An Atlas by that name already exists!");

			std::ifstream file(filename.c_str());
			if(!file.is_open())
				throw std::runtime_error("Atlas file failed to load!");

			Atlas* a = new Atlas(&file);

			file.close();

			mAtlases[name] = a;
			return a;
		}
		//-------------------------------------------------------------------

		/** Creates a Batch */
		Batch* createBatch(String name, String atlasname, size_t w = 0, size_t h = 0)
		{
			if(!w)
				w = mWidth;
			if(!h)
				h = mHeight;

			if(mBatches.find(name) != mBatches.end())
				throw std::runtime_error("A Batch by that name already exists!");
			if(mAtlases.find(atlasname) == mAtlases.end())
				throw std::runtime_error("No such Atlas!");
			Batch* b = new Batch(mAtlases[atlasname], w, h);
			mBatches[name] = b;
			return b;
		}
		//-------------------------------------------------------------------

		void destroyBatch(Batch* batch)
		{
			for(std::map<String,Batch*>::iterator it = mBatches.begin(); it != 
				mBatches.end(); ++it)
			{
				if(it->second == batch)
				{
					delete it->second;
					mBatches.erase(it);
					return;
				}
			}
		}
		//-------------------------------------------------------------------

		void destroyBatch(String batch)
		{
			std::map<String, Batch*>::iterator it = mBatches.find(batch);
			if(it != mBatches.end())
			{
				delete it->second;
				mBatches.erase(it);
			}
		}
		//-------------------------------------------------------------------

		Batch* getBatch(String name)
		{
			return mBatches.find(name) == mBatches.end() ? 0 : mBatches[name];
		}
		//-------------------------------------------------------------------
		
		Atlas* getAtlas(String name)
		{
			return mAtlases.find(name) == mAtlases.end() ? 0 : mAtlases[name];
		}
		//-------------------------------------------------------------------
	
	private:

		std::map<String,Batch*> mBatches;
		std::map<String,Atlas*> mAtlases;
		size_t mWidth;
		size_t mHeight;

	};
}

#endif
