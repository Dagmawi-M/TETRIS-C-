
/*
     HiLCoE School of Computer Science & Technology
          Problem Solving with Proramming
          Assignment on Tetris

     Start-up code developed by
     DAGMAWI MEKONNEN
     DAGMAWI KINDU
     DAGMAWI ZINAHBIZU

     Winter 2016
*/
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <ctype.h>
#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include <time.h>
#include <sstream>  // for string streams
#include <fstream>


const int NB_BLOCKS = 5;
const int BAR_BLOCK = 2;
const int T_BLOCK   = 1;
const int L_BLOCK   = 5;
const int LR_BLOCK  = 4;
const int BOX_BLOCK = 3;
const int HORIZONTAL = 1;
const int VERTICAL = 2;
const int NORTH = 1;
const int EAST = 2;
const int WEST = 3;
const int SOUTH = 4;
const int RIGHT = 1;
const int LEFT = 2;
const int DOWN  = 3;

const int BOARD_COLOR   = BLACK;
const int BKGRD_COLOR   = BOARD_COLOR;
const int FILLING_COLOR = GREEN; //LIGHTGRAY;
const int FRGRD_COLOR   = 1; //CYAN; //BLUE; //GREEN; //RED; // LIGHTGRAY;
// const int FRGRD_COLOR   = BOARD_COLOR; //FILLING_COLOR;
const int GRID_COLOR    = BLACK;
const int BORDER_COLOR  = GRID_COLOR;

int LEVEL1_SPEED = 300;

const int BOARDWIDTH 	= 180;
const int BOARDHEIGHT	= 240;
const int NB_ROWS  	= 15;
const int NB_COLS  	= 10;
const int CELL_SIZE	= BOARDHEIGHT/(NB_ROWS+1);
const int LEFTCORNER	= (640 - (CELL_SIZE*(NB_COLS+2)))/2; //230;
const int TOPCORNER	= 120;
const int INFOAREAWIDTH	= 600;
const int INFOAREAHEIGHT= 105;
const int INFOAREALEFT	= 20;
const int INFOAREATOP	= 370;
const int SCOREAREATOP	= 150;
const int SCOREAREALEFT	= 20;
const int SCOREWIDTH=120;
const int SCOREHEIGHT=25;

const int HIGHSCOREAREAWIDTH	= 350;
const int HISHSCOREAREAHEIGHT= 180;
const int HIGHSCOREAREALEFT	= 120;
const int HIGHSCOREAREATOP	= 370;

const int SHOWBLOCKAREATOP=TOPCORNER+100;
const int SHOWBLOCKAREALEFT=LEFTCORNER+200;
const int SHOWBLOCKWIDTH=90;
const int SHOWBLOCKHEIGHT=90;
const int SPEEDAREATOP=SCOREAREATOP-30;
const int SPEEDAREALEFT=20;


const int LEFTARROW=75;
const int RIGHTARROW=77;
const int UPARROW=72;
const int DOWNARROW=80;
const int ENTER=13;
const int ESC=27;
const int SPACE=32;
const int PLUS=43;
const int MINUS=45;

int Highscore=0;

//initializes graphics driver
void initGraphEngine()
{
    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, "...\\BGI");
}

void displayInfo(char *msg)
{
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, YELLOW);
    bar(INFOAREALEFT+1,INFOAREATOP+100,INFOAREALEFT+INFOAREAWIDTH,INFOAREATOP+INFOAREAHEIGHT-1);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1.5);
    outtextxy(INFOAREALEFT+30,INFOAREATOP+50,msg);
}

void ScoreInfo(char *msg){
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, BLACK);
    //bar(SCOREAREALEFT+1,SCOREAREATOP+15,SCOREAREALEFT+SCOREWIDTH,SCOREAREATOP+SCOREAREATOP-1);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1.5);
    outtextxy(SCOREAREALEFT+3,SCOREAREATOP+7,msg);}
void scoree(char *msg){
 setcolor(WHITE);
 settextstyle(DEFAULT_FONT, HORIZ_DIR, 1.9);
  outtextxy(SCOREAREALEFT+60,SCOREAREATOP+7,msg);
}
void nextBlockInfo(char *msg){
    setfillstyle(SOLID_FILL, BLACK);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1.0);
    outtextxy(SHOWBLOCKAREALEFT+9,SHOWBLOCKAREATOP-20,msg);}

void speed(char *msg){
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1.9);
    outtextxy(SPEEDAREALEFT+60,SPEEDAREATOP+7,msg);}

void speedTabInfo(char *msg){
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, BLACK);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1.6);
    outtextxy(SPEEDAREALEFT+3,SPEEDAREATOP+7,msg);}

void clearDisplayArea(){
    setfillstyle(SOLID_FILL, BLACK);
    bar(LEFTCORNER+CELL_SIZE,0,(LEFTCORNER+BOARDWIDTH-CELL_SIZE),TOPCORNER-1);}

void backGround(){
    setfillstyle(SOLID_FILL, BLUE);
    bar(0,0,(LEFTCORNER+640),TOPCORNER+720);}

void fillGrid(){
    int x = LEFTCORNER+CELL_SIZE,  y = TOPCORNER;
    setcolor(GRID_COLOR);
    for(int i=1; i<=NB_ROWS; i++)
    {
        for (int j=1; j<=NB_COLS; j++)
        {
            rectangle(x,y,x+CELL_SIZE,y+CELL_SIZE);
            x+=CELL_SIZE;
        }
        x=LEFTCORNER+CELL_SIZE;
        y+=CELL_SIZE;
    }
}

void drawWelcomeScreen(char *msg )
{
   // setfillstyle(SOLID_FILL, BLUE);
   // bar(LEFTCORNER,TOPCORNER,LEFTCORNER+640,TOPCORNER+720);
      setfillstyle(SOLID_FILL, BLACK);
    bar(INFOAREALEFT,INFOAREATOP-200,INFOAREALEFT+INFOAREAWIDTH,INFOAREATOP-200+INFOAREAHEIGHT);
    rectangle(INFOAREALEFT,INFOAREATOP-200,INFOAREALEFT+INFOAREAWIDTH,INFOAREATOP-200+INFOAREAHEIGHT);
//circle(INFOAREALEFT+300,SHOWBLOCKAREATOP+5,100);
 setfillstyle(SOLID_FILL, BLUE);
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 6.0);
      outtextxy(INFOAREALEFT+150,SHOWBLOCKAREATOP-130,"TETRIS");
      settextstyle(DEFAULT_FONT, HORIZ_DIR, 3.0);
      outtextxy(INFOAREALEFT+430,SHOWBLOCKAREATOP-130,"V2");
     // circle(INFOAREALEFT+460,SHOWBLOCKAREATOP-115,25);

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2.0);
        outtextxy(INFOAREALEFT+250,SHOWBLOCKAREATOP-10,msg);//play
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1.5);
    outtextxy(INFOAREALEFT+190,SHOWBLOCKAREATOP+10,"[PRESS ANY KEY TO START]");

      settextstyle(DEFAULT_FONT, HORIZ_DIR, 1.8);
    outtextxy(INFOAREALEFT+50,SHOWBLOCKAREATOP+100,"DAGMAWI MEKONNEN");

 settextstyle(DEFAULT_FONT, HORIZ_DIR, 1.8);
    outtextxy(INFOAREALEFT+250,SHOWBLOCKAREATOP+100,"DAGMAWI KINDU");

     settextstyle(DEFAULT_FONT, HORIZ_DIR, 1.8);
    outtextxy(INFOAREALEFT+440,SHOWBLOCKAREATOP+100,"DAGMAWI ZINAHBIZU");


}
void clearwelcomescreen(){
    setfillstyle(SOLID_FILL, BLACK);
    bar(0,0,(LEFTCORNER+640),TOPCORNER+720);}

void drawBoard()
{
// Playing Board
    setfillstyle(SOLID_FILL, BLUE);
    bar(LEFTCORNER,TOPCORNER,LEFTCORNER+BOARDWIDTH,TOPCORNER+BOARDHEIGHT);
    setfillstyle(SOLID_FILL, BOARD_COLOR);
    bar(LEFTCORNER+CELL_SIZE,TOPCORNER,(LEFTCORNER+BOARDWIDTH-CELL_SIZE),(TOPCORNER+BOARDHEIGHT-CELL_SIZE));
    fillGrid();

// Display Area
    setfillstyle(SOLID_FILL, BLUE);
    bar(INFOAREALEFT,INFOAREATOP,INFOAREALEFT+INFOAREAWIDTH,INFOAREATOP+INFOAREAHEIGHT);
    rectangle(INFOAREALEFT,INFOAREATOP,INFOAREALEFT+INFOAREAWIDTH,INFOAREATOP+INFOAREAHEIGHT);

//Score Area
setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLACK);
    bar(SCOREAREALEFT,SCOREAREATOP,SCOREAREALEFT+SCOREWIDTH,SCOREAREATOP+SCOREHEIGHT);
    rectangle (SCOREAREALEFT,SCOREAREATOP,SCOREAREALEFT+SCOREWIDTH,SCOREAREATOP+SCOREHEIGHT);

//show block area
rectangle (SHOWBLOCKAREALEFT,SHOWBLOCKAREATOP,SHOWBLOCKAREALEFT+SHOWBLOCKWIDTH,SHOWBLOCKAREATOP+SHOWBLOCKHEIGHT);

//speed block area
rectangle (SPEEDAREALEFT,SPEEDAREATOP,SPEEDAREALEFT+SCOREWIDTH,SPEEDAREATOP+25);

//Playing Manual Area
setcolor(WHITE);
 outtextxy(SPEEDAREALEFT+4,SPEEDAREATOP+100-13,"PLAYING MANUAL");
 setcolor(BLUE);
rectangle (SPEEDAREALEFT,SPEEDAREATOP+100,SPEEDAREALEFT+SCOREWIDTH,SPEEDAREATOP+209);
rectangle (SPEEDAREALEFT+25,SPEEDAREATOP+100+10,SPEEDAREALEFT+25+10,SPEEDAREATOP+100+10+10); //UA
 // settextstyle(DEFAULT_FONT, HORIZ_DIR, 0.5);
 setcolor(WHITE);
     outtextxy(SPEEDAREALEFT+25+2,SPEEDAREATOP+100+10+3,"^");
rectangle (SPEEDAREALEFT+25,SPEEDAREATOP+100+22,SPEEDAREALEFT+25+10,SPEEDAREATOP+100+22+10); //DA

rectangle (SPEEDAREALEFT+25+12,SPEEDAREATOP+100+22,SPEEDAREALEFT+25+22,SPEEDAREATOP+100+22+10); //RA
  outtextxy(SPEEDAREALEFT+25+12+2,SPEEDAREATOP+100+22+3,">");
