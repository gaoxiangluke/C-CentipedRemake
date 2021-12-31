/*
    Authors: Xiang Gao, Justin Lui, Mackensi Holt
    Program Title: Centipede: Star Wars Edition
    Program Descrption: Plays Centipede.
    Date Created: 4/18/2017
    Due Date: 5/1/2017
    Date Last Modified: 4/30/2017
*/

#include "fett.h"

Fett::Fett()
{
    mPosX = 0;
    mPosY = 480;

    //Initialize the velocity
    fettBox.h = FETT_HEIGHT;
    fettBox.w = FETT_WIDTH;
    fettBox.x = mPosX;
    fettBox.y = mPosY;
    mVelX = 5;
    mVelY = 5;
    straight = false;
    bounce = 0;
    existence = true;
}

void Fett::move()
{
    if(existence == true)
    {
        //Move the boba fett left or right
        mPosX += mVelX;
        fettBox.x = mPosX;

        //If the boba fett went too far to the left or right
        if( ( mPosX < 0 ) || ( mPosX + FETT_WIDTH > 600 ) )
        {
            //Move back
            mVelX *= -1;
        }


        //Move the boba fett up or down
        mPosY += mVelY;
        fettBox.y = mPosY;

        if(straight == false)
        {
            if(bounce % 100 == 0)
            {
                mVelY *= -1;
            }
            bounce++;
        }

    }

    //If the boba fett went too far up or down
    if( ( mPosY < 480 ) || ( mPosY + FETT_HEIGHT > 690 ) )
    {
        //Move back
        mVelY *= -1;
    }
}

void Fett::changeDirection()
{
    if(existence == true)
    {
        if(straight)
        {
            mVelX = 0;
            straight = false;
        }
        else
        {
            mVelX = 5;
            straight = true;
        }
    }
}

void Fett::render()
{
    if(existence == true)
    {
        //Show the boba fett
        gFettTexture.render( mPosX, mPosY );
    }
}

void Fett::resetFett()
{
    mPosX = 0;
    mPosY = 480;
    fettBox.x = mPosX;
    fettBox.y = mPosY;
    straight = false;
    bounce = 0;
    existence = true;
    mVelX = 5;
    mVelY = 5;
}
