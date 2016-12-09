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
#include <SFML/Graphics.hpp>
#include "particle.hpp"


particle::particle()
{
		mScale.x = 0.1;
		mScale.y = 0.1;
		mAlpha   = 255;
		mKillMe  = false;
		mSpeed   = 5;
}

particle::~particle()
{
}

void particle::setup(float x, float y, float angle, float speed, sf::Image& imageReference)
{
	mOrigin.x 	 = x;
	mOrigin.y 	 = y;
	mAngle    	 = angle;
	mSpeed    	 = speed;
	mPhysicTimer = 0;
	mSineSize	   = 0;
	
	mSprite.SetImage(imageReference);
}

void particle::motion(float timer)
{

		mPosition.x = mOrigin.x + ( mSpeed * cos((360-mAngle) * 3.1415f / 180) * mPhysicTimer) + ((mSineSize + (mSineSize/2) * cos(mPhysicTimer*2)) - mSineSize);
		mPosition.y = mOrigin.y + ( mSpeed * sin((360-mAngle) * 3.1415f / 180) * mPhysicTimer) - ( 0.5 * 10 * ( mPhysicTimer * mPhysicTimer ));
		mPhysicTimer += timer;
	  mSineSize    += timer*2;
		mScale.x += (timer*50);
		mScale.y += (timer*50);
	
		mAlpha = mAlpha - (timer*40);
	
		if (mAlpha <= 0)
		{
			mAlpha 	= 0;
			mKillMe = true;
		}
	
		if (mScale.x >= 64)
			mScale.x=64;

		if (mScale.y >= 64)
			mScale.y=64;

}

void particle::display(sf::RenderWindow & window, float offsetX, float offsetY)
{
	mSprite.SetPosition(
											(mPosition.x - (mScale.x/2)) + offsetX,
											(mPosition.y - (mScale.y/2)) + offsetY 				
										 );
	
	mSprite.Resize(mScale);
	mSprite.SetColor(sf::Color(255,255,255,(sf::Uint8)mAlpha));
	window.Draw(mSprite);
}

bool particle::killMe()
{
	return mKillMe;
}