rectangle (SPEEDAREALEFT+25-12,SPEEDAREATOP+100+22,SPEEDAREALEFT+25+10-12,SPEEDAREATOP+100+22+10); //LA
 outtextxy(SPEEDAREALEFT+25-12,SPEEDAREATOP+100+22+3,"<");
 outtextxy(SPEEDAREALEFT+25+12+18,SPEEDAREATOP+100+22+3,"Movement");

rectangle (SPEEDAREALEFT+25-8,SPEEDAREATOP+100+22+22,SPEEDAREALEFT+25+20,SPEEDAREATOP+100+22+10+26); //PLUS-SPEED
 outtextxy(SPEEDAREALEFT+25-8+10,SPEEDAREATOP+100+22+22+1,"+");
  outtextxy(SPEEDAREALEFT+25+10+18,SPEEDAREATOP+100+22+22+1,"Speed +");


rectangle (SPEEDAREALEFT+25-8,SPEEDAREATOP+100+22+42,SPEEDAREALEFT+25+20,SPEEDAREATOP+100+22+10+47); //MINUS-SPEED
 outtextxy(SPEEDAREALEFT+25-8+10,SPEEDAREATOP+100+22+42+3,"-");
  outtextxy(SPEEDAREALEFT+25+10+18,SPEEDAREATOP+100+22+42+1,"Speed -");

 rectangle (SPEEDAREALEFT+25-8,SPEEDAREATOP+100+22+62,SPEEDAREALEFT+25+20,SPEEDAREATOP+100+22+62+15); //pause
 outtextxy(SPEEDAREALEFT+25-8+3,SPEEDAREATOP+100+22+62+2,"Alt");
  outtextxy(SPEEDAREALEFT+25+10+18,SPEEDAREATOP+100+22+62+1,"Pause");
}
void Gameoverscreen(char *msg)
{

    setfillstyle(SOLID_FILL, BLACK);
    bar(HIGHSCOREAREALEFT,HIGHSCOREAREATOP-200,HIGHSCOREAREALEFT+HIGHSCOREAREAWIDTH,HIGHSCOREAREATOP-200+HISHSCOREAREAHEIGHT);
    rectangle(HIGHSCOREAREALEFT,HIGHSCOREAREATOP-200,HIGHSCOREAREALEFT+HIGHSCOREAREAWIDTH,HIGHSCOREAREATOP-200+HISHSCOREAREAHEIGHT);

    setcolor( YELLOW );
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 4.0);
     outtextxy(HIGHSCOREAREALEFT+5,HIGHSCOREAREATOP-250,msg);//SCOREBOARD


     setcolor(WHITE);
     rectangle(HIGHSCOREAREALEFT+20,HIGHSCOREAREATOP-150,HIGHSCOREAREALEFT+20+100,HIGHSCOREAREATOP-150+20);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1.0);
    outtextxy(HIGHSCOREAREALEFT+20+10,HIGHSCOREAREATOP-150+5,"YOUR SCORE");
    outtextxy(HIGHSCOREAREALEFT+20+100+5,HIGHSCOREAREATOP-150+5,".................");//.........
      settextstyle(DEFAULT_FONT, HORIZ_DIR, 1.0);//FOR THE HIGHSCORE NUMBER
     outtextxy(HIGHSCOREAREALEFT+20+10,HIGHSCOREAREATOP-90+5,"HIGHSCORE");//PASSED FROM SCORE VARIABLE

    rectangle(HIGHSCOREAREALEFT+20,HIGHSCOREAREATOP-90,HIGHSCOREAREALEFT+20+100,HIGHSCOREAREATOP-90+20);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1.0);
   // outtextxy(HIGHSCOREAREALEFT+20+3,HIGHSCOREAREATOP-90+5," HIGHSCORE");
     outtextxy(HIGHSCOREAREALEFT+20+100+5,HIGHSCOREAREATOP-90+5,".................");//..........
}

void highscore(char *Highscore,char *Yourscore)
{
     setcolor( YELLOW );
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2.0);
    outtextxy(HIGHSCOREAREALEFT+20+100+5+145,HIGHSCOREAREATOP-150+5,Yourscore);//Your_score

    outtextxy(HIGHSCOREAREALEFT+20+100+5+145,HIGHSCOREAREATOP-90+5,Highscore);  // High_score
}

void reDrawCellsGrid(int xLeft, int yTop, int nbCells, int orientation)
{
    // redraw the grid of cells
    int i;
    setcolor(BORDER_COLOR);
    for (i=1; i<=nbCells; i++)
    {
        rectangle(xLeft, yTop, xLeft+CELL_SIZE, yTop+CELL_SIZE);
        if (orientation == HORIZONTAL)  xLeft=xLeft+CELL_SIZE;
        else yTop = yTop + CELL_SIZE;
    }
}

//*******************************************************************************************************************************************
//******************************************************************** /  DRAWING BLOCKS  / *************************************************************************
//*******************************************************************************************************************************************

//DRAWS BAR BLOCK
void drawBarBlock(int xLeft, int yTop, int orientation, int fillingColor)
{
    setfillstyle(SOLID_FILL, fillingColor);
    if (orientation==HORIZONTAL)
    {
        bar(xLeft, yTop, xLeft+4*CELL_SIZE,yTop+CELL_SIZE);
        reDrawCellsGrid(xLeft, yTop, 4, HORIZONTAL);
    }
    else   // orientation is VERTICAL
    {
        bar(xLeft, yTop, xLeft+CELL_SIZE, yTop+4*CELL_SIZE);
        reDrawCellsGrid(xLeft, yTop ,4, VERTICAL);
    }
}
//DRAWS BOX BLOCK
void drawBoxBlock(int xLeft, int yTop ,int fillingColor)
{
    int orientation=HORIZONTAL;
    setfillstyle(SOLID_FILL, fillingColor);
    bar(xLeft, yTop, xLeft+2*CELL_SIZE,yTop+2*CELL_SIZE );
    reDrawCellsGrid(xLeft, yTop, 2 , orientation);
    reDrawCellsGrid(xLeft, yTop+CELL_SIZE, 2 , orientation);
}
//DRAWS T BLOCK
void drawT_Block(int xLeft, int yTop, int orientation,int fillingColor)
{
     setfillstyle(SOLID_FILL, fillingColor);
    if (orientation==NORTH)
    {
        bar(xLeft+CELL_SIZE,yTop,xLeft+2*CELL_SIZE,yTop+CELL_SIZE);
        bar(xLeft,yTop+CELL_SIZE,xLeft+3*CELL_SIZE,yTop+2*CELL_SIZE);

        reDrawCellsGrid(xLeft+CELL_SIZE, yTop, 1, NORTH);
        reDrawCellsGrid(xLeft, yTop+CELL_SIZE, 3, NORTH);
    }
    else if (orientation == EAST)
    {
        bar(xLeft,yTop,xLeft+CELL_SIZE,yTop+3*CELL_SIZE);
        bar(xLeft+CELL_SIZE,yTop+CELL_SIZE,xLeft+2*CELL_SIZE,yTop+2*CELL_SIZE);

        reDrawCellsGrid(xLeft+CELL_SIZE, yTop+CELL_SIZE, 1, EAST);
        reDrawCellsGrid(xLeft, yTop, 3, EAST);
    }
    else if (orientation == WEST)
    {
        bar(xLeft,yTop+CELL_SIZE,xLeft+CELL_SIZE,yTop+2*CELL_SIZE);
        bar(xLeft+CELL_SIZE,yTop,xLeft+2*CELL_SIZE,yTop+3*CELL_SIZE);

        reDrawCellsGrid(xLeft, yTop+CELL_SIZE, 1, WEST);
        reDrawCellsGrid(xLeft+CELL_SIZE, yTop, 3, WEST);
    }

    else if (orientation == SOUTH)
    {
        bar(xLeft,yTop,xLeft+3*CELL_SIZE,yTop+CELL_SIZE);
        bar(xLeft+CELL_SIZE,yTop+CELL_SIZE,xLeft+2*CELL_SIZE,yTop+2*CELL_SIZE);

        reDrawCellsGrid(xLeft, yTop, 3, HORIZONTAL);
        reDrawCellsGrid(xLeft+CELL_SIZE, yTop+CELL_SIZE, 1, SOUTH);
    }
}

//DRAWS L-BLOCK
void drawLBlock(int xLeft, int yTop, int orientation,int fillingColor)
  {
        setfillstyle(SOLID_FILL, fillingColor);
     if (orientation == NORTH) {
          bar(xLeft+2*CELL_SIZE,yTop,xLeft+3*CELL_SIZE,yTop+CELL_SIZE);
          bar(xLeft,yTop+CELL_SIZE,xLeft+3*CELL_SIZE,yTop+2*CELL_SIZE);
    reDrawCellsGrid(xLeft+2*CELL_SIZE,yTop,1,NORTH);
    reDrawCellsGrid(xLeft,yTop+CELL_SIZE,3,HORIZONTAL);
     }

     else if (orientation == EAST) {
            bar(xLeft,yTop,xLeft+CELL_SIZE,yTop+3*CELL_SIZE);
            bar(xLeft+CELL_SIZE,yTop+2*CELL_SIZE,xLeft+2*CELL_SIZE,yTop+3*CELL_SIZE);
        reDrawCellsGrid(xLeft,yTop,3,VERTICAL);
        reDrawCellsGrid(xLeft+CELL_SIZE,yTop+2*CELL_SIZE,1,EAST);
    }
     else if (orientation == WEST) {
          bar(xLeft,yTop,xLeft+CELL_SIZE,yTop+CELL_SIZE);
          bar(xLeft+CELL_SIZE,yTop,xLeft+2*CELL_SIZE,yTop+3*CELL_SIZE);
     reDrawCellsGrid(xLeft,yTop,1,WEST);
     reDrawCellsGrid(xLeft+CELL_SIZE,yTop,3,VERTICAL);
     }
     else if (orientation == SOUTH) {
          bar(xLeft,yTop,xLeft+3*CELL_SIZE,yTop+CELL_SIZE);
          bar(xLeft,yTop+CELL_SIZE,xLeft+CELL_SIZE,yTop+2*CELL_SIZE);
         reDrawCellsGrid(xLeft,yTop,3,HORIZONTAL);
         reDrawCellsGrid(xLeft,yTop+CELL_SIZE,1,SOUTH);
     }

  }
  void drawLRBlock(int xLeft, int yTop, int orientation, int fillingColor)
  {
     setfillstyle(SOLID_FILL, fillingColor);
     if (orientation==NORTH) {
	  bar(xLeft, yTop, xLeft+CELL_SIZE,yTop+CELL_SIZE);
	  bar(xLeft, yTop+CELL_SIZE, xLeft+3*CELL_SIZE,yTop+2*CELL_SIZE);
	  reDrawCellsGrid(xLeft, yTop, 1, HORIZONTAL);
	  reDrawCellsGrid(xLeft, yTop+CELL_SIZE, 3, HORIZONTAL);
     }
     else if(orientation==EAST)  {
	  bar(xLeft, yTop, xLeft+CELL_SIZE, yTop+3*CELL_SIZE);
	  bar(xLeft+CELL_SIZE, yTop, xLeft+2*CELL_SIZE, yTop+CELL_SIZE);
	  reDrawCellsGrid(xLeft+CELL_SIZE, yTop ,1, VERTICAL);
	  reDrawCellsGrid(xLeft, yTop, 3, VERTICAL);
     }
     else if (orientation==SOUTH) {
	  bar(xLeft, yTop, xLeft+3*CELL_SIZE,yTop+CELL_SIZE);
	  bar(xLeft+2*CELL_SIZE, yTop+CELL_SIZE, xLeft+3*CELL_SIZE,yTop+2*CELL_SIZE);
	  reDrawCellsGrid(xLeft+2*CELL_SIZE, yTop+CELL_SIZE, 1, HORIZONTAL);
	  reDrawCellsGrid(xLeft, yTop, 3, HORIZONTAL);
     }
     else  {
	  bar(xLeft+CELL_SIZE, yTop, xLeft+2*CELL_SIZE, yTop+3*CELL_SIZE);
	  bar(xLeft, yTop+2*CELL_SIZE, xLeft+CELL_SIZE, yTop+3*CELL_SIZE);
	  reDrawCellsGrid(xLeft, yTop+2*CELL_SIZE ,1, VERTICAL);
	  reDrawCellsGrid(xLeft+CELL_SIZE, yTop, 3, VERTICAL);
     }
  }


