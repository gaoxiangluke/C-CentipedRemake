/*
    Authors: Xiang Gao, Justin Lui, Mackensi Holt
    Program Title: Centipede: Star Wars Edition
    Program Descrption: Plays Centipede.
    Date Created: 4/18/2017
    Due Date: 5/1/2017
    Date Last Modified: 4/30/2017
*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "object.h"
#include "initialization.h"
#include "Asteroid.h"
using namespace std;
//Screen dimension constants
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 690;

//The window we'll be rendering to
SDL_Window* gWindow ;
//font
TTF_Font *gFont;
//The window renderer
SDL_Renderer* gRenderer;
//Texture
textureSet gxwingTexture;
textureSet gBulletTexture;
textureSet segmentText;
textureSet headText;
textureSet startScreenText;
textureSet asteroid1;
textureSet asteroid2;
textureSet asteroid3;
textureSet asteroid4;
textureSet gameOver;
textureSet lifeRemaining;
textureSet levelCount;
textureSet pointCount;
textureSet starDestroyer;
textureSet gFettTexture;
textureSet modeSelect;
SDL_tools backgroundMusic;
SDL_tools shootingMusic;
SDL_tools explosion;
SDL_tools death;
int main( int argc, char* args[] )
{

    //Start up SDL and create window
    if( !init(SCREEN_HEIGHT,SCREEN_WIDTH) )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //The dot that will be moving around on the screen
            Object object_in_game;
            //While application is running
            while( !quit )
            {

                object_in_game.musicPlayer();
                eventHandler(quit,object_in_game,e);
                object_in_game.setup();

                //move object
                object_in_game.objectMovement(SCREEN_HEIGHT,SCREEN_WIDTH);

                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0);
                SDL_RenderClear( gRenderer );

                //rendering object
                object_in_game.objectRendering();

                //Update screen
                SDL_RenderPresent( gRenderer );
            }
        }
        //Free resources and close SDL
        close();

        return 0;
    }
}
