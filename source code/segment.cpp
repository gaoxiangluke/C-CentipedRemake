/*
    Authors: Xiang Gao, Justin Lui, Mackensi Holt
    Program Title: Centipede: Star Wars Edition
    Program Descrption: Plays Centipede.
    Date Created: 4/18/2017
    Due Date: 5/1/2017
    Date Last Modified: 4/30/2017
*/

#include "segment.h"
#include "textureSet.h"
#include <string>

Segment::Segment()
{
    SvelX = 5;
    sPosX = 0;
    sPosY = 30;
    IsHead = false;
    IsConnectf = true;
    IsConnectb = true;
    IsCreated = false;
    moveDirection = 'r';
    segmentBox.w = Segment_Width;
    segmentBox.h = Segment_Height;
    collsiona = false;
    bccollision = false;
}
void Segment::move(int screenHeight, int screenWidth)
{


    if ((sPosX < 0) || ( sPosX + Segment_Width > screenWidth) || collsiona)
    {

        //change direction
        if(moveDirection == 'r')
        {
            if(collsiona && sPosX>30)
            {
                sPosX -= 30;
            }
            moveDirection = 'l';


        }
        else if (moveDirection == 'l')
        {

            if(collsiona && sPosX + Segment_Width < screenWidth - 30)
            {
                sPosX += 30;
            }
            moveDirection = 'r';

        }
        sPosY += Segment_Height;
    }

    if(moveDirection == 'r')
    {
        sPosX += SvelX;
        segmentBox.x = sPosX;
        segmentBox.y = sPosY;
    }
    else if (moveDirection == 'l')
    {
        sPosX -= SvelX;
        segmentBox.x = sPosX;
        segmentBox.y = sPosY;
    }
    if(sPosY + Segment_Height > screenHeight)
    {
        sPosY -= 4 * Segment_Height;
    }

}

void Segment::render()
{
    if(IsCreated == true)
    {
        if (IsHead == true)
        {
            headText.render(sPosX, sPosY);
        }
        else
        {
            segmentText.render(sPosX, sPosY);
        }
    }
}

void Segment::setp(int x, int y)
{
    sPosX = x;
    sPosY = y;
    segmentBox.x = sPosX;
    segmentBox.y = sPosY;
}

void Segment::setv(int x)
{
    SvelX = x;
}

Centipede::Centipede()
{
    headcount = 12;
    parts[11].IsHead = true;
    parts[0].IsConnectb = false;
    parts[11].IsConnectf = false;

    for (int i = 0; i < 12; i++)
    {
        parts[i].IsCreated = true;
        parts[i].setp(i*parts[i].Segment_Width, 30);
    }
}

void Centipede::moveAll(int h, int w)
{
    for (int i = 0; i < 12; i++)
    {
        if (parts[i].IsCreated == true)
        {
            parts[i].move(h, w);
        }

    }
}

void Centipede::renderAll()
{
    for (int i = 0; i < 12; i++)
    {
        if (parts[i].IsCreated == true)
        {
            parts[i].render();
        }
    }
}

void Centipede::velocityCheck()
{
    for (int i = 0; i < 12; i++)
    {
        if(parts[i].IsConnectf == false && parts[i].IsConnectb == false)
        {
            parts[i].setv(4);
        }
        else
        {
            parts[i].setv(3);
        }
    }
}

void Centipede::reset(int levelNum)
{
    headcount = 12;
    for (int i = 0; i < 12; i++)
    {
        parts[i].IsCreated = true;
        parts[i].setp(i*parts[i].Segment_Width, 30);
        parts[i].IsHead = false;
        parts[i].IsConnectf = true;
        parts[i].IsConnectb = true;
        parts[i].moveDirection = 'r';
        parts[i].collsiona = false;
    }
    setHead(levelNum);
    parts[0].IsConnectb = false;
}

//check the collision between bullet and centipede
void Centipede::collisionbc(int i)
{
    if (i != 0)
    {
        if (parts[i].bccollision == true)
        {
            parts[i-1].IsHead = true;
            parts[i+1].IsConnectb = false;
            parts[i-1].IsConnectf = false;
        }
    }

}

//rest head of centipede depends on level NUMBER
void Centipede::setHead(int levelNum)
{
    for(int k = 1; k <= levelNum; k++)
    {
        parts[12-k].IsHead = true;
        parts[12-k].IsConnectf = false;
        parts[12-(k-1)].IsConnectb = false;
    }
}

