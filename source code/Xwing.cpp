/*
    Authors: Xiang Gao, Justin Lui, Mackensi Holt
    Program Title: Centipede: Star Wars Edition
    Program Descrption: Plays Centipede.
    Date Created: 4/18/2017
    Due Date: 5/1/2017
    Date Last Modified: 4/30/2017
*/

#include "Xwing.h"
#include "textureSet.h"

Xwing::Xwing()
{
    //Initialize the offsets
    mPosX = 300;
    mPosY = 630;
    thinkTime = 0;
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
    //set x-wing collision coordinate
    xwingCollider.h = Xwing_HEIGHT;
    xwingCollider.w = Xwing_WIDTH;
    xwingCollider.x = mPosX;
    xwingCollider.y = mPosY;
    xacollison = false;
    lifeCount = 3;
}

void Xwing::handleEvent( SDL_Event& e )
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
        case SDLK_UP:
            mVelY -= Xwing_VEL;
            break;
        case SDLK_DOWN:
            mVelY += Xwing_VEL ;
            break;
        case SDLK_LEFT:
            mVelX -= Xwing_VEL ;
            break;
        case SDLK_RIGHT:
            mVelX += Xwing_VEL ;
            break;
        }
    }

    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
        case SDLK_UP:
            mVelY += Xwing_VEL;
            break;
        case SDLK_DOWN:
            mVelY -= Xwing_VEL;
            break;
        case SDLK_LEFT:
            mVelX += Xwing_VEL;
            break;
        case SDLK_RIGHT:
            mVelX -= Xwing_VEL;
            break;
        }
    }
}

void Xwing::move(int screenHeight,int screenWidth)
{
    //Move the xwing left or right
    mPosX += mVelX;
    xwingCollider.x=mPosX;

    //If the xwing went too far to the left or right
    if(( mPosX < 0 ) || ( mPosX + Xwing_WIDTH > screenWidth )||(xacollison))
    {
        //Move back
        mPosX -= mVelX;
    }

    //Move the xwing up or down
    mPosY += mVelY;
    xwingCollider.y = mPosY;
    //If the xwing went too far up or down
    if( (mPosY < 480) || ( mPosY + Xwing_HEIGHT > screenHeight ) ||(xacollison))
    {
        //Move back
        mPosY -= mVelY;
    }
}

void Xwing::render()
{
    if(lifeCount > 0)
    {
        //Show the x-wing
        gxwingTexture.render( mPosX, mPosY );
    }
}

//reset x-wing
void Xwing::reset()
{
    //Initialize the offsets
    mPosX = 300;
    mPosY = 630;
    thinkTime = 0;
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
    //set x-wing collision coordinate
    xwingCollider.h = Xwing_HEIGHT;
    xwingCollider.w = Xwing_WIDTH;
    xwingCollider.x = mPosX;
    xwingCollider.y = mPosY;
    xacollison = false;
    lifeCount = 3;
}
