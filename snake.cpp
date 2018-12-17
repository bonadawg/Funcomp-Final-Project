//James Bonadonna, Section 2
//snake.cpp, implements the Snake class, creates the methods and functions

#include"snake.h"
#include<iostream>
#include<vector>
#include"gfxnew.h"
#include<unistd.h>
#include<cmath>

using namespace std;

Snake::Snake(){
	setSnake(vector<float> {0,1,2},vector<float> {0,1,2},25,0);
}

Snake::Snake(vector<float> a, vector<float> b,int c,bool d){
	setSnake(a,b,c,d);
}

Snake::~Snake(){
}

void Snake::setSnake(vector<float> a,vector<float> b,int c,bool d){
	xVals=a;
	yVals=b;
	dir=c;
	shape=d;
}

int Snake::getSize(){
	return xVals.size();
}

int Snake::move(int a,float xSz,float ySz,bool d){
	shape=d;
	gfx_clear();
	if(a==1 && dir!=4){ //ensures the snake can't turn around on itself
		usleep(125000); //pauses the screen to make sure the player can see it
		for(int i=xVals.size()-1;i>0;i--){
			xVals[i]=xVals[i-1];
			yVals[i]=yVals[i-1]; //cycles through the snake to push back its location
		}
		if(xVals[0]>=20){
			xVals[0]=xVals[0]-20; //moves the head forward
		}
		else
			return -1; //returns false if it reaches the boundary
		if(yVals[0]<34 || yVals[0]>ySz-1 || xVals[0]>xSz-1)
			return -1; //returns false if any part of the body reaches the boundary
		dir=a;
	}else if(a==2 && dir!=3){
		usleep(125000);
		for(int i=xVals.size()-1;i>0;i--){
			xVals[i]=xVals[i-1];
			yVals[i]=yVals[i-1];
		}
		if((yVals[0])>=60)
			yVals[0]=yVals[0]-20;
		else
			return -1;
		if(xVals[0]<0 || yVals[0]>ySz-1 || xVals[0]>xSz-1)
			return -1;
		dir=a;
	}else if(a==3 && dir!=2){
		usleep(125000);
		for(int i=xVals.size()-1;i>0;i--){
			xVals[i]=xVals[i-1];
			yVals[i]=yVals[i-1];
		}
		if((yVals[0]+40)<=ySz)
			yVals[0]=yVals[0]+20;
		else
			return -1;
		if(xVals[0]<0 || yVals[0]<34 ||  xVals[0]>xSz-1)
			return -1;
		dir=a;
	}else if(a==4 && dir!=1){
		usleep(125000);
		for(int i=xVals.size()-1;i>0;i--){
			xVals[i]=xVals[i-1];
			yVals[i]=yVals[i-1];
		}
		if((xVals[0])<=xSz-20)
			xVals[0]=xVals[0]+20;
		else
			return -1;
		if(xVals[0]<0 || yVals[0]<34 || yVals[0]>ySz-1)
			return -1;
		dir=a;
	}else{
		usleep(50000); //if the direction is opposite to the snake's movement, gives a small pause to keep motion fluid
		a=dir;
	}
	if(intersect(xVals[0],yVals[0]))
		return -1;
	for(int i=0;i<xVals.size();i++){
		if(!shape)
			gfx_fill_rectangle(xVals[i],yVals[i],17,17);
		else
			gfx_fill_circle(xVals[i]+17/2,yVals[i]+17/2,17/2); //determines which shape to make the body out of
	}
	gfx_flush();
	return a;
}

bool Snake::eatFood(float a[2]){
	if(abs(xVals[0]-a[0])<5 && abs(yVals[0]-a[1])<5) //checks to see if the snake hits the food
		return 1;
	else 
		return 0;
}

void Snake::add(float a[5]){
	xVals.push_back(a[0]);
	yVals.push_back(a[1]); //pushes the new value back to the snake
}

bool Snake::intersect(float x,float y){
	for(int i=1;i<xVals.size();i++){
		if(abs(x-xVals[i])<5 && abs(y-yVals[i])<5) //loops through the snake to see if the desired point intersects with the body
			return 1;
	}
	return 0;
}
