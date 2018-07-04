//
//  Sprite.hpp
//  Checkers
//
//  Created by Bhavish Bhattar on 6/22/18.
//  Copyright © 2018 Bhavish Bhattar. All rights reserved.
//

#ifndef Sprite_hpp
#define Sprite_hpp

#include <stdio.h>
#include<string>
#include "Graphics.h"
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
struct SDL_Rect;
struct SDL_Texture;

using namespace std;
class Sprite{
public:
    Sprite();
    Sprite(Graphics &graphics, const string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY);
    virtual ~Sprite();
    virtual void update(){};
    void draw(Graphics &graphics, int x, int y);
    
private:
    SDL_Rect _sourceRect;
    SDL_Texture* _spriteSheet;
    
    float _x,_y;

};

#endif /* Sprite_hpp */
