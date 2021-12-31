/*
    Authors: Xiang Gao, Justin Lui, Mackensi Holt
    Program Title: Centipede: Star Wars Edition
    Program Descrption: Plays Centipede.
    Date Created: 4/18/2017
    Due Date: 5/1/2017
    Date Last Modified: 4/30/2017
*/

#ifndef FETT_H_INCLUDED
#define FETT_H_INCLUDED
#include "textureSet.h"
#include <cstdlib>  //needed to use rand

using namespace std;

extern textureSet gFettTexture;

//The fett that will move around on the screen
class Fett
{
public:
    //The dimensions of the fett
    static const int FETT_WIDTH = 30;
    static const int FETT_HEIGHT = 30;

    //Maximum axis velocity of the fett
    static const int FETT_VEL = 5;

    //Initializes the variables
    Fett();

    //Moves the fett
    void move();

    //Change Direction of the fett
    void changeDirection();

    //Shows the fett on the screen
    void render();
    bool straight;
    int bounce;

    //existence of fett
    bool existence;

    //fett collision check
    SDL_Rect fettBox;

    //RESET
    void resetFett();

private:
    //The X and Y offsets of the fett
    int mPosX, mPosY;

    //The velocity of the fett
    int mVelX, mVelY;
};


#endif // FETT_H_INCLUDED
