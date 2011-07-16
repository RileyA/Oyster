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
			:Drawable(atlas), mCaption(caption), mAlignH(HA_LEFT), mAlignV(VA_TOP)
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
					makeChar(flag, cursor, mCaption[i], out, len);

					// use width on the last one
					cursor += i == mCaption.size() -1 ? g->w : g->advance;
					if(previous && g->getKerning(previous))
						cursor += g->getKerning(previous);
					previous = mCaption[i];
				}
			}

			mFlags = 0;
		}
		//-------------------------------------------------------------------
		
		/** Makes a character quad */
		virtual void makeChar(DirtyFlags flag, int cursor, char c, Mesh& out, int linelen)
		{
			int yoffset = 0;
			int xoffset = 0;
			
			if(mAlignV == VA_CENTER)
				yoffset = mScaleY / 2 - mFont->getLineHeight() / 2;
			else if(mAlignV == VA_BOTTOM)
				yoffset = mScaleY - mFont->getLineHeight();
			
			if(mAlignH == HA_RIGHT)
				xoffset = mScaleX - linelen;
			else if(mAlignH == HA_CENTER)
				xoffset = (mScaleX - linelen)/2;

			bool updatePos = flag & (1<<3) || flag & (1);
			bool updateTex = flag & (1<<3) || flag & (1<<1);
			bool updateCol = flag & (1<<3) || flag & (1<<2);
			bool updateAll = flag & (1<<3);

			int lineheight = mFont->getLineHeight();
			Font::Glyph* g = mFont->getGlyph(c);

			if(!g)
				return;

			// decide if we need to clip
			int clipleft = 0, clipright = 0;
			int cliptop = 0, clipbottom = 0;

			// left
			if(cursor + g->w + xoffset < 0)
				return;// clip it all
			else if(cursor + xoffset < 0)
			{
				// clip part
				clipleft = - (cursor + xoffset);
			}

			// right
			if(cursor + xoffset > mScaleX)
				return;// clip it all
			else if(cursor + g->w + xoffset > mScaleX)
			{
				// clip part
				clipright = (cursor + xoffset + g->w) - mScaleX;
			}

			// up
			if(yoffset + lineheight < 0)
				return;// clip it all
			else if(yoffset < 0)
			{
				// clip part
				cliptop = -yoffset;
			}

			// down
			if(yoffset > mScaleY)
				return;// clip it all
			else if(yoffset + lineheight > mScaleY)
			{
				// clip part
				clipbottom = (yoffset + lineheight) - mScaleY;
			}

			if(updatePos)
			{
				mPosX += xoffset;
				mPosY += yoffset;
				out.vertex(mPosX + cursor + clipleft, mPosY + cliptop);
				out.vertex(mPosX + cursor + g->w - clipright, mPosY + cliptop);
				out.vertex(mPosX + cursor + g->w - clipright, mPosY + g->h - clipbottom);
				out.vertex(mPosX + cursor + clipleft, mPosY + g->h - clipbottom);
				mPosX -= xoffset;
				mPosY -= yoffset;
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
				out.texcoord(static_cast<int>(g->x + clipleft), static_cast<int>(g->y + cliptop));
				out.texcoord(static_cast<int>(g->x + g->w - clipright), static_cast<int>(g->y + cliptop));
				out.texcoord(static_cast<int>(g->x + g->w - clipright), static_cast<int>(g->y + g->h - clipbottom));
				out.texcoord(static_cast<int>(g->x + clipleft), static_cast<int>(g->y + g->h - clipbottom));
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
					cursor += i == mCaption.size() -1 ? g->w : g->advance;
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

		void setAlign(VerticalAlign v)
		{
			mAlignV = v;
			mFlags |= 1;
		}
		//-------------------------------------------------------------------

		void setAlign(HorizontalAlign h)
		{
			mAlignH = h;
			mFlags |= 1;
		}
		//-------------------------------------------------------------------

	protected:

		Font* mFont;
		String mCaption;
		HorizontalAlign mAlignH;
		VerticalAlign mAlignV;

	};
}

#endif
