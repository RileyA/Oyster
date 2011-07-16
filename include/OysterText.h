#ifndef OYSTER_TEXT_H
#define OYSTER_TEXT_H

#include "OysterStdHeaders.h"
#include "OysterDrawable.h"
#include "OysterFont.h"

namespace Oyster
{
	class Text : public Drawable
	{
	public:

		Text(Atlas* atlas, String caption = "", String font = "DEFAULT")
			:Drawable(atlas), mCaption(caption)
		{
			mFont = mAtlas->getFont(font);
		}
		//-------------------------------------------------------------------

		virtual ~Text()
		{
			
		}
		//-------------------------------------------------------------------
		
		virtual void update(DirtyFlags flag, Mesh& out)
		{
			int len = getLength();
			int cursor = 0;
			char previous = 0;

			for(int i = 0; i < mCaption.size(); ++i)
			{
				if(mCaption[i] == ' ')
				{
					cursor += mFont->getSpaceWidth();
				}
				else if(Font::Glyph* g = mFont->getGlyph(mCaption[i]))
				{
					makeChar(flag, cursor, mCaption[i], out);

					// use width on the last one
					cursor += i == mCaption.size() -1 ? g->advance : g->w;
					if(previous && g->getKerning(previous))
						cursor += g->getKerning(previous);
					previous = mCaption[i];
				}
			}

			mFlags = 0;
		}
		//-------------------------------------------------------------------
		
		/** Makes a character quad */
		virtual void makeChar(DirtyFlags flag, int cursor, char c, Mesh& out)
		{
			bool updatePos = flag & (1<<3) || flag & (1);
			bool updateTex = flag & (1<<3) || flag & (1<<1);
			bool updateCol = flag & (1<<3) || flag & (1<<2);
			bool updateAll = flag & (1<<3);

			int lineheight = mFont->getLineHeight();
			Font::Glyph* g = mFont->getGlyph(c);

			if(!g)
				return;

			if(updatePos)
			{
				out.vertex(mPosX + cursor, mPosY);
				out.vertex(mPosX + cursor + g->w, mPosY);
				out.vertex(mPosX + cursor + g->w, mPosY + g->h);
				out.vertex(mPosX + cursor, mPosY + g->h);
			}

			if(updateAll)
			{
				uint16_t startInd = out.vertices.size()/3 - 4;
				
				// tri 1
				out.indices.push_back(startInd);
				out.indices.push_back(startInd+1);
				out.indices.push_back(startInd+2);
				// tri 2
				out.indices.push_back(startInd);
				out.indices.push_back(startInd+2);
				out.indices.push_back(startInd+3);
			}

			if(updateTex)
			{
				out.texcoord(static_cast<int>(g->x), static_cast<int>(g->y));
				out.texcoord(static_cast<int>(g->x + g->w), static_cast<int>(g->y));
				out.texcoord(static_cast<int>(g->x + g->w), static_cast<int>(g->y + g->h));
				out.texcoord(static_cast<int>(g->x), static_cast<int>(g->y + g->h));
			}

			if(updateCol)
			{
				for(int i = 0; i < 4; ++i)
					out.color(mColor);
			}
		}
		//-------------------------------------------------------------------

		// gets the length of the text in pixels
		virtual int getLength()
		{
			int cursor = 0;
			char previous = 0;
			for(int i = 0; i < mCaption.size(); ++i)
			{
				if(mCaption[i] == ' ')
				{
					cursor += mFont->getSpaceWidth();
				}
				else if(Font::Glyph* g = mFont->getGlyph(mCaption[i]))
				{
					// use width on the last one
					cursor += i == mCaption.size() -1 ? g->advance : g->w;
					if(previous && g->getKerning(previous))
						cursor += g->getKerning(previous);
				}
				previous = mCaption[i];
			}

			return cursor;
		}
		//-------------------------------------------------------------------

		void setCaption(String cap)
		{
			mCaption = cap;
		}
		//-------------------------------------------------------------------

		String getCaption()
		{
			return mCaption;
		}
		//-------------------------------------------------------------------

	protected:

		Font* mFont;
		String mCaption;

	};
}

#endif
