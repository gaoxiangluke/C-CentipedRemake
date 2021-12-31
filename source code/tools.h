/*
    Authors: Xiang Gao, Justin Lui, Mackensi Holt
    *** Part of code origniates from Dr. Booth's SDL_Plotter.h file
    Program Title: Centipede: Star Wars Edition
    Program Descrption: Plays Centipede.
    Date Created: 4/18/2017
    Due Date: 5/1/2017
    Date Last Modified: 4/30/2017
*/

#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <string.h>
#include <iostream>
#include <string>
#include <string.h>
#include <map>

using namespace std;

const char UP_ARROW    = 1;
const char DOWN_ARROW  = 2;
const char LEFT_ARROW  = 3;
const char RIGHT_ARROW = 4;
const int RED_SHIFT   = 65536;
const int GREEN_SHIFT = 256;
const int BLUE_SHIFT  = 1;
const int ALPHA_SHIFT = 16777216;
const int WHITE = 255;
const int MAX_THREAD = 100;

#define MUS_PATH "scratch.wav"

//sample threaded sound function
static int Sound(void *data);

struct param
{
    bool play;
    bool running;
    bool pause;
    SDL_Thread*  threadID;
    SDL_cond *cond;
    SDL_mutex *mut;
    string name;

    param()
    {
        play = false;
        running = false;
        pause = false;
    }
};

class SDL_tools
{
private:

    bool leftMouseButtonDown;
    Uint32 * pixels;
    const Uint8* currentKeyStates;

    int row, col;
    bool quit;
    SDL_Event event;

    //Sound Stuff
    bool SOUND;
    int soundCount;
    map<string, param> soundMap;

public:
    SDL_tools()
    {
        leftMouseButtonDown = false;
        quit = false;
        SOUND = true;

        SDL_Init(SDL_INIT_AUDIO);

        pixels   = new Uint32[col * row];

        memset(pixels, WHITE, col * row * sizeof(Uint32));

        //SOUND Thread Pool
        Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
        soundCount = 0;
    }

    ~SDL_tools()
    {
        delete[] pixels;
        SDL_Quit();
    }

    bool getQuit()
    {
        return quit;
    }

