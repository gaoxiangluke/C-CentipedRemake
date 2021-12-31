/*
    Authors: Xiang Gao, Justin Lui, Mackensi Holt
    *** Part of code originates from Lazy Foo' Productions Tutorial
    Program Title: Centipede: Star Wars Edition
    Program Descrption: Plays Centipede.
    Date Created: 4/18/2017
    Due Date: 5/1/2017
    Date Last Modified: 4/30/2017
*/

#ifndef INITIALIZATION_H_INCLUDED
#define INITIALIZATION_H_INCLUDED

#include "object.h"

//initialize SDL
bool init(int screenHeight, int screenWidth);

//load media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//handle event
void eventHandler(bool& quit, Object& x, SDL_Event& e);

#endif // INITIALIZATION_H_INCLUDED
