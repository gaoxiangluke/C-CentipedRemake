/*
    Authors: Xiang Gao, Justin Lui, Mackensi Holt
    Program Title: Centipede: Star Wars Edition
    Program Descrption: Plays Centipede.
    Date Created: 4/18/2017
    Due Date: 5/1/2017
    Date Last Modified: 4/30/2017
*/

#ifndef STAR_H_INCLUDED
#define STAR_H_INCLUDED
#include "textureSet.h"
#include <cstdlib>
#include "grid.h"

using namespace std;

extern textureSet starDestroyer;

//class for star destroyer
class Star
{
private:
    static const int Star_Width = 30;
    static const int Star_Height = 30;
    int sVelY;
public:
    int sPosX;
    int sPosY;
    bool existence;
    Star();
    void setStar(bool spawnStar, GridFactory gridMushroom);
    void render();
    void moveStar(int height);
    SDL_Rect starBox;
};


#endif // STAR_H_INCLUDED