//*******************************************************************************************************************************************
//******************************************************************** /  BLOCKS GENERATION / *************************************************************************
//*******************************************************************************************************************************************

// GENERATES BAR BLOCK
void generateBarBlock(int & orientation, int & xLeft, int & yTop, int & fillingColor)
{
    orientation = rand()%2 + 1;
    fillingColor = rand()%4 + 1;
    yTop = TOPCORNER;
    if (orientation == HORIZONTAL) xLeft  = LEFTCORNER+4*CELL_SIZE;
    else    xLeft = LEFTCORNER+5*CELL_SIZE;
    drawBarBlock(xLeft,yTop,orientation, fillingColor);
}


// GENERATES BOX BLOCK
void generateBoxBlock(int & xLeft, int & yTop,int &fillingColor)
{
    fillingColor = rand()%4 + 1;
    yTop = TOPCORNER;
    xLeft  = LEFTCORNER+5*CELL_SIZE;
    drawBoxBlock(xLeft,yTop, fillingColor);
}

// GENERATES T BLOCK
void generateT_Block(int & orientation, int & xLeft, int & yTop,int &fillingColor)
{
    orientation = rand()%4 + 1;
    fillingColor = rand()%4 + 1;
    yTop = TOPCORNER;
    if (orientation == NORTH ||orientation == EAST ||orientation == WEST) xLeft  = LEFTCORNER+5*CELL_SIZE;
    else    xLeft = LEFTCORNER+4*CELL_SIZE;
    drawT_Block(xLeft,yTop,orientation, fillingColor);
}


// GENERATES L BLOCK
void generateLBlock(int & orientation, int & xLeft, int & yTop, int & fillingColor){
    orientation=rand()%4+1;
    fillingColor=rand()%4+1;
    yTop=TOPCORNER;
    if(orientation%2==0) xLeft=LEFTCORNER+(4+rand()%3)*CELL_SIZE;
    else xLeft=LEFTCORNER+(4+rand()%2)*CELL_SIZE;
    drawLBlock(xLeft,yTop,orientation,fillingColor);

}
//GENERATES LR BLOCK
void generateLRBlock(int & orientation, int & xLeft, int & yTop, int & fillingColor)
      {
	orientation = rand()%4 + 1;
	fillingColor = rand()%4 + 1;
	yTop = TOPCORNER;
	if (orientation == NORTH || orientation == SOUTH|| orientation == EAST || orientation == WEST)
    xLeft  = LEFTCORNER+4*CELL_SIZE;
	else    xLeft = LEFTCORNER+5*CELL_SIZE;
	drawLRBlock(xLeft,yTop,orientation, fillingColor );
     }


// ************* BLOCKS GENERATION CENTRAL **************************

void Radnomizer(int Number[10])
{
    Number[10]=0;
     for (int i=0;i<10;i++)
     {
       Number[i]= rand()%3+1;
     }
}
void generateNewBlock( int * blockId, int * orientation,int * xLeft, int *yTop, int * fillingColor, const int next[10],int Block)
{


   // random(NB_BLOCKS) + 1;
   //int j=0;
      // *blockId = next[j] ;
 *blockId= rand()%5+1;
    switch(*blockId)
    {
    case BAR_BLOCK:generateBarBlock(*orientation, *xLeft, *yTop, *fillingColor);break;
    case T_BLOCK  :generateT_Block(*orientation, *xLeft, *yTop, *fillingColor);break;
    case L_BLOCK  :generateLBlock(*orientation, *xLeft, *yTop, *fillingColor);break;
    case LR_BLOCK :generateLRBlock(*orientation, *xLeft, *yTop, *fillingColor);break;
    case BOX_BLOCK:generateBoxBlock( *xLeft, *yTop, *fillingColor);break;
    }

}




//*******************************************************************************************************************************************
//******************************************************************** / CHECK TRANSLATION ROUTES / *************************************************************************
//*******************************************************************************************************************************************

// ******************************* CHECK BAR BLOCK TRANSLATE  *********************
// check if Bar block can be moved to the left
void checkTranslateBarRouteLeft(int orientation, int xLeft, int yTop, int &freeRoute)
{
    int maxNbCells;
    // check if route is not blocked
    yTop = yTop + CELL_SIZE/2;
    freeRoute = 1; //route is free
    switch (orientation)
    {
    case HORIZONTAL:
        xLeft = xLeft - CELL_SIZE/2;
        if (getpixel(xLeft, yTop) != BOARD_COLOR) freeRoute = 0;
        break;

    case VERTICAL:
        maxNbCells = 4;
        xLeft  = xLeft - CELL_SIZE/2;
        do
            if (getpixel(xLeft, yTop) == BOARD_COLOR )
            {
                yTop = yTop + CELL_SIZE;
                maxNbCells--;
            }
            else  freeRoute = 0; // route is blocked
        while ( maxNbCells >= 1 && freeRoute);
        break;
    }
}

// check if Bar block can be moved to the right
void checkTranslateBarRouteRight(int orientation, int xLeft, int yTop, int &freeRoute)
{
    int maxNbCells;
    // check if route is not blocked

    freeRoute = 1; //route is free
    switch (orientation)
    {
    case HORIZONTAL:
        // maxNbCells = 1;
        yTop = yTop + CELL_SIZE/2;
        xLeft = xLeft + 4*CELL_SIZE + CELL_SIZE/2;
        if (getpixel(xLeft, yTop) != BOARD_COLOR)
            freeRoute = 0;
        break;

    case VERTICAL:
        maxNbCells = 4;
        yTop = yTop + CELL_SIZE/2;
        xLeft  = xLeft + CELL_SIZE + CELL_SIZE/2;
        do
            if (getpixel(xLeft, yTop) == BOARD_COLOR )
            {
                yTop = yTop + CELL_SIZE;
                maxNbCells--;
            }
            else  freeRoute = 0; // route is blocked
        while ( maxNbCells >= 1 && freeRoute);
        break;
    }
}

// check if Bar block can be moved down
void checkTranslateBarRouteDown(int orientation, int xLeft, int yTop, int &freeRoute)
{
    int maxNbCells;
    // check if route is not blocked
    xLeft = xLeft + CELL_SIZE/2;
    freeRoute = 1; //route is not blocked
    switch(orientation)
    {
    case HORIZONTAL:
        maxNbCells = 4;
        yTop  = yTop + CELL_SIZE + CELL_SIZE/2;
        do
            if (getpixel(xLeft, yTop) == BOARD_COLOR )
            {
                xLeft = xLeft + CELL_SIZE;
                maxNbCells--;
            }
            else  freeRoute = 0; // route is blocked
        while ( maxNbCells >= 1 && freeRoute);
        break;

    case VERTICAL:
        yTop = yTop + 4*CELL_SIZE + CELL_SIZE/2;
        if (getpixel(xLeft, yTop) != BOARD_COLOR) freeRoute = 0;
        break;
    }
}

// Invoke the appropriate checking function for Bar block depending on the direction
int checkTranslateBarRoute(int orientation, int xLeft, int yTop,int direction)
{
    int maxNbCells, freeRoute = 1;
    switch (direction)
    {
    case RIGHT:checkTranslateBarRouteRight(orientation, xLeft, yTop,freeRoute);break;
    case LEFT:checkTranslateBarRouteLeft(orientation, xLeft, yTop,freeRoute);break;
    case DOWN:checkTranslateBarRouteDown(orientation, xLeft, yTop,freeRoute);break;
    }
    return freeRoute;
}

//*******************************************************************CHECK BOX BLOCK TRANSLATE***********************************************************************
void checkTranslateBoxRouteLeft(int xLeft, int yTop, int & freeRoute) //LEFT
{
    int maxNbCells;

    // check if route is not blocked
    yTop = yTop + CELL_SIZE/2;
    freeRoute = 1; //route is free

    maxNbCells = 2;
    xLeft  = xLeft - CELL_SIZE/2;
    do
        if (getpixel(xLeft, yTop) == BOARD_COLOR )
        {
            yTop = yTop + CELL_SIZE;
            maxNbCells--;
        }
        else  freeRoute = 0; // route is blocked
    while ( maxNbCells >= 1 && freeRoute);


}

// check if box block can be moved to the right
void checkTranslateBoxRouteRight(int xLeft, int yTop, int & freeRoute)
{
    int maxNbCells;
    // check if route is not blocked
    yTop = yTop + CELL_SIZE/2;
    freeRoute = 1; //route is free

    maxNbCells = 2;
    xLeft  = xLeft + 2*CELL_SIZE + CELL_SIZE/2;
    do
        if (getpixel(xLeft, yTop) == BOARD_COLOR )
        {
            yTop = yTop + CELL_SIZE;
            maxNbCells--;
        }
        else  freeRoute = 0; // route is blocked
    while ( maxNbCells >= 1 && freeRoute);
}

