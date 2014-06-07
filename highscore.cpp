#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <windows.h>
#include <time.h>

#include <string>
#include <string.h>
#include <fstream>
#include <sstream>
#include <SDL/SDL_Mixer.h>
#include "font.h"
#include "highscore.h"






void BKShighscore::DrawIMG(SDL_Surface *img, int x, int y,
                                int w, int h, int x2, int y2)
{
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  SDL_Rect dest2;
  dest2.x = x2;
  dest2.y = y2;
  dest2.w = w;
  dest2.h = h;
  SDL_BlitSurface(img, &dest2, myscreen, &dest);
}

void BKShighscore::DrawIMG(SDL_Surface *img, int x, int y)
{
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  SDL_BlitSurface(img, NULL, myscreen, &dest);
}

void BKShighscore::Draw()
{
     SDL_Surface *mbg = SDL_LoadBMP("data\\highscorelist.bmp");
     
     
     SDL_Event event2;
     int selected = 0;
     int mdone = 0;
     DrawIMG(mbg, 0,0);
     while(mdone = 0)
     {
                 
     while ( SDL_PollEvent(&event2) )
    {

      if ( event2.type == SDL_KEYDOWN )
      {
        if ( event2.key.keysym.sym == SDLK_ESCAPE) { mdone = 1; }
        
        
        
        }
        
        
        
     
      }
      SDL_Flip(myscreen);
      }
      
     BKSmenu t(myscreen);
     t.Draw();
     
    
}



int makeTrans(SDL_Surface *mythingy)
{
 SDL_SetColorKey(mythingy, SDL_SRCCOLORKEY, SDL_MapRGB(mythingy->format, 255, 0, 255) );    
 return 0;
}
void BKSmenu::DrawIMG(SDL_Surface *img, int x, int y,
                                int w, int h, int x2, int y2)
{
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  SDL_Rect dest2;
  dest2.x = x2;
  dest2.y = y2;
  dest2.w = w;
  dest2.h = h;
  SDL_BlitSurface(img, &dest2, myscreen, &dest);
}

void BKSmenu::DrawIMG(SDL_Surface *img, int x, int y)
{
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  SDL_BlitSurface(img, NULL, myscreen, &dest);
}



bool BKSmenu::isDone()
{
     return menuDone; 
}


