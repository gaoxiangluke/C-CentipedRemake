/*
    Authors: Xiang Gao, Justin Lui, Mackensi Holt
    Program Title: Centipede: Star Wars Edition
    Program Descrption: Plays Centipede.
    Date Created: 4/18/2017
    Due Date: 5/1/2017
    Date Last Modified: 4/30/2017
*/

#ifndef XWING_H_INCLUDED
#define XWING_H_INCLUDED

#include "textureSet.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "collisioncheck.h"

using namespace std;

extern textureSet gxwingTexture;

class Xwing
{
public:
    //The dimensions of the xwing
    static const int Xwing_WIDTH = 30;
    static const int Xwing_HEIGHT = 30;

    //Maximum axis velocity of the xwing
    static const int Xwing_VEL = 5;

    //Initializes the variables
    Xwing();

    //Takes key presses and adjusts the xwing's velocity
    void handleEvent( SDL_Event& e );

    //Moves the dot
    void move(int screenHeight,int screenWidth);

    //Shows the dot on the screen
    void render();
    //The X and Y offsets of the dot
    int mPosX, mPosY;
    int thinkTime;

    //xwing's collision box
    SDL_Rect xwingCollider;

    //check collision between asteroid and xwing
    bool xacollison;
    int lifeCount;
    void reset();

private:
    //The velocity of the dot
    int mVelX, mVelY;
};


#endif // XWING_H_INCLUDED
