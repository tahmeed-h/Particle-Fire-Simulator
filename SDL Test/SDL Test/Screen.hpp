//
//  Screen.hpp
//  SDL Test
//
//  Created by Abdul Hoque Habib on 24/10/2024.
//

#ifndef Screen_hpp
#define Screen_hpp

#include <stdio.h>
#include <SDL.h>

namespace TH {
    class Screen {
    public:
        const static int SCREEN_WIDTH = 800; //units are in pixels
        const static int SCREEN_HEIGHT = 600;
    private:
        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
        SDL_Texture* m_texture;
        Uint32* m_buffer;
        Uint32* m_tempBuffer;
    public:
        Screen();
        bool init(); //Initializes SDL, creates the window and renderer, sets the screen to white and prepares the screen for rendering.
        void update();
        void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue); //takes an x,y co-ordinate to locate what pixel we want. Uint are basically the unsigned chars we used in the Bit Shifting project.
        bool processEvents();
        void close();
        void clearScreen();
        void boxBlur();
    };
}

#endif /* Screen_hpp */
