/*
    Authors: Xiang Gao, Justin Lui, Mackensi Holt
    *** Part of this code originates from Lazy Foo' Productions Tutorials
    Program Title: Centipede: Star Wars Edition
    Program Descrption: Plays Centipede.
    Date Created: 4/18/2017
    Due Date: 5/1/2017
    Date Last Modified: 4/30/2017
*/

#include "textureSet.h"
#include "initialization.h"
#include "object.h"
#include <SDL_ttf.h>
#include <sstream>

//The window we'll be rendering to textureSet
extern SDL_Window* gWindow ;
//The window renderer
extern SDL_Renderer* gRenderer;
//font
extern TTF_Font *gFont;
//Texture
extern textureSet gDotTexture;
extern textureSet gBulletTexture;
extern textureSet segmentText;
extern textureSet headText;
extern textureSet startScreenText;
extern textureSet asteroid1;
extern textureSet asteroid2;
extern textureSet asteroid3;
extern textureSet asteroid4;
extern textureSet gameOver;
extern stringstream lifeText;
extern textureSet lifeRemaining;
extern textureSet starDestroyer;
extern textureSet gFettTexture;
extern SDL_tools backgroundMusic;
extern SDL_tools shootingMusic;
extern SDL_tools explosion;
extern SDL_tools death;
extern textureSet modeSelect;

bool init(int screenHeight,int screenWidth)
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create window
        gWindow = SDL_CreateWindow( "Centipede:Star Wars Edition", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create vsynced renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }
            }
        }
    }

    return success;
}
//load media
bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load dot texture
    if( !gxwingTexture.loadFromFile( "assets/xwing.bmp" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !gBulletTexture.loadFromFile( "assets/bullet.bmp" ) )
    {
        printf( "Failed to load bullet texture!\n" );
        success = false;
    }
    if( !segmentText.loadFromFile( "assets/segment.bmp" ) )
    {
        printf( "Failed to load segment texture!\n" );
        success = false;
    }
    if( !headText.loadFromFile( "assets/head.bmp" ) )
    {
        printf( "Failed to load head texture!\n" );
        success = false;
    }
    if( !asteroid1.loadFromFile( "assets/asteroid1.bmp" ) )
    {
        printf( "Failed to load asteroid texture!\n" );
        success = false;
    }
    if( !asteroid2.loadFromFile( "assets/asteroid2.bmp" ) )
    {
        printf( "Failed to load asteroid texture!\n" );
        success = false;
    }
    if( !asteroid3.loadFromFile( "assets/asteroid3.bmp" ) )
    {
        printf( "Failed to load asteroid texture!\n" );
        success = false;
    }
    if( !asteroid4.loadFromFile( "assets/asteroid4.bmp" ) )
    {
        printf( "Failed to load asteroid texture!\n" );
        success = false;
    }
    if( !starDestroyer.loadFromFile( "assets/star.bmp" ) )
    {
        printf( "Failed to load starDestroyer texture!\n" );
        success = false;
    }
    if( !gameOver.loadFromFile( "assets/gameOver.bmp" ) )
    {
        printf( "Failed to render text texture!\n" );
        success = false;
    }
    if( !gFettTexture.loadFromFile( "assets/Boba.bmp" ) )
    {
        printf( "Failed to load fett texture!\n" );
        success = false;
    }
    if( !startScreenText.loadFromFile("assets/gametitle.bmp") )
    {
        printf( "Failed to render text texture!\n" );
        success = false;
    }
    if( !modeSelect.loadFromFile("assets/specialCode.bmp") )
    {
        printf( "Failed to render text texture!\n" );
        success = false;
    }
    gFont = TTF_OpenFont( "assets/lazy.ttf", 14 );
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }

    backgroundMusic.initSound("assets/background.wav");
    shootingMusic.initSound("assets/blaster.wav");
    explosion.initSound("assets/explosion.wav");
    death.initSound("assets/death.wav");
    return success;
}
void close()
{
    //Free loaded images
    gxwingTexture.free();
    gBulletTexture.free();
    segmentText;
    headText.free();
    startScreenText.free();
    asteroid1.free();
    asteroid2.free();
    asteroid3.free();
    asteroid4.free();
    gameOver.free();
    starDestroyer.free();
    gFettTexture.free();
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
void eventHandler(bool& quit,Object& x,SDL_Event& e)
{
    //Handle events on queue
    while( SDL_PollEvent( &e ) != 0 )
    {
        //User requests quit
        if( e.type == SDL_QUIT )
        {
            quit = true;
        }

        x.objectEvent(e);
    }
}
