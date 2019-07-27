//
//  Display.h
//  Lab 10
//
//  Created by Akarsh Kumar on 4/22/19.
//  Copyright © 2019 Akarsh Kumar. All rights reserved.
//

#ifndef Display_h
#define Display_h

#include <math.h>
//#include <iostream>

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Vector.h"

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 160

#define GAME_VIEW_WIDTH 100
#define GAME_VIEW_HEIGHT 100

//#define DISPLAY_WIDTH 64
//#define DISPLAY_HEIGHT 128

#define CROSSHAIR_RADIUS 10

//#define DISPLAY_WIDTH 10
//#define DISPLAY_HEIGHT 10

//#define DISPLAY_WIDTH 700
//#define DISPLAY_HEIGHT 700

#define DISPLAY_NUM_PIXELS DISPLAY_WIDTH*DISPLAY_HEIGHT

#define BLACK 0x0000

#define BLUE 0xF800
#define GREEN 0x07E0
#define RED 0x001F

#define BLUE_COLOR_SHIFT 11
#define GREEN_COLOR_SHIFT 5
#define RED_COLOR_SHIFT 0

struct Color{
    uint16_t color;
    Color() {
        color = BLACK;
    }
    Color(const Color& another){
        this->color = another.color;
    }
    Color(uint16_t color){
        this->color = color;
    }
    Color(uint8_t r_, uint8_t g_, uint8_t b_){
        color = ((r_ >> 3) << RED_COLOR_SHIFT)|(((g_ >> 2) << GREEN_COLOR_SHIFT))|((b_ >> 3) << BLUE_COLOR_SHIFT);
    }
    
    uint8_t getR() const{
        return (color&RED)>>RED_COLOR_SHIFT<<3;
    }
    uint8_t getG() const{
        return (color&GREEN)>>GREEN_COLOR_SHIFT<<2;
    }
    uint8_t getB() const{
        return (color&BLUE)>>BLUE_COLOR_SHIFT<<3;
    }
    
};


Color avgColor2(Color c1, Color c2){
    return Color((c1.getR()+c2.getR())/2, (c1.getG()+c2.getG())/2, (c1.getB()+c2.getB())/2);
}

void displayInitImpl();

void displayInitScreen();

void setColor(int x, int y, const Color& col);

void solidifyDisplay();

void clearScreen();

/*
std::ostream& operator<<(std::ostream& os, const Color& col)
{
    os<< "Color: ("<<(int)col.getR()<<", "<<(int)col.getG()<<", " <<(int)col.getB()<<")";
    return os;
}
*/





void drawLine(int x1, int y1, int x2, int y2) {
    float dist = (y2-y1)*(y2-y1)+(x2-x1)*(x2-x1);
    dist = sqrt(dist);
    
    float dx = ((float)(x2-x1))/dist/2;
    float dy = ((float)(y2-y1))/dist/2;
    float x = x1;
    float y = y1;
    for(int i = 0; i<=dist*2;i++){
        if(x>=0 && x<DISPLAY_WIDTH && y>=0 && y<DISPLAY_HEIGHT){
            setColor((int)x,(int)y,Color(255,0,255));
            
            x+=dx;
            y+=dy;
        }
    }
}


void displayInit(){
    displayInitImpl();
}

void fillScreen(uint16_t color);
void fillScreen(Color color){
    fillScreen(color.color);
}
void fillRect(int x, int y, uint16_t color, int width, int height);

void drawBitMap(int px, int py, const uint16_t* image, int bitmapWidth, int bitmapHeight);

void dynamicDrawBitMap(int px, int py, const uint16_t* image, int bitmapWidth, int bitmapHeight, int drawWidth, int drawHeight){
	
	float boxWidth = (float) drawWidth/bitmapWidth;
	float boxHeight = (float) drawHeight/bitmapHeight;
	
	int boxWidthInt = (int)(boxWidth+.99);
	int boxHeightInt = (int)(boxHeight+.99);
	for(int y=0; y <bitmapHeight;y++){
		for(int x=0; x<bitmapWidth;x++){
			int startx= (int)((float)x*boxWidth)+px;
			int starty= (int)((float)y*boxHeight)+py;
			fillRect(startx, starty, image[y*bitmapWidth+x], boxWidthInt, boxHeightInt);
		}
	}
}

void renderHUD();
void updateHUDInfo();

void viewportToScreen(Vector2D viewportVect, int* px, int* py){
	*px = ((viewportVect.x()+1.0f)/2.0f)*GAME_VIEW_WIDTH;;
	*py = ((viewportVect.y()+1.0f)/2.0f)*GAME_VIEW_HEIGHT;
}
Vector2D screenToViewport(int px, int py){
	return Vector2D((float)(px-GAME_VIEW_WIDTH/2)/(float)(GAME_VIEW_WIDTH/2), (float)(py-GAME_VIEW_HEIGHT/2)/(float)(GAME_VIEW_HEIGHT/2));
	
}

#endif /* Display_h */
