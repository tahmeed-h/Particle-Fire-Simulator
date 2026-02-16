//
//  Screen.cpp
//  SDL Test
//
//  Created by Abdul Hoque Habib on 24/10/2024.
//

#include "Screen.hpp"
#include <SDL.h>
#include <iostream>
using namespace std;
namespace TH{


Screen::Screen() :
m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer(NULL), m_tempBuffer(NULL) {
    
} //setting these pointer to NULL ensures that they don't start with random, undefined memory addresses. It creates a clear, intentional starting state

bool Screen::init() {
    
    const int SCREEN_WIDTH = 800; //units are in pixels
    const int SCREEN_HEIGHT = 600;
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0) { //SDL_Init() is a standard function in the SDL library, and it's used to initialize SDL subsystems like video, audio, or timer. The argument SDL_INIT_VIDEO is a flag that specifies which subsystem (in this case, the video subsystem) you want to initialize. So SDL_INIT_VIDEO is the argument of the function SDL_Init.
        cout << "SDL init failed." << SDL_GetError() << endl;
        return false; //If SDL fails to initialize the video subsystem, the program will return 1 (an error)
    }
    
    cout << "SDL init succeeded " << endl;
    
    m_window = SDL_CreateWindow("Particle Fire Explosion", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); //using SDL wiki to find the function CreateWIndow, we find the funciton takes 5 arguments:const char *title, int x, int y, int w, int h, Uint32 flags). Uint32 means it can store a 32-bit unsigned int and 'flags' just represnets diff options the window has. In this case the argument 'SDL_WINDOW_SHOWN' means the window is visible when created
    //'window' stores the address of the window created by the SDL_CreateWindow function. SDL_CreateWindow creates a window, that is of type/belongs to 'SDL_Window'.