// check if Box block can be moved down
void checkTranslateBoxRouteDown(int xLeft, int yTop, int & freeRoute)
{
    int maxNbCells;
    // check if route is not blocked
    xLeft = xLeft + CELL_SIZE/2;
    freeRoute = 1; //route is not blocked
    maxNbCells = 2;
    yTop  = yTop + 2*CELL_SIZE + CELL_SIZE/2;
    do
        if (getpixel(xLeft, yTop) == BOARD_COLOR )
        {
            xLeft = xLeft + CELL_SIZE;
            maxNbCells--;
        }
        else  freeRoute = 0; // route is blocked
    while ( maxNbCells >= 1 && freeRoute);
}


// Invoke the appropriate checking function for Bar block depending on the direction
int checkTranslateBoxRoute(int xLeft, int yTop, int direction)
{
    int maxNbCells, freeRoute = 1;
    switch (direction)
    {
    case RIGHT:checkTranslateBoxRouteRight(xLeft, yTop, freeRoute);break;
    case LEFT: checkTranslateBoxRouteLeft(xLeft, yTop, freeRoute);break;
    case DOWN: checkTranslateBoxRouteDown(xLeft, yTop, freeRoute);break;
    }
    return freeRoute;
}

//*******************************************************************CHECK T BLOCK TRANSLATE***********************************************************************
void checkTranslateT_RouteLeft(int orientation, int xLeft, int yTop, int & freeRoute)
{
    int maxNbCells;
    // check if route is not blocked
    yTop = yTop + CELL_SIZE/2;
    freeRoute = 1; //route is free
    switch (orientation)
    {
    case NORTH:
        xLeft = xLeft + CELL_SIZE/2;
        if (getpixel(xLeft, yTop) != BOARD_COLOR) freeRoute = 0;
        if(getpixel(xLeft-CELL_SIZE, yTop+CELL_SIZE) != BOARD_COLOR ) freeRoute = 0;
        break;

    case EAST:
        maxNbCells = 3;
        xLeft  = xLeft - CELL_SIZE/2;
        do
            if (getpixel(xLeft, yTop) == BOARD_COLOR )
            {
                yTop = yTop + CELL_SIZE;
                maxNbCells--;
            }
            else  freeRoute = 0; // route is blocked
        while ( maxNbCells >= 1 && freeRoute);
        break;
    case SOUTH:
        xLeft = xLeft - CELL_SIZE/2;
        if (getpixel(xLeft, yTop) != BOARD_COLOR) freeRoute = 0;
        if(getpixel(xLeft+CELL_SIZE, yTop+CELL_SIZE) != BOARD_COLOR ) freeRoute = 0;

        break;
    case WEST:
        xLeft = xLeft + CELL_SIZE/2;
        if (getpixel(xLeft, yTop) != BOARD_COLOR) freeRoute = 0;
        if(getpixel(xLeft-CELL_SIZE, yTop+CELL_SIZE) != BOARD_COLOR ) freeRoute = 0;
        if(getpixel(xLeft, yTop+2*CELL_SIZE) != BOARD_COLOR ) freeRoute = 0;
        break;
    }
}

// check if Bar block can be moved to the right
void checkTranslateT_RouteRight(int orientation, int xLeft, int yTop, int & freeRoute)
{
    int maxNbCells;
    // check if route is not blocked
    yTop = yTop + CELL_SIZE/2;
    freeRoute = 1; //route is free
    switch (orientation)
    {
    case NORTH:
        xLeft = xLeft +2*CELL_SIZE + CELL_SIZE/2;
        if (getpixel(xLeft, yTop) != BOARD_COLOR) freeRoute = 0;
        if(getpixel(xLeft+CELL_SIZE, yTop+CELL_SIZE) != BOARD_COLOR ) freeRoute = 0;
        break;

    case EAST:
        xLeft = xLeft+CELL_SIZE+CELL_SIZE/2;
        if (getpixel(xLeft, yTop) != BOARD_COLOR) freeRoute = 0;
        if(getpixel(xLeft+CELL_SIZE, yTop+CELL_SIZE) != BOARD_COLOR ) freeRoute = 0;
        if(getpixel(xLeft, yTop+2*CELL_SIZE) != BOARD_COLOR ) freeRoute = 0;
        break;
    case SOUTH:
        xLeft = xLeft + 3*CELL_SIZE + CELL_SIZE/2;
        if (getpixel(xLeft, yTop) != BOARD_COLOR) freeRoute = 0;
        if(getpixel(xLeft-CELL_SIZE, yTop+CELL_SIZE) != BOARD_COLOR ) freeRoute = 0;

        break;
    case WEST:
        maxNbCells = 3;
        xLeft  = xLeft + 2*CELL_SIZE + CELL_SIZE/2;
        do
            if (getpixel(xLeft, yTop) == BOARD_COLOR )
            {
                yTop = yTop + CELL_SIZE;
                maxNbCells--;
            }
            else  freeRoute = 0; // route is blocked
        while ( maxNbCells >= 1 && freeRoute);
        break;
    }
}

// check if Bar block can be moved down
void checkTranslateT_RouteDown(int orientation, int xLeft, int yTop, int &freeRoute)
{
    int maxNbCells;
    // check if route is not blocked
    xLeft = xLeft + CELL_SIZE/2;
    freeRoute = 1; //route is not blocked
    switch (orientation)
    {
    case NORTH:
        maxNbCells = 3;
        yTop  = yTop + 2*CELL_SIZE + CELL_SIZE/2;
        do
            if (getpixel(xLeft, yTop) == BOARD_COLOR )
            {
                xLeft = xLeft + CELL_SIZE;
                maxNbCells--;
            }
            else  freeRoute = 0; // route is blocked
        while ( maxNbCells >= 1 && freeRoute);
        break;

    case EAST:
        yTop = yTop + 3*CELL_SIZE + CELL_SIZE/2;
        if (getpixel(xLeft, yTop) != BOARD_COLOR) freeRoute = 0;
        if(getpixel(xLeft+CELL_SIZE, yTop-CELL_SIZE) != BOARD_COLOR ) freeRoute = 0;
        break;
    case SOUTH:
        yTop = yTop + CELL_SIZE + CELL_SIZE/2;
        freeRoute=0;
        if (getpixel(xLeft, yTop) == BOARD_COLOR)
            if(getpixel(xLeft+CELL_SIZE, yTop+CELL_SIZE) == BOARD_COLOR )
                if(getpixel(xLeft+2*CELL_SIZE, yTop) == BOARD_COLOR ) freeRoute = 1;

        break;
    case WEST:
        yTop = yTop + 2*CELL_SIZE + CELL_SIZE/2;
        if (getpixel(xLeft, yTop) != BOARD_COLOR) freeRoute = 0;
        if(getpixel(xLeft+CELL_SIZE, yTop+CELL_SIZE) != BOARD_COLOR ) freeRoute = 0;
        break;
    }
}

// Invoke the appropriate checking function for Bar block depending on the direction
int checkTranslateT_Route(int orientation, int xLeft, int yTop, int direction)
{
    int maxNbCells, freeRoute = 1;
    switch (direction)
    {
    case RIGHT:checkTranslateT_RouteRight(orientation, xLeft, yTop, freeRoute);break;
    case LEFT:checkTranslateT_RouteLeft(orientation, xLeft, yTop, freeRoute);break;
    case DOWN:checkTranslateT_RouteDown(orientation, xLeft, yTop, freeRoute);break;
    }
    return freeRoute;
}
//***************************************************/ L BLOCK CHECK TRANSLATION /**********************************************

void checkTranslateLRouteRight(int orientation,int x,int y,int &freeRoute){
    freeRoute=1;
    switch(orientation){
        case NORTH: x+=7*CELL_SIZE/2;       y+=CELL_SIZE/2;
                    if(getpixel(x,y)!=BOARD_COLOR)freeRoute=0;
                    else{ y+=CELL_SIZE;
                          if(getpixel(x,y)!=BOARD_COLOR)freeRoute=0;}break;
        case SOUTH: x+=3*CELL_SIZE/2;       y+=3*CELL_SIZE/2;
                    if(getpixel(x,y)!=BOARD_COLOR)freeRoute=0;
                    else{
                        x+=2*CELL_SIZE;     y-=CELL_SIZE;
                    if(getpixel(x,y)!=BOARD_COLOR)freeRoute=0;}  break;
        case WEST:  x+=5*CELL_SIZE/2;       y+=CELL_SIZE/2;
                    for(int i=0;i<3;i++)if(getpixel(x,y+i*CELL_SIZE)!=BOARD_COLOR)freeRoute=0;  break;
        case EAST:  x+=3*CELL_SIZE/2;       y+=CELL_SIZE/2;
                    if(getpixel(x,y)!=BOARD_COLOR)freeRoute=0;
                    else{   y+=CELL_SIZE;
                            if(getpixel(x,y)!=BOARD_COLOR)freeRoute=0;
                            else{
                                x+=CELL_SIZE;   y+=CELL_SIZE;
                                if(getpixel(x,y)!=BOARD_COLOR)freeRoute=0;}} break;}
}
void checkTranslateLRouteLeft(int orientation,int x,int y,int &freeRoute){
    freeRoute=1;
    switch(orientation){
        case NORTH: x-=CELL_SIZE/2;     y+=3*CELL_SIZE/2;
                    if(getpixel(x,y)!=BOARD_COLOR)freeRoute=0;
                    else{
                        x+=2*CELL_SIZE; y-=CELL_SIZE;
                        if(getpixel(x,y)!=BOARD_COLOR)freeRoute=0;} break;
        case SOUTH: x-=CELL_SIZE/2;     y+=CELL_SIZE/2;
                    if(getpixel(x,y)!=BOARD_COLOR)freeRoute=0;
                    else{   y+=CELL_SIZE;
                            if(getpixel(x,y)!=BOARD_COLOR)freeRoute=0;} break;
        case WEST : x-=CELL_SIZE/2;     y+=CELL_SIZE/2;
                    if(getpixel(x,y)!=BOARD_COLOR)freeRoute=0;
                    else{
                        x+=CELL_SIZE;   y+=CELL_SIZE;
                        if(getpixel(x,y)!=BOARD_COLOR)freeRoute=0;
                        else{   y+=CELL_SIZE;
                                if(getpixel(x,y)!=BOARD_COLOR)freeRoute=0;}} break;
        case EAST : x-=CELL_SIZE/2;     y+=CELL_SIZE/2;
                    for(int i=0;i<3;i++)if(getpixel(x,y+i*CELL_SIZE)!=BOARD_COLOR)freeRoute=0; break; }
}
void checkTranslateLRouteDown(int orientation,int x,int y,int &freeRoute){
    freeRoute=1;
    switch(orientation){
        case NORTH: x+=CELL_SIZE/2;     y+=5*CELL_SIZE/2;
                    for(int i=0;i<3;i++)if(getpixel(x+i*CELL_SIZE,y)!=BOARD_COLOR)freeRoute=0; break;
        case SOUTH: x+=CELL_SIZE/2;     y+=5*CELL_SIZE/2;
                    if(getpixel(x,y)!=BOARD_COLOR)freeRoute=0;
                    else{
                        x+=CELL_SIZE;   y-=CELL_SIZE;
                        if(getpixel(x,y)!=BOARD_COLOR)freeRoute=0;
                        else{ x+=CELL_SIZE;
                            if(getpixel(x,y)!=BOARD_COLOR)freeRoute=0;}} break;
        case WEST:  x+=CELL_SIZE/2;     y+=3*CELL_SIZE/2;
                    if(getpixel(x,y)!=BOARD_COLOR)freeRoute=0;
                    else{
                        x+=CELL_SIZE;   y+=2*CELL_SIZE;
                        if(getpixel(x,y)!=BOARD_COLOR)freeRoute=0;} break;
        case EAST:  x+=CELL_SIZE/2;     y+=7*CELL_SIZE/2;
                    if(getpixel(x,y)!=BOARD_COLOR)freeRoute=0;
                    else{ x+=CELL_SIZE;
                        if(getpixel(x,y)!=BOARD_COLOR)freeRoute=0;}break;}
}
int checkTranslateLRoute(int orientation, int xLeft, int yTop,int direction){
    int maxNbCells, freeRoute = 1;
    switch (direction) {
        case RIGHT: checkTranslateLRouteRight(orientation, xLeft, yTop,freeRoute); break;
        case LEFT : checkTranslateLRouteLeft(orientation, xLeft, yTop,freeRoute); break;
        case DOWN : checkTranslateLRouteDown(orientation, xLeft, yTop,freeRoute); break;}
    return freeRoute;
}


