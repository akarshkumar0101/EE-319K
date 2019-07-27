//
//  DrawST7735.h
//  Lab 10
//
//  Created by Akarsh Kumar on 4/27/19.
//  Copyright © 2019 Akarsh Kumar. All rights reserved.
//

#ifndef DrawST7735_h
#define DrawST7735_h

#include "Display.h"
#include "ST7735.h"





inline void rawSetColor(int x, int y, const Color& color){
    ST7735_DrawPixel(x, y, color.color);
}

void clearScreen(){
	ST7735_FillScreen(0);
}
void displayInitImpl(){
	
}
void displayInitScreen(){
	for(int x=0; x<DISPLAY_WIDTH;x++){
        for(int y=0; y <DISPLAY_HEIGHT;y++){
//          setColor(x,y, Color(x*255/DISPLAY_WIDTH, y*255/DISPLAY_HEIGHT, 128));
            rawSetColor(x, y, Color(x*255/DISPLAY_WIDTH, y*255/DISPLAY_HEIGHT, 128));
            //rawSetColor(x, y, Color(255,0,0));
            //setColor(x,y, Color(128,0,0));
        }
    }
}

void setColor(int x, int y, const Color& col){
	rawSetColor(x,y,col);
}

void solidifyDisplay(){
	
}

void fillRect(int x, int y, uint16_t color, int width, int height){
	ST7735_FillRect(x,y,width, height,color);
}

void fillScreen(uint16_t color){
	ST7735_FillScreen(color);
}

void drawBitMap(int x, int y, uint16_t* image, int width, int height){
	ST7735_DrawBitmap(x,y,image,width,height);
}

#endif /* DrawST7735_h */
