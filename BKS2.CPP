#define AI_SPEED 0.9

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <windows.h>
#include <time.h>
#include <string>
#include <string.h>
#include <sstream>
#include <math.h>
#include <SDL/SDL_mixer.h>
#include "font.h"
#include "highscore.h"



using namespace std;
string my_entry = "";
int dwidth = 35;
int dheight = 35;
int audioch = 1;
int monsterStart = 0;
bool stopGame = false;
bool boxCleared = false;
int boxTime = 0;
int myBoxX = 0;
int myBoxY = 0;
int channel = 5;
bool animateAI = false;
bool monster = false;
bool drawfps = true;
int loopIt = 0;
int oldscore = 0;
bool godMod = true;
int ko = 0;
int totalSpawn = 1;
bool carSPlayed = false;
bool blink = false;
bool gamePaused = false;
int collision = -1;
int w;
int fps = 0;
int tempfps = time( NULL ) + 1;
int blink182 = 1;
int a = 0;
int c = 0;
int nextBoxSpawn = time(NULL);
int lives = 3;
int carX = 1020;
int carY = 322;
double car_speed = 600;
double car_timer;
double car_timerdiff;
double car_movementvalue;
double car_secsperframe;
double d_speed = 0.4;
double scooterspeed = 300;
double timer; //used to check the current time
double timerdiff; //used to determine the time elapsed
double secsperframe; //used to hold the value for how many seconds have elapsed between frames
double movementvalue; //value to move by each frame
double movementvaluescooter; //value to move by each frame
int lastframe = SDL_GetTicks();
int cartime = time( NULL ) + 15;
int carangle = 0; // 0 = right to left 1 = left to right 2 = down to up 3 = up to down
int score = 0;
int ypos = 0, xpos = 0;
int randx = 0, randy = 0;
int chars = 1;
int deadGuysX[5000];
int deadGuysY[5000];
int deadGuysGFX[5000];
int totalDeadGuys = -1;
int AIy[5000];
int AIx[5000];
int oldX[5000];
int oldY[5000];
int bloodLenght = -1;
int bloodX[3];
int bloodY[3];
int animation[500];
int totalAI = 0;
int change = 0;
int godModStart = time(NULL);
//int AIx = 2; int AIy = 600;
int AImove = 3;
SDLFont *font1;
//SDLFont *font2;
SDL_Surface *deadScooters[5000];
SDL_Surface *dead0;
SDL_Surface *dead1;
SDL_Surface *dead2;
SDL_Surface *dead3;
SDL_Surface *dead4;
SDL_Surface *dead5;
SDL_Surface *dead6;
SDL_Surface *dead7;
SDL_Surface *dead8;
SDL_Surface *dead9;
SDL_Surface *dead10;
SDL_Surface *dead11;
SDL_Surface *dead12;
SDL_Surface *dead13;
SDL_Surface *dead14;
SDL_Surface *blackbg;
SDL_Surface *credits;
SDL_Surface *car;
SDL_Surface *redleft;
SDL_Surface *redright;
SDL_Surface *redup;
SDL_Surface *reddown;
SDL_Surface *blueleft;
SDL_Surface *blueright;
SDL_Surface *blueup;
SDL_Surface *bluedown;
SDL_Surface *greenleft;
SDL_Surface *greenright;
SDL_Surface *greenup;
SDL_Surface *greendown;
SDL_Surface *splat;
SDL_Surface *spacer;
SDL_Surface *gameover;
SDL_Surface *beathighscore;
SDL_Surface *exitgame;
SDL_Surface *topbar;
SDL_Surface *point;
SDL_Surface *back;
SDL_Surface *image;
SDL_Surface *screen;
SDL_Surface *apple;
SDL_Surface *one;
SDL_Surface *two;
SDL_Surface *three;
SDL_Surface *four;
SDL_Surface *five;
SDL_Surface *six;
SDL_Surface *monsterbox;
SDL_Surface *seven;
SDL_Surface *eight;
SDL_Surface *nine;
SDL_Surface *zero;
SDL_Surface *scooter_up;
SDL_Surface *scooter_down;
SDL_Surface *scooter_left;
SDL_Surface *scooter_right;
SDL_Surface *scooter_upright;
SDL_Surface *scooter_upleft;
SDL_Surface *scooter_downright;
SDL_Surface *scooter_downleft;
Mix_Music *music;
Mix_Chunk *fart;
Mix_Chunk *crash;
Mix_Chunk *crash2;
Mix_Chunk *crash3;
Mix_Chunk *honk1;
Mix_Chunk *honk2;
Mix_Chunk *splatsound;
Mix_Chunk *cardriving;
int getAudioChannel()
{
    if(audioch == 1) audioch = 2;
    else if(audioch == 2) audioch = 3;
    else if(audioch == 3) audioch = 4;
    else if(audioch == 4) audioch = 5;
    else if(audioch == 5) audioch = 6;
    else if(audioch == 6) audioch = 7;
    else audioch = 1;
    return audioch;
}
void DrawIMG(SDL_Surface *img, int x, int y,
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
    SDL_BlitSurface(img, &dest2, screen, &dest);
}
char * stringToChar(string input)
{
    char * name1 = new char[255];
    std::strcpy(name1, input.c_str());
    return name1;
}
int cDetect(int xa, int ya, int wa, int ha, int xb, int yb, int wb, int hb)
{
    if(xb + wb < xa) return 0; //just checking if their
    if(xb > xa + wa) return 0; //bounding boxes even touch
    if(yb + hb < ya) return 0;
    if(yb > ya + ha) return 0;
    return 1;
}
string intToString(int theint)
{
    string str;
    stringstream out;
    out << theint;
    return out.str();
}
int InitImages()
{
    blackbg = SDL_LoadBMP("data\\blackbg.bmp");
    credits = SDL_LoadBMP("data\\credits.bmp");
    monsterbox = SDL_LoadBMP("data\\monsterbox.bmp");
    //DET
    dead0 = SDL_LoadBMP("data\\scooter\\dead\\0.bmp");
    dead1 = SDL_LoadBMP("data\\scooter\\dead\\1.bmp");
    dead2 = SDL_LoadBMP("data\\scooter\\dead\\2.bmp");
    dead3= SDL_LoadBMP("data\\scooter\\dead\\3.bmp");
    dead4 = SDL_LoadBMP("data\\scooter\\dead\\4.bmp");
    dead5 = SDL_LoadBMP("data\\scooter\\dead\\5.bmp");
    dead6 = SDL_LoadBMP("data\\scooter\\dead\\6.bmp");
    dead7= SDL_LoadBMP("data\\scooter\\dead\\7.bmp");
    dead8 = SDL_LoadBMP("data\\scooter\\dead\\8.bmp");
    dead9 = SDL_LoadBMP("data\\scooter\\dead\\9.bmp");
    dead10 = SDL_LoadBMP("data\\scooter\\dead\\10.bmp");
    dead11= SDL_LoadBMP("data\\scooter\\dead\\11.bmp");
    dead12 = SDL_LoadBMP("data\\scooter\\dead\\12.bmp");
    dead13 = SDL_LoadBMP("data\\scooter\\dead\\13.bmp");
    dead14 = SDL_LoadBMP("data\\scooter\\dead\\14.bmp");
    //fonts
    font1 = initFont("data\\font1");
    //font2 = initFont("data\\font2",1,1,0);
    //cars
    car = SDL_LoadBMP("data\\cars\\redleft.bmp");
    redleft = SDL_LoadBMP("data\\cars\\redleft.bmp");
    redright= SDL_LoadBMP("data\\cars\\redright.bmp");
    reddown= SDL_LoadBMP("data\\cars\\reddown.bmp");
    redup= SDL_LoadBMP("data\\cars\\redup.bmp");
    blueleft = SDL_LoadBMP("data\\cars\\blueleft.bmp");
    blueright= SDL_LoadBMP("data\\cars\\blueright.bmp");
    bluedown= SDL_LoadBMP("data\\cars\\bluedown.bmp");
    blueup= SDL_LoadBMP("data\\cars\\blueup.bmp");
    greenleft = SDL_LoadBMP("data\\cars\\greenleft.bmp");
    greenright= SDL_LoadBMP("data\\cars\\greenright.bmp");
    greendown= SDL_LoadBMP("data\\cars\\greendown.bmp");
    greenup= SDL_LoadBMP("data\\cars\\greenup.bmp");
    //im sick of writing comments
    scooter_up = SDL_LoadBMP("data\\scooter\\up.bmp");
    scooter_down = SDL_LoadBMP("data\\scooter\\down.bmp");
    scooter_left = SDL_LoadBMP("data\\scooter\\left.bmp");
    scooter_right = SDL_LoadBMP("data\\scooter\\right.bmp");
    scooter_upright = SDL_LoadBMP("data\\scooter\\upright.bmp");
    scooter_upleft = SDL_LoadBMP("data\\scooter\\upleft.bmp");
    scooter_downright = SDL_LoadBMP("data\\scooter\\downright.bmp");
    scooter_downleft = SDL_LoadBMP("data\\scooter\\downleft.bmp");
    splat = SDL_LoadBMP("data\\hero\\dead2.bmp");
    spacer = SDL_LoadBMP("data\\spacer.bmp");
    one = SDL_LoadBMP("data\\numbers\\1.bmp");
    two = SDL_LoadBMP("data\\numbers\\2.bmp");
    three = SDL_LoadBMP("data\\numbers\\3.bmp");
    four = SDL_LoadBMP("data\\numbers\\4.bmp");
    five = SDL_LoadBMP("data\\numbers\\5.bmp");
    six = SDL_LoadBMP("data\\numbers\\6.bmp");
    seven = SDL_LoadBMP("data\\numbers\\7.bmp");
    eight = SDL_LoadBMP("data\\numbers\\8.bmp");
    nine = SDL_LoadBMP("data\\numbers\\9.bmp");
    zero = SDL_LoadBMP("data\\numbers\\0.bmp");
    point = SDL_LoadBMP("data\\hero\\point.bmp");
    gameover = SDL_LoadBMP("data\\gameover.bmp");
    beathighscore = SDL_LoadBMP("data\\beathighscore.bmp");
    exitgame = SDL_LoadBMP("data\\exitgame.bmp");
    topbar = SDL_LoadBMP("data\\toppart.bmp");
    SDL_SetColorKey(monsterbox, SDL_SRCCOLORKEY, SDL_MapRGB(monsterbox->format, 255, 0, 255) );
    SDL_SetColorKey(dead0, SDL_SRCCOLORKEY, SDL_MapRGB(dead0->format, 255, 0, 255) );
    SDL_SetColorKey(dead1, SDL_SRCCOLORKEY, SDL_MapRGB(dead1->format, 255, 0, 255) );
    SDL_SetColorKey(dead2, SDL_SRCCOLORKEY, SDL_MapRGB(dead2->format, 255, 0, 255) );
    SDL_SetColorKey(dead3, SDL_SRCCOLORKEY, SDL_MapRGB(dead3->format, 255, 0, 255) );
    SDL_SetColorKey(dead4, SDL_SRCCOLORKEY, SDL_MapRGB(dead4->format, 255, 0, 255) );
    SDL_SetColorKey(dead5, SDL_SRCCOLORKEY, SDL_MapRGB(dead5->format, 255, 0, 255) );
    SDL_SetColorKey(dead6, SDL_SRCCOLORKEY, SDL_MapRGB(dead6->format, 255, 0, 255) );
    SDL_SetColorKey(dead7, SDL_SRCCOLORKEY, SDL_MapRGB(dead7->format, 255, 0, 255) );
    SDL_SetColorKey(dead8, SDL_SRCCOLORKEY, SDL_MapRGB(dead8->format, 255, 0, 255) );
    SDL_SetColorKey(dead9, SDL_SRCCOLORKEY, SDL_MapRGB(dead9->format, 255, 0, 255) );
    SDL_SetColorKey(dead10, SDL_SRCCOLORKEY, SDL_MapRGB(dead10->format, 255, 0, 255) );
    SDL_SetColorKey(dead11, SDL_SRCCOLORKEY, SDL_MapRGB(dead11->format, 255, 0, 255) );
    SDL_SetColorKey(dead12, SDL_SRCCOLORKEY, SDL_MapRGB(dead12->format, 255, 0, 255) );
    SDL_SetColorKey(dead13, SDL_SRCCOLORKEY, SDL_MapRGB(dead13->format, 255, 0, 255) );
    SDL_SetColorKey(dead14, SDL_SRCCOLORKEY, SDL_MapRGB(dead14->format, 255, 0, 255) );
    SDL_SetColorKey(car, SDL_SRCCOLORKEY, SDL_MapRGB(car->format, 255, 0, 255) );
    SDL_SetColorKey(redup, SDL_SRCCOLORKEY, SDL_MapRGB(redup->format, 255, 0, 255) );
    SDL_SetColorKey(reddown, SDL_SRCCOLORKEY, SDL_MapRGB(reddown->format, 255, 0, 255) );
    SDL_SetColorKey(redright, SDL_SRCCOLORKEY, SDL_MapRGB(redright->format, 255, 0, 255) );
    SDL_SetColorKey(redleft, SDL_SRCCOLORKEY, SDL_MapRGB(redleft->format, 255, 0, 255) );
    SDL_SetColorKey(blueup, SDL_SRCCOLORKEY, SDL_MapRGB(blueup->format, 255, 0, 255) );
    SDL_SetColorKey(bluedown, SDL_SRCCOLORKEY, SDL_MapRGB(bluedown->format, 255, 0, 255) );
    SDL_SetColorKey(blueright, SDL_SRCCOLORKEY, SDL_MapRGB(blueright->format, 255, 0, 255) );
    SDL_SetColorKey(blueleft, SDL_SRCCOLORKEY, SDL_MapRGB(blueleft->format, 255, 0, 255) );
    SDL_SetColorKey(greenup, SDL_SRCCOLORKEY, SDL_MapRGB(greenup->format, 255, 0, 255) );
    SDL_SetColorKey(greendown, SDL_SRCCOLORKEY, SDL_MapRGB(greendown->format, 255, 0, 255) );
    SDL_SetColorKey(greenright, SDL_SRCCOLORKEY, SDL_MapRGB(greenright->format, 255, 0, 255) );
    SDL_SetColorKey(greenleft, SDL_SRCCOLORKEY, SDL_MapRGB(greenleft->format, 255, 0, 255) );
    SDL_SetColorKey(splat, SDL_SRCCOLORKEY, SDL_MapRGB(splat->format, 255, 0, 255) );
    SDL_SetColorKey(spacer, SDL_SRCCOLORKEY, SDL_MapRGB(spacer->format, 255, 0, 255) );
    SDL_SetColorKey(point, SDL_SRCCOLORKEY, SDL_MapRGB(point->format, 255, 0, 255) );
    SDL_SetColorKey(one, SDL_SRCCOLORKEY, SDL_MapRGB(one->format, 255, 0, 255) );
    SDL_SetColorKey(two, SDL_SRCCOLORKEY, SDL_MapRGB(two->format, 255, 0, 255) );
    SDL_SetColorKey(three, SDL_SRCCOLORKEY, SDL_MapRGB(three->format, 255, 0, 255) );
    SDL_SetColorKey(four, SDL_SRCCOLORKEY, SDL_MapRGB(four->format, 255, 0, 255) );
    SDL_SetColorKey(five, SDL_SRCCOLORKEY, SDL_MapRGB(five->format, 255, 0, 255) );
    SDL_SetColorKey(six, SDL_SRCCOLORKEY, SDL_MapRGB(six->format, 255, 0, 255) );
    SDL_SetColorKey(seven, SDL_SRCCOLORKEY, SDL_MapRGB(seven->format, 255, 0, 255) );
    SDL_SetColorKey(eight, SDL_SRCCOLORKEY, SDL_MapRGB(eight->format, 255, 0, 255) );
    SDL_SetColorKey(nine, SDL_SRCCOLORKEY, SDL_MapRGB(nine->format, 255, 0, 255) );
    SDL_SetColorKey(zero, SDL_SRCCOLORKEY, SDL_MapRGB(zero->format, 255, 0, 255) );
    back = SDL_LoadBMP("data\\bg.bmp");
    image = SDL_LoadBMP("data\\hero\\up.bmp");
    apple = SDL_LoadBMP("data\\apple.bmp");
    SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 255, 0, 255) );
    SDL_SetColorKey(apple, SDL_SRCCOLORKEY, SDL_MapRGB(apple->format, 255, 0, 255) );
    SDL_SetColorKey(scooter_up, SDL_SRCCOLORKEY, SDL_MapRGB(scooter_up->format, 255, 0, 255) );
    SDL_SetColorKey(scooter_down, SDL_SRCCOLORKEY, SDL_MapRGB(scooter_down->format, 255, 0, 255) );
    SDL_SetColorKey(scooter_left, SDL_SRCCOLORKEY, SDL_MapRGB(scooter_left->format, 255, 0, 255) );
    SDL_SetColorKey(scooter_right, SDL_SRCCOLORKEY, SDL_MapRGB(scooter_right->format, 255, 0, 255) );
    SDL_SetColorKey(scooter_upleft, SDL_SRCCOLORKEY, SDL_MapRGB(scooter_upleft->format, 255, 0, 255) );
    SDL_SetColorKey(scooter_upright, SDL_SRCCOLORKEY, SDL_MapRGB(scooter_upright->format, 255, 0, 255) );
    SDL_SetColorKey(scooter_downleft, SDL_SRCCOLORKEY, SDL_MapRGB(scooter_downleft->format, 255, 0, 255) );
    SDL_SetColorKey(scooter_downright, SDL_SRCCOLORKEY, SDL_MapRGB(scooter_downright->format, 255, 0, 255) );
    return 0;
}
void DrawIMG(SDL_Surface *img, int x, int y)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_BlitSurface(img, NULL, screen, &dest);
}
void DrawBG()
{
    DrawIMG(back, 0, 0);
}
void DrawScooter(int id, int x, int y)
{
    if(animation[id] == 0)
    {
        DrawIMG(scooter_up,x,y);
    }
    else if(animation[id] == 1)
    {
        DrawIMG(scooter_down,x,y);
    }
    else if(animation[id] == 2)
    {
        DrawIMG(scooter_left,x,y);
    }
    else if(animation[id] == 3)
    {
        DrawIMG(scooter_right,x,y);
    }
    else if(animation[id] == 4)
    {
        DrawIMG(scooter_upleft,x,y);
    }
    else if(animation[id] == 5)
    {
        DrawIMG(scooter_upright,x,y);
    }
    else if(animation[id] == 6)
    {
        DrawIMG(scooter_downleft,x,y);
    }
    else if(animation[id] == 7)
    {
        DrawIMG(scooter_downright,x,y);
    }
    else
    {
        DrawIMG(scooter_up,x,y);
    }
}
int random_max(int highest_number)
{
    return rand() % highest_number + 1;
}
bool collideApple()
{
    if(xpos+35 >= randx && xpos <= randx+30 && ypos+35 >= randy && ypos <= randy+30) return true; else return false;
}
int stringToInt(string input)
{
    std::string str(input);
    std::istringstream strin(str);
    int i;
    strin >> i;
    return i;
}
int beatHighscore(int myscore)
{
    //returns -1 if you dont beat it. else it will return whatever pos you beat..
    //START OF FUNNY STUFF
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
                }
                else names[n] += memblock[i];
            }
            if(i == 19 || i == 39 || i == 59 || i == 79 || i == 99) {
                n++;
            }
        }
    }
    int intscores[5];
    for(int yay = 0; yay < 5; yay++)
    {
        intscores[yay] = stringToInt(scores[yay]);
    }
    int thispos = -1;
    for(int yay = 4; yay >= 0; yay--)
    {
        if(myscore > intscores[yay])
        {
            thispos = yay+1;
        }
    }
    delete[] memblock;
    return thispos;
    //END OF FUNNY STUFF
}
void DrawNumber(string number)
{
    w = 45;
    chars = 1;
    while(chars <= number.size())
    {
        if(number.substr(chars-1,1) == "1" ) DrawIMG(one,w,8);
        else if(number.substr(chars-1,1) == "2")DrawIMG(two,w,8);
        else if(number.substr(chars-1,1) == "3")DrawIMG(three,w,8);
        else if(number.substr(chars-1,1) == "4")DrawIMG(four,w,8);
        else if(number.substr(chars-1,1) == "5")DrawIMG(five,w,8);
        else if(number.substr(chars-1,1) == "6")DrawIMG(six,w,8);
        else if(number.substr(chars-1,1) == "7")DrawIMG(seven,w,8);
        else if(number.substr(chars-1,1) == "8")DrawIMG(eight,w,8);
        else if(number.substr(chars-1,1) == "9")DrawIMG(nine,w,8);
        else DrawIMG(zero,w,8);
        w = w + 12;
        chars++;
    }
}
void clearApple()
{
    DrawIMG(back, randx, randy, 30, 30, randx, randy);
    SDL_Flip(screen);
}
void clearScore()
{
    //DrawIMG(back, 0,0);
    DrawIMG(back, 2, 2, 500, 40, 2, 2);
    SDL_Flip(screen);
}
bool fumble(int percent)
{
    //fumble class.. plug in the chances that a unit fumbles
    if(change == 0) change = 1; else if(change == 1) change = 3; else change = 0;
    srand(time(NULL) + change);
    if(random_max(100) <= percent) return true; else return false;
}
bool collideTopWall()
{
    if(ypos-1 < 37) return false; else return true;
}
bool collideLeftWall()
{
    if(xpos-1 < 0) return false; else return true;
}
bool collideRightWall()
{
    if(xpos+1 > 989) return false; else return true;
}
bool collideBottomWall()
{
    if(ypos+1 > 733) return false; else return true;
}
void newAI()
{

    
    srand(time( NULL ) + score + xpos + totalAI);
    int myRandX = random_max(980);
    int myRandY = random_max(700);
    while(myRandY < 37)
    {
        myRandY = random_max(700);
    }
    while(cDetect(myRandX, myRandY, 500, 500, xpos, ypos,100,100) == 1)
    {
        myRandX = random_max(980);
        myRandY = random_max(700);
    }

    AIx[totalAI] = myRandX;
    AIy[totalAI] = myRandY;
    oldX[totalAI] = myRandX;
    oldY[totalAI] = myRandY;
    animation[totalAI] = 0;
    totalAI++;
}
void newAI(int x, int y)
{
    
    AIx[totalAI] = x;
    AIy[totalAI] = y;
    oldX[totalAI] = x;
    oldY[totalAI] = y;
    animation[totalAI] = 0;
    totalAI++;
}
void crazyAttack(int howManyAIs)
{
    int topA = 0;
    int leftA = 0;
    int rightA = 0;
    int bottomA = 0;
    for(int crazy = 0; crazy < (int) howManyAIs/4; crazy++)
    {
        //ai loop
        //make one on top
        newAI(topA, 0 - random_max(400));
        topA += 35;
        //make one on bottom
        newAI(bottomA, 768 + random_max(400));
        bottomA += 35;
        //make on on the left
        newAI(0 - random_max(400), leftA);
        leftA += 35;
        //make on on the right
        newAI(1024 + random_max(400), rightA);
        rightA += 35;
    }
}
int insideWorld(int x, int y)
{
    /*
    insideWorld rules:
    0 = everything is fine
    1 = unit is too high
    2 = unit is too low
    3 = unit is too much to the left
    4 = unit is too much to the right
    */
    if(y <= 37) return 1;
    else if(y >= 768) return 2;
    else if(x < 0) return 3;
    else if(x > 768) return 4;
    else {
        return 0;
    }
}