///////////////////////////////////////////////////////////LR BLOCK//////////////////////////////////////////////////////////


void checkTranslateLRRouteLeft(int orientation, int xLeft, int yTop, int &
freeRoute)
      {      int maxNbCells;

	  yTop = yTop + CELL_SIZE/2;
	  freeRoute = 1;
	  switch (orientation) {
	    case NORTH:
             maxNbCells = 2;
	       xLeft  = xLeft-CELL_SIZE/2;
	       do
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    yTop = yTop + CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0;
	       while ( maxNbCells >= 1 && freeRoute);
	       break;
	    case EAST:
             maxNbCells = 3;
	       xLeft  = xLeft-CELL_SIZE/2;
	       do
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    yTop = yTop + CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0;
	       while ( maxNbCells >= 1 && freeRoute);
	       break;
	  case SOUTH:
          maxNbCells = 2;
	       xLeft = xLeft - CELL_SIZE/2;
	       do
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    xLeft = xLeft + 2*CELL_SIZE;
		    yTop = yTop + CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0;
	       while ( maxNbCells >= 1 && freeRoute);
	       break;
      case WEST:
            maxNbCells = 2;
	freeRoute = 1;
	xLeft = xLeft + CELL_SIZE/2;
	if (getpixel(xLeft, yTop) == BOARD_COLOR ){
	do
	   if (getpixel(xLeft, yTop+CELL_SIZE) == BOARD_COLOR ){
	    xLeft = xLeft - CELL_SIZE;
	    yTop= yTop +CELL_SIZE;
	    maxNbCells--;
	   }
	   else  freeRoute = 0;
	while (maxNbCells > 0 && freeRoute);
	}
	else freeRoute =0;
	  }}
	  void checkTranslateLRRouteRight(int orientation, int xLeft, int yTop, int &freeRoute)
      {
           int maxNbCells;

	  freeRoute = 1;
	  switch (orientation) {
	    case NORTH:
	       maxNbCells = 2;
	       yTop = yTop + CELL_SIZE/2;
	       xLeft  = xLeft + CELL_SIZE + CELL_SIZE/2;
	       do
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    yTop = yTop + CELL_SIZE;
		     xLeft  = xLeft + 2*CELL_SIZE ;
		    maxNbCells--;
		}
		else  freeRoute = 0;
	       while ( maxNbCells >= 1 && freeRoute);
	       break;
        case EAST:
            maxNbCells = 2;
	       yTop = yTop + CELL_SIZE/2;
	       xLeft = xLeft + 2*CELL_SIZE + CELL_SIZE/2;
	if (getpixel(xLeft, yTop) == BOARD_COLOR ){
	do
	   if (getpixel(xLeft-CELL_SIZE, yTop+CELL_SIZE) == BOARD_COLOR ){
	    yTop= yTop +CELL_SIZE;
	    maxNbCells--;
	   }
	   else  freeRoute = 0;
	while (maxNbCells > 0 && freeRoute);
	}
	else freeRoute =0;
	       break;
        case SOUTH:
	       maxNbCells = 2;
	       xLeft  = xLeft+ 3*CELL_SIZE + CELL_SIZE/2;
	       yTop = yTop + CELL_SIZE/2;
	       do
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    yTop = yTop + CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0;
	       while ( maxNbCells >= 1 && freeRoute);
	       break;


	    case WEST:
	       maxNbCells = 3;
	       yTop = yTop + CELL_SIZE/2;
	       xLeft  = xLeft + 2*CELL_SIZE + CELL_SIZE/2;
	       do
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    yTop = yTop + CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0;
	       while ( maxNbCells >= 1 && freeRoute);
	       break;
	  }
      }

void checkTranslateLRRouteDown(int orientation, int xLeft, int yTop, int &freeRoute)
      {
           int maxNbCells;

	  xLeft = xLeft + CELL_SIZE/2;
	  freeRoute = 1;
	  switch(orientation) {
	   case NORTH:
	        maxNbCells = 3;
	       yTop = yTop + 2*CELL_SIZE + CELL_SIZE/2;
	       do
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
            xLeft  = xLeft+CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0;
	       while ( maxNbCells >= 1 && freeRoute);
	       break;


	   case EAST:
          maxNbCells = 2;
	       yTop = yTop + CELL_SIZE+CELL_SIZE/2;
	       xLeft = xLeft + CELL_SIZE;
	       do
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    xLeft = xLeft - CELL_SIZE;
		    yTop = yTop + 2*CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0;
	       while ( maxNbCells >= 1 && freeRoute);
	       break;
       case SOUTH:
             maxNbCells = 2;
	freeRoute = 1;
	yTop = yTop + CELL_SIZE + CELL_SIZE/2;
	if (getpixel(xLeft, yTop) == BOARD_COLOR ){
	do
	   if (getpixel(xLeft+CELL_SIZE, yTop) == BOARD_COLOR ){
	    xLeft = xLeft + CELL_SIZE;
	    yTop= yTop +CELL_SIZE;
	    maxNbCells--;
	   }
	   else  freeRoute = 0;
	while (maxNbCells > 0 && freeRoute);
	}
	else freeRoute =0;
	       break;
       case WEST:
            maxNbCells = 2;
	       yTop = yTop + 3*CELL_SIZE + CELL_SIZE/2;
	       do
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
            xLeft  = xLeft+CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0;
	       while ( maxNbCells >= 1 && freeRoute);
	       break;
	  }
      }


int checkTranslateLRRoute(int orientation, int xLeft, int yTop,int direction)
{    int maxNbCells, freeRoute = 1;
     switch (direction) {
       case RIGHT: checkTranslateLRRouteRight(orientation, xLeft, yTop,freeRoute); break;
       case LEFT:  checkTranslateLRRouteLeft(orientation, xLeft, yTop,freeRoute); break;
       case DOWN:  checkTranslateLRRouteDown(orientation, xLeft, yTop,freeRoute); break;
     }
     return freeRoute;
  }


//***************************************************/ ROUTE FREE TRANSLATION CENTRAL /**********************************************

// Invoke the appropriate route checking function for translation depending on block Id
int translateRouteFree(int blockId, int orientation, int xLeft, int yTop,int direction)
{
    int freeRoute;
    switch(blockId)
    {
    case T_BLOCK  : freeRoute = checkTranslateT_Route(orientation, xLeft,  yTop,  direction);break;
    case L_BLOCK  : freeRoute = checkTranslateLRoute(orientation, xLeft,  yTop,  direction);break;
    case LR_BLOCK : freeRoute = checkTranslateLRRoute(orientation, xLeft,  yTop,  direction);break;
    case BOX_BLOCK: freeRoute = checkTranslateBoxRoute(xLeft, yTop,direction);break;
    case BAR_BLOCK: freeRoute = checkTranslateBarRoute(orientation, xLeft, yTop, direction);break;
    }
    return freeRoute;
}

//*******************************************************************************************************************************************
//******************************************************************** / BLOCK TRANSLATIONS / *************************************************************************
//*******************************************************************************************************************************************

//******************************************TRANSLATE BAR BLOCK **********************************

void translateBarBlock(int orientation, int & xLeft, int & yTop, int fillingColor,int direction)
{
    // Erase the bar at current position
    drawBarBlock(xLeft, yTop, orientation, BKGRD_COLOR);
    switch (direction)
    {
    case RIGHT:xLeft = xLeft + CELL_SIZE;break;
    case LEFT :xLeft = xLeft - CELL_SIZE;break;
    case DOWN :yTop = yTop + CELL_SIZE;break;
    }
    // Now redraw the bar at the new position
    drawBarBlock(xLeft, yTop, orientation, fillingColor);
}

// *********************************TRANSLATE BOX BLOCK **************************
void translateBoxBlock(int & xLeft, int & yTop,int fillingColor, int direction)

{
    switch (direction)
    {
    case RIGHT:
        //To Erase the bar with background color
        drawBoxBlock(xLeft, yTop,BKGRD_COLOR);
        // To redraw the bar at the new position
        xLeft = xLeft + CELL_SIZE;
        // yTop is unchanged;
        drawBoxBlock(xLeft, yTop,fillingColor);
        break;

    case LEFT:
        // To Erase the bar with background color
        drawBoxBlock(xLeft, yTop, BKGRD_COLOR);
        // To redraw the bar at the new position
        xLeft = xLeft - CELL_SIZE;
        // yTop is unchanged;
        drawBoxBlock(xLeft, yTop, fillingColor);
        break;

    case DOWN:
        //  To Erase the bar with background color
        drawBoxBlock(xLeft, yTop, BKGRD_COLOR);
        // To redraw the bar at the new position
        // xLeft is unchanged
        yTop = yTop + CELL_SIZE;
        drawBoxBlock(xLeft, yTop, fillingColor);
        break;
    }
}

