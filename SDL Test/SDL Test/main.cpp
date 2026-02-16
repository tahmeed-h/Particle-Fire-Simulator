//
//  main.cpp
//  SDL Test
//
//  Created by Tahmeed Habib on 17/10/2024.
//

//The primary purpose of a renderer is to control how and where graphics are displayed on the screen (so its job is to draw on the screen/window). It acts as an intermediary between your graphics data (textures, shapes, etc.) and the actual output you see on the screen. It esseantially acts as the paintbrush that lets you paint on the canvas (window)
//A texture is an image or graphic that can be drawn onto the screen. It contains pixel data (like colors and transparency). The purpose of a texture is to hold the visual information that you want to render on the screen. This would be the paint iteself
// buffer means a region of memory allocated to store data temporarily. In SDL and other graphics libraries, buffers are used to hold pixel data before presenting it to the scree

#include <iostream>
#include <SDL.h>
#include "Screen.hpp"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Swarm.hpp"
#include "Particle.hpp"
using namespace std;
using namespace TH;

int main() {
    
    srand(time(NULL)); //srand() used to initialize the random number generator with a unique seed (starting point for the RNG). srand sets the starting point, or "seed," for generating random numbers with rand(). If you use the same seed each time, rand() will produce the same sequence of "random" numbers. By providing a unique seed, you ensure different sequences of random numbers each time the program runs. Without calling srand() with a unique seed, the random number generator defaults to a constant seed (often zero), producing the same sequence of "random" numbers each time you run the program. returns the current time as the number of seconds since January 1, 1970 (known as the Unix epoch). NULL indicates that you don’t want to store the current time; you only want to retrieve it
    
    Screen screen1;
    
    if(screen1.init() == false) { //both calls screen1.init() and evaluates its return value. Calling init(): When you write screen1.init(), it runs init() and initializes the SDL resources. Checking the Return Value: After init() runs, it returns either true or false. This value is then evaluated by the if statement to check for any initialization error. If init() returns false, the if block runs and outputs an error message. So, while it might look like it’s only checking for errors, this line first executes init()
        cout << "Error with SDL system. " << endl;
    }
    
    
        //bool quit = false;
        
    Swarm swarm1;
        
        while(true) { //loop that will run as long as quit remains false. If we set quit to true in the while loop, we will make the loop quit as the condition in the brackets will no longer be true.
            //update particles (like positions, colours, etc)
            
            
           //screen1.update(); just a test. The white backround we initalised in init() is executed first as we called update before changing the pixels to purple. So the white screen appears but then the for loop is executed and the screen then changes to purple.
            
         
            
            //Drawing particles
            int time_elapsed = SDL_GetTicks();
            
            
            //screen1.clearScreen(); //as the particles are moving from one position to another, we must clear the screen each frame/iteration or else the particles will just stay there and build up
            
            swarm1.updateAllParticles(time_elapsed);
            
            
            unsigned char green = (unsigned char)((1 + sin(time_elapsed * 0.0001)) * 127.5); // we use an unsigned char as it can hold values from 0 to 255 and only holds positive values.
            unsigned char red = (unsigned char)((1 + sin(time_elapsed * 0.0002)) * 127.5);
            unsigned char blue = (unsigned char)((1 + sin(time_elapsed * 0.0003)) * 127.5); //The + 1 shifts the entire sin curve up, so the min and max range is now 0 to 2. This happens as the +1 is applied to the result of sin(...), which shifts the output values (the heights of the wave) up by 1 unit. This directly affects the y-values, raising the sine wave so it oscillates between 0 and 2, rather than -1 and 1. We do this as we want a positive RGB value. We then multiply whatever the output of this is by 127.5 to give a range of 0 to 255. sin(...) is the angle and 127.5 is the hypotenuse. Green cycles from 0 to 255 the slowest (as it has the smallest angle input), then red and then blue.
            
            //cout << green << endl;
            /*for(int y = 0; y < Screen::SCREEN_HEIGHT; y++) {
                for(int x = 0; x < Screen::SCREEN_WIDTH; x++) {
                    screen1.setPixel(x, y, red, green, blue); //The function  screen1.setPixel purpose is to choose the colour of a pixel and the position of the pixel you want to set on the screen. First argument is the column of the pixel. Second argument is the row of the pixel. Third is red compnent of the colour, fourth is the green component and third is the blue.
                }
            }
            //for each row, all the x values are iterated through, so we visit every pixel on the screen. So when y=0 (first row), it will move to the inner for loop and iterate through all the x values (which represent the columns of that row), filling in the 0th row with the setPixel function's values. Then the iteration for y=0 is finished, so it moves on to y=1 and the process starts again. Changes whole screen colour
            */
            
            
            //screen1.setPixel(400, 300, 0x00, 0x00, 0x00); //sets a black pixel to the co-ordinates (400,300), relative to the screens width and heigh
            
            const Particle * const pParticles = swarm1.getParticles(); //stores first address of allocated memory for the number of particles in 'pParticles'. It also has a const pointer to a const Particle, so you cant modify the address the pointers pointing to or the value of the pointer  (respectively explained)
            for(int i = 0; i < Swarm::NUOFPARTICLES; i++) { //iterates over each particle object in that was allocated (5000 of them)
                Particle oneparticle = pParticles[i]; //Retrieves the i-th Particle object from pParticles (which holds all particles) and assigns it to a new Particle instance, oneparticle. This provides a copy of each particle, which we can use to modify it. It also does not alter the original particle data stored in the array pParticles. :
                //need to map the x co-ordianted range of -1 to 1 to the screens range of pixels to plot the particle on th escreen:
                //3. //int x = (oneparticle.m_x + 1) * Screen::SCREEN_WIDTH/2;
                //3.//int y = (oneparticle.m_y + 1) * Screen::SCREEN_HEIGHT/2;
                //mapping from cartesian (origin (0,0) at centre to pixel grid (origin (0,0) top left)): +1 shifts range from -1 to 1 to 0 to 2 to give positive values as our goal is to get a range from 0 to the max screen pixels. So we multiply by the screen width and height divided by 2 to cancel the 2 in the range 0 to 2 to leave us with a range 0 to SCREEN_WIDTH and 0 to SCREEN_HEIGHT. (0 starts from top left). This worked perfectly with the cartesian mapping as we were working directly with x and y co-ords and could map it easily but now when using polar co-ordinates, we convert it to cartesian when mapping it to the screen and it doesnt account for the screen's aspect ratio:
                
               
                int x = (oneparticle.m_x + 1) * Screen::SCREEN_WIDTH/2;
                int y = oneparticle.m_y * Screen::SCREEN_WIDTH/2 + Screen::SCREEN_HEIGHT/2;
                //mapped from polar to cartesian in void Particle::updatePositionEachParticle(int interval) and now to pixel grid oo-ords. We now use screen width for the y direction so that the x and y range for the particle is now the same. However, now the particles dont start in the middle as the screen is a rectangle and we arent mapping the y co-ordinate to the same range of the respective screen pixels. int y = oneparticle.m_y * Screen::SCREEN_WIDTH/2 would return 0, which is the first row in the array, so the particles would start at the top and x starts in the 400th column (as m_x is set to 0 in the constructor and SCREEN_WIDTH is 800)- in the middle. So we have to add half the Screens heght to bring the y value central.
                
                screen1.setPixel(x, y, red, green, blue); //sets colour of each particle
            }
            
            
            screen1.boxBlur();
         
            
            screen1.update();//after pixel atrributes, like colour and position have been set, we update them and show the screen
            
            //checking for events (like any user interaction-key presses, mouse movements, window close actions, etc)
            if(screen1.processEvents() == false) {
                break; //if the function processEvents returns false, it means the user has pressed the quit button, so this will break the program out of the loop and executes screen1.close()
            }
        }
             
        
    screen1.close();
        
    
    return 0;
}




