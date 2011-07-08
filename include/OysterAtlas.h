#include "OysterStdHeaders.h"

namespace Oyster
{
	class Atlas
	{
	public:

		/** Constructor, takes a pointer to a filestream for a definition file */
		Atlas::Atlas(std::ifstream* definition)
		{

		}
		//-------------------------------------------------------------------------

		Atlas::~Atlas()
		{
			
		}
		//-------------------------------------------------------------------------

	private:

		String mTextureName;

	};
}