void BKSmenu::Draw()
{
     
     
  std::ifstream::pos_type size;   
char * memblock;

                std::string names[10];
                     std::string scores[10];
       std::ifstream file ("data\\cars\\carup.raw", std::ios::in|std::ios::binary|std::ios::ate);
  if (file.is_open())
  {
                     
    size = file.tellg();

    memblock = new char [size];
    file.seekg (0, std::ios::beg);
    file.read (memblock, size);
    file.close();

    //cout << size << endl;
    int n = 0;
    for(int i = 0; i < size; i++)
    {
            
            if(memblock[i] != '%')
            {
            
            if(memblock[i] == '0' || memblock[i] == '1' || memblock[i] == '2' || memblock[i] == '3' || memblock[i] == '4' || memblock[i] == '5' || memblock[i] == '6' || memblock[i] == '7' || memblock[i] == '8' || memblock[i] == '9')
            {
            scores[n] += memblock[i];
            
                 
            } else names[n] += memblock[i];
            
            }
            
            
            
            if(i == 19 || i == 39 || i == 59 || i == 79 || i == 99) { n++;  }
            
            
            
            }
             
            }
            
        
    
    char * name1 = new char[255];
   std::strcpy(name1, names[0].c_str());
   
   char * name2 = new char[255];
   std::strcpy(name2, names[1].c_str());
   
   char * name3 = new char[255];
   std::strcpy(name3, names[2].c_str());
   
   char * name4 = new char[255];
   std::strcpy(name4, names[3].c_str());
   
   char * name5 = new char[255];
   std::strcpy(name5, names[4].c_str());
   
   char * score1 = new char[255];
   std::strcpy(score1, scores[0].c_str());
   
   char * score2 = new char[255];
   std::strcpy(score2, scores[1].c_str());
   
   char * score3 = new char[255];
   std::strcpy(score3, scores[2].c_str());
   
   char * score4 = new char[255];
   std::strcpy(score4, scores[3].c_str());
   
   char * score5 = new char[255];
   std::strcpy(score5, scores[4].c_str());
   
    delete[] memblock;  

   
   
   
   
     
     
    
   
     
     
     
     
     
     
     
     SDLFont *font1;       
//SDLFont *font2;

font1 = initFont("data\\font1");
  //font2 = initFont("data\\font2",1,1,0);
     
     
     
     SDL_Surface *bg = SDL_LoadBMP("data\\menu.bmp");
     SDL_Surface *quit = SDL_LoadBMP("data\\menu\\quit.bmp");
     SDL_Surface *quit_s = SDL_LoadBMP("data\\menu\\quit_s.bmp");
     SDL_Surface *start = SDL_LoadBMP("data\\menu\\start.bmp");
     SDL_Surface *start_s = SDL_LoadBMP("data\\menu\\start_s.bmp");
     SDL_Surface *high = SDL_LoadBMP("data\\menu\\high.bmp");
     SDL_Surface *high_s = SDL_LoadBMP("data\\menu\\high_s.bmp");
     
     makeTrans(quit);
     makeTrans(quit_s);
     makeTrans(start);
     makeTrans(start_s);
     makeTrans(high);
     makeTrans(high_s);
     
    
     int startX = 395;
     int startY = 260;
    
     int highX = 425;
     int highY = startY+60;
    
      int quitX = 446;
     int quitY = highY+60;
     DrawIMG(bg, 0,0);
     DrawIMG(start_s, startX, startY);
     DrawIMG(high, highX, highY);
      DrawIMG(quit, quitX, quitY);
     int selected = 0;
     SDL_Event event2;
     int done = 0;
     while(done == 0)
     {
      while ( SDL_PollEvent(&event2) )
    {

      if ( event2.type == SDL_KEYDOWN )
      {
        if ( event2.key.keysym.sym == SDLK_DOWN) { selected++; if(selected >= 3) selected = 0;
        
        
        }
        if ( event2.key.keysym.sym == SDLK_UP) { selected--; if(selected <= -1) selected = 2;
        
        
        
        
        }
        
        if(selected == 0)
        DrawIMG(start_s, startX, startY);
        else DrawIMG(start, startX, startY);
        
        if(selected == 1)
        DrawIMG(high_s, highX, highY);
        else DrawIMG(high, highX, highY);
        
        if(selected == 2)
        DrawIMG(quit_s, quitX, quitY);
        else DrawIMG(quit, quitX, quitY);
        
        if( event2.key.keysym.sym == SDLK_RETURN) { done = 1; }
      }
    
    SDL_Flip(myscreen);
    }
}
if(selected == 1) {
            
         
            SDL_Surface *mbg = SDL_LoadBMP("data\\highscorelist.bmp");
            DrawIMG(mbg, 0,0);
            int q = 0;
            SDL_Event event3;
            
            while(q == 0)
            {
                    
                    drawString(myscreen,font1,353,240,"1. %s",name1);
                    drawString(myscreen,font1,634,240,"%s",score1);
                    
                    drawString(myscreen,font1,353,300,"2. %s",name2);
                    drawString(myscreen,font1,634,300,"%s",score2);
                    
                    drawString(myscreen,font1,353,360,"3. %s",name3);
                    drawString(myscreen,font1,634,360,"%s",score3);
                    
                    drawString(myscreen,font1,353,420,"4. %s",name4);
                    drawString(myscreen,font1,634,420,"%s",score4);
                    
                    drawString(myscreen,font1,353,480,"5. %s",name5);
                    drawString(myscreen,font1,634,480,"%s",score5);
                    while ( SDL_PollEvent(&event3) )
    {

      if ( event3.type == SDL_KEYDOWN )
      {
        if ( event3.key.keysym.sym == SDLK_ESCAPE) { q = 1; break; }
            
      }
            
     }
             
             SDL_Flip(myscreen); 
             }
             
             Draw();
     }
if(selected == 2) killGame = true;
  menuDone = true;
freeFont(font1);
  //freeFont(font2);
     
}
