//
//  main.cpp
//  Lab 10
//
//  Created by Akarsh Kumar on 4/22/19.
//  Copyright � 2019 Akarsh Kumar. All rights reserved.
//

#define RELEASE

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

//#include <iostream>


#include <math.h>


#include "AKMath.h"
#include "Game.h"
#include "Camera.h"
#include "Matrix3x3.h"
#include "Vector.h"
#include "VectorMath.h"
#include "Display.h"
#include "Texture.h"
#include "Drawing.h"


#ifdef RELEASE

#include "DrawST7735.h"
#include "ADCSWTrigger.h"
#include "DAC.h"

#else

#include <iostream>
#include <thread>
#include <chrono>
#include "DrawOpenGL.h"



#endif




void raytracing(){
	for(int py = 0;py<DISPLAY_HEIGHT;py+=1){
		for(int px = 0;px<DISPLAY_WIDTH;px+=1){
    
            //start = std::chrono::system_clock::now();
        
        
            Color col (0,0,0);
            float cx = (2.0f*(float)px-(float)DISPLAY_WIDTH)/(float)DISPLAY_WIDTH;
            float cy = (2.0f*(float)py-(float)DISPLAY_HEIGHT)/(float)DISPLAY_HEIGHT;
        
            //Vector3D dir = Camera::getPixelRay(cx, cy);
            Vector3D dir = Camera::getPixelRayWithViewPort(cx, cy);
        
        
            //current = std::chrono::system_clock::now();
            //diff = (current - start)*1000000;
            //std::cout<<diff.count()<<std::endl;
        
        
            //53 units to calc
            float dist = 10000000;
            for(int i=0;i<Game::gameWalls.length();i++){
                LinePlaneIntersection rayInt = (Game::gameWalls.get(i)).intersect(Camera::pos, dir);
                if(rayInt.doesIntersect()){
                    rayInt.calculateIntersectionPoint();
                    rayInt.calculateIntersectionOnPlane();
                    if(rayInt.intersectionIsInFront()){
                        float newdist = rayInt.getIntersectionPoint().dist(Camera::pos);
                        if(rayInt.intersectsNormalPlane() && newdist<dist){
                            
                            col = Game::gameWalls.get(i).color;
                            //col = 0xFFFF;
                            dist = newdist;
                        }
                        //1break;
                    }
                }
            }
            //col = Color(0,0,255);
            //fillRect(py-3,px-3,7,7,col.color);
            setColor(px, py, col.color);
        }
    }
}
/*
#define XPARTNUM 8
#define XPARTLEN DISPLAY_WIDTH/XPARTNUM
#define YPARTNUM 8
#define YPARTLEN DISPLAY_HEIGHT/YPARTNUM

uint16_t partitionBitMap[XPARTLEN * YPARTLEN];

void raytracing2(){
	for(int ypart = 0; ypart<YPARTNUM;ypart++){
		for(int xpart = 0; xpart<XPARTNUM;xpart++){
			
			for(int y=0; y<YPARTLEN;y+=4){
				for(int x=0; x<XPARTLEN;x+=4){
					
					int px = x+xpart*XPARTLEN;
					int py = y+ypart*YPARTLEN;
					
					Color col (0,0,0);
					float cx = (2.0f*(float)px-(float)DISPLAY_WIDTH)/(float)DISPLAY_WIDTH;
					float cy = (2.0f*(float)py-(float)DISPLAY_HEIGHT)/(float)DISPLAY_HEIGHT;
					
					//Vector3D dir = Camera::getPixelRay(cx, cy);
					Vector3D dir = Camera::getPixelRayWithViewPort(cx, cy);
					
					
					//current = std::chrono::system_clock::now();
					//diff = (current - start)*1000000;
					//std::cout<<diff.count()<<std::endl;
					
					
					//53 units to calc
					float dist = infin;
					for(int i=0;i<Game::gameWalls.length();i++){
									//drawObject(&(Game::gameObjects[i]));
                        LinePlaneIntersection rayInt = (Game::gameWalls.get(i)).intersect(Camera::pos, dir);
                        if(rayInt.doesIntersect()){
                            rayInt.calculateIntersectionPoint();
                            rayInt.calculateIntersectionOnPlane();
                            float newdist = rayInt.getIntersectionPoint().dist(Camera::pos);
                            if(rayInt.intersectsNormalPlane() && newdist<dist){
                                col = Game::gameWalls.get(i).color;
                                dist = newdist;
                            }
                            //1break;
                        }
					}
					
					
					partitionBitMap[x+y*XPARTLEN] = col.color;
					
				}
			}
			drawBitMap(ypart*YPARTLEN, xpart*XPARTLEN, partitionBitMap, YPARTLEN, XPARTLEN);
		}
	}
}
 */

