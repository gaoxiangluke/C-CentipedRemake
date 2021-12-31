/*
    Authors: Xiang Gao, Justin Lui, Mackensi Holt
    Program Title: Centipede: Star Wars Edition
    Program Descrption: Plays Centipede.
    Date Created: 4/18/2017
    Due Date: 5/1/2017
    Date Last Modified: 4/30/2017
*/

#include "text.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;
Text::Text()
{
    tPosX = 200;
    tPosY = 240;
    retryTime = 0;
}
//type enter to enter next step of the game
void Text::handleEvent(SDL_Event& e,int& step,string& specialCode,bool &special)
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //change rendering step
        switch( e.key.keysym.sym )
        {
        case SDLK_SPACE:
        {
            if (step == 1)
            {
                step++;
            }
            else if (step == 4)
            {
                step = 1;
            }
            else if (step == 3 && special == false)
            {
                step = 1;
                retryTime++;
                if(retryTime >= -1)
                {
                    special = true;
                }
                specialCode = "0";
            }
            else if(step == 3 && special == true)
            {
                step++;
                specialCode = "0";
            }
            break;
        }

        //add  to special code
        case SDLK_UP:
            specialCode += "1";
            break;
        case SDLK_DOWN:
            specialCode += "2";
            break;
        case SDLK_LEFT:
            specialCode += "3";
            break;
        case SDLK_RIGHT:
            specialCode += "4";
            break;
        case SDLK_a:
            specialCode += "a";
            break;
        case SDLK_b:
            specialCode += "b";
            break;
        case SDLK_p:
            specialCode += "p";
            break;
        case SDLK_f:
            specialCode += "f";
            break;
        case SDLK_i:
            specialCode += "i";
            break;
        case SDLK_m:
            specialCode += "m";
            break;
        case SDLK_w:
            specialCode += "w";
            break;
        case SDLK_y:
            specialCode += "y";
            break;
        case SDLK_n:
            specialCode += "n";
            break;
        }
    }
}

//rendering Text
void Text::renderText(int step)
{
    if(step == 1)
    {
        startScreenText.render(tPosX, tPosY);
    }
    else if(step == 3)
    {
        gameOver.render(0,0);
    }
    else if (step == 2)
    {
        lifeRemaining.render(500,0);
        levelCount.render(250,0);
        pointCount.render(50,0);
    }
    else if(step == 4)
    {
        modeSelect.render(0,0);
    }
}

void Text::changePosition(int step)
{
    if (step == 1)
    {
        tPosX = 0;
        tPosY = 0;
    }
}

//print the remaining life on screen
void Text::setInfo(int lifeCounter, int level, int point)
{
    stringstream lifeText;
    SDL_Color textColor = { 255, 255, 255 };
    lifeText.str( "" );
    lifeText<< "Life " << lifeCounter;

    if( !lifeRemaining.loadFromRenderedText( lifeText.str().c_str(), textColor ) )
    {
        printf( "Failed to render text texture!\n" );
    }

    stringstream levelText;
    levelText.str("");
    levelText<<" Level "<< level;
    if( !levelCount.loadFromRenderedText( levelText.str().c_str(), textColor ) )
    {
        printf( "Failed to render text texture!\n" );
    }

    stringstream pointText;
    pointText.str("");
    pointText<<" Point "<<point;
    if( !pointCount.loadFromRenderedText( pointText.str().c_str(), textColor ) )
    {
        printf( "Failed to render text texture!\n" );
    }
}