// ***************************************TRANSLATE  T BLOCK ************************************

void translateT_Block(int orientation, int & xLeft, int & yTop,int fillingColor, int direction)
{
    switch (direction)
    {
    case RIGHT:
        // Erase the bar at current position
        drawT_Block(xLeft, yTop, orientation, BKGRD_COLOR);
        // Now redraw the bar at the new position
        xLeft = xLeft + CELL_SIZE;
        // yTop is unchanged;
        drawT_Block(xLeft, yTop, orientation, fillingColor);
        break;

    case LEFT:
        // Erase the bar at current position
        drawT_Block(xLeft, yTop, orientation, BKGRD_COLOR);
        // Now redraw the bar at the new position
        xLeft = xLeft - CELL_SIZE;
        // yTop is unchanged;
        drawT_Block(xLeft, yTop, orientation, fillingColor);
        break;

    case DOWN:
        // Erase the bar at current position
        drawT_Block(xLeft, yTop, orientation, BKGRD_COLOR);
        // Now redraw the bar at the new position
        // xLeft is unchanged
        yTop = yTop + CELL_SIZE;
        drawT_Block(xLeft, yTop, orientation, fillingColor);
        break;
    }
}

//////////////////////////////////////////TRANSLATE L BLOCK//////////////////////////////////////
void translateLBlock(int orientation,int &xLeft, int &yTop,int fillingColor,int direction){
    drawLBlock(xLeft,yTop,orientation,BKGRD_COLOR);
    switch (direction) {
        case RIGHT: xLeft = xLeft + CELL_SIZE; break;
        case LEFT : xLeft = xLeft - CELL_SIZE; break;
        case DOWN : yTop = yTop + CELL_SIZE; break;}
     drawLBlock(xLeft,yTop,orientation,fillingColor);
}
//////////////////////////////////////////TRANSLATE LR BLOCK//////////////////////////////////////
void translateLRBlock(int orientation, int & xLeft, int & yTop, int fillingColor,
	int direction)
  {

     drawLRBlock(xLeft, yTop, orientation, BKGRD_COLOR);
     switch (direction) {
       case RIGHT: xLeft = xLeft + CELL_SIZE; break;
       case LEFT : xLeft = xLeft - CELL_SIZE; break;
       case DOWN : yTop = yTop + CELL_SIZE;   break;
     }

     drawLRBlock(xLeft, yTop, orientation, fillingColor );
  }
//***************************************************/ BLOCK TRANSLATION CENTRAL/**********************************************

// Invoke the appropriate function for translation depending on block Id
void translateBlock(int blockId, int & orientation, int & xLeft, int & yTop,int fillingColor, int direction)
{
    switch(blockId)
    {
    case T_BLOCK  :translateT_Block(orientation, xLeft, yTop, fillingColor, direction);break;
    case L_BLOCK  :translateLBlock(orientation, xLeft, yTop, fillingColor, direction);break;
    case LR_BLOCK :translateLRBlock(orientation, xLeft, yTop, fillingColor, direction);break;
    case BOX_BLOCK:translateBoxBlock( xLeft, yTop, fillingColor, direction);break;
    case BAR_BLOCK:translateBarBlock(orientation, xLeft, yTop, fillingColor, direction);break;
    }
}
//*******************************************************************************************************************************************
//******************************************************************** CHECK  ROTATION *************************************************************************
//*******************************************************************************************************************************************

//*************************************************/ CHECK ROTATE BAR BLOCK /***************************************
// Check if a Bar block can be rotated
int checkRotateBarRoute(int orientation, int xLeft, int yTop)
{
    int maxNbCells, x, y, freeRoute;
    switch (orientation)
    {
    case HORIZONTAL:
        // Checking upper three cells
        maxNbCells = 3;
        freeRoute = 1;
        x = xLeft + CELL_SIZE + CELL_SIZE/2;
        y = yTop  + CELL_SIZE + CELL_SIZE/2;
        do
            if (getpixel(x, y) == BOARD_COLOR )
            {
                x = x + CELL_SIZE;
                maxNbCells--;
            }
            else  freeRoute = 0; // route is blocked
        while (maxNbCells >=1 && freeRoute);

        // Checking lower three cells
        if (freeRoute)   // if route is so far free
        {
            maxNbCells = 3;
            freeRoute = 1;
            x = xLeft + CELL_SIZE   + CELL_SIZE/2;
            y = yTop  + 2*CELL_SIZE + CELL_SIZE/2;
            do
                if (getpixel(x, y) == BOARD_COLOR )
                {
                    x = x + CELL_SIZE;
                    maxNbCells--;
                }
                else  freeRoute = 0; // route is blocked
            while (maxNbCells >=1 && freeRoute);
        }
        break;

    case VERTICAL:
        // Checking left two cells
        maxNbCells = 2;
        freeRoute = 1; // assume route is free
        x = xLeft - CELL_SIZE/2;
        y = yTop  + CELL_SIZE/2;
        do
            if (getpixel(x, y) == BOARD_COLOR )
            {
                y = y + CELL_SIZE;
                maxNbCells--;
            }
            else  freeRoute = 0; // route is blocked
        while (maxNbCells > 0 && freeRoute);

        // Checking middle three cells
        if (freeRoute)   // if route is so far free
        {
            maxNbCells = 3;
            freeRoute  = 1;
            x = xLeft + CELL_SIZE + CELL_SIZE/2;
            y = yTop  + CELL_SIZE + CELL_SIZE/2;
            do
                if (getpixel(x, y) == BOARD_COLOR )
                {
                    y = y + CELL_SIZE;
                    maxNbCells--;
                }
                else  freeRoute = 0; // route is blocked
            while (maxNbCells > 0 && freeRoute);
        }

        // right most three cells
        if (freeRoute)   // if route is so far free
        {
            maxNbCells = 3;
            freeRoute = 1;
            x = xLeft + 2*CELL_SIZE + CELL_SIZE/2;
            y = yTop  + CELL_SIZE   + CELL_SIZE/2;
            do
                if (getpixel(x, y) == BOARD_COLOR )
                {
                    y = y + CELL_SIZE;
                    maxNbCells--;
                }
                else  freeRoute = 0; // route is blocked
            while (maxNbCells > 0 && freeRoute);
        }
        break;
    }
    return freeRoute;
}

//*************************************************Check ROTATE T BLOCK *************************************************

int checkRotateT_Route(int orientation, int xLeft, int yTop)
{
    int x, y, freeRoute, maxNbCells;
    switch (orientation)
    {
    case NORTH:
        if (getpixel(xLeft + 2*CELL_SIZE + CELL_SIZE/2, yTop  + CELL_SIZE/2) == BOARD_COLOR )
            if (getpixel(xLeft + 2*CELL_SIZE + CELL_SIZE/2, yTop  + CELL_SIZE/2 + 2*CELL_SIZE) == BOARD_COLOR )
                if (getpixel(xLeft + CELL_SIZE + CELL_SIZE/2 , yTop  + CELL_SIZE/2 + 2*CELL_SIZE) == BOARD_COLOR ) freeRoute = 1;
                else freeRoute=0;
        break;

    case EAST:
        if (getpixel(xLeft+CELL_SIZE+CELL_SIZE/2, yTop+CELL_SIZE/2) == BOARD_COLOR)
            if(getpixel(xLeft+CELL_SIZE+CELL_SIZE/2, yTop+2*CELL_SIZE+CELL_SIZE/2) == BOARD_COLOR)
                if(getpixel(xLeft - CELL_SIZE/2, yTop + 2*CELL_SIZE + CELL_SIZE/2) == BOARD_COLOR) freeRoute= 1;
                else freeRoute = 0;
        break;
    case SOUTH:
        if (getpixel(xLeft + CELL_SIZE/2, yTop + CELL_SIZE + CELL_SIZE/2) == BOARD_COLOR)
            if(getpixel(xLeft + 2*CELL_SIZE + CELL_SIZE/2, yTop + CELL_SIZE + CELL_SIZE/2) == BOARD_COLOR) freeRoute = 1;
            else freeRoute = 0;
        break;
    case WEST:
        if (getpixel(xLeft + CELL_SIZE/2, yTop + CELL_SIZE/2) == BOARD_COLOR)
            if(getpixel(xLeft + CELL_SIZE/2, yTop+ 2*CELL_SIZE + CELL_SIZE/2) == BOARD_COLOR)
                if(getpixel(xLeft + 2*CELL_SIZE + CELL_SIZE/2, yTop + CELL_SIZE + CELL_SIZE/2) == BOARD_COLOR) freeRoute= 1;
                else freeRoute = 0;
        break;
    }
    return freeRoute;
}
 //*************************************************Check ROTATE L BLOCK *************************************************


    int checkRotateLRoute(int orientation, int xLeft, int yTop)
  {  int maxNbCells, x, y, freeRoute;
     switch (orientation) {
      case NORTH:

	maxNbCells = 2;
	freeRoute = 1;
	x = xLeft + CELL_SIZE/2;
	y = yTop  + CELL_SIZE/2;
	do
	   if (getpixel(x, y) == BOARD_COLOR ){
	      x = x + CELL_SIZE;
	      maxNbCells--;
	   }
	   else  freeRoute = 0;
	while (maxNbCells >=1 && freeRoute);


	if (freeRoute) {
	   maxNbCells = 2;
	   freeRoute = 1;
	   x = xLeft + CELL_SIZE   + CELL_SIZE/2;
	   y = yTop  + 2*CELL_SIZE + CELL_SIZE/2;
	   do
	   if (getpixel(x, y) == BOARD_COLOR ){
	       x = x + CELL_SIZE;
	       maxNbCells--;
	   }
	   else  freeRoute = 0;
	   while (maxNbCells >=1 && freeRoute);
	}
	break;

      case EAST:

	maxNbCells = 2;
	freeRoute = 1;
	x = xLeft - CELL_SIZE/2;
	y = yTop  + CELL_SIZE + CELL_SIZE/2;
	do
	   if (getpixel(x, y) == BOARD_COLOR ){
	    y = y + CELL_SIZE;
	    maxNbCells--;
	   }
	   else  freeRoute = 0;
	while (maxNbCells > 0 && freeRoute);


	if (freeRoute) {
	   maxNbCells = 2;
	   freeRoute  = 1;
	   x = xLeft + CELL_SIZE + CELL_SIZE/2;
	   y = yTop  + CELL_SIZE/2;
	   do
	  if (getpixel(x, y) == BOARD_COLOR ){
	     y = y + CELL_SIZE;
	     maxNbCells--;
	  }
	  else  freeRoute = 0;
	   while (maxNbCells > 0 && freeRoute);
	}
	break;
	case SOUTH:

	              maxNbCells = 2;
	               freeRoute = 1;
	        x = xLeft + CELL_SIZE/2;
            y = yTop  - CELL_SIZE/2;
if(getpixel(x+3*CELL_SIZE, y) == BOARD_COLOR){
                 do
	                        if (getpixel(x, y) == BOARD_COLOR ){
	                            x = x + CELL_SIZE;
	                               maxNbCells--;
	                             }
	                   else  freeRoute = 0;
	             while (maxNbCells > 0 && freeRoute);


	if (freeRoute) {
	   maxNbCells = 2;
	   freeRoute  = 1;
	   x = xLeft + CELL_SIZE + CELL_SIZE/2;
	   y = yTop  + CELL_SIZE + CELL_SIZE/2;
	   do
	  if (getpixel(x, y) == BOARD_COLOR ){
	     x = x + CELL_SIZE;
	     maxNbCells--;
	  }
	  else  freeRoute = 0;
	   while (maxNbCells > 0 && freeRoute);
	}}
	else freeRoute = 0;
	break;
	case WEST:

	maxNbCells = 2;
	freeRoute = 1;
	x = xLeft + CELL_SIZE/2;
	y = yTop  + CELL_SIZE + CELL_SIZE/2;
if(getpixel(x-CELL_SIZE, y) == BOARD_COLOR){
	do
	   if (getpixel(x, y) == BOARD_COLOR ){
	    y = y + CELL_SIZE;
	    maxNbCells--;
	   }
	   else  freeRoute = 0;
	while (maxNbCells > 0 && freeRoute);


	if (freeRoute) {
	   maxNbCells = 2;
	   freeRoute  = 1;
	   x = xLeft + 2*CELL_SIZE + CELL_SIZE/2;
	   y = yTop  + CELL_SIZE/2;
	   do
	  if (getpixel(x, y) == BOARD_COLOR ){
	     y = y + CELL_SIZE;
	     maxNbCells--;
	  }
	  else  freeRoute = 0;
	   while (maxNbCells > 0 && freeRoute);
	}}
	else freeRoute = 0;
	break;
     }
     return freeRoute;
  }
  //*************************************************Check ROTATE LR BLOCK *************************************************