    if(m_window == NULL) { //If SDL_CreateWindow fails, it will return NULL (a null pointer), which indicates that the window was not created successfully.
        cout << "Window could not be created.  " << SDL_GetError() << endl; //describing the most recent error that occurred within the SDL library
        SDL_Quit();
        return false;
    }
    
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC); //Declares a pointer to an SDL_Renderer. The renderer is used to handle drawing operations in your window (like rendering images, shapes, or textures). The pointer 'renderer' will store the address of the newly created renderer.  SDL_CreateRenderer is a function that creates the renderer and returns the address of it. 'window' is where the renderer will draw to. It is passing the memory address where the window object resides. Passing -1 means SDL will choose the first available rendering driver that supports the requested features (in this case, VSync). Last argument is a flag: SDL_RENDERER_PRESENTVSYNC means the renderer should use vertical synchronization (computer screen refreshes from the top left hand corner and vertically goes down). VSync ensures that the renderer's updates are synchronized with the display's refresh rate, which can prevent screen tearing. renderes  main role is to provide a way to draw 2D graphics (textures, shapes, etc.) onto the window
    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT); //SDL_Texture* texture: This declares a pointer to an SDL_Texture object. The SDL_CreateTexture function returns the address of the newly created texture, and this is stored in 'texture'. The texture represents a 2D image or a block of pixel data that you can render to the screen using a renderer. First argument:  renderer is responsible for actually drawing the texture onto the window or screen. Second argument: This specifies the pixel format for the texture, which defines how each pixel is stored in memory. SDL_PIXELFORMAT_RGBA8888 means that each pixel is represented by 32 bits (4 bytes), with 8 bits (1 byte) for each channel: Red, Green, Blue, and Alpha (transparency). So, each pixel in this texture will have an RGBA value. Third argument: SDL_TEXTUREACCESS_STATIC means the texture’s content will not change frequently. Fourth argument: this specifies the width of the texture in pixels. In this case, the width of the texture will match the width of the window. Same for height of texture.
    
    if(m_renderer == NULL) { //Function SDL_Renderer return NULL if theres an error
        cout << "Couldnt create renderer. " << SDL_GetError() << endl;
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }
    
    if(m_texture == NULL) { //Function SDL_Renderer return NULL if theres an error
        cout << "Couldnt create texture. " << SDL_GetError() << endl;
        SDL_DestroyWindow(m_window);
        SDL_DestroyRenderer(m_renderer);
        SDL_Quit();
        return false;
    }
        
    m_buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];//Uint32 is an int SDL has defined as part of its data types, which is bascially an unsigned 32-bit int. Need to allocate enough of these for all the pixels on the screen. Each pixel has 4 values (RGBA), each of them being one byte. So each pixel has four bytes/32 bits. So for every pixel we need an int to repreesent the info for the pixel. This is essentially the template for our pixels
    
    //Previous error: When you declared Uint32* m_buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT]; inside the init function, it created a new local variable named m_buffer. This local variable shadows the member variable m_buffer of the Screen class, which means that any reference to m_buffer inside init actually refers to this new local variable.
    
    //write pixel info to buffer
   // memset(buffer, 0xFF, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32)); //memset is a standard C library function that fills a block of memory with a specific value. First argument: buffer points to the block of memory we want to fill. Second argument: This is the value that will be set to each byte of the  memory block. As Uint32 is 32-bits (4-byte) unsigned integer, setting it to 255 means that all bytes in each Uint32 will be set to 255 initalised to 255 (the max value of a unsigned byte), and converting this to hex gives you 0xFF, which is opaque white. Thid argument: Calculates the total size (in bytes) of the memory block that needs to be filled. SCREEN_WIDTH * SCREEN_HEIGHT gives the total number of pixels (each pixel represented by one Uint32). sizeof(Uint32) gives the size of one Uint32 (which is 4 bytes).
    
    //buffer[30000] = 0xFFFFFFFF; //Accesses the 30,000th element in the buffere array (which are the pixels). Each pair of FF (255) is assigned to R, G, B and A. Format is 0xRRGGBBAA. This makes this specific pixel opaque white.
    m_tempBuffer =  new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT]; //our buffer for the previous pixels location- for the blur
    
    memset(m_buffer, 0, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32)); //initialises all of buffer to 0, which is black
    memset(m_tempBuffer, 0, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32)); //t//initialises all of blur buffer to 0, which is black.
    
    
    for(int i=0; i < SCREEN_WIDTH*SCREEN_HEIGHT; i++) { //This loop initializes each pixel in the buffer to the color white (0xFFFFFFFF). It achieves the same effect as memset but does so more slowly because it iterates through each pixel individually. This method allows us to set the color of each pixel, providing the flexibility to customize colors based on the pixel's position or implement special effects etc.
        m_buffer[i] = 0x000000; // assigns the value 0xFFFFFFFF to the ith element of m_buffer, setting whole screen to white.  If we never called update(), this change won't be reflected visually on the screen. The update() function takes the pixel data from the buffer and renders/draws it to the display. So, the screen will remain unchanged until update() is executed. Whats happening here is when the update() function is later called, the screen will display a white background right from the start
       // m_buffer[i] = 0x00FF0000;//Format is 0xRRGGBBAA (format can change depending on system.) So we have fully opaque, fully green.
    }
    
    
    return true;
}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
    // sets a specific pixel in m_buffer to a specified color with red, green, blue, and alpha values.
    
    //checking if particle is mapped to off the screen
    if(x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
        //return; //if co-ords are less than or greater than the screen pixels width/height, it will exit the function to prevent attempts to set a pixel outside the display area. If we dont do this and it tries to set a pixel outisde of the screen, it would be trying to access a memory location that it shouldn't- creating an error
        return;
    }
    
    Uint32 colour = 0; //we want colour to be able to store a hexadecimal in the format 0xRRGGBBAA, This requires 32 bits as each hexadecimal digit is worth 4 bits, and we have 8 hexadecimal digits in total- 2 for each component.
    
    colour = colour + red;
    colour = colour << 8; //shifts all the values (in this case only red) by 8 bita
    //Adds red to colour (now 000000000000000000000000RRRRRRRR), then shifts left by 8 bits (colour << 8), making it 0000000000000000RRRRRRRR00000000. In hexadecimal: 0x0000RR00.
    
    colour = colour + green; //fills in the now empty spaces on the right of red: 0000000000000000RRRRRRRRGGGGGGGG
    colour = colour << 8; // then shifts left by 8 bits: 00000000RRRRRRRRGGGGGGGG00000000
    //Adds green to colour (now 0x00001234), then shifts left by 8 bits, making it 0x00RRGG00
    
    colour = colour + blue; //00000000RRRRRRRRGGGGGGGGBBBBBBBB
    colour = colour << 8; //RRRRRRRRGGGGGGGGBBBBBBBB00000000, which is 0xRRGGGBB00
    
    colour = colour + 0xFF; //Adds alpha to colour, resulting in RRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA     0xRRGGBBFF, where RR, GG, BB are values in hexadecimal (we only use hexa to help us visually.)
    
    m_buffer[(y * SCREEN_WIDTH) + x] = colour; //assigns the constructed colour to a specific pixel in m_buffer, located at (x, y). buffer is where all pixels are, stored in an array.
    
