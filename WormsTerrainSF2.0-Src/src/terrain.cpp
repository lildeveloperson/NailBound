/*
    This file is part of example for "how to make worms style terrain with SFML2".

    This is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "terrain.hpp"
#include <string>
#include <iostream>
#include <cstring>
// -------------------------------------------------------------------------------------------------
//
// -------------------------------------------------------------------------------------------------

terrain::terrain()
{

}

// -------------------------------------------------------------------------------------------------
//
// -------------------------------------------------------------------------------------------------

terrain::terrain(std::string mask, std::string borderUp, std::string borderDn, std::string texture)
{
	mBorderOffset.x = 0;
	mBorderOffset.y = 0;
	
	mMask.LoadFromFile(mask);
	mMask.SetSmooth(false);

	mBorderUp.LoadFromFile(borderUp);
	mBorderUp.SetSmooth(false);
	
	mBorderDn.LoadFromFile(borderDn);
	mBorderDn.SetSmooth(false);
	
	mTexture.LoadFromFile(texture);
	mTexture.SetSmooth(false);
	
	mOutput.LoadFromFile(mask);
	mOutput.SetSmooth(false);
	
	paintBorder();
	fill();

}

// -------------------------------------------------------------------------------------------------
//
// -------------------------------------------------------------------------------------------------

terrain::~terrain()
{

}

// -------------------------------------------------------------------------------------------------
//
// -------------------------------------------------------------------------------------------------

bool	terrain::save(std::string output)
{
	mOutput.SaveToFile(output);
}

// -------------------------------------------------------------------------------------------------
//
// -------------------------------------------------------------------------------------------------

void terrain::fill()
{
	sf::Vector2i	textureOffset(0,0);

	for(int y=0; y<mOutput.GetHeight();++y)
	{
		for(int x=0; x<mOutput.GetWidth();++x)
		{
			sf::Color	pixel = mOutput.GetPixel(x,y);
			
			if(pixel==sf::Color(255,255,255))
			{
				mOutput.SetPixel(x,y,mTexture.GetPixel(textureOffset.x,textureOffset.y));
			}
	
			textureOffset.x++;if(textureOffset.x >= mTexture.GetWidth()){textureOffset.x = 0;}

		}
			textureOffset.y++;if(textureOffset.y >= mTexture.GetHeight()){textureOffset.y = 0;}
	}
}

// -------------------------------------------------------------------------------------------------
//
// -------------------------------------------------------------------------------------------------

int terrain::paintVerticalBorder(int x, int y, sf::Color mask, sf::Image texture)
{

	int min  = texture.GetHeight();
	int max  = 0; 
	int xx 	 = x;
	int yy 	 = y;
	float step = 0;
	
	mBorderOffset.y = 0;
	
	while(mOutput.GetPixel(xx,yy)==mask)
	{
		yy--;
	}
	
	yy  ++;
	min  = 	yy;

	while(mOutput.GetPixel(xx,yy)==mask)
	{
		yy++;
	}

	max  = yy;
	step = (float)texture.GetHeight() / (float)(max-min);
	

	for(int ty=min;ty<(max+1);++ty)
	{
	
		sf::Color borderColor = texture.GetPixel(mBorderOffset.x, mBorderOffset.y);
		mOutput.SetPixel(xx,ty,borderColor);
		
		mBorderOffset.y += (int)step;
		if(mBorderOffset.y > texture.GetHeight()-1)
		{
			mBorderOffset.y = texture.GetHeight()-1;
		}
		
	}

	
	mBorderOffset.x ++;
	if(mBorderOffset.x > texture.GetWidth()-1)
	{
		mBorderOffset.x = 0;
	}

	return max;
}

// -------------------------------------------------------------------------------------------------
//
// -------------------------------------------------------------------------------------------------

void terrain::paintBorder()
{
	int mindec = 0;
	int maxdec = 0;
	
	int decUP	 = mBorderUp.GetHeight(); 
	int decDN	 = mBorderDn.GetHeight(); 


	for(int y=0; y<mMask.GetHeight();++y)
	{
		for(int x=0; x<mMask.GetWidth();++x)
		{
		
			if(y+decDN < mMask.GetHeight())
			{
				maxdec = decDN;
			}
			else
			{
				maxdec = decDN + abs(y-decDN);
			}

			sf::Color colorA = mMask.GetPixel(x,y+maxdec);
			sf::Color colorB = mMask.GetPixel(x,y);
		
			if(colorA == sf::Color(0,0,0) && colorB == sf::Color(255,255,255))
			{
				mOutput.SetPixel(x,y,sf::Color(0,255,0));
			}
		
			if(y-decUP>=0)
			{
				mindec = decUP;
			}
			else
			{
				mindec = decUP - abs(y-decUP);
			}

			sf::Color colorC = mMask.GetPixel(x,y-mindec);
			sf::Color colorD = mMask.GetPixel(x,y);
		
			if(colorC == sf::Color(0,0,0) && colorD == sf::Color(255,255,255))
			{
				mOutput.SetPixel(x,y,sf::Color(255,0,0));
			}
			
		}
	}
	
	for(int y=0; y<mOutput.GetHeight();++y)
	{
		for(int x=0; x<mOutput.GetWidth();++x)
		{
		 	sf::Color color = mOutput.GetPixel(x,y);
		 	
		 	if(color == sf::Color(255,0,0))
		 	{
		 		//paintTopBorder(x,y);
		 		paintVerticalBorder(x,y,sf::Color(255,0,0),mBorderUp);
		 	}
		 	
		 	if(color == sf::Color(0,255,0))
		 	{
			 	paintVerticalBorder(x,y,sf::Color(0,255,0),mBorderDn);
		 	}
		 	
		}
	}
}

// -------------------------------------------------------------------------------------------------
//
// -------------------------------------------------------------------------------------------------

void terrain::makeHole(int x, int y, int radius)
{

	sf::Sprite map;
	map.SetImage(mOutput);
	sf::Shape hole = sf::Shape::Circle(sf::Vector2f(x,y), radius, sf::Color(0,0,0));
		
	sf::RenderImage out;
	out.Create(mOutput.GetWidth(),mOutput.GetHeight(),1);

		out.Clear();
			out.Draw(map);
			out.Draw(hole);
		out.Display();

	mOutput = out.GetImage();	
}

// -------------------------------------------------------------------------------------------------
//
// -------------------------------------------------------------------------------------------------
sf::Image& terrain::getImage()
{
	return  mOutput;
}

// -------------------------------------------------------------------------------------------------
//
// -------------------------------------------------------------------------------------------------
int terrain::getTerrainHeight(int x, int y)
{
	sf::Color Pixel;
	
	if ( x > 0 && y > 0 && x < mOutput.GetWidth() && y < mOutput.GetHeight() )
	{
		Pixel = mOutput.GetPixel(x,y);
		
		if(Pixel != sf::Color(0,0,0,0))
		{
			while(Pixel != sf::Color(0,0,0,0))
			{
				if (x>=0 && x<mOutput.GetWidth() && y >=0 && y <mOutput.GetHeight())
				{
					Pixel = mOutput.GetPixel(x,y);
				}
					y--;
				
				if(y==mOutput.GetHeight())
					return -1;
		
				if(y==0)
					return -1;		
			}
		
			return y;	
		}
		else 
		{
			while(Pixel == sf::Color(0,0,0,0))
			{
				if (x>=0 && x<mOutput.GetWidth() && y >=0 && y <mOutput.GetHeight())
				{
					Pixel = mOutput.GetPixel(x,y);
				}
				y++;

			if(y==mOutput.GetHeight())
				return -1;
		
			if(y==0)
				return -1;
				
			}

			return y;
		}
		
	}
	else
	{
	return -1;
	}
}
// -------------------------------------------------------------------------------------------------
//
// -------------------------------------------------------------------------------------------------




