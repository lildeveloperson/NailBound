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

#include <list>
#include <iostream>
#include <time.h>
#include <SFML/Graphics.hpp>

#include "terrain.hpp"
#include "particle.hpp"



int main()
{
		
		srand ( time(NULL) );

		sf::VideoMode desktop = sf::VideoMode::GetDesktopMode();
		
		sf::RenderWindow window(desktop, "Worms test");//,sf::Style::Fullscreen);
		int WindowWidth 	 = window.GetWidth();
		int WindowHeight   = window.GetHeight();
		sf::View view 		 = window.GetDefaultView();
		
		
		sf::Image 	splashImg;
		sf::Sprite 	splashSpr;
		splashImg.LoadFromFile("./medias/misc/splash.png");
		splashSpr.SetImage(splashImg);
		
		// Throw all particle in simple liste		 
    std::list<particle*> particles;
  	std::list<particle*>::iterator it;
  	it = particles.begin();
  	
  	// Load sea wave
  	sf::Image sea;
  	sf::Sprite wave;
  	sea.LoadFromFile("./medias/misc/wave.png");
  	wave.SetImage(sea);
  	float seaOffset=0;
  	
  	// Load particle sprite
		sf::Image smoke;
		smoke.LoadFromFile("./medias/misc/smoke.png");

		// Load Terrain
		terrain worms(
									"./medias/terrains/mask/mask_02.png",
									"./medias/terrains/desert/border_top.png",
									"./medias/terrains/desert/border_down.png",
									"./medias/terrains/desert/desert.png"
									);

		// Terrain offset for scrolling
		float	terrainOffSetX=0;
		float terrainOffSetY=0;

		int terrainWidth  = worms.getImage().GetWidth();
		int terrainHeight = worms.getImage().GetHeight();

		// Sprite for display the result of terrain::getTerrainHeight()
		sf::Image heightArrow;
		heightArrow.LoadFromFile("./medias/misc/arrow.png");
		
		// This arrow represent the terrain surface collision
		sf::Sprite arrow;
		arrow.SetImage(heightArrow);
		arrow.SetColor(sf::Color(128,128,128,128));
		
		// Sprite for display terrain normal
		sf::Image normalArrow;
		normalArrow.LoadFromFile("./medias/misc/normal.png");
		sf::Sprite normal;
		normal.SetImage(normalArrow);
		normal.SetOrigin(32,64);
		/*
		sf::Vector2f direction;
		sf::Vector2f normal;
		*/
		// Some variables...
		bool mouseClicked = false;
		bool updateTerrain = true;
		
		// Sprite for display the terrain
		sf::Sprite sTerrain;
		sTerrain.SetImage(worms.getImage());

		while (window.IsOpened())
    {
        // Process events
        sf::Event event;
        while (window.PollEvent(event))
        {
            // Close window : exit
            if (event.Type == sf::Event::Closed)
                window.Close();
        }
 
				const sf::Input& input = window.GetInput();
				if (input.IsKeyDown(sf::Key::Escape)) window.Close();
				
				// ------------------------------------------------------------------------------
				// terrain scrolling
				// ------------------------------------------------------------------------------
				float pixelSec = 1.f * window.GetFrameTime();
				if (input.IsKeyDown(sf::Key::Left))  terrainOffSetX += pixelSec;
				if (input.IsKeyDown(sf::Key::Right)) terrainOffSetX -= pixelSec;
				if (input.IsKeyDown(sf::Key::Up))    terrainOffSetY += pixelSec;
				if (input.IsKeyDown(sf::Key::Down))  terrainOffSetY -= pixelSec;
 	
 				// ------------------------------------------------------------------------------
 				// Lock scrolling
 				// ------------------------------------------------------------------------------
 				
 				if(terrainOffSetX>0)
 				terrainOffSetX=0;

 				if(terrainOffSetX < -terrainWidth+WindowWidth  )
 				terrainOffSetX=-terrainWidth+WindowWidth;
 				
 			  if(terrainOffSetY<-terrainHeight+WindowHeight)
 				terrainOffSetY=-terrainHeight+WindowHeight;
 				
 				/*
 				if(terrainOffSetY>4096)
 					terrainOffSetY=4096;
				*/
 				
  			sTerrain.SetPosition(terrainOffSetX,terrainOffSetY);
			  // ------------------------------------------------------------------------------
 				
 				
 				
 				// ------------------------------------------------------------------------------
 				// Get terrain height
 				// ------------------------------------------------------------------------------
 				int posX 	 = (input.GetMouseX() - terrainOffSetX);
 				int posY 	 = input.GetMouseY()  - terrainOffSetY;
 				int height = worms.getTerrainHeight(posX, posY);		
 
 				// Set position of our arrow
 				arrow.SetPosition(
									 				posX - (arrow.GetSize().x/2) + terrainOffSetX,
									 				(height - arrow.GetSize().y + terrainOffSetY)
									 				);
									 				
 				normal.SetPosition(
									 				posX + terrainOffSetX,
									 				(height + terrainOffSetY)
									 				);
									 				
									 				
				// Compute normal of surface		
				int h1 = worms.getTerrainHeight(posX-2, posY);						 				
				int h2 = worms.getTerrainHeight(posX+2, posY);						 				
									 				
				sf::Vector2f A(posX-2,h1);
				sf::Vector2f B(posX+2,h2);

 				sf::Vector2f dir;
 				dir = B - A;
 				
 				// Get vector lenght
				float L = sqrt(dir.x*dir.x + dir.y*dir.y);

				if(L!=0)
				{
					dir.x / L;
					dir.y / L;
				}

				// get angle in deegre
				float angle = atan2( dir.y, dir.x ) *180/3.14159265f;

				normal.SetRotation(angle);
				
				 
 
			  // ------------------------------------------------------------------------------

 
			  // ------------------------------------------------------------------------------
			  // Making a hole !
			  // ------------------------------------------------------------------------------
	 			if( input.IsMouseButtonDown(sf::Mouse::Left) == true && mouseClicked == false && height != -1 )
	 			{
	 				mouseClicked = true;
	 				worms.makeHole(posX, height,50);
	 				updateTerrain=true;
	 				
	 				// Create some particle	
					for(int n=0; n<15; ++n)
					{ 				
		 				particle * newParticle = new particle();
	 					newParticle->setup(posX, height,  (rand() % 360) , rand() % 10 + 15, smoke);
	 				  particles.push_back(newParticle);
	 				}
		
	 			}
 				
 				// Release mouse for next shoot !
	 			if( input.IsMouseButtonDown(sf::Mouse::Left) == false && mouseClicked == true )
	 			{
	 				mouseClicked = false;
	 			} 
  
 				// ------------------------------------------------------------------------------
 				// Update terrain if needed.
 				// ------------------------------------------------------------------------------
	 			if(updateTerrain==true)
	 			{
		 			updateTerrain=false;
	 			  sf::Image * terrainImage =& worms.getImage();
	 			  terrainImage->CreateMaskFromColor(sf::Color(0,0,0));
	 			  sTerrain.SetImage(*terrainImage);
				}
 
				// ------------------------------------------------------------------------------
				// Update all particles
				// ------------------------------------------------------------------------------
	 			for(it=particles.begin();it!=particles.end();++it)
	 			{
	 					particle * Particle = *it;
			 			Particle->motion( 0.005 * window.GetFrameTime() );
	 			}
 	 			
 				// ------------------------------------------------------------------------------
 				// Sea motion
 				// ------------------------------------------------------------------------------

	 			seaOffset += 0.1 * window.GetFrameTime();
				if(seaOffset>128)
					seaOffset=0;

				// ------------------------------------------------------------------------------
        // Clear screen
        // ------------------------------------------------------------------------------
        window.Clear(sf::Color(64,128,255));
        
		    // ------------------------------------------------------------------------------
				// Draw upper sea
		    // ------------------------------------------------------------------------------
		    int Brightness=192;

				for(int j=0; j<4; ++j)
				{      
			
				Brightness = 128 + (16*j);
		    wave.SetColor(sf::Color(Brightness,Brightness,Brightness,192));
			
				  for(int i=-10; i<40; ++i)
				  {
				  		wave.SetPosition(
															(((i*128)+terrainOffSetX)+seaOffset)+(j*32), 
															((worms.getImage().GetHeight()-128)+terrainOffSetY)+(j*32)-136  
															);
						  window.Draw(wave);
						  
				  }
		    } 	
		    // ------------------------------------------------------------------------------ 

		    // ------------------------------------------------------------------------------
		    // Draw terrain
		    // ------------------------------------------------------------------------------ 
		    window.Draw(sTerrain);
        
        // ------------------------------------------------------------------------------
        // if arrow is on the terrain , display it!
        // ------------------------------------------------------------------------------	
        if (height != -1)
        {
	       	window.Draw(arrow);
					window.Draw(normal);
       	}
        // ------------------------------------------------------------------------------
        // Draw all particles
       	// ------------------------------------------------------------------------------ 	
	 			for(it=particles.begin();it!=particles.end();++it)
	 			{
	 					particle * Particle = *it;
			 			
			 			
			 			if (Particle->killMe()==true)
			 			{
			 				particles.erase(it);
			 				delete Particle;
			 				it--;
			 			}
			 			else
			 			{
				 			Particle->display(window,terrainOffSetX, terrainOffSetY );
			 			}

	 			}
        	
		    // ------------------------------------------------------------------------------
				// Draw bottom sea
		    // ------------------------------------------------------------------------------
				for(int j=0; j<4; ++j)
				{      
			
				Brightness = 128 + (16*(j+4));
		    wave.SetColor(sf::Color(Brightness,Brightness,Brightness,192));
			
				  for(int i=-10; i<40; ++i)
				  {
				  		wave.SetPosition(
															(((i*128)+terrainOffSetX)+seaOffset)+(j*32), 
															((worms.getImage().GetHeight()-128)+terrainOffSetY)+(j*32)  
															);
						  window.Draw(wave);
						  
				  }
		    } 	
      // ------------------------------------------------------------------------------  	
      
      // ------------------------------------------------------------------------------
      // Display our game !
      // ------------------------------------------------------------------------------ 
      window.Draw(splashSpr); 	
      window.Display();
    }





return EXIT_SUCCESS;
}

