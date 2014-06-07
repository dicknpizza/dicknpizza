#include <SDL/SDL.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
//outputs the highscore position -1 if the given score didn't beat any of the existing
/*
int checkHighscore(int score);



void addNewScore();

void displayCurrentScores();
*/



int makeTrans(SDL_Surface *mythingy);



class BKShighscore
{
      private:
      bool menuDone;
      SDL_Surface *myscreen;
      void DrawIMG(SDL_Surface *img, int x, int y,
      int w, int h, int x2, int y2);
      void  DrawIMG(SDL_Surface *img, int x, int y);
      public:
      BKShighscore(SDL_Surface *screen)
      {                   
                          
                          
                          myscreen = screen;
                          menuDone = false;
                          }
      void Draw();
      
      
};

class BKSmenu
{
     private:
             bool menuDone;
             SDL_Surface *myscreen;
            void DrawIMG(SDL_Surface *img, int x, int y,
                                int w, int h, int x2, int y2);
                              void  DrawIMG(SDL_Surface *img, int x, int y);
      public:
      bool killGame;
      BKSmenu(SDL_Surface *screen)
      {                   killGame = false;
                          menuDone = false;
                          myscreen = screen;
                          }
      
      bool isDone();
       void Draw();       
};


