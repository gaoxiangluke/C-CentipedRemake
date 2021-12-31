/*
    Authors: Xiang Gao, Justin Lui, Mackensi Holt
    Program Title: Centipede: Star Wars Edition
    Program Descrption: Plays Centipede.
    Date Created: 4/18/2017
    Due Date: 5/1/2017
    Date Last Modified: 4/30/2017
*/

#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED
#include "textureSet.h"
#include <string>

using namespace std;

//class for start screen text
extern textureSet startScreenText;
extern textureSet gameOver;
extern textureSet lifeRemaining;
extern textureSet levelCount;
extern textureSet pointCount;
extern textureSet modeSelect;
class Text
{
private:
    int tPosX;
    int tPosY;
public:
    Text();
    void handleEvent(SDL_Event& e,int& step, string& specialCode, bool& special);
    void renderText(int step);
    void changePosition(int step);
    void setInfo(int lifeCounter,int level,int point);
    //count number of retries
    int retryTime;
};


#endif // TEXT_H_INCLUDED
