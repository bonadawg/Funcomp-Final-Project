//James Bonadonna, Section 2
//project.cpp, main driver for the final project, creates a board and plays the game of Snake

#include"gfxnew.h"
#include<iostream>
#include<cmath>
#include"snake.h"
#include<unistd.h>
#include<time.h>

char play(int,float,float,bool);
void placeFood(float[2],Snake);

using namespace std;

int main(){
	srand (time(NULL)); //resets the random number generator
	float xsize=603;
	float ysize=454; //sets the bounds for the screen, offset to allow for the boundary rectangle
	char c;
	int dir=4;
	bool shape=0;
	
	char thefont[] = "7x13"; //changes the font
  	char mytext[] = "Use the Arrow Keys to Move Around. Press ESC to exit and W to retry.";
	char modText[]="Press Q to toggle the shape. Press a direction to start. Press P to pause.";
  	int x_winctr, y_winctr; //window's center
  	int pxl_w, x_txt, y_txt; //text string's parameters

	gfx_open(xsize,ysize,"James Bonadonna, Final Project"); //opens the window
	while(true){
		gfx_changefont(thefont);
    	x_winctr = xsize/2;
    	y_winctr = ysize/2;
		pxl_w = gfx_textpixelwidth(mytext, thefont);
    	x_txt = x_winctr-pxl_w/2;
   		y_txt = y_winctr-y_winctr/2;
   		gfx_text(x_txt, y_txt, mytext);
		gfx_text(x_txt,y_txt*1.2,modText); //display the text, by first determining its lower left corner
		gfx_rectangle(0,50,xsize-1,ysize-51);
   		gfx_flush();

		c=gfx_wait();
		switch(c){
			case 27:
				return 0; //exits if ESC is pressed
			case 'w':
				gfx_clear(); //resets the game if w is pressed
				break;
			case 'Q': //left arrow
				c=play(1,xsize,ysize,shape);
				break;
			case 'R': //up arrow
				c=play(2,xsize,ysize,shape);
				break;
			case 'T': //down arrow
				c=play(3,xsize,ysize,shape);
				break;
			case 'S': //right arrow
				c=play(4,xsize,ysize,shape);
				break;
		}if(c==27)
			return 0;
		else if(c<0){
			gfx_rectangle(0,50,xsize-1,ysize-51);
   			gfx_text(250, 200, "GAME OVER");
			gfx_flush();
		}else if(c=='q')
			shape=!shape;
	}
	return 0;
}

char play(int dir,float xsize,float ysize,bool shape){
	float genVals[2]={0}; //instantiates the x and y value array
	gfx_clear();
	gfx_rectangle(0,50,xsize-1,ysize-51); //prints the rectangle
	gfx_flush();
	usleep(75000);
	char paused;
	char pFont[]="12x24";
	char gFont[]="7x13";
	Snake s(vector<float>{xsize/(float)2.969+20,xsize/(float)2.969,xsize/(float)2.969-20},vector<float>{ysize/(float)1.945,ysize/(float)1.945,ysize/(float)1.945},4,shape); //creates the snake to be used
	placeFood(genVals,s); //places the first food
	while(true){
		if(gfx_event_waiting()){
			char c=gfx_wait();
			switch(c){
				case 27:
					gfx_clear();
					return 27;
				case 'w':
					gfx_clear();
					return 'w';
				case 'q':
					shape=!shape;
					break;
				case 'p':
					gfx_changefont(pFont);
					gfx_text(250,200, "PAUSED");
					do{
						paused=gfx_wait();
						if(paused==27 || paused=='w'){
							gfx_clear();
							return paused;
						}if(paused=='q')
							shape=!shape;
					}while(paused!='p');
					gfx_changefont(gFont);
					break; //pauses the screen if p is pressed, p is pressed again to resume
				case 'Q': //left arrow
					gfx_clear();
					gfx_rectangle(0,50,xsize-1,ysize-51);
					dir=1;
					break;
				case 'R': //up arrow
					gfx_clear();
					gfx_rectangle(0,50,xsize-1,ysize-51);
					dir=2;
					break;
				case 'T': //down arrow
					gfx_clear();
					gfx_rectangle(0,50,xsize-1,ysize-51);
					dir=3;
					break;
				case 'S': //right arrow
					gfx_clear();
					gfx_rectangle(0,50,xsize-1,ysize-51);
					dir=4; //inputs change the direction which is called when the snake is moved
					break;
			}
		}
	dir=s.move(dir,xsize,ysize,shape); //calls a method to move the snake
	if(dir<0){
		gfx_clear();
		char newFont[] = "12x24";
		gfx_changefont(newFont);
		string score="SCORE: ";
		score.append(to_string(s.getSize()-3)); //outputs the player's final score
   		gfx_text(250, 250, score.c_str());
		gfx_flush();
		return -1;
	}
	gfx_rectangle(0,50,xsize-1,ysize-51);
	string score="Score: ";
	score.append(to_string(s.getSize()-3)); //outputs the player's current score
   	gfx_text(250, 25, score.c_str());
	gfx_flush();
	if(!shape)
		gfx_fill_rectangle(genVals[0],genVals[1],20,20);
	else
		gfx_fill_circle(genVals[0]+10,genVals[1]+10,10); //determines which shape to make the food and places it
	if(s.eatFood(genVals)){
		placeFood(genVals,s);
		s.add(genVals); //if the snake has eaten the food, place a new food and add one link to the snake
	}
	gfx_flush();
	}
}

void placeFood(float a[2],Snake s){
	string score="Score: ";
	score.append(to_string(s.getSize()-3));
   	gfx_text(250, 25, score.c_str());
	gfx_flush();
	do{
	a[0]=(rand()%29)*20+3.099/2;
	a[1]=(rand()%19)*20+50 +3.419/2; //generates a new location for food
	}while(s.intersect(a[0],a[1])); //loop ensures the food doesn't go on the snake
}