//y * SCREEN_WIDTH gives the starting position of row y in m_buffer (since each row has SCREEN_WIDTH pixels). Adding x shifts us to the xth pixel in that row. E.g if we want the sixth row, we set y=5 (as first row is 0), so 5x800 would give us the 4000th pixel, which is the index of the first pixel on the sixth row. And adding an x value gives a certain pixel in the row. We must use this due to the way arrays are stored in memory. We always have to count across rows, never down
}


void Screen::update() {
    SDL_UpdateTexture(m_texture, NULL, m_buffer, SCREEN_WIDTH*sizeof(Uint32)); //SDL_UpdateTexture is used to update the pixel data of a texture. First argument: passes the address of texture. Second argument: the area to update. NULL means to update the entire texture. Third argument: passes address of pixel info. Fourth argument: pitch of the texture update- the number of bytes in a row of pixels.
     SDL_RenderClear(m_renderer); // clears the current rendering target (the window). After this call, the rendering target is empty, and you can draw new textures or shapes on top of it.
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL); //This function copies a texture to the current rendering target (the window). First argument: passes address of where texture will be drawn/rendered. Second argument: address of the texture you want to draw on the screen. Third argument: specifies the area of the texture to copy. By passing NULL, you are telling SDL to use the entire texture. If you wanted to draw only a part of the texture, you would provide an SDL_Rect that defines that area. Fourth argument:  destination rectangle, which specifies where to draw the texture on the screen. By passing NULL, you’re telling SDL to use the texture’s original size and draw it at its default position (usually starting at the top-left corner of the rendering target). So this function essentially connects the texture and renderer, setting it up for it to be displayed.
    SDL_RenderPresent(m_renderer); //actually shows and displays the rendered texture. It takes all the rendering commands that have been executed and presents them to the screen. There are two buffers in memory: one for rendering/drawing (the back buffer) and one for display (the front buffer). While you draw to the back buffer, the front buffer is what the user sees. When you call SDL_RenderPresent(renderer), SDL swaps the back buffer with the front buffer, making the newly rendered content visible to the user.
    
    //Summary: UpdateTexture: function that updates the pixel data of a texture.
    //RenderClear: This function clears the current rendering target (the window) with a specified color, erasing everything that was drawn previously. Gives clean slate for next drawing operation
    //RenderCopy: This function copies a texture to the current rendering target (the window
    //RenderPresent: This function actually shows the rendered texture on the screen.

}

