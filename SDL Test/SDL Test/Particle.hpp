//
//  Particle.hpp
//  SDL TEST
//
//  Created by Abdul Hoque Habib on 04/11/2024.
//

//This class represents an individual particle, containing its properties
//This  can be used in other programs, where the screen size is not fixed for example as we are only defining the proprties of an inidvidual particle and nothing specific to a system or API like SDL
#ifndef Particle_hpp
#define Particle_hpp

#include <stdio.h>

struct Particle { //only difference between a class and a struct is, by default, the members are public and not private like a class
public: //we break encapsulation so we are able to access the member variables frequently instead of using a get method every time we needed to access it- which is inefficient
    double m_x; //double gives us more precision for the pixel co-ordinates
    double m_y;
   
    //2. double xpeed; //these were used for the Cartesian co-ordiantes, where we assigned the posotion and speed in in 'update()', where all particles have the same speed and direction that is recalculated every time update() is called, which is every frame as its in a while loop. It doesnt look uniform as all particles have the same values applied each frame. However, their positions are not reset, and they have their own unique starting position, so each particle’s movement is based on its unique, previously updated position- giving the appearance of each particle traveling in its own direction.
    //2. double yspeed;
    
   //3. double m_xspeed; //random 'speed' of particle (just the incremental change of the particles new position and old position)
    //3. double m_yspeed; these were used for the Cartesian co-ordinates, where we assigned the position and speed in the constructor, and not in 'update()', so each particle now had its own speed and direction
private:
    double m_speed; //how far the particle moves per frame
    double m_direction; // the angle from 0 to 360 degrees the particle moves in
private:
    void constructorFunc();
public:
    Particle();
    void updatePositionEachParticle(int interval);
};


#endif /* Particle_hpp */

