#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <map>
#include <string>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>


struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;

using namespace std;

class Graphics {
public:
  Graphics();
  ~Graphics();
    
    /* SDL_Sufrace
     Loads an image into the map if it doesnt alread exist
     Thus each image will be only oaded once, and returns the image from the map.
     */
    SDL_Surface * loadImage(const string &filePath);
    
    /*draws texture to screen*/
    void blitSurface(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);
    
    /*renders everything to the screen */
    void flip();
    
    /*clears the screen*/
    void clear();
    
    /*returns the renderer*/
    SDL_Renderer* getRenderer() const;
    
    void createRenderer();
    void setWindow();

private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    
    std::map<string, SDL_Surface*> _spriteSheet;
    
    

};

#endif
