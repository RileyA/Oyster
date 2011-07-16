#ifndef OYSTER_STD_HEADERS_H
#define OYSTER_STD_HEADERS_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <fstream>
#include <stdexcept>
#include <stdint.h>

namespace Oyster
{
	// save some typing, without using the whole namespace...
	typedef std::string String;
	typedef float Real;
	typedef unsigned char DirtyFlags;

	struct Color
	{
		Color(unsigned int _r = 0, unsigned int _g = 0, unsigned int _b = 0, unsigned int _a = 255)
			:r(_r),g(_g),b(_b),a(_a) {}
		unsigned int r;
		unsigned int g;
		unsigned int b;
		unsigned int a;
	};

	enum VerticalAlign
	{
		VA_CENTER,
		VA_TOP,
		VA_BOTTOM
	};

	enum HorizontalAlign
	{
		HA_LEFT,
		HA_CENTER,
		HA_RIGHT
	};
}

#endif