int checkRotateLRRoute(int orientation, int xLeft, int yTop)
  {  int maxNbCells, x, y, freeRoute;
     switch (orientation) {
      case NORTH:

	maxNbCells = 2;
	freeRoute = 1;
	x = xLeft + CELL_SIZE + CELL_SIZE/2;
	y = yTop  + CELL_SIZE/2;
	do
	   if (getpixel(x, y) == BOARD_COLOR ){
	      x = x + CELL_SIZE;
	      maxNbCells--;
	   }
	   else  freeRoute = 0;
	while (maxNbCells >=1 && freeRoute);


	if (freeRoute) {
	   maxNbCells = 2;
	   freeRoute = 1;
	   x = xLeft + CELL_SIZE   + CELL_SIZE/2;
	   y = yTop  + 2*CELL_SIZE + CELL_SIZE/2;
	   do
	   if (getpixel(x, y) == BOARD_COLOR ){
	       x = x + CELL_SIZE;
	       maxNbCells--;
	   }
	   else  freeRoute = 0;
	   while (maxNbCells >=1 && freeRoute);
	}
	break;

      case EAST:

	maxNbCells = 2;
	freeRoute = 1;
	x = xLeft - CELL_SIZE/2;
	y = yTop  + CELL_SIZE + CELL_SIZE/2;
	do
	   if (getpixel(x, y) == BOARD_COLOR ){
	    y = y + CELL_SIZE;
	    maxNbCells--;
	   }
	   else  freeRoute = 0;
	while (maxNbCells > 0 && freeRoute);


	if (freeRoute) {
	   maxNbCells = 3;
	   freeRoute  = 1;
	   x = xLeft + CELL_SIZE + CELL_SIZE/2;
	   y = yTop  + CELL_SIZE + CELL_SIZE/2;
	   do
	  if (getpixel(x, y) == BOARD_COLOR ){
	     y = y + CELL_SIZE;
	     maxNbCells--;
	  }
	  else  freeRoute = 0;
	   while (maxNbCells > 0 && freeRoute);
	}
	break;
	case SOUTH:
	maxNbCells = 2;
	freeRoute = 1;
	x = xLeft + CELL_SIZE/2;
	y = yTop  - CELL_SIZE/2;
	do
	   if (getpixel(x, y) == BOARD_COLOR ){
	      x = x + CELL_SIZE;
	      maxNbCells--;
	   }
	   else  freeRoute = 0;
	while (maxNbCells >=1 && freeRoute);


	if (freeRoute) {
	   maxNbCells = 2;
	   freeRoute = 1;
	   x = xLeft + CELL_SIZE/2;
	   y = yTop  + CELL_SIZE + CELL_SIZE/2;
	   do
	   if (getpixel(x, y) == BOARD_COLOR ){
	       x = x + CELL_SIZE;
	       maxNbCells--;
	   }
	   else  freeRoute = 0;
	   while (maxNbCells >=1 && freeRoute);
	}
     break;
     case WEST:

	maxNbCells = 2;
	freeRoute = 1;
	x = xLeft + CELL_SIZE/2;
	y = yTop  + CELL_SIZE/2;
	do
	   if (getpixel(x, y) == BOARD_COLOR ){
	    y = y + CELL_SIZE;
	    maxNbCells--;
	   }
	   else  freeRoute = 0;
	while (maxNbCells > 0 && freeRoute);


	if (freeRoute) {
	   maxNbCells = 2;
	   freeRoute  = 1;
	   x = xLeft + 2*CELL_SIZE + CELL_SIZE/2;
	   y = yTop  + CELL_SIZE/2;
	   do
	  if (getpixel(x, y) == BOARD_COLOR ){
	     y = y + CELL_SIZE;
	     maxNbCells--;
	  }
	  else  freeRoute = 0;
	   while (maxNbCells > 0 && freeRoute);
	}
	break;
     }
     return freeRoute;
  }
// Invoke the appropriate route checking function for rotation depending on block Id
int rotateRouteFree(int blockId, int orientation, int xLeft, int yTop)
{
    int freeRoute;
    switch(blockId)
    {
    case T_BLOCK  :freeRoute = checkRotateT_Route(orientation, xLeft, yTop);break;
    case L_BLOCK  :freeRoute = checkRotateLRoute(orientation, xLeft, yTop);break;
    case LR_BLOCK :freeRoute = checkRotateLRRoute(orientation, xLeft, yTop);break;
    case BOX_BLOCK:break;
    case BAR_BLOCK:freeRoute = checkRotateBarRoute(orientation, xLeft, yTop);break;
    }
    return freeRoute;
}

//*******************************************************************************************************************************************
//******************************************************************** ROTATION *************************************************************************
//*******************************************************************************************************************************************


////*************************************************ROTATE BAR BLOCK ***************************************
void rotateBarBlock(int & orientation, int & xLeft, int & yTop, int fillingColor)
{
    // Erase the bar at current position
    drawBarBlock(xLeft, yTop, orientation, BKGRD_COLOR);
    // Now compute the new location
    switch (orientation)
    {
    case HORIZONTAL:
        orientation = VERTICAL;
        xLeft = xLeft + CELL_SIZE;
        yTop  = yTop  - CELL_SIZE;
        break;

    case VERTICAL:
        orientation = HORIZONTAL;
        xLeft = xLeft - CELL_SIZE;
        yTop  = yTop  + CELL_SIZE;
        break;
    }
    // Now redraw the bar at the new position
    drawBarBlock(xLeft, yTop, orientation, fillingColor);
}
//************************************************************************ROTATE T BLOCK ******************************************

void rotateT_Block(int & orientation, int & xLeft, int & yTop, int fillingColor){//CHECK CHECK CHECK
    drawT_Block(xLeft, yTop, orientation, BKGRD_COLOR);
    switch (orientation) {
        case NORTH: orientation = EAST; xLeft+=CELL_SIZE;break;
        case EAST:orientation = SOUTH;xLeft-=CELL_SIZE;yTop+=CELL_SIZE;break;
        case SOUTH: orientation=WEST; yTop-=CELL_SIZE;break;
        case WEST : orientation=NORTH; break;}
    drawT_Block(xLeft, yTop, orientation, fillingColor );
}
//************************************************************************ROTATE L BLOCK ******************************************


void rotateLBlock(int & orientation, int & xLeft, int & yTop, int fillingColor)
 {

   drawLBlock(xLeft, yTop, orientation, BKGRD_COLOR);

   switch (orientation) {
     case NORTH:
       orientation = EAST;
       xLeft = xLeft + CELL_SIZE;
       break;

     case EAST:
       orientation = SOUTH;
       xLeft = xLeft - CELL_SIZE;
       yTop  = yTop  + CELL_SIZE;
       break;
     case SOUTH:
       orientation = WEST;
       xLeft = xLeft + CELL_SIZE;
       yTop  = yTop  - CELL_SIZE;
       break;
      case WEST:
       orientation = NORTH;
       xLeft = xLeft - CELL_SIZE;
       break;
   }

   drawLBlock(xLeft, yTop, orientation, fillingColor );
 }

 //************************************************************************ROTATE LR BLOCK ******************************************
void rotateLRBlock(int & orientation, int & xLeft, int & yTop, int fillingColor)
 {
   // Erase the bar at current position
   drawLRBlock(xLeft, yTop, orientation, BKGRD_COLOR);
   // Now compute the new location
   switch (orientation) {
     case NORTH:
       orientation = EAST;
       xLeft = xLeft + CELL_SIZE;
       break;

     case EAST:
       orientation = SOUTH;
       xLeft = xLeft - CELL_SIZE;
       yTop  = yTop  + CELL_SIZE;
       break;
     case SOUTH:
       orientation = WEST;
       yTop=yTop-CELL_SIZE;
       break;
     case WEST:
       orientation = NORTH;

       break;
   }
   // Now redraw the bar at the new position
   drawLRBlock(xLeft, yTop, orientation, fillingColor /*FRGRD_COLOR*/);
 }

//**************************************************************************************************** ROTATE BLOCK CENTRAL**************
// Invokes the appropriate rotating function depending on the block Id
void rotateBlock(int blockId, int & orientation, int & xLeft, int & yTop,int fillingColor)
{
    switch(blockId)
    {
    case T_BLOCK  :rotateT_Block(orientation, xLeft, yTop, fillingColor);break;
    case L_BLOCK  :rotateLBlock(orientation, xLeft, yTop, fillingColor);break;
    case LR_BLOCK :rotateLRBlock(orientation, xLeft, yTop, fillingColor);break;
    case BOX_BLOCK:
    case BAR_BLOCK:rotateBarBlock(orientation, xLeft, yTop, fillingColor);break;
    }
}



