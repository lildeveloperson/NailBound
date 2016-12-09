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

#ifndef TERRAIN_HPP
#define TERRAIN_HPP


#include <SFML/Graphics.hpp>
#include <string>


class	terrain
{
	public:
		terrain();
		terrain(std::string mask, std::string borderUp, std::string borderDn, std::string texture);
		~terrain();
		
		
		// ---------------------------------------
		// save(std::string output);
		// Save the result into file output.
		// ---------------------------------------
		bool 				save(std::string output);
		
		// ---------------------------------------
		// makeHole(int x, int y, int radius);
		// Create Hole at the coordinate x,y
		// the size is determined by radius
		// ---------------------------------------
		void 				makeHole(int x, int y, int radius);
		
		// ---------------------------------------
		// getImage()
		// get instance of the SFML image for 
		// display or modify the result.
		// ---------------------------------------
		sf::Image&  getImage();
		
		
		// ---------------------------------------
		// getTerrainHeight(int x, int y)
		// Retrieve terrain height by 
		// the given coordinates
  	// ---------------------------------------
		int 				getTerrainHeight(int x, int y);

	private:
	
		void 							fill();
		int  							paintVerticalBorder(int x, int y, sf::Color mask, sf::Image texture);
		void 							paintBorder();

		sf::Image					mMask;
		sf::Image					mBorderUp;
		sf::Image					mBorderDn;
		sf::Image					mTexture;
		sf::Image					mOutput;	
		sf::Vector2i			mBorderOffset;
};



#endif
