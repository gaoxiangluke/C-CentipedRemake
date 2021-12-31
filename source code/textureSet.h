#ifndef TEXTURESET_H_INCLUDED
#define TEXTURESET_H_INCLUDED

/*
    Authors: Xiang Gao, Justin Lui, Mackensi Holt
    Program Title: Centipede: Star Wars Edition
    Program Descrption: Plays Centipede.
    Date Created: 4/18/2017
    Due Date: 5/1/2017
    Date Last Modified: 4/30/2017
*/

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL_ttf.h>
#include <sstream>
#include "tools.h"

//The window we'll be rendering to
extern SDL_Window* gWindow ;

//The window renderer
extern SDL_Renderer* gRenderer;

class textureSet
{
public:
    //Initializes variables
    textureSet();

    //Deallocates memory
    ~textureSet();

    //Loads image at specified path
    bool loadFromFile( std::string path );


    //Creates image from font string
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor );


    //Deallocates texture
    void free();

    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    //Set blending
    void setBlendMode( SDL_BlendMode blending );

    //Set alpha modulation
    void setAlpha( Uint8 alpha );

    //Renders texture at given point
    void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

    //Gets image dimensions
    int getWidth();
    int getHeight();

private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
};



#endif // TEXTURESET_H_INCLUDED
