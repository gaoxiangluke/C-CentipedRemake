/*
    Authors: Xiang Gao, Justin Lui, Mackensi Holt
    Program Title: Centipede: Star Wars Edition
    Program Descrption: Plays Centipede.
    Date Created: 4/18/2017
    Due Date: 5/1/2017
    Date Last Modified: 4/30/2017
*/

#ifndef ASTEROID_H_INCLUDED
#define ASTEROID_H_INCLUDED

#include "textureSet.h"
#include <cstdlib>  //needed to use rand
#include <ctime>    //needed to use time
#include <iostream>
#include "collisioncheck.h"
#include "grid.h"
using namespace std;

extern textureSet asteroid1;
extern textureSet asteroid2;
extern textureSet asteroid3;
extern textureSet asteroid4;

//class for asteroid
class Asteroid
{
private:
    static const int asteroid_WIDTH = 30;
    static const int asteroid_HEIGHT = 30;
public:
    bool collisionOther;

    Asteroid();
    int APosX;
    int APosY;
    void setPos(GridFactory& gridMushroom);
    void render();
    SDL_Rect asteroidBox;
    int gridNumber;
    int lifeCounter;
    int x;
    int y;
    bool existence;
};
//a class for all Asteroid
class AsteroidFactory
{
private:
public:
    Asteroid asteroids[100];
    AsteroidFactory();
    void renderAll();
    void setPosAll(GridFactory& gridMushroom);
    void createAsteroid(int x,int y,GridFactory& gridMushroom);
    bool checkAsteroid(int levelNum);
};

#endif // ASTEROID_H_INCLUDED
