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

#ifndef PARTICLE_HPP
#define PARTICLE_HPP
class particle
{
	public:
	
		particle();
		~particle();
		
		void setup(float x, float y, float angle, float speed, sf::Image& imageReference);
		void motion(float timer);
		void display(sf::RenderWindow & window, float offsetX, float offsetY);
		bool killMe();
		
	
	private:
		sf::Sprite		mSprite;
		sf::Vector2f  mOrigin;
		sf::Vector2f	mPosition;
		float 				mSpeed;
		float					mPhysicTimer;
		float					mAngle;
		sf::Vector2f	mScale;
		float					mAlpha;
		bool					mKillMe;	
		float					mSineSize;
};
#endif
