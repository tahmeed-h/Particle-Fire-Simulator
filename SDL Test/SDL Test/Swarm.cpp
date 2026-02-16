//
//  Swarm.cpp
//  SDL Test 
//
//  Created by Abdul Hoque Habib on 04/11/2024.
//

#include "Swarm.hpp"


Swarm::Swarm() : lastTime(0) {
    m_pParticles = new Particle[NUOFPARTICLES]; // dynamically allocates memory for an array of Particle objects on the heap, where NUOFPARTICLES defines the number of particles. The pointer m_pParticles (declared in Swarm.hpp) now points to the first element in this array, allowing Swarm to access and manage the array of Particle objects. Allocating memory for an object means reserving a specific block of memory in the computer's RAM where object’s of the class 'Particle's data will be stored. This block includes enough space for the object's member variables (like integers, floats, pointers, etc.), which hold the object's state. Once allocated, you can access and manipulate the object's data and call its member functions, which operate on that data
}


void Swarm::updateAllParticles(int elapsed) {
    
    int interval = elapsed - lastTime; // finds the time taken between each time update() is executed as it finds the differenec between the total time since the program before the for loop and the new total time including the time taken for the for loop
    for(int i = 0; i < Swarm::NUOFPARTICLES; i++) { //iterates over each particle object in that was allocated (5000 of them)
        m_pParticles[i].updatePositionEachParticle(interval); //for the i-th particle, calls the updatePositionEachParticle to update their position- passing the time interval to it.
        //you can only access Particle members when using m_pParticles[i] as m_pParticles is an array of Particle objects. When you use m_pParticles[i], the compiler interprets this as accessing the i-th Particle object. Consequently, you can only call methods or access members that belong to the Particle class
    }
    
    lastTime = elapsed; //everytime we finish updating all the particles (after the for loop), we set lastTime to the total amount of miliseconds that has elapsed since the program began running, ready for the next iteration. This then allows us to calculate how long has passed from this time to the next frame (as we are subtracting from the new elapsed time), which is calculated and storedi n 'interval'
}

Swarm::~Swarm(){
    delete [] m_pParticles; //reallocates memory the array of Particle objects took back into the system
}