// Invokes the appropriate function depending on the arrow key pressed
void handleUserInput(int blockId, int & orientation,int & xLeft, int & yTop, int fillingColor, int key)
{
    switch(key)
    {
    case LEFTARROW:
        if (translateRouteFree(blockId,orientation, xLeft, yTop, LEFT))
            translateBlock(blockId, orientation, xLeft, yTop, fillingColor, LEFT);
        break;
    case RIGHTARROW:
        if (translateRouteFree(blockId,orientation, xLeft, yTop, RIGHT))
            translateBlock(blockId, orientation, xLeft, yTop, fillingColor, RIGHT);
        break;
    case UPARROW:
        if (rotateRouteFree(blockId, orientation, xLeft, yTop))
            rotateBlock(blockId, orientation, xLeft, yTop, fillingColor);
        break;
    case DOWNARROW:// Do you see any need for the DOWN Arrow key?
        displayInfo("down arrow key pressed...");
        break;
    }
}

// checks whether or not game is over
int gameOver()
{
    int xLeft, yTop, maxNbCells, gOver;
    // check if the top middle two/four cells are not covered
    yTop  = TOPCORNER + CELL_SIZE /2;
    xLeft = LEFTCORNER + 4*CELL_SIZE + CELL_SIZE/2;
    maxNbCells = 2;  // or 4
    gOver = 0;   // game is not over
    while ( maxNbCells >= 1 && !gOver)
        if (getpixel(xLeft, yTop) == BOARD_COLOR )
        {
            xLeft = xLeft + CELL_SIZE;
            maxNbCells--;
        }
        else  gOver = 1;   // game is over
    return gOver;
}

// checks confirmation of ESCAPE
int escapeConfirmed()
{
    char ans;
    displayInfo("Are you sure you want to Exit [Y/N] ?>");
    do
        ans=toupper(char(getch()));
    while (ans != 'Y' && ans != 'N');
    if(ans == 'Y') return 1;
    else  return 0;
}


// falls a block until it touches "ground"
int freeFall(int blockId, int orientation, int & xLeft, int & yTop,int fillingColor)
{
    int fallBlocked = 0;
    if (translateRouteFree(blockId, orientation, xLeft, yTop, DOWN))
    {
      Beep(400,10);
        translateBlock(blockId, orientation, xLeft, yTop, fillingColor, DOWN);
        delay(LEVEL1_SPEED); //Levels can be introduced
    }
    else fallBlocked = 1;
    return fallBlocked;
}


 void showBlock(int *currentBlock,int *orientation,int *fillingColor,int next[9000],int Block)
        {
              setfillstyle(SOLID_FILL, BLACK);
        bar(SHOWBLOCKAREALEFT+1, SHOWBLOCKAREATOP+1,SHOWBLOCKAREALEFT+SHOWBLOCKWIDTH-1,SHOWBLOCKAREATOP+SHOWBLOCKHEIGHT-1);
          switch(*currentBlock)
    {
    case T_BLOCK  :drawT_Block(SHOWBLOCKAREALEFT+10+CELL_SIZE, SHOWBLOCKAREATOP+20+CELL_SIZE, *orientation,*fillingColor);break;
    case L_BLOCK  :drawLBlock(SHOWBLOCKAREALEFT+10, SHOWBLOCKAREATOP+20, *orientation,*fillingColor);break;
    case LR_BLOCK :drawLBlock(SHOWBLOCKAREALEFT+13, SHOWBLOCKAREATOP+20, *orientation,*fillingColor);break;
    case BOX_BLOCK:drawBoxBlock(SHOWBLOCKAREALEFT+30, SHOWBLOCKAREATOP+30,*fillingColor);break;
    case BAR_BLOCK: if (*orientation==HORIZONTAL)  drawBarBlock(SHOWBLOCKAREALEFT+15, SHOWBLOCKAREATOP+20+CELL_SIZE, *orientation,*fillingColor);break;

        drawBarBlock(SHOWBLOCKAREALEFT+10+2*CELL_SIZE, SHOWBLOCKAREATOP+15, *orientation,*fillingColor);break;

        }

    }

void OneCell(int x,int y,int cellColor)
{
    x-=CELL_SIZE/2;
    y+=CELL_SIZE/2;
    setfillstyle(SOLID_FILL,cellColor);
    bar(x,y,x+CELL_SIZE,y+CELL_SIZE);
    reDrawCellsGrid(x,y,1,HORIZONTAL);
}

void MakeBlackRow(int y)
{

    int x=LEFTCORNER+CELL_SIZE;
    y-=CELL_SIZE/2;
    setfillstyle(SOLID_FILL,BOARD_COLOR);
    bar(x,y,x+NB_COLS*CELL_SIZE,y+CELL_SIZE);
    reDrawCellsGrid(x,y,NB_COLS,HORIZONTAL);
}

void CopyCellsAbove(int y)
{
    int x=LEFTCORNER+3*CELL_SIZE/2;
    y-=CELL_SIZE;
    while((y>TOPCORNER))
        {
        for(int i=0;i<NB_COLS;i++)
        {
         OneCell(x+i*CELL_SIZE,y,getpixel(x+i*CELL_SIZE,y));
        }
        MakeBlackRow(y);
        y-=CELL_SIZE;
        }
}
void checkBlockfill()
{
    int y=NB_ROWS*CELL_SIZE+TOPCORNER;
    int x=LEFTCORNER+(NB_COLS+1)*CELL_SIZE;
    x-=CELL_SIZE/2;
    y-=CELL_SIZE/2;
    for(int i=0;i<NB_ROWS;i++)
        {
        int counter=1;
        for(int j=0;j<NB_COLS;j++)
            if(getpixel(x-j*CELL_SIZE,y)!=BKGRD_COLOR)
                counter++;
        if(counter==(1+NB_COLS))
{Beep(900,10);
            MakeBlackRow(y);
            CopyCellsAbove(y);
            Beep(1000,10);
                     }
                y-=CELL_SIZE;
        }
}
// Controls the overall logic of the game
void playGame()
{

    int currentBlock, currentOrientation, key,Speed=0,score=0,next[10],Block=0;
    char speedmsg [33];char scoremsg [33],Highscoremsg[60];
    int xLeftCurrent, yTopCurrent, fillingColor, fallBlocked;

std:: fstream Highscorefile;
Highscorefile.open("C:\\Users\\Xentos\\Desktop\\File\\some.txt");

//Highscorefile.(0,ios::beg);
//Highscorefile>>Highscore;

itoa (Speed,speedmsg,10);
itoa (score,scoremsg,10);
 speed(speedmsg);
 scoree(scoremsg);
    do
    {

        Radnomizer(next);
        displayInfo("press ESC to abort the game");
        checkBlockfill();
        // clearKeyBoard(); // clears any key pressed

        generateNewBlock(&currentBlock, &currentOrientation, &xLeftCurrent,&yTopCurrent, &fillingColor,next,Block);

        Block=Block+1;
        score=score+10;//adding a score of 10 after each generation
        itoa (score,scoremsg,10);//changes the score integer value to string message
        scoree(scoremsg);//calling the score display function
        showBlock(&currentBlock,&currentOrientation,&fillingColor,next,Block);//calling the show next block Function


        do   // loop as long as the current block is falling down
        {
            do
                fallBlocked = freeFall(currentBlock, currentOrientation, xLeftCurrent,yTopCurrent, fillingColor);

            while (!kbhit() && !fallBlocked);
            if (!fallBlocked)   // ie. key is pressed
            {
                key=getch();
                switch(key)
                {
                case ESC:
                    if (!escapeConfirmed()) key = 1;
                    break;
                case SPACE:
                    displayInfo("space key pressed...");
                    break;
                case PLUS:
                {
                    Speed=Speed+1;
                    LEVEL1_SPEED= LEVEL1_SPEED-20;
                    itoa (Speed,speedmsg,10);
                    speed(speedmsg);
                    displayInfo("Speed Increased.......");
                    Beep(400,500);
                    delay(300);
                    break;

                }
                case MINUS:
                {
                    Speed=Speed-1;
                    LEVEL1_SPEED= LEVEL1_SPEED+20;
                    itoa (Speed,speedmsg,10);
                    speed(speedmsg);
                    displayInfo("Speed Decreased......");
                      Beep(300,500);

                    delay(300);
                     break;
                }
                case '\0' :   // Key is not int the 256 ASCII table
                {
                    key = getch();
                    handleUserInput(currentBlock, currentOrientation, xLeftCurrent,yTopCurrent, fillingColor, key);
                }
                }
            }
        }
        while (key != ESC && !fallBlocked);
    }
    while (key != ESC && !gameOver());
if(gameOver())
{
    if(score>Highscore)
    {
        Highscore=score;
        Highscorefile<<Highscore;
    }

    Highscorefile.seekg(0,std:: ios::beg);
    Highscorefile>>Highscore;

    itoa (Highscore,Highscoremsg,10);
    Gameoverscreen("SCORE BOARD");

    highscore(Highscoremsg,scoremsg);
    LEVEL1_SPEED=300;

}
}
// Launches the game
int main()
{

    std:: fstream Highscorefile;
    Highscorefile.open("C://Users//Xentos//Desktop//File//some.txt");
    Highscorefile>>Highscore;
    system ("color F0");
    int key;
    initGraphEngine();
    do
    {
        backGround();//welcoming background
        drawWelcomeScreen("PLAY");//Welcome screen

        getch();//waits user interaction
        clearwelcomescreen();//clears welcoming screen and background
        drawBoard();
        //clearKeyBoard(); // clears any previously pressed key strokes
        clearDisplayArea();
        displayInfo("press ENTER key to play or ESC to Exit    ");
        ScoreInfo("SCORE:");
        nextBlockInfo("NEXT BLOCK");
        speedTabInfo("SPEED :");
        key=getch();
        switch(key)
        {
        case ESC:
            if (!escapeConfirmed()) key = 1; // to erase ESCAPE
            break;
        case ENTER:
            playGame();
            if(gameOver())
            {
                displayInfo("Game Over!!! Press any key --->        ");
                LEVEL1_SPEED=300;
            }

                        getch();

        } // switch
    }
    while (key != ESC);   // this is to exit from the program
    displayInfo ("Come Again ... ");
    delay(1000);
    backGround();
    drawWelcomeScreen("PLAY");
    return 0;
}