bool Screen::processEvents() {
    SDL_Event event; //This declares a variable of type SDL_Event. SDL_Event is a structure in SDL that stores information about events (like key presses, mouse movements, window interactions, etc.) that the user or the operating system generates. We use this variable to detect and respond to events in the main loop.
    while(SDL_PollEvent(&event)) { // SDL_PollEvent(&event) is an SDL function that checks for pending events in the event queue and fills the event structure with information about the next available event. The function returns 1 (true) if there is an event, and 0 (false) if there are no more events in the queue. This means the loop will keep running as long as there are events to process. The events can be things like closing the window, key presses, mouse movements, or system events like resizing the window. &event passes the address of event, so SDL_PollEvent can store details of this next event in 'event', so it actually modifies it. We pass the address of 'event' as it needs to fill in the details of the next event into an SDL_Event structure. To do this, it must have access to the actual SDL_Event variable we declared, not just a copy. Passing the address allows SDL_PollEvent to write directly to the event variable.
        if(event.type == SDL_QUIT) { //event:SDL_Event structure that stores information about an event (like a key press, mouse movement, or window action). SDL processes these events as they occur. event.type: event.type  specifies what type of event occurred. This could be something like SDL_KEYDOWN (a key press), SDL_MOUSEMOTION (mouse movement), or in this case, SDL_QUIT, which is the event type that SDL generates when the user closes the window. SDL_QUIT: This  represents the event that occurs when the user clicks the "X" button in the window’s title bar, indicating they want to close the application. It's also triggered if the program is terminated by the system or by another process.

            return false; //when in main: sets quit to true, so boolean expression in while loop brackets no longer true and the loop ends. Now its in the cpp file, we return false when the user quits the program.
        }
    }
    return true;
}

