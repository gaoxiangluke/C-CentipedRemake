/*
    Authors: Xiang Gao, Justin Lui, Mackensi Holt
    Program Title: Centipede: Star Wars Edition
    Program Descrption: Plays Centipede.
    Date Created: 4/18/2017
    Due Date: 5/1/2017
    Date Last Modified: 4/30/2017
*/

#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Xwing.h"
#include "segment.h"

extern SDL_tools shootingMusic;
extern textureSet gBulletTexture;

class Bullet
{
private:
    //bullet width, height
    static const int BULLET_WIDTH = 10;
    static const int BULLET_HEIGHT = 30;
public:
    Bullet();
    int bPosX;
    int bPosY;
    bool bExistence;
    void move();
    void bulletInt(Xwing dot);
    int bVelY;
    void render();
    SDL_Rect bulletBox;
    //check collision between bullet and asteroid
    bool collision;

};
class BulletFactory
{
private:
    int Max_load;

public:
    Bullet bullets[100];
    BulletFactory();
    void bulletCheck(Xwing dot);
    void handleEvent(SDL_Event& e);
    void bulletRendering();
    void moveBullet(int screenHeight);
    bool shooting=false;
    int getMaxLoad();
    void loadChanger(int maxBullet);
    void bulletControl(Xwing& dot);

};

#endif // BULLET_H_INCLUDED
