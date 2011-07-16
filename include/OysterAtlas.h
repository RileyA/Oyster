#ifndef OYSTER_ATLAS_H
#define OYSTER_ATLAS_H

#include "OysterStdHeaders.h"
#include "OysterFont.h"

namespace Oyster
{
	struct Sprite
	{
		Sprite(String n, int _x, int _y, int _w, int _h)
			:name(n),x(_x),y(_y),w(_w),h(_h) {}

		String name;
		int x,y,w,h;
	};

	class Atlas
	{
	public:

		/** Constructor, takes a pointer to a filestream for a definition file */
		Atlas(std::ifstream* definition)
			:mWhitePixel(0)
		{
			String temp;
			String section = "";
			(*definition)>>temp;

			Font* f;

			// parse the totally contrived and fragile file format...
			while(definition->good())
			{
				if(temp[0] == '[')
				{
					section = temp;
				}
				else
				{
					if(section == "[Texture]")
					{
						if(temp == "file")
						{
							(*definition)>>mTextureName;
						}
						else if(temp == "dimensions")
						{
							(*definition)>>mTextureWidth;
							(*definition)>>mTextureHeight;
						}
						else if(temp == "whitepixel")
						{
							int x, y;
							(*definition)>>x;
							(*definition)>>y;
							// a 1x1 'sprite'
							mWhitePixel = new Sprite("WhitePixel", x, y, 1, 1);
						}
					}
					else if(section == "[Font]")
					{
						if(temp == "name")
						{
							String name;
							(*definition)>>name;
							f = new Font(name);
							mFonts[name] = f;
						}
						else if(temp == "spacelength")
						{
							int w;
							(*definition)>>w;
							f->setSpaceWidth(w);
						}
						else if(temp == "lineheight")
						{
							int h;
							(*definition)>>h;
							f->setLineHeight(h);
						}
						else
						{
							if(temp.substr(0,6) == "glyph_")
							{
								char code = atoi(temp.substr(6).c_str());
								int x,y,w,h,advance;
								(*definition)>>x;
								(*definition)>>y;
								(*definition)>>w;
								(*definition)>>h;
								(*definition)>>advance;
								f->addGlyph(code, x, y, w, h, advance);
							}
							else if(temp.substr(0,8) == "kerning_")
							{
								char code = atoi(temp.substr(8).c_str());
								char code2;
								int kern;
								(*definition)>>code2;
								(*definition)>>kern;
                                f->getGlyph(code)->addKerning(code2, kern);
							}
						}						
					}
					else if(section == "[Sprites]")
					{
						String name = temp;
						int x,y,w,h;
						(*definition)>>x;
						(*definition)>>y;
						(*definition)>>w;
						(*definition)>>h;
						mSprites[name] = new Sprite(name, x, y, w, h);
					}
				}
				(*definition)>>temp;
			}
		}
		//-------------------------------------------------------------------------

		~Atlas()
		{
			for(std::map<String, Font*>::iterator i = mFonts.begin(); i != mFonts.end(); ++i)
				delete i->second;
			for(std::map<String, Sprite*>::iterator i = mSprites.begin(); i != mSprites.end(); ++i)
				delete i->second;
			if(mWhitePixel)
				delete mWhitePixel;
		}
		//-------------------------------------------------------------------------

		String getTextureName()
		{
			return mTextureName;
		}
		//-------------------------------------------------------------------------

		Sprite* getSprite(String name)
		{
			std::map<String,Sprite*>::iterator it = mSprites.find(name);
			if(it == mSprites.end())
				return 0;
			return mSprites[name];
		}
		//-------------------------------------------------------------------------
		
		Sprite* getWhitePixel()
		{
			return mWhitePixel;
		}
		//-------------------------------------------------------------------------

		size_t getAtlasWidth()
		{
			return mTextureWidth;
		}
		//-------------------------------------------------------------------------

		size_t getAtlasHeight()
		{
			return mTextureHeight;
		}	
		//-------------------------------------------------------------------------

		Font* getFont(String name)
		{
			if(mFonts.find(name) != mFonts.end())
				return mFonts[name];
			return 0;
		}
		//-------------------------------------------------------------------------
	
	private:

		String mTextureName;
		Sprite* mWhitePixel;
		std::map<String, Font*> mFonts;
		std::map<String, Sprite*> mSprites;
		size_t mTextureWidth;
		size_t mTextureHeight;

	};
}

#endif
