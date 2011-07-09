#ifndef OYSTER_ATLAS_H
#define OYSTER_ATLAS_H

#include "OysterStdHeaders.h"

namespace Oyster
{
	class Atlas
	{
	public:

		/** Constructor, takes a pointer to a filestream for a definition file */
		Atlas(std::ifstream* definition)
		{

		}
		//-------------------------------------------------------------------------

		~Atlas()
		{
			
		}
		//-------------------------------------------------------------------------

	private:

		String mTextureName;

	};
}

#endif
