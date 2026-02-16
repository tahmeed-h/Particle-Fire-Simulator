//
//  Swarm.hpp
//  SDL Test
//
//  Created by Abdul Hoque Habib on 04/11/2024.
//

//This class manages a collection (or "swarm") of particles, handling memory allocation and acting as a container. It initializes, stores, and updates all Particle instances, and provides access to each particle for rendering.

#ifndef Swarm_hpp
#define Swarm_hpp

#include <stdio.h>
#include "Particle.hpp"

class Swarm {
public:
    const static int NUOFPARTICLES = 5000;
private:
    Particle *m_pParticles; //is private so needs a get function to access the array.
    int lastTime;
public:
    Swarm();
    ~Swarm();
    
    const Particle * const getParticles() { // getter for the array of Particle objects allocated. 'a constant pointer to a Particle that's constant'. const pointer (pointer will always point at same memory address, which is the first Particle object in the arraye) to a const Particle object (The Particle objects in the array cannot be modified via this pointer.)
        return m_pParticles; //the function returns the address of m_pParticles
        //E.g. of changing address of pointer: swarm.m_pParticles = new Particle[500];. Changes address because it reallocates memory for a new array of Particle objects. Before this line, m_pParticles pointed to the original array. After this line, m_pParticles points to a new block of memory that holds 500 Particle objects.
        //E.g. of changing value of pointer: swarm.m_pParticles[i].m_x = 1.0; (this accesses the m_x variable of the i-th Particle in the m_pParticles array that belongs to the Swarm class and assigns it the value 1.0, changing the value of the pointer
        //So it gives access to the array of particles, with both the data and the pointer being protected from modification
    }
    
    void updateAllParticles(int elapsed);
    
};

#endif /* Swarm_hpp */