void Screen::boxBlur() { //we want to calculate a new screen with blurred values for all the pixels. We are essentially storing all the pixels previous values in another temporary buffer
    
    //We want to write to m_buffer as we are actually drawing those pixels to the screen. At the moment, all the pixels are stored in m_buffer, so we want to tempBuffer to point at the memory m_buffer pointed at so store the pixels into tempBuffer so we can use this to apply the blur effect and then put it back into m_buffer
    Uint32 *temp = m_buffer; //store the address m_buffer is pointing at (which is the first address of the first particle object in the array of memory for particle objects)
    m_buffer = m_tempBuffer; //buffer now points at the memory address of tempBuffer
    m_tempBuffer = temp; //tempBuffer now points at memory address of buffer, so we have swapped the memory locations each buffer points at with each other.
    
    //Now we want to iterate through all the pixels, look at tempBuffer, which now contains the pixels values (colour, position, etc)- create a blur effect and then copy this into m_buffer- which is now a clean buffer. We dont erase any buffers, but keep blurring the same screen. So everytime a new pixel is drawn, the previous pixels will get more and more blurred, but the new pixels will look more comparatively sharper. This creates a trailing effect.
    //to do this, we need to create a box so we can have the current pixel we are working with and the neighbouring pixels around it, in a 3x3 grid (could be other sizes), so the pixel is at the centre.
    /*
     A B C
     D X E
     F G H
     X is the current pixel. The rest are its neighbouring pixels. These 8 neighbouring pixels contribute for the new colour value for the the central pixel. Pixels at the edges or corners of the image have fewer neighbors. Special handling is often needed for these pixels. We add up the colour (RGB) values in each of the 9 pixels, then divide the rsult by 9 and then store this in the central pixel, creating a blur effect. Each time the screen is updated, the previously drawn pixels get blurred more due to repeated averaging. New pixels (e.g., from particle movement) appear sharper. Over repeated updates, this creates a trailing effect where older pixels fade out smoothly as calculating the average blends the colours, reducing its sharpness everytime.
     */
    
    for(int y=0; y < SCREEN_HEIGHT; y++){ //iterates through each row of all the pixels on the screen. Although we access the screens pixels as if it was stored as 2D, it is typically stored as 1D in memory. The compiler handles the index calculation automatically. You can access elements as if they're in 2D, but internally, the compiler maps them to the appropriate 1D index
        for(int x=0; x < SCREEN_WIDTH; x++){ //iterates through each column of all the pixels on the screen
            
            //Each pixel we iterate through at (x, y) is treated as the center of a 3×3 grid:
            /*
             A B C
             D X E
             F G H
             */
            
            int redTotal = 0; //resets the total (when calculating the average colour values) for every iteration of the next pixel
            int greenTotal = 0;
            int blueTotal = 0;
        
            
            for(int row=-1; row<=1; row++) { //These loops access all neighboring pixels relative to the current, central pixel (x, y), where row=-1 is the first row and col=-1 is the first column, giving the top left pixel 'A'
                for(int col=-1; col <=1; col++) {
                    int currentx = x + col; //stores x co-ord of neighbour or central pixel
                    int currenty = y + row; //stores y co-ord of neighbour or central pixel
                    
                    if((currentx >= 0 && currentx<SCREEN_WIDTH) && (currenty >=0 && currenty<SCREEN_HEIGHT)) { //If we had the screen's very top left pixel at y=0, x=0- some of its neighbouring pixels would be off the screen. So, we have to take measures for this. currentx >= 0 ensures the pixel isnt to the left of the screen, at a negative index. currentx<SCREEN_WIDTH ensures the pixel's X-coordinate is within the screen width (not beyond the right edge). currenty >=0 ensures the pixel's Y-coordinate is not above the screen (negative index). currenty < SCREEN_HEIGHT ensures the pixel's Y-coordinate is within the screen height (not below the bottom edge). && ensures both x and y conditions are true for the if statement to run
                        Uint32 colour = m_tempBuffer[currenty * SCREEN_WIDTH + currentx]; //stores the entire 32 bit colour colour value for the specific pixel. We map the row (y) to the screen's size because for memory like this, it is stored as 1D, where there is only one row. This means to access the next row, you need to "skip" over all the pixels in the previous row. Specifically, to get from row y = 0 to row y = 1, you need to jump by the number of columns (SCREEN_WIDTH) . For columns (x), no mapping is required since they are contiguous within each 'row'.
                        Uint8 red = colour >> 24; //need to right shift colour by 24 bits to get red values by itself as each pixels colour is currently RRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA, so shifting everything 24 bits to the right gives RRRRRRRR
                        Uint8 green = colour >> 16; //gives RRRRRRRRGGGGGGGG, but is packed into an 8 bit int, and green is shifted into the 8-bit space (in bit-shifting this is always on the side your shifting), we are left with GGGGGGGG
                        Uint8 blue = colour >> 8; //gives RRRRRRRRGGGGGGGGBBBBBBBB, but it is packed into an 8 bit int, and blue is shifted into the 8 bit space, leaving BBBBBBBB
                        
                        redTotal = redTotal + red;
                        greenTotal = greenTotal + green;
                        blueTotal = blueTotal + blue;
                        //for each of the neighbouring pixels being iterated through and the central one, it accumulates the red, green, and blue components of each pixel.
                        
                    }
                
                }
            }
            
            Uint8 red = redTotal/9; //can use these variable names again as they are scoped to their curly brackets
            Uint8 green = greenTotal/9;
            Uint8 blue  = blueTotal/9;
            //for each of the neighbouring pixels being iterated through and the central one, this calculates the average colour value of each colour component. This averaged color is then used to apply the blur effect to the central pixel, producing a smoother transition across the screen by blending the neighboring pixels' colours
            
            setPixel(x, y, red, green, blue);
        }
    }
        
}

void Screen::close() {
    delete [] m_buffer;
    delete [] m_tempBuffer;
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyTexture(m_texture);
    SDL_DestroyWindow(m_window); //cleans any resources window used
    SDL_Quit(); //shuts down SDL system
}

void Screen::clearScreen() {
    memset(m_buffer, 0, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));
    //sets all ements of the array m_buffer to 0, which os black, essentially clearign the screen. SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32): The total size of the buffer in bytes (width × height × size of one pixel).
    memset(m_tempBuffer, 0, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));
}



}
