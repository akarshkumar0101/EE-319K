//
//  Display.h
//  Lab 10
//
//  Created by Akarsh Kumar on 4/22/19.
//  Copyright © 2019 Akarsh Kumar. All rights reserved.
//

#ifndef Display_h
#define Display_h


#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 160

//#define DISPLAY_WIDTH 10
//#define DISPLAY_HEIGHT 10

//#define DISPLAY_WIDTH 700
//#define DISPLAY_HEIGHT 700

#define DISPLAY_NUM_PIXELS DISPLAY_WIDTH*DISPLAY_HEIGHT


struct Color{
    Color(): Color(0,0,0){
    }
    Color(uint8_t r_, uint8_t g_, uint8_t b_): r(r_),g(g_),b(b_) {
    }
    
    uint8_t r, g, b;
};

Color pixels[DISPLAY_WIDTH][DISPLAY_HEIGHT];

void initPixels(){
    for(int x=0; x<DISPLAY_WIDTH;x++){
        for(int y=0; y <DISPLAY_HEIGHT;y++){
//            pixels[x][y].r = (x%2)*255;
//            pixels[x][y].g = (y%2)*255;
//            pixels[x][y].b = 0;
            
            pixels[x][y].r = 0;
            pixels[x][y].g = 0;
            pixels[x][y].b = 0;
        }
    }
}

Color getColor(int x, int y){
    return pixels[x][y];
}

void setColor(int x, int y, Color col){
    pixels[x][y] = col;
}



#endif /* Display_h */