    bool kbhit()
    {
        bool flag = false;
        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_KEYDOWN)
            {
                flag = true;
            }
            if( event.type == SDL_QUIT )
            {
                quit = true;
            }
        }
        return flag;
    }

    char getKey()
    {
        char key = '\0';

        currentKeyStates = SDL_GetKeyboardState( NULL );
        if(currentKeyStates[SDL_SCANCODE_A]) key = 'A';
        if(currentKeyStates[SDL_SCANCODE_B]) key = 'B';
        if(currentKeyStates[SDL_SCANCODE_C]) key = 'C';
        if(currentKeyStates[SDL_SCANCODE_D]) key = 'D';
        if(currentKeyStates[SDL_SCANCODE_E]) key = 'E';
        if(currentKeyStates[SDL_SCANCODE_F]) key = 'F';
        if(currentKeyStates[SDL_SCANCODE_G]) key = 'G';
        if(currentKeyStates[SDL_SCANCODE_H]) key = 'H';
        if(currentKeyStates[SDL_SCANCODE_I]) key = 'I';
        if(currentKeyStates[SDL_SCANCODE_J]) key = 'J';
        if(currentKeyStates[SDL_SCANCODE_K]) key = 'K';
        if(currentKeyStates[SDL_SCANCODE_L]) key = 'L';
        if(currentKeyStates[SDL_SCANCODE_M]) key = 'M';
        if(currentKeyStates[SDL_SCANCODE_N]) key = 'N';
        if(currentKeyStates[SDL_SCANCODE_O]) key = 'O';
        if(currentKeyStates[SDL_SCANCODE_P]) key = 'P';
        if(currentKeyStates[SDL_SCANCODE_Q]) key = 'Q';
        if(currentKeyStates[SDL_SCANCODE_R]) key = 'R';
        if(currentKeyStates[SDL_SCANCODE_S]) key = 'S';
        if(currentKeyStates[SDL_SCANCODE_T]) key = 'T';
        if(currentKeyStates[SDL_SCANCODE_U]) key = 'U';
        if(currentKeyStates[SDL_SCANCODE_V]) key = 'V';
        if(currentKeyStates[SDL_SCANCODE_W]) key = 'W';
        if(currentKeyStates[SDL_SCANCODE_X]) key = 'X';
        if(currentKeyStates[SDL_SCANCODE_Y]) key = 'Y';
        if(currentKeyStates[SDL_SCANCODE_Z]) key = 'Z';
        if(currentKeyStates[SDL_SCANCODE_1]) key = '1';
        if(currentKeyStates[SDL_SCANCODE_2]) key = '2';
        if(currentKeyStates[SDL_SCANCODE_3]) key = '3';
        if(currentKeyStates[SDL_SCANCODE_4]) key = '4';
        if(currentKeyStates[SDL_SCANCODE_5]) key = '5';
        if(currentKeyStates[SDL_SCANCODE_6]) key = '6';
        if(currentKeyStates[SDL_SCANCODE_7]) key = '7';
        if(currentKeyStates[SDL_SCANCODE_8]) key = '8';
        if(currentKeyStates[SDL_SCANCODE_9]) key = '9';
        if(currentKeyStates[SDL_SCANCODE_0]) key = '0';
        if(currentKeyStates[SDL_SCANCODE_SPACE]) key = ' ';
        if(currentKeyStates[SDL_SCANCODE_DOWN])  key = DOWN_ARROW;
        if(currentKeyStates[SDL_SCANCODE_UP])    key = UP_ARROW;
        if(currentKeyStates[SDL_SCANCODE_LEFT])  key = LEFT_ARROW;
        if(currentKeyStates[SDL_SCANCODE_RIGHT]) key = RIGHT_ARROW;
        if(currentKeyStates[SDL_SCANCODE_RETURN]) key = SDL_SCANCODE_RETURN;
        if(currentKeyStates[SDL_SCANCODE_ESCAPE]) quit = true;

        return key;
    }

    void plotPixel(int x, int y, int r, int g, int b)
    {
        pixels[y * col + x] = RED_SHIFT*r + GREEN_SHIFT*g + BLUE_SHIFT*b;
    }

    void clear()
    {
        memset(pixels, WHITE, col * row * sizeof(Uint32));
    }
    void setcol(int c)
    {
        col = c;
    }
    void setrow(int r)
    {
        row = r;
    }
    int getRow()
    {
        return row;
    }

    int getCol()
    {
        return col;
    }

    void initSound(string sound)
    {
        //int  *threadReturnValue;

        if(!soundMap[sound].running)
        {
            param* p = &soundMap[sound];
            p->name = sound;
            p->cond = SDL_CreateCond();
            p->mut = SDL_CreateMutex();

            p->threadID = SDL_CreateThread( Sound, sound.c_str(), (void*)p );
            //p->threadID = SDL_CreateThread( Sound, "SoundThread", (void*)p );
            //SDL_DetachThread(p->threadID);
        }
    }

    void setQuit(bool flag)
    {
        this->quit = flag;
    }

    void playSound(string sound)
    {
        if(soundMap[sound].running)
        {
            SDL_CondSignal(soundMap[sound].cond);
        }
    }

    void quitSound(string sound)
    {
        soundMap[sound].running = false;
        SDL_CondSignal(soundMap[sound].cond);
    }

    void Sleep(int ms)
    {
        SDL_Delay(ms);
    }

};

//Threaded Function

static int Sound(void *data)
{
    param *p = (param*)data;
    p -> running = true;
    Mix_Chunk *gScratch = NULL;
    gScratch = Mix_LoadWAV( p -> name.c_str() );


    while(p -> running)
    {
        SDL_mutexP( p -> mut );
        SDL_CondWait(p -> cond, p -> mut);
        Mix_PlayChannel( -1, gScratch, 0 );
        p -> play = false;
        SDL_mutexV(p -> mut);
    }

    Mix_FreeChunk( gScratch );
    p -> running = false;
    return 0;
}


#endif // TOOLS_H_INCLUDED
