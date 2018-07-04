/*Graphics class that
holds all info dealing with Graphics
*/
#include<iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Graphics.h"

Graphics::Graphics(){
  SDL_CreateWindowAndRenderer(640,600,0,&this->_window, &this->_renderer);
  SDL_SetWindowTitle(this->_window, "Checkers");
}

void Graphics::createRenderer(){
    SDL_CreateWindowAndRenderer(640,600,0,&this->_window, &this->_renderer);
}
void Graphics::setWindow(){
     SDL_SetWindowTitle(this->_window, "Checkers");
}

Graphics::~Graphics(){
  SDL_DestroyWindow(this->_window);
}

SDL_Surface* Graphics::loadImage(const string &filePath){
    if (this-> _spriteSheet.count(filePath) == 0){
        this->_spriteSheet[filePath] = IMG_Load(filePath.c_str());
        cout<<(_spriteSheet[filePath]);
    }
    return this->_spriteSheet[filePath];
}

void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle){
    SDL_RenderCopy(this->_renderer, texture, sourceRectangle, destinationRectangle);
}

void Graphics::flip()
{ SDL_RenderPresent(this->_renderer);
}

void Graphics::clear(){
    SDL_RenderClear(this->_renderer);
}

SDL_Renderer* Graphics::getRenderer() const {
    return this->_renderer;
}