void draw(){

    //Camera::pos = Camera::pos-xhat.scale(.01);
    //Camera::dir = rotateVector(-1*M_PI/180, Camera::dir, Camera::up);
    Camera::right = Camera::dir.cross(Camera::up);
    
    Camera::establishViewPort();
    
		for(int y=0;y<GAME_VIEW_HEIGHT;y++){
			for(int x=0;x<GAME_VIEW_WIDTH;x++){
				setGameColor(x,y,0);
			}
		}
		Vector3D dirXY = Vector3D(Camera::dir.x(), Camera::dir.y(),0);
		Vector3D horizonPoint = dirXY.scale(10000)+Camera::pos;
		LinePlaneIntersection hpInt = Camera::projectOntoViewPort(horizonPoint);
		
		
		if(hpInt.doesIntersect()){
			hpInt.calculateIntersectionPoint();
			hpInt.calculateIntersectionOnPlane();
			Vector2D point = hpInt.getIntersectionOnPlane();
			int horizonPx, horizonPy;
			viewportToScreen(point,&horizonPx, &horizonPy);
			
			
			for(int y=0;y<AKmin(GAME_VIEW_HEIGHT,horizonPy);y++){
				if(y<0||y>=GAME_VIEW_HEIGHT){
					continue;
				}
				for(int x=0;x<GAME_VIEW_WIDTH;x++){
					setGameColor(x,y,Color(0,155+(horizonPy-y)/2,0).color);
				}
			}
			for(int y=horizonPy;y<GAME_VIEW_HEIGHT;y++){
				if(y<0||y>=GAME_VIEW_HEIGHT){
					continue;
				}
				for(int x=0;x<GAME_VIEW_WIDTH;x++){
					setGameColor(x,y,Color(128,128,128).color);
				}
			}
			
		}
		
		/*
		if(Game::numGameTicks%10==0){
			ST7735_SetCursor(0,0);
			ST7735_OutUDec(Game::numGameTicks);
		}
		*/
		
		
		/*
		draw3DPoint(Vector3D(0,0,0),Color(255,0,0).color);
		draw3DPoint(Vector3D(1,0,0),Color(255,0,0).color);
		draw3DPoint(Vector3D(0,1,0),Color(255,0,0).color);
		draw3DPoint(Vector3D(1,1,0),Color(255,0,0).color);
    draw3DPoint(Vector3D(0,0,1),Color(255,0,0).color);
		draw3DPoint(Vector3D(1,0,1),Color(255,0,0).color);
		draw3DPoint(Vector3D(0,1,1),Color(255,0,0).color);
		draw3DPoint(Vector3D(1,1,1),Color(255,0,0).color);
		*/
    
    if(false){
        raytracing();
    }
    else{
        //established viewport already
        for(int i=0;i<Game::gameWalls.length();i++){
            //drawObject(&(Game::gameObjects[i]));
            //drawWallOutline(&(Game::gameWalls.get(i)));
        }
    }
		
		/*
		for(int x=0; x<DISPLAY_WIDTH;x++){
			for(int y=0; y <DISPLAY_HEIGHT;y++){
				setColor(x,y,Color(255,0,0));
			}
		}
		*/
    
    //solidifyDisplay();
    
    for(int i=0; i <Game::gameZombies.length();i++){
        Game::Zombie& zomb = Game::gameZombies.get(i);
        drawZombie(zomb);
    }
		for(int i=0; i <Game::gameAmmoCarts.length();i++){
        Game::AmmoCart& cart = Game::gameAmmoCarts.get(i);
        drawAmmoCart(cart);
    }
		
		//ST7735_DrawBitmap(64, 160,gunTexture, 28,32);
		//dynamicDrawBitMap(80,64,ZOMBIE_MAP,5,5,15,15);
		
		
		if(Game::showShooting){
			scaleDrawBitMapGame((GAME_VIEW_WIDTH-GUNFIRE_TEXTURE_WIDTH+10)/2,GUNFIRE_TEXTURE_HEIGHT/2-5,gunfireTexture,GUNFIRE_TEXTURE_WIDTH, GUNFIRE_TEXTURE_HEIGHT,25,25);
			Game::showShooting = false;
		}
    
    for(int i=-5;i<=5;i++){
			if(i==-1 || i ==0||i==1){
				continue;
			}
        setGameColor(GAME_VIEW_WIDTH/2+i, GAME_VIEW_HEIGHT/2, 0xFFFF);
        setGameColor(GAME_VIEW_WIDTH/2, GAME_VIEW_HEIGHT/2+i, 0xFFFF);
    }
    
		
}
//8.86 sec to set 403,200 pixel colors - around 45,500 pixels per sec
//1 sec to call clear screen 20 times - around 20 fps
//4.1 sec to draw 5000 bitmaps of size 320 - around 390,243.9 pixels per sec
//3.5 sec to do 1000*20480 operations