double Gaussian(double x, double y,double r) { 

    double dotP = ((x*x)+(y*y));
    double dByR = -dotP/r;
    double expVal = exp(dByR);

    return expVal; 
} 

double VectorLength(double x, double y) {
    return sqrt((x*x)+(y*y));
}

void moveAI(bool stay) {
    a = 0;
    bool co = false;
    bool dontDraw = false;
    while(a < totalAI)
    {
        dontDraw = false;
        animateAI = true;
        if(AIx[a] != -400 && AIy[a] != -400)
        {

            // ==================
            // START CAR / SCOOTER COLLIDE
            // ==================

            if(cDetect(AIx[a],AIy[a],35,48,carX, carY, 400,400) == 1 && carSPlayed != true)
            {
                //PLAY HONK HONK!!!
                Mix_PlayChannel(5, honk1, 0);
                carSPlayed = true;
            }
            if(carangle == 0 || carangle == 1 || carangle == 2)
            {
                //car is driving horizontal
                if(cDetect(AIx[a],AIy[a],35,48,carX, carY, 140,64) == 1)
                {
                    if(random_max(3) == 1) Mix_PlayChannel(getAudioChannel(), crash, 0); else if(random_max(2) == 1) Mix_PlayChannel(getAudioChannel(), crash2, 0); else Mix_PlayChannel(getAudioChannel(), crash3, 0);
                    Mix_PlayChannel(getAudioChannel(), splatsound, 0);
                    totalDeadGuys++;
                    deadGuysGFX[totalDeadGuys] = random_max(14);
                    while(deadGuysGFX[totalDeadGuys] > 5 && deadGuysGFX[totalDeadGuys] < 11) deadGuysGFX[totalDeadGuys] = random_max(14);
                    switch(deadGuysGFX[totalDeadGuys])
                    {
                        case 0:
                        deadScooters[totalDeadGuys] = dead0;
                        break;
                        case 1:
                        deadScooters[totalDeadGuys] = dead1;
                        break;
                        case 2:
                        deadScooters[totalDeadGuys] = dead2;
                        break;
                        case 3:
                        deadScooters[totalDeadGuys] = dead3;
                        break;
                        case 4:
                        deadScooters[totalDeadGuys] = dead4;
                        break;
                        case 5:
                        deadScooters[totalDeadGuys] = dead5;
                        break;
                        case 6:
                        deadScooters[totalDeadGuys] = dead6;
                        break;
                        case 7:
                        deadScooters[totalDeadGuys] = dead7;
                        break;
                        case 8:
                        deadScooters[totalDeadGuys] = dead8;
                        break;
                        case 9:
                        deadScooters[totalDeadGuys] = dead9;
                        break;
                        case 10:
                        deadScooters[totalDeadGuys] = dead10;
                        break;
                        case 11:
                        deadScooters[totalDeadGuys] = dead11;
                        break;
                        case 12:
                        deadScooters[totalDeadGuys] = dead12;
                        break;
                        case 13:
                        deadScooters[totalDeadGuys] = dead13;
                        break;
                        case 14:
                        deadScooters[totalDeadGuys] = dead14;
                        break;
                        default:
                        deadScooters[totalDeadGuys] = dead0;
                    }
                    dontDraw = true;
                    deadGuysX[totalDeadGuys] = AIx[a];
                    deadGuysY[totalDeadGuys] = AIy[a];
                    totalAI--;
                    AIx[a] = AIx[totalAI];
                    AIy[a] = AIy[totalAI];
                    
                }
            }
            else {
                //car is driving vertical
                if(cDetect(AIx[a],AIy[a],35,48,carX, carY, 60,135) == 1)
                {
                    if(random_max(3) == 1) Mix_PlayChannel(getAudioChannel(), crash, 0); else if(random_max(2) == 1) Mix_PlayChannel(getAudioChannel(), crash2, 0); else Mix_PlayChannel(getAudioChannel(), crash3, 0);
                    Mix_PlayChannel(getAudioChannel(), splatsound, 0);
                    totalDeadGuys++;
                    deadGuysGFX[totalDeadGuys] = random_max(14);
                    while(deadGuysGFX[totalDeadGuys] <= 5) deadGuysGFX[totalDeadGuys] = random_max(14);
                    switch(deadGuysGFX[totalDeadGuys])
                    {
                        case 0:
                        deadScooters[totalDeadGuys] = dead0;
                        break;
                        case 1:
                        deadScooters[totalDeadGuys] = dead1;
                        break;
                        case 2:
                        deadScooters[totalDeadGuys] = dead2;
                        break;
                        case 3:
                        deadScooters[totalDeadGuys] = dead3;
                        break;
                        case 4:
                        deadScooters[totalDeadGuys] = dead4;
                        break;
                        case 5:
                        deadScooters[totalDeadGuys] = dead5;
                        break;
                        case 6:
                        deadScooters[totalDeadGuys] = dead6;
                        break;
                        case 7:
                        deadScooters[totalDeadGuys] = dead7;
                        break;
                        case 8:
                        deadScooters[totalDeadGuys] = dead8;
                        break;
                        case 9:
                        deadScooters[totalDeadGuys] = dead9;
                        break;
                        case 10:
                        deadScooters[totalDeadGuys] = dead10;
                        break;
                        case 11:
                        deadScooters[totalDeadGuys] = dead11;
                        break;
                        case 12:
                        deadScooters[totalDeadGuys] = dead12;
                        break;
                        case 13:
                        deadScooters[totalDeadGuys] = dead13;
                        break;
                        case 14:
                        deadScooters[totalDeadGuys] = dead14;
                        break;
                        default:
                        deadScooters[totalDeadGuys] = dead0;
                    }
                    dontDraw = true;
                    deadGuysX[totalDeadGuys] = AIx[a];
                    deadGuysY[totalDeadGuys] = AIy[a];
                    totalAI--;
                    AIx[a] = AIx[totalAI];
                    AIy[a] = AIy[totalAI];
                    
                }
            }

            // ==================
            // END CAR / SCOOTER COLLIDE
            // ==================


            if(AIx[a] != -400 && AIy[a] != -400)
            {



                // ==================
                // START CAR / PLAYER COLLIDE
                // ==================
                if(cDetect(AIx[a],AIy[a],35,48,xpos,ypos,dwidth,dheight) == 1)
                {
                    if(godMod == false)
                    {
                        Mix_PlayChannel(3, splatsound, 0);
                        lives--;
                        bloodLenght++;
                        bloodX[bloodLenght] = xpos;
                        bloodY[bloodLenght] = ypos;
                        DrawIMG(back,0,0);
                        godModStart = time(NULL);
                        godMod = true;
                    }
                    if(monster == true)
                    {
                        totalDeadGuys++;
                        if(random_max(3) == 1) Mix_PlayChannel(getAudioChannel(), crash, 0); else if(random_max(2) == 1) Mix_PlayChannel(getAudioChannel(), crash2, 0); else Mix_PlayChannel(getAudioChannel(), crash3, 0);
                        Mix_PlayChannel(getAudioChannel(), splatsound, 0);
                        deadGuysGFX[totalDeadGuys] = random_max(14);
                        while(deadGuysGFX[totalDeadGuys] <= 5) deadGuysGFX[totalDeadGuys] = random_max(14);
                        switch(deadGuysGFX[totalDeadGuys])
                        {
                            case 0:
                            deadScooters[totalDeadGuys] = dead0;
                            break;
                            case 1:
                            deadScooters[totalDeadGuys] = dead1;
                            break;
                            case 2:
                            deadScooters[totalDeadGuys] = dead2;
                            break;
                            case 3:
                            deadScooters[totalDeadGuys] = dead3;
                            break;
                            case 4:
                            deadScooters[totalDeadGuys] = dead4;
                            break;
                            case 5:
                            deadScooters[totalDeadGuys] = dead5;
                            break;
                            case 6:
                            deadScooters[totalDeadGuys] = dead6;
                            break;
                            case 7:
                            deadScooters[totalDeadGuys] = dead7;
                            break;
                            case 8:
                            deadScooters[totalDeadGuys] = dead8;
                            break;
                            case 9:
                            deadScooters[totalDeadGuys] = dead9;
                            break;
                            case 10:
                            deadScooters[totalDeadGuys] = dead10;
                            break;
                            case 11:
                            deadScooters[totalDeadGuys] = dead11;
                            break;
                            case 12:
                            deadScooters[totalDeadGuys] = dead12;
                            break;
                            case 13:
                            deadScooters[totalDeadGuys] = dead13;
                            break;
                            case 14:
                            deadScooters[totalDeadGuys] = dead14;
                            break;
                            default:
                            deadScooters[totalDeadGuys] = dead0;
                        }
                        dontDraw = true;
                        deadGuysX[totalDeadGuys] = AIx[a];
                        deadGuysY[totalDeadGuys] = AIy[a];
                        score++;
                        totalAI--;
                        AIx[a] = AIx[totalAI];
                        AIy[a] = AIy[totalAI];
                        
                    }
                }


                // ==================
                // END CAR / PLAYER COLLIDE
                // ==================



                // ==================
                // START AI MOVEMENT
                // ==================
                if(AImove == 3)
                {
                    oldX[a] = AIx[a];
                    oldY[a] = AIy[a];
                    

                            

                    double dirXRepel = 0;
                    double dirYRepel = 0;

                    if (totalAI > 1) {
                        for(int z = 0; z < totalAI; z++)
                        {
                            if(z != a)
                            {
                                double dirOtherAIX = AIx[a]-AIx[z];
                                double dirOtherAIY = AIy[a]-AIy[z];

                                double lengthOtherAI = VectorLength(dirOtherAIX,dirOtherAIY);

                                double weightRepel = Gaussian(dirOtherAIX,dirOtherAIY,2000);


                                if (lengthOtherAI == 0) {
                                    lengthOtherAI = 0.01;
                                }

                                dirOtherAIX = dirOtherAIX/lengthOtherAI;
                                dirOtherAIY = dirOtherAIY/lengthOtherAI;
                                



                                dirXRepel += weightRepel*dirOtherAIX;
                                dirYRepel += weightRepel*dirOtherAIY;
                            }
                        }

                        dirXRepel = -dirXRepel/(totalAI-1);
                        dirYRepel = -dirYRepel/(totalAI-1);
                    }


                    double dirX = AIx[a]-xpos;
                    double dirY = AIy[a]-ypos;
                    
                    // Normalize speed vector
                    double length = VectorLength(dirX,dirY);

                    if ((int) length != 0) {
                        dirX = (dirX/length);
                        dirY = (dirY/length);
                    } else {
                        dirX = 0;
                        dirY = 0;
                    }  


                    dirX += dirXRepel*4.0; // 4.0 is additional repel weight
                    dirY += dirYRepel*4.0; // 4.0 is additional repel weight
                    
                    AIx[a] -= round(AI_SPEED*movementvalue*dirX);
                    AIy[a] -= round(AI_SPEED*movementvalue*dirY);
                    //printf("dir: %.2f [%.2f,%.2f]\n",movementvaluescooter,round(movementvaluescooter*dirX),round(movementvaluescooter*dirY));






                }
                if(animateAI == true)
                {
                    int calcX = AIx[a]-oldX[a];
                    int calcY = AIy[a]-oldY[a];
                    if(calcY == 0 && calcX > 0)
                    {
                        animation[a] = 3;
                    }
                    else if(calcY == 0 && calcX < 0)
                    {
                        animation[a] = 2;
                    }
                    else if(calcX == 0 && calcY > 0)
                    {
                        animation[a] = 1;
                    }
                    else if(calcX == 0 && calcY < 0)
                    {
                        animation[a] = 0;
                    }
                    else if(calcX < 0 && calcY < 0)
                    {
                        animation[a] = 4;
                    }
                    else if(calcX > 0 && calcY < 0)
                    {
                        animation[a] = 5;
                    }
                    else if(calcX < 0 && calcY > 0)
                    {
                        animation[a] = 6;
                    }
                    else if(calcX > 0 && calcY > 0)
                    {
                        animation[a] = 7;
                    }
                    else {
                        animation[a] = 0;
                    }
                }
                if(dontDraw == false)  DrawScooter(a,AIx[a],AIy[a]); else DrawIMG(back,oldX[a]-40,oldY[a]-40,120,120,oldX[a]-40,oldY[a]-40);

                // ==================
                // END AI MOVEMENT
                // ==================
            }
            
        }
        co = false;
        a++;
        //end of while loop
    }
    if(AImove == 1) AImove = 2; else if(AImove == 2) AImove = 3; else AImove = 1;
}
bool carOutOfScreen()
{
    if(carX <= -200 ||carY >= 800 || carX >= 1100 || carY <= -200) return true; else return false;
}
void DrawApple()
{
    srand(time(NULL));
    while(collideApple() == true)
    {
        randx = random_max(989);
        randy = random_max(733);
    }
    srand(time(NULL));
    while(randy <= 37 || collideApple() == true)
    {
        randx = random_max(989);
        randy = random_max(733);
    }
    DrawIMG(apple, randx, randy);
}
char intToChar(int an_int)
{
    char an_array[255];
    return sprintf(an_array, "%d", an_int);
}
void setscore(int posi, int thescore, string playername)
{
    std::ifstream::pos_type size;
    char * memblock;
    std::ifstream file ("data\\cars\\carup.raw", std::ios::in|std::ios::binary|std::ios::ate);
    if (file.is_open())
    {
        size = file.tellg();
        memblock = new char [size];
        file.seekg (0, std::ios::beg);
        file.read (memblock, size);
        file.close();
    }
    string temphigh = memblock;
    //NOTE:
    std::string names[10];
    std::string scores[10];
    int n = 0;
    for(int i = 0; i < size; i++)
    {
        if(memblock[i] != '%')
        {
            if(memblock[i] == '0' || memblock[i] == '1' || memblock[i] == '2' || memblock[i] == '3' || memblock[i] == '4' || memblock[i] == '5' || memblock[i] == '6' || memblock[i] == '7' || memblock[i] == '8' || memblock[i] == '9')
            {
                scores[n] += memblock[i];
            }
            else names[n] += memblock[i];
        }
        if(i == 19 || i == 39 || i == 59 || i == 79 || i == 99) {
            n++;
        }
    }
    //ARRAYSTUFF
    for(int mychar = 0; mychar < temphigh.length(); mychar++)
    {
        if(posi == 1 && mychar == 0) {
            temphigh.replace(0,playername.length(),stringToChar(playername)); for(int tem = 0+playername.length(); tem < 10; tem++) temphigh.replace(tem,1,"%"); temphigh.replace(10,intToString(thescore).length(),stringToChar(intToString(thescore))); for(int tem = 10+intToString(thescore).length(); tem < 20; tem++) temphigh.replace(tem,1,"%"); break;
        }
        if(posi == 2 && mychar == 20) {
            temphigh.replace(20,playername.length(),stringToChar(playername)); for(int tem = 20+playername.length(); tem < 30; tem++) temphigh.replace(tem,1,"%"); temphigh.replace(30,intToString(thescore).length(),stringToChar(intToString(thescore))); for(int tem = 30+intToString(thescore).length(); tem < 40; tem++) temphigh.replace(tem,1,"%"); break;
        }
        if(posi == 3 && mychar == 40) {
            temphigh.replace(40,playername.length(),stringToChar(playername)); for(int tem = 40+playername.length(); tem < 50; tem++) temphigh.replace(tem,1,"%"); temphigh.replace(50,intToString(thescore).length(),stringToChar(intToString(thescore))); for(int tem = 50+intToString(thescore).length(); tem < 60; tem++) temphigh.replace(tem,1,"%"); break;
        }
        if(posi == 4 && mychar == 60) {
            temphigh.replace(60,playername.length(),stringToChar(playername)); for(int tem = 60+playername.length(); tem < 70; tem++) temphigh.replace(tem,1,"%"); temphigh.replace(70,intToString(thescore).length(),stringToChar(intToString(thescore))); for(int tem = 70+intToString(thescore).length(); tem < 80; tem++) temphigh.replace(tem,1,"%"); break;
        }
        if(posi == 5 && mychar == 80) {
            temphigh.replace(80,playername.length(),stringToChar(playername)); for(int tem = 80+playername.length(); tem < 90; tem++) temphigh.replace(tem,1,"%"); temphigh.replace(90,intToString(thescore).length(),stringToChar(intToString(thescore))); for(int tem = 90+intToString(thescore).length(); tem < 100; tem++) temphigh.replace(tem,1,"%"); break;
        }
    }
    temphigh.erase(101);
    ofstream myfile ("data\\cars\\carup.raw");
    if (myfile.is_open())
    {
        myfile << temphigh;
        myfile.close();
    }
    for(int mychar = 0; mychar < temphigh.length(); mychar++)
    {
        if(posi == 1 && mychar == 0) {
            cout << stringToInt(scores[0]) << endl; setscore(posi+1, stringToInt(scores[0]), names[0]);
        }
        if(posi == 2 && mychar == 20) {
            cout << stringToInt(scores[1]) << endl; setscore(posi+1, stringToInt(scores[1]), names[1]);
        }
        if(posi == 3 && mychar == 40) {
            cout << stringToInt(scores[2]) << endl; setscore(posi+1, stringToInt(scores[2]), names[2]);
        }
        if(posi == 4 && mychar == 60) {
            cout << stringToInt(scores[3]) << endl; setscore(posi+1, stringToInt(scores[3]), names[3]);
        }
        if(posi == 5 && mychar == 80) {
            cout << stringToInt(scores[4]) << endl; setscore(posi+1, stringToInt(scores[4]), names[4]);
        }
    }
}
void DrawScene()
{
    if(cDetect(xpos,ypos,35,48,carX, carY, 400,400) == 1 && carSPlayed != true)
    {
        //PLAY HONK HONK!!!
        Mix_PlayChannel(5, honk1, 0);
        carSPlayed = true;
    }
    a = 0;
    while(a <= totalAI)
    {
        DrawIMG(back, oldX[a]-20, oldY[a]-20, 100, 100, oldX[a]-20, oldY[a]-20);
        a++;
    }
    if(carangle == 0 || carangle == 1 || carangle == 2)
    DrawIMG(back, carX, carY, 150, 70, carX, carY);
    else DrawIMG(back, carX, carY, 70, 150, carX, carY);
    if(bloodLenght != -1)
    {
        ko = 0;
        while(ko <= bloodLenght)
        {
            DrawIMG(splat, bloodX[ko], bloodY[ko]);
            ko++;
        }
    }
    if(totalDeadGuys != -1)
    {
        loopIt = 0;
        while(loopIt <= totalDeadGuys)
        {
            DrawIMG(deadScooters[loopIt], deadGuysX[loopIt], deadGuysY[loopIt]);
            loopIt++;
        }
    }
    if(score > 99)
    {
        if(boxTime >= time(NULL))
        {
            DrawIMG(monsterbox,myBoxX,myBoxY);
            if(cDetect(xpos,ypos,35,35,myBoxX, myBoxY, 60,35) == 1)
            {
                boxTime = 0;
                dwidth = 120;
                dheight = 100;
                monster = true;
                godModStart = time( NULL) + 999999;
                crazyAttack(75);
                monsterStart = time(NULL);
                nextBoxSpawn = time(NULL);
                boxCleared = false;
                godMod = true;
            }
        }
        else {
            dwidth = 35;
            dheight = 35;
            DrawIMG(back,myBoxX,myBoxY, 150,150,myBoxX,myBoxY);
        }
        if(boxCleared == false) {
            DrawIMG(back,myBoxX,myBoxY, 150,150,myBoxX,myBoxY);
            nextBoxSpawn = time(NULL);
            boxCleared = true;
        }
        if(fumble(5) == true && boxTime < time(NULL) && nextBoxSpawn + 120 <= time(NULL))
        {
            boxTime = time(NULL) + 3;
            boxCleared = false;
            myBoxX = random_max(900);
            myBoxY = random_max(700);
        }
    }
    if(randx != 0 && randy != 0)
    {
        DrawIMG(apple, randx, randy);
    }
    DrawIMG(image, xpos, ypos);
    if(monsterStart + 7 <= time(NULL) && monster == true)
    {
        DrawIMG(back,0,0);
        monster = false;
        godMod = false;
    }
    if(time(NULL) - godModStart > 3)
    {
        godMod = false;
    }
    moveAI(false);

    if(carangle == 0 || carangle == 1 || carangle == 2)
    {
        //car is driving horizontal
        if(cDetect(xpos,ypos,35,35,carX, carY, 150,67) == 1 && godMod == false)
        {
            //Mix_PlayChannel(2, crash, 0);
            Mix_PlayChannel(getAudioChannel(), splatsound, 0);
            lives--;
            DrawIMG(back,0,0);
            bloodLenght++;
            bloodX[bloodLenght] = xpos;
            bloodY[bloodLenght] = ypos;
            // DrawIMG(back,0,0);
            godModStart = time(NULL);
            godMod = true;
        }
    }
    else {
        //car is driving vertical
        if(cDetect(xpos,ypos,35,35,carX, carY, 65,140) == 1 && godMod == false)
        {
            // make a nice splatting noiseMix_PlayChannel(2, crash, 0);
            lives--;
            DrawIMG(back,0,0);
            Mix_PlayChannel(getAudioChannel(), splatsound, 0);
            bloodLenght++;
            bloodX[bloodLenght] = xpos;
            bloodY[bloodLenght] = ypos;
            // DrawIMG(back,0,0);
            godModStart = time(NULL);
            godMod = true;
        }
    }
    //if the random car time has passed and car has left screen
    if(cartime - time(NULL) <= 0 && carOutOfScreen() == true)
    {
        int carcolor = random_max(4);
        carangle = random_max(4);
        Mix_PlayChannel(getAudioChannel(), cardriving, 0);
        carSPlayed = false;
        if(carangle == 1 || carangle == 0)
        {
            if(carcolor == 1)
            car = blueleft;
            else if(carcolor == 2)
            car = greenleft;
            else car = redleft;
            carX = 1025;
            int carY = 322;
            cartime = time(NULL) + random_max(10);
        }
        else
        if(carangle == 2)
        {
            if(carcolor == 1)
            car = blueright;
            else if(carcolor == 2)
            car = greenright;
            else car = redright;
            carX = -200;
            carY = 405;
            cartime = time(NULL) + random_max(10);
        }
        else
        if(carangle == 3)
        {
            if(carcolor == 1)
            car = bluedown;
            else if(carcolor == 2)
            car = greendown;
            else car = reddown;
            carX = 433;
            carY = -200;
            cartime = time(NULL) + random_max(10);
        }
        else
        if(carangle == 4)
        {
            if(carcolor == 1)
            car = blueup;
            else if(carcolor == 2)
            car = greenup;
            else car = redup;
            carX = 520;
            carY = 1000;
            cartime = time(NULL) + random_max(10);
        }
    }
    if(carangle == 0 || carangle == 1) carX += -2*car_movementvalue;
    else if(carangle == 2) carX += 2*car_movementvalue;
    else if(carangle == 3) carY += 2*car_movementvalue;
    else carY -= 2*car_movementvalue;
    DrawIMG(car,carX,carY);
    DrawIMG(topbar,0,0);
    //DrawNumber(intToString(time(NULL)));
    DrawNumber(intToString(score));
    if(lives >= 1) DrawIMG(point, 935, 7);
    if(lives >= 2) DrawIMG(point, 960, 7);
    if(lives >= 3) DrawIMG(point, 985, 7);
    /* char *str;
    int adas=567;
    str=itoa(adas, str, 10);
    */
    //DrawIMG(back, 5, 768, 100,100,5,768);
    //drawString(screen,font2,5,5,"%d",tempfps);
    SDL_Flip(screen);
}
int main(int argc, char *argv[])
{
    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
    int audio_channels = 8;
    int audio_buffers = 4096;
    newAI();
    int done=0;
    Uint8* keys;
    if ( SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0 )
    {
        printf("Unable to init SDL: %s\n", SDL_GetError());
        exit(1);
    }
    if(Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048)) {
        printf("Unable to open audio!\n");
        exit(1);
    }
    cardriving = Mix_LoadWAV("data\\sound\\cardriving.wav");
    music = Mix_LoadMUS("data\\sound\\theme.wav");
    fart = Mix_LoadWAV("data\\sound\\fart.wav");
    honk1 = Mix_LoadWAV("data\\sound\\honk1.wav");
    honk2 = Mix_LoadWAV("data\\sound\\honk2.wav");
    crash2 = Mix_LoadWAV("data\\sound\\crash2.wav");
    crash3 = Mix_LoadWAV("data\\sound\\crash3.wav");
    crash = Mix_LoadWAV("data\\sound\\crash.wav");
    splatsound = Mix_LoadWAV("data\\sound\\splat.wav");
    Mix_PlayMusic(music, -1);
    atexit(SDL_Quit);
    screen=SDL_SetVideoMode(1024,768,32,SDL_SWSURFACE|SDL_FULLSCREEN);
    if ( screen == NULL )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        exit(1);
    }
    Mix_FadeInMusic(music, 100, 10000);
    SDL_ShowCursor(0);
    int showBks = 0;
    if(showBks == 0) DrawIMG(SDL_LoadBMP("data\\bks.bmp"), 0,0);
    SDL_Flip(screen);
    SDL_Event event2;
    SDL_Event a;
    SDL_Event go;
    while(showBks == 0)
    {
        while ( SDL_PollEvent(&event2) )
        {
            if ( event2.type == SDL_KEYDOWN )
            {
                if ( event2.key.keysym.sym == SDLK_ESCAPE || event2.key.keysym.sym == SDLK_RETURN ) {
                    showBks = 2;
                }
            }
        }
    }
    BKSmenu menu(screen);
    menu.Draw();
    SDL_Flip(screen);
    if(menu.isDone() == true){
        if(menu.killGame == true) done = 1;
        InitImages();
        if(menu.killGame != true)DrawBG();
        if(menu.killGame != true) DrawApple();
        xpos = 500;
        ypos = 350;
        tempfps = 120;
        int testTime = time(NULL) + 1;
        timer = SDL_GetTicks();
        car_timer = SDL_GetTicks();
        cartime = time(NULL) + 15;
        int carcolor = random_max(4);
        carangle = random_max(4);
        carSPlayed = true;
        if(carangle == 1 || carangle == 0)
        {
            if(carcolor == 1)
            car = blueleft;
            else if(carcolor == 2)
            car = greenleft;
            else car = redleft;
            carX = 1025;
            int carY = 322;
            cartime = time(NULL) + 20;
        }
        else
        if(carangle == 2)
        {
            if(carcolor == 1)
            car = blueright;
            else if(carcolor == 2)
            car = greenright;
            else car = redright;
            carX = -200;
            carY = 405;
            cartime = time(NULL) + 20;
        }
        else
        if(carangle == 3)
        {
            if(carcolor == 1)
            car = bluedown;
            else if(carcolor == 2)
            car = greendown;
            else car = reddown;
            carX = 433;
            carY = -200;
            cartime = time(NULL) + 20;
        }
        else
        if(carangle == 4)
        {
            if(carcolor == 1)
            car = blueup;
            else if(carcolor == 2)
            car = greenup;
            else car = redup;
            carX = 520;
            carY = 1000;
            cartime = time(NULL) + 20;
        }
        carX = -999999;
        carY = -9991000;
        while(done == 0)
        {
            if(menu.killGame == true) {
                done = 1; break;
            }
            //first determine how many seconds elapsed
            timerdiff = SDL_GetTicks()-timer;
            //now compute the movement value
            movementvalue = (double)(d_speed*timerdiff);
            
            movementvaluescooter = (double)(scooterspeed*secsperframe);
            
            //get the new time
            timer = SDL_GetTicks();
            /* CAR STUFF START */
            car_timerdiff = SDL_GetTicks()-car_timer;
            //the function reads in milliseconds so convert to seconds by dividing by 1000
            car_secsperframe =(double)(car_timerdiff/1000.0);
            //now compute the movement value
            car_movementvalue = (double)(car_speed*car_secsperframe);
            //get the new time
            car_timer = SDL_GetTicks();
            /* CAR STUFF END */
            if(time(NULL) < testTime )
            {
                fps++;
                drawfps = true;
            }
            else {
                tempfps = fps;
                fps = 0;
                testTime = time(NULL) + 1;
                drawfps = true;
            }
            if(lives == -1)
            {
                //if death has occured restart the game
                //ToDo: Funny "Game Over" screen.
                gamePaused = true;
                DrawIMG(back,0,0);
                oldscore = score;
                score = 0;
                lives = 3;
                xpos = 500;
                int carX = 1020;
                carY = 322;
                cartime = time( NULL ) + 15;
                ypos = 350;
                totalAI = -1;
                newAI();
            }
            if(gamePaused == false && stopGame == false)
            {
                SDL_Event event;
                while ( SDL_PollEvent(&event) )
                {
                    if ( event.type == SDL_QUIT ) {
                        done = 1;
                    }
                    if ( event.type == SDL_KEYDOWN )
                    {
                        if ( event.key.keysym.sym == SDLK_ESCAPE ) {
                            stopGame = true;
                        }
                    }
                }
                keys = SDL_GetKeyState(NULL);
                if ( keys[SDLK_UP] && collideTopWall() == true ) {
                    if(monster == true)
                        image = SDL_LoadBMP("data\\monster\\up.bmp");
                    else
                        image = SDL_LoadBMP("data\\hero\\up.bmp");

                    if(monster == true)
                        SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 255, 18, 255) );
                    else 
                        SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 255, 0, 255) );

                    if(monster == true)
                        DrawIMG(back, xpos, ypos, 150, 150, xpos, ypos);
                    else
                        DrawIMG(back, xpos, ypos, 42, 42, xpos, ypos); 

                    ypos -= (int)movementvalue;

                   
                }
                if ( keys[SDLK_DOWN] && collideBottomWall() == true ) {
                    if(monster == true) image = SDL_LoadBMP("data\\monster\\down.bmp"); else image = SDL_LoadBMP("data\\hero\\down.bmp"); if(monster == true) SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 255, 18, 255) ); else SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 255, 0, 255) ); if(monster == true) DrawIMG(back, xpos, ypos, 150, 150, xpos, ypos); else DrawIMG(back, xpos, ypos, 42, 42, xpos, ypos); ypos += (int)movementvalue; 
                }
                if ( keys[SDLK_LEFT] && collideLeftWall() == true ) {
                    if(monster == true) image = SDL_LoadBMP("data\\monster\\left.bmp"); else image = SDL_LoadBMP("data\\hero\\left.bmp"); if(monster == true) SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 255, 18, 255) ); else SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 255, 0, 255) ); if(monster == true) DrawIMG(back, xpos, ypos, 150, 150, xpos, ypos); else DrawIMG(back, xpos, ypos, 42, 42, xpos, ypos); xpos -= (int)movementvalue; 
                }
                if ( keys[SDLK_RIGHT] && collideRightWall() == true) {
                    if(monster == true) image = SDL_LoadBMP("data\\monster\\right.bmp"); else image = SDL_LoadBMP("data\\hero\\right.bmp"); if(monster == true) SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 255, 18, 255) ); else SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 255, 0, 255) ); if(monster == true) DrawIMG(back, xpos, ypos, 150, 150, xpos, ypos); else DrawIMG(back, xpos, ypos, 42, 42, xpos, ypos); xpos += (int)movementvalue; 
                }
                if ( keys[SDLK_UP] && keys[SDLK_RIGHT] && collideTopWall() == true && collideRightWall() == true){
                    if(monster == true) image = SDL_LoadBMP("data\\monster\\rightup.bmp"); else image = SDL_LoadBMP("data\\hero\\rightup.bmp"); if(monster == true) SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 255, 18, 255) ); else SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 255, 0, 255) ); if(monster == true) DrawIMG(back, xpos, ypos, 150, 150, xpos, ypos); else DrawIMG(back, xpos-2, ypos-2, 42, 42, xpos-2, ypos-2);
                }
                if ( keys[SDLK_UP] && keys[SDLK_LEFT] && collideTopWall() == true && collideLeftWall() == true){
                    if(monster == true) image = SDL_LoadBMP("data\\monster\\leftup.bmp"); else image = SDL_LoadBMP("data\\hero\\leftup.bmp"); if(monster == true) SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 255, 18, 255) ); else SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 255, 0, 255) ); if(monster == true) DrawIMG(back, xpos, ypos, 150, 150, xpos, ypos); else DrawIMG(back, xpos-2, ypos-2, 42, 42, xpos-2, ypos-2);
                }
                if ( keys[SDLK_DOWN] && keys[SDLK_RIGHT] && collideBottomWall() == true && collideRightWall() == true){
                    if(monster == true) image = SDL_LoadBMP("data\\monster\\rightdown.bmp"); else image = SDL_LoadBMP("data\\hero\\rightdown.bmp"); if(monster == true) SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 255, 18, 255) ); else SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 255, 0, 255) ); if(monster == true) DrawIMG(back, xpos, ypos, 150, 150, xpos, ypos); else DrawIMG(back, xpos-2, ypos-2, 42, 42, xpos-2, ypos-2);
                }
                if ( keys[SDLK_DOWN] && keys[SDLK_LEFT] && collideBottomWall() == true && collideLeftWall() == true){
                    if(monster == true) image = SDL_LoadBMP("data\\monster\\leftdown.bmp"); else image = SDL_LoadBMP("data\\hero\\leftdown.bmp"); if(monster == true) SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 255, 18, 255) ); else SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 255, 0, 255) ); if(monster == true) DrawIMG(back, xpos, ypos, 150, 150, xpos, ypos); else DrawIMG(back, xpos-2, ypos-2, 42, 42, xpos-2, ypos-2);
                }
                if(collideApple())
                {
                    //Do we have a collision!??! MAN I OWN!!
                    Mix_PlayChannel(1, fart, 0);
                    clearApple();
                    clearScore();
                    score++;
                    DrawApple();

                    if(score%50 == 0)
                        totalSpawn++;

                    if(score%10 == 0)
                    {
                        for(int i = 0; i < totalSpawn; i++)
                            newAI();
                    }

                    
                        
                    
                }
                DrawScene();
            }
            else {
                while(stopGame == true)
                {
                    DrawIMG(exitgame,312,234);
                    while ( SDL_PollEvent(&go) )
                    {
                        if ( go.type == SDL_KEYDOWN )
                        {
                            if ( go.key.keysym.sym == SDLK_RETURN ) {
                                menu.Draw();
                                godModStart = time(NULL);
                                DrawIMG(back,0,0);
                                stopGame = false;
                                totalSpawn = 1;
                                xpos = 500;
                                ypos = 350;
                                bloodLenght = -1;
                                totalDeadGuys = -1;
                                score = 0;
                                score = 0;
                                lives = 3;
                                xpos = 500;
                                carX = 1020;
                                carY = 322;
                                cartime = time( NULL ) + 15;
                                ypos = 350;
                                totalAI = -1;
                                newAI();
                                stopGame = false;
                                // DrawIMG(gameover,312,234);
                                DrawIMG(back,0,0);
                                SDL_Flip(screen);
                            }
                            if ( go.key.keysym.sym == SDLK_ESCAPE) {
                                stopGame = false;
                                DrawIMG(back,0,0);
                            }
                        }
                    }
                    /*
                    menu.Draw();
                    DrawIMG(back,0,0);
                    */
                    SDL_Flip(screen);
                }
                if(gamePaused == true)
                {
                    DrawBG();
                    totalSpawn = 1;
                    bloodLenght = -1;
                    totalDeadGuys = -1;
                    DrawNumber(intToString(oldscore));
                    if(beatHighscore(oldscore) != -1)
                    DrawIMG(beathighscore,312,234); else
                    DrawIMG(gameover,312,234);
                    //LETS SAY THE HIGH SCORE IS BEAT
                    if(beatHighscore(oldscore) != -1) drawString(screen,font1,340,380,"You are now #%s on the list!",stringToChar(intToString(beatHighscore(oldscore))));
                    if(beatHighscore(oldscore) != -1) drawString(screen,font1,415,445,"%s",stringToChar(my_entry));
                    //END OF SUPERFICIAL THINGY
                    while ( SDL_PollEvent(&go) )
                    {
                        if ( go.type == SDL_KEYDOWN )
                        {
                            if(beatHighscore(oldscore) != -1)
                            {
                                if ( go.key.keysym.sym == SDLK_BACKSPACE ) {
                                    my_entry = my_entry.substr(0,my_entry.length()-1); DrawBG(); if(beatHighscore(oldscore) != -1) DrawIMG(beathighscore,312,234); else
                                    DrawIMG(gameover,312,234);
                                }
                                if ( go.key.keysym.sym == SDLK_q && my_entry.length() <= 9) {
                                    my_entry.append("Q");
                                }
                                if ( go.key.keysym.sym == SDLK_a && my_entry.length() <= 9) {
                                    my_entry.append("A");
                                }
                                if ( go.key.keysym.sym == SDLK_w && my_entry.length() <= 9) {
                                    my_entry.append("W");
                                }
                                if ( go.key.keysym.sym == SDLK_e && my_entry.length() <= 9) {
                                    my_entry.append("E");
                                }
                                if ( go.key.keysym.sym == SDLK_r && my_entry.length() <= 9) {
                                    my_entry.append("R");
                                }
                                if ( go.key.keysym.sym == SDLK_t && my_entry.length() <= 9) {
                                    my_entry.append("T");
                                }
                                if ( go.key.keysym.sym == SDLK_y && my_entry.length() <= 9) {
                                    my_entry.append("Y");
                                }
                                if ( go.key.keysym.sym == SDLK_u && my_entry.length() <= 9) {
                                    my_entry.append("U");
                                }
                                if ( go.key.keysym.sym == SDLK_i && my_entry.length() <= 9) {
                                    my_entry.append("I");
                                }
                                if ( go.key.keysym.sym == SDLK_o && my_entry.length() <= 9) {
                                    my_entry.append("O");
                                }
                                if ( go.key.keysym.sym == SDLK_p && my_entry.length() <= 9) {
                                    my_entry.append("P");
                                }
                                if ( go.key.keysym.sym == SDLK_s && my_entry.length() <= 9) {
                                    my_entry.append("S");
                                }
                                if ( go.key.keysym.sym == SDLK_d && my_entry.length() <= 9) {
                                    my_entry.append("D");
                                }
                                if ( go.key.keysym.sym == SDLK_f && my_entry.length() <= 9) {
                                    my_entry.append("F");
                                }
                                if ( go.key.keysym.sym == SDLK_g && my_entry.length() <= 9) {
                                    my_entry.append("G");
                                }
                                if ( go.key.keysym.sym == SDLK_h && my_entry.length() <= 9) {
                                    my_entry.append("H");
                                }
                                if ( go.key.keysym.sym == SDLK_j && my_entry.length() <= 9) {
                                    my_entry.append("J");
                                }
                                if ( go.key.keysym.sym == SDLK_k && my_entry.length() <= 9) {
                                    my_entry.append("K");
                                }
                                if ( go.key.keysym.sym == SDLK_l && my_entry.length() <= 9) {
                                    my_entry.append("L");
                                }
                                if ( go.key.keysym.sym == SDLK_z && my_entry.length() <= 9) {
                                    my_entry.append("Z");
                                }
                                if ( go.key.keysym.sym == SDLK_x && my_entry.length() <= 9) {
                                    my_entry.append("X");
                                }
                                if ( go.key.keysym.sym == SDLK_c && my_entry.length() <= 9) {
                                    my_entry.append("C");
                                }
                                if ( go.key.keysym.sym == SDLK_v && my_entry.length() <= 9) {
                                    my_entry.append("V");
                                }
                                if ( go.key.keysym.sym == SDLK_b && my_entry.length() <= 9) {
                                    my_entry.append("B");
                                }
                                if ( go.key.keysym.sym == SDLK_n && my_entry.length() <= 9) {
                                    my_entry.append("N");
                                }
                                if ( go.key.keysym.sym == SDLK_m && my_entry.length() <= 9) {
                                    my_entry.append("M");
                                }
                            }
                            if ( go.key.keysym.sym == SDLK_RETURN ) {
                                xpos = 500;
                                ypos = 350; if(beatHighscore(oldscore) != -1) {
                                    godModStart = time(NULL); setscore(beatHighscore(oldscore), oldscore, my_entry);
                                }
                                gamePaused = false; cartime = time(NULL) + random_max(10); DrawIMG(back,0,0);
                            }
                            if ( go.key.keysym.sym == SDLK_ESCAPE) {
                                totalSpawn = 1;
                                menu.Draw();
                                bloodLenght = -1;
                                totalDeadGuys = -1;
                                score = 0;
                                cartime = time(NULL) + 15;
                                godModStart = time(NULL);
                                stopGame = false;
                                xpos = 500;
                                ypos = 350;
                                // DrawIMG(gameover,312,234);
                                DrawIMG(back,0,0);
                                SDL_Flip(screen);
                            }
                        }
                    }
                    //DrawIMG(gameover,312,234);
                    //drawString(screen,font1,353,300,"%s",stringToChar(intToString(beatHighscore(oldscore))));
                    SDL_Flip(screen);
                }
            }
        }
    }
    int melikes = 1;
    SDL_Flip(screen);
    int cy = 768;
    while(melikes == 1)
    {
        DrawIMG(blackbg, 0,0);
        DrawIMG(credits, 220, cy);
        SDL_Event event;
        while ( SDL_PollEvent(&event) )
        {
            if ( event.type == SDL_QUIT ) {
                melikes = 0;
            }
            if ( event.type == SDL_KEYDOWN )
            {
                if ( event.key.keysym.sym == SDLK_ESCAPE ) {
                    melikes = 0;
                }
                if ( event.key.keysym.sym == SDLK_RETURN ) {
                    melikes = 0;
                }
            }
        }
        cy-= 1;
        if(cy < -1130) cy = 768;
        SDL_Flip(screen);
    }
    freeFont(font1);
    // freeFont(font2);
    Mix_FreeChunk(honk2);
    Mix_FreeChunk(honk1);
    Mix_FreeChunk(fart);
    Mix_FreeChunk(crash);
    Mix_FreeChunk(crash2);
    Mix_FreeChunk(crash3);
    Mix_FreeMusic(music);
    Mix_FreeChunk(splatsound);
    Mix_FreeChunk(cardriving);
    return 0;
}
