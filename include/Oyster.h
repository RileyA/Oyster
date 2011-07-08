#include "OysterStdHeaders.h"
#include "OysterAtlas.h"
#include "OysterBatch.h"

namespace Oyster
{
	/** The root for everything */
	class Oyster
	{
	public:

		Oyster()
		{
			
		}
		//-------------------------------------------------------------------

		~Oyster()
		{
			while(!mBatches.empty())
			{
				delete mBatches.front();
				mBatches.pop_front();
			}
			while(!mAtlases.empty())
			{
				delete mAtlases.front();
				mAtlases.pop_front();
			}
		}
		//-------------------------------------------------------------------

		/** Create an Atlas based on a .atlas definition file */
		void createAtlas(String filename)
		{
			std::ifstream file(filename);
			if(!file.is_open())
				throw std::runtime_error("Atlas file failed to load!");
			mAtlases.push_back(new Atlas(&file));
			file.close();
		}

	private:

		std::list<Batch*> mBatches;
		std::list<Atlas*> mAtlases;

	};
}
