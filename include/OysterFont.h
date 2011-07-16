#ifndef OYSTER_FONT_H
#define OYSTER_FONT_H

namespace Oyster
{
	class Font
	{
	public:

		/** A Character */
		struct Glyph
		{
			Glyph(char _ascii, int _x, int _y, int _w, int _h, int _advance)
				:ascii(_ascii),x(_x),y(_y),w(_w),h(_h),advance(_advance){}

			void addKerning(char c, int offset)
			{
				kernings[c] = offset;
			}

			int getKerning(char c)
			{
				if(kernings.find(c) != kernings.end())
					return kernings[c];
				return 0;
			}

			// in px
			int x, y, w, h, advance;

			// this glyph's ascii code
			char ascii;

			std::map<char, int> kernings;
		};
		//-------------------------------------------------------------------	


		Font(String name)
			:mName(name){}
		//-------------------------------------------------------------------	

		~Font()
		{
			for(std::map<char,Glyph*>::iterator it = mGlyphs.begin(); it != mGlyphs.end(); ++it)
				delete it->second;
		}
		//-------------------------------------------------------------------	
		
		void addGlyph(char code, int x, int y, int w, int h, int advance)
		{
			mGlyphs[code] = new Glyph(code, x, y, w, h, advance);
		}
		//-------------------------------------------------------------------	

		Glyph* getGlyph(char code)
		{
			if(mGlyphs.find(code) == mGlyphs.end())
				return false;
			return mGlyphs[code];
		}
		//-------------------------------------------------------------------	


		float getLineHeight()
		{
			return mLineHeight;
		}
		//-------------------------------------------------------------------	

		float getSpaceWidth()
		{
			return mSpaceWidth;
		}
		//-------------------------------------------------------------------	

		void setLineHeight(float height)
		{
			mLineHeight = height;
		}
		//-------------------------------------------------------------------	

		void setSpaceWidth(float width)
		{
			mSpaceWidth = width;
		}
		//-------------------------------------------------------------------	

	protected:

		std::map<char, Glyph*> mGlyphs;
		float mLineHeight;
		float mSpaceWidth;
		String mName;
	};
}

#endif
