/*
    Authors: Xiang Gao, Justin Lui, Mackensi Holt
    Program Title: Centipede: Star Wars Edition
    Program Descrption: Plays Centipede.
    Date Created: 4/18/2017
    Due Date: 5/1/2017
    Date Last Modified: 4/30/2017
*/

#include "Bullet.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Xwing.h"

Bullet::Bullet()
{
    bPosX = 0;
    bPosY = 0;
    bVelY = 0;
    bulletBox.w = BULLET_WIDTH;
    bulletBox.h = BULLET_HEIGHT;
    collision = false;
}
//move bullet
void Bullet::move()
{
    //Move the dot up
    bPosY += bVelY;
    bulletBox.x = bPosX;
    bulletBox.y = bPosY;

}
//render bullet
void Bullet::render()
{
    //Show the bullet;

    gBulletTexture.render( bPosX,bPosY );



}
//initialize position of bullet
void Bullet::bulletInt(Xwing dot)
{
    bPosX = dot.mPosX + 14;
    bPosY = dot.mPosY;
}

//initialize bullet factory
BulletFactory::BulletFactory()
{

    Max_load = 13;
    for (int i = 0; i < 100; i++)
    {
        bullets[i].bExistence = false;
    }
}
//handle bullet event
void BulletFactory::handleEvent( SDL_Event& e )
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_SPACE:
            {
                shooting = true;
            }
        }
    }

    if( e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_SPACE:
            {
                shooting = false;
            }
        }
    }
}

//check bullet event existence
void BulletFactory::bulletCheck(Xwing dot)
{
    if (shooting == true)
    {
        shootingMusic.playSound("assets/blaster.wav");
        for (int i = 0; i < 100; i++)
        {
            //check bullet existence initialize bullet
            if(bullets[i].bExistence == false)
            {
                bullets[i].bExistence = true;
                bullets[i].bulletInt(dot);
                bullets[i].bVelY -= 5;
                break;
            }
        }
    }
}

void BulletFactory::bulletRendering()
{
    for (int i = 0; i < 100; i++)
    {
        if (bullets[i].bExistence == true)
        {
            bullets[i].render();
        }
    }
}

void BulletFactory::moveBullet(int screenHeight)
{
    int k = 0;
    for (int i = 0; i < 100; i++)
    {
        bullets[i].move();
        if (bullets[i].bPosY < 0 || (bullets[i].bPosY + 20 > screenHeight ) || bullets[i].collision)
        {
            bullets[i].bExistence = false;
            bullets[i].bPosY -= bullets[i].bVelY;
            bullets[i].bVelY += 5;
        }
    }
}

//get max load
int BulletFactory::getMaxLoad()
{
    int maxload;
    maxload = Max_load;
    return maxload;
}

//change max load
void BulletFactory::loadChanger(int maxBullet)
{
    Max_load = maxBullet;
}

//control the time difference of each bullet
void BulletFactory::bulletControl(Xwing &dot)
{
    dot.thinkTime--;
    if (dot.thinkTime < 0)
    {
        bulletCheck(dot);
        dot.thinkTime = getMaxLoad();
    }
}

