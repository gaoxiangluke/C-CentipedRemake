/*
    Authors: Xiang Gao, Justin Lui, Mackensi Holt
    Program Title: Centipede: Star Wars Edition
    Program Descrption: Plays Centipede.
    Date Created: 4/18/2017
    Due Date: 5/1/2017
    Date Last Modified: 4/30/2017
*/

#ifndef SEGMENT_H_INCLUDED
#define SEGMENT_H_INCLUDED

#include "textureSet.h"
#include <string>
#include "collisioncheck.h"
#include <iostream>

extern textureSet segmentText;
extern textureSet headText;

class Segment
{
private:

    //velocity of segment
    int SvelX;

public:
    //set move direction
    char moveDirection;
    //position of segment
    int sPosX;
    int sPosY;
    //segment height and
    static const int Segment_Height = 30;
    static const int Segment_Width = 30 ;
    Segment();
    //mark the segment as head if true
    bool IsHead;
    //mark the segment as connect if true
    bool IsConnectf;
    bool IsConnectb;
    bool IsCreated;
    void move(int screenHeight, int screenWidth);
    void render();
    void setp(int x, int y);
    void setv(int x);
    SDL_Rect segmentBox;
    bool collsiona;
    bool bccollision;
};

//combine segment to a centipede
class Centipede
{
private:
public:
    Segment parts[50];
    Centipede();
    void renderAll();
    void moveAll(int h,int w);
    void velocityCheck();
    //check if addition  head are created
    int headcount;
    void reset(int levelNum);
    void collisionbc(int i);
    void setHead(int levelNum);

};


#endif // SEGMENT_H_INCLUDED
