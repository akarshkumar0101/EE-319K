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

#define DISPLAY_WIDTH 160
#define DISPLAY_HEIGHT 128

#define CROSSHAIR_RADIUS 10

//#define DISPLAY_WIDTH 10
//#define DISPLAY_HEIGHT 10

//#define DISPLAY_WIDTH 700
//#define DISPLAY_HEIGHT 700

#define DISPLAY_NUM_PIXELS DISPLAY_WIDTH*DISPLAY_HEIGHT


#define BLACK 0x0000
#define RED_MASK 0xF800
#define GREEN_MASK 0x07E0
#define BLUE_MASK 0x001F

#define RED_COLOR_SHIFT 11
#define GREEN_COLOR_SHIFT 5
#define BLUE_COLOR_SHIFT 0

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
        return (color&RED_MASK)>>RED_COLOR_SHIFT<<3;
    }
    uint8_t getG() const{
        return (color&GREEN_MASK)>>GREEN_COLOR_SHIFT<<2;
    }
    uint8_t getB() const{
        return (color&BLUE_MASK)>>BLUE_COLOR_SHIFT<<3;
    }
    
};


Color avgColor2(Color c1, Color c2){
    return Color((c1.getR()+c2.getR())/2, (c1.getG()+c2.getG())/2, (c1.getB()+c2.getB())/2);
}

/*
std::ostream& operator<<(std::ostream& os, const Color& col)
{
    os<< "Color: ("<<(int)col.getR()<<", "<<(int)col.getG()<<", " <<(int)col.getB()<<")";
    return os;
}
*/

void displayInit();
void displayInitScreen();

void setColor(int x, int y, const Color& col);

void solidifyDisplay();



void drawLine(int x1, int y1, int x2, int y2) {
    float dist = (y2-y1)*(y2-y1)+(x2-x1);
    dist = sqrt(dist);
    
    float dx = ((float)(x2-x1))/dist/2;
    float dy = ((float)(y2-y1))/dist/2;
    float x = x1;
    float y = y1;
    for(int i = 0; i<=dist*2;i++){
        setColor((int)x,(int)y,Color(255,0,255));
        
        x+=dx;
        y+=dy;
    }
}






#endif /* Display_h */