void startRendering(){
    
    //clearScreen();
		

    int N=0;
		
		while(!Game::gameOver){
        N++;
        
			Game::gameTick();
        draw();
				renderGame();
        
        
        
#ifdef RELEASE
				
			/*
        if(GPIO_PORTE_DATA_R & 0x08){
            Game::rotateHorizontal(-.1);
        }
        if(GPIO_PORTE_DATA_R & 0x02){
            Game::rotateHorizontal(.1);
        }
			*/
				if(!(GPIO_PORTB_DATA_R & 0x40)){
						if(!Game::isShooting){
							Game::shoot();
						}
        }
				else{
					Game::isShooting = false;
				}
				
				if(!(GPIO_PORTB_DATA_R & 0x80)){
					Game::nuke();
        }
				
				if(Random()<5){
					playZombieSound();
				}
				
				
				uint32_t joystickdata[4];
		
				ADC_In89(joystickdata);
				joystickdata[0] &=0xFFF;
				joystickdata[1] &=0xFFF;
				joystickdata[2] &=0xFFF;
				joystickdata[3] &=0xFFF;
		
				/*
				float rotateh = (float)((joystickdata[0])-2034);
				float rotatev = (float)((joystickdata[1])-2112);
				float moveh = (float)((joystickdata[2])-2050);
				float movev = (float)((joystickdata[3])-2033);
				
				*/
				
				
				float rotatev = (float)(joystickdata[0]);
				float rotateh = (float)(joystickdata[1]);
				float movev = (float)(joystickdata[2]);
				float moveh = (float)(joystickdata[3]);
				
				//0 is right stick(camera) vertical inverted
				//1 is right stick(camera) horizontal proper
				//2 is left stick(move) vertical proper
				//3 is left stick(move) horizontal inverted
				
				rotatev-=2010;
				rotateh-=2090;
				movev-=2070;
				moveh-=2090;
				
				rotatev /=2048;
				rotateh /=2048;
				movev /=2048;
				moveh /=2048;
				
				rotatev*=-.1;
				rotateh*=-.1;
				movev*=.05;
				moveh*=-.05;
				
				if(abs(rotateh)>.02){
					Game::rotateHorizontal(rotateh);
				}
				if(abs(rotatev)>.02){
					Game::rotateVertical(rotatev);
				}
				if(abs(moveh)>.02){
					Game::moveSide(moveh);
				}
				if(abs(movev)>.02){
					Game::moveForward(movev);
				}
				
						
        
        
#endif
        
    }
    fillScreen(Color(0,0,0).color);
		
		
		ST7735_SetCursor(5,5);
		ST7735_SetTextColor(Color(255,0,0).color);
		
		
		ST7735_OutString("YOU DIED");
		
		
		ST7735_SetTextColor(Color(0,255,255).color);
		
		ST7735_SetCursor(5,9);
		ST7735_OutString("Round:");
		ST7735_SetCursor(5,12);
		ST7735_OutString("Zombies Killed:");
		
		ST7735_SetTextColor(Color(0,255,0).color);
		ST7735_SetCursor(5,10);
		ST7735_OutUDec(Game::round);
		ST7735_SetCursor(5,13);
		ST7735_OutUDec(Game::numZombiesKilled);
		
}



int mainTM4C(){
#ifdef RELEASE
    
    renderHUD();
		
		Timer1_Init(&Game::gameTick,2666666); // 30 Hz 
    startRendering();
    
#endif
    return 0;
}
int mainOpenGL(){
#ifndef RELEASE
    
    std::thread renderingThread(startRendering);
    
    startRenderingFromPixelBuffer();
	
#endif
    return 0;
}








int mainf() {
    displayInit();
    
    displayInitScreen();
    
    solidifyDisplay();
    Game::initGame();
    
#ifdef RELEASE
    mainTM4C();
#else
    mainOpenGL();
#endif
	
    return 0;
}

//takes 30 sec to rotate 360 deg when calculating and drawing 20 pixels per edge (480 pixel draws)
//takes 17 sec to rotate 360 deg when calc and draw 1 pixel
//takes 21 sec to rotate 360 deg when calc 1 and pixels 480 (479 dummy draws)

//does half the time come from rotating camera vector?? with sins and cos??


//MAIN TIME CONSUMER:
//drawing the walls and clearing the screen*


//OKAY, Steps:
// try enabling floating point see how that affects it.
// if it doesn't help, convert whole thing to integers
