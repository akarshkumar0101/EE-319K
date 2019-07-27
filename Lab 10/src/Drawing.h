//
//  Drawing.h
//  Lab 10
//
//  Created by Akarsh Kumar on 5/5/19.
//  Copyright © 2019 Akarsh Kumar. All rights reserved.
//

#ifndef Drawing_h
#define Drawing_h

#include "Texture.h"
#include "Display.h"
#include "DrawST7735.h"
#include "ST7735.h"
#include "Game.h"


#define LR_BORDER_LENGTH (DISPLAY_WIDTH-GAME_VIEW_WIDTH)/2
#define BOT_BORDER_LENGTH LR_BORDER_LENGTH*3
#define TOP_BORDER_LENGTH DISPLAY_HEIGHT-BOT_BORDER_LENGTH-GAME_VIEW_HEIGHT

uint16_t gamePixelBuffer[GAME_VIEW_WIDTH*GAME_VIEW_HEIGHT];


void renderGame(){
    ST7735_DrawBitmap(LR_BORDER_LENGTH, TOP_BORDER_LENGTH+GAME_VIEW_HEIGHT-1, gamePixelBuffer, GAME_VIEW_WIDTH, GAME_VIEW_HEIGHT);
}
void scaleDrawBitMapScreen(int px, int py, const uint16_t* image, int bitmapWidth, int bitmapHeight, int drawWidth, int drawHeight);


void updateHUDInfo(){
	ST7735_SetCursor(17,12);
	ST7735_OutString("   ");
	ST7735_SetCursor(17,12);
	ST7735_OutUDec(Game::numBullets);
	
	ST7735_SetCursor(17,14);
	ST7735_OutString(" ");
	ST7735_SetCursor(17,14);
	ST7735_OutUDec(Game::numNukesAvailable);
}

void renderInfo() {
	scaleDrawBitMapScreen(90, 133, bulletTexture, BULLET_TEXTURE_WIDTH, BULLET_TEXTURE_HEIGHT, 5,15);
	
	scaleDrawBitMapScreen(85, 147, nukeTexture, NUKE_TEXTURE_WIDTH, NUKE_TEXTURE_HEIGHT, 15,9);
	updateHUDInfo();
}


void drawHealth(){
	for(int i=0;i<Game::health;i++){
		scaleDrawBitMapScreen(15+10*i, 133, heartTexture, HEART_TEXTURE_WIDTH, HEART_TEXTURE_HEIGHT, 8,7);
	}
}

void renderDynamicHUD(){
		scaleDrawBitMapScreen(LR_BORDER_LENGTH, DISPLAY_HEIGHT, cobblestoneTexture, COBBLESTONE_TEXTURE_WIDTH, COBBLESTONE_TEXTURE_HEIGHT, GAME_VIEW_WIDTH, BOT_BORDER_LENGTH);
		scaleDrawBitMapScreen((DISPLAY_WIDTH-GUN_TEXTURE_WIDTH)/2+2, DISPLAY_HEIGHT-1,  gunTexture, GUN_TEXTURE_WIDTH, GUN_TEXTURE_HEIGHT, 45,45);
		renderInfo();
}
void renderHUD(){
		ST7735_SetCursor(4,0);
		ST7735_SetTextColor(0xFF);
		ST7735_OutString("KINO DER EER");
		
    ST7735_DrawBitmap(0, DISPLAY_HEIGHT-1, leftmossycobblestoneTexture, LEFTMOSSYCOBBLESTONE_TEXTURE_WIDTH, LEFTMOSSYCOBBLESTONE_TEXTURE_HEIGHT);
    ST7735_DrawBitmap(DISPLAY_WIDTH-RIGHTMOSSYCOBBLESTONE_TEXTURE_WIDTH, DISPLAY_HEIGHT-1, rightmossycobblestoneTexture, RIGHTMOSSYCOBBLESTONE_TEXTURE_WIDTH, RIGHTMOSSYCOBBLESTONE_TEXTURE_HEIGHT);
		renderDynamicHUD();
		
		drawHealth();
}



inline void setGameColor(const int x, const int y, const uint16_t& color){
    gamePixelBuffer[y*GAME_VIEW_WIDTH+x] = color;
}


void draw3DPoint(Vector3D coor, const uint16_t color){
    //float s, t, d;
    LinePlaneIntersection vpintersect = Camera::projectOntoViewPort(coor);
    
    if(Camera::isInDirectionOfCamera(coor) && vpintersect.doesIntersect()){
        
        vpintersect.calculateIntersectionPoint();
        vpintersect.calculateIntersectionOnPlane();
        
        int px;
        int py;
        
        viewportToScreen(vpintersect.getIntersectionOnPlane(),&px,&py);
        
        if(px>=0&&px<GAME_VIEW_WIDTH&&py>=0&&py<GAME_VIEW_HEIGHT){
					setGameColor(px,py,color);
        }
    }
}

/*
 void pixelResolution(Game::GameObject* goptr, int* out_x, int* out_y){
 //xdir
 float t1, t2, t3, t4;
 //ydir
 float s1, s2, s3, s4;
 float d1, d2, d3, d4;
 Camera::projectOntoViewPort(goptr->m_pos, &s1, &t1, &d1);
 Camera::projectOntoViewPort((goptr)->m_pos+(goptr)->m_aVect, &s2, &t2, &d2);
 Camera::projectOntoViewPort((goptr)->m_pos+(goptr)->m_bVect, &s3, &t3, &d3);
 Camera::projectOntoViewPort((goptr)->m_pos+(goptr)->m_aVect+(goptr)->m_bVect, &s4, &t4, &d4);
 
 float smin = infin, smax = -infin, tmin = infin, tmax = -infin;
 
 if(d1!=infin && d1!=-infin){
 smin = min(smin, s1);
 smax = max(smax, s1);
 tmin = min(tmin, t1);
 tmax = max(tmax, t1);
 }
 if(d2!=infin && d2!=-infin){
 smin = min(smin, s2);
 smax = max(smax, s2);
 tmin = min(tmin, t2);
 tmax = max(tmax, t2);
 }
 if(d3!=infin && d3!=-infin){
 smin = min(smin, s3);
 smax = max(smax, s3);
 tmin = min(tmin, t3);
 tmax = max(tmax, t3);
 }
 if(d4!=infin && d4!=-infin){
 smin = min(smin, s4);
 smax = max(smax, s4);
 tmin = min(tmin, t4);
 tmax = max(tmax, t4);
 }
 *out_x = (tmax-tmin)*DISPLAY_WIDTH/2;
 *out_y = (smax-smin)*DISPLAY_HEIGHT/2;
 }
 
 void drawObject(Game::GameObject* goptr) {
 
 int resx, resy;
 
 pixelResolution(goptr, &resx, &resy);
 
 for(float resxi = 0; resxi < 1; resxi += (float)1/resx){
 for(float resyi = 0; resyi < 1; resyi+= (float)1/resy){
 Vector3D point = goptr->m_pos + goptr->m_aVect.scale(resyi) + goptr->m_bVect.scale(resxi);
 draw3DPoint(point, goptr->texture->get(resxi*goptr->texture->width, resyi*goptr->texture->height));
 }
 }
 }
 */

void drawLine2D(const Vector2D& p1, const Vector2D& p2){
    float dy = abs(p2.y()-p1.y());
    float dx = abs(p2.x()-p1.x());
    
    
    float p1xf;
    float p1yf;
    
    float p2xf;
    float p2yf;
    
    if(dy>dx){
        float m = (p2.x()-p1.x())/(p2.y()-p1.y());
        float b = p1.x()-m*p1.y();
        
        p1yf = AKmax(-1.0, p1.y());
        p1yf = AKmin(1.0, p1yf);
        p1xf = m*p1yf+b;
        
        p2yf = AKmax(-1.0, p2.y());
        p2yf = AKmin(1.0, p2yf);
        p2xf = m*p2yf+b;
        
    }
    else{
        float m = (p2.y()-p1.y())/(p2.x()-p1.x());
        float b = p1.y()-m*p1.x();
        
        p1xf = AKmax(-1.0, p1.x());
        p1xf = AKmin(1.0, p1xf);
        p1yf = m*p1xf+b;
        
        p2xf = AKmax(-1.0, p2.x());
        p2xf = AKmin(1.0, p2xf);
        p2yf = m*p2xf+b;
        
    }
    int p1x = ((p1xf+1.0f)/2.0f)*GAME_VIEW_WIDTH;
    int p1y = ((p1yf+1.0f)/2.0f)*GAME_VIEW_HEIGHT;
    int p2x = ((p2xf+1.0f)/2.0f)*GAME_VIEW_WIDTH;
    int p2y = ((p2yf+1.0f)/2.0f)*GAME_VIEW_HEIGHT;
    
    drawLine(p1x, p1y, p2x, p2y);
    
}

void drawLine3D(const Vector3D& p1, const Vector3D& p2){
    
    
    bool isInDir1 = Camera::isInDirectionOfCamera(p1);
    bool isInDir2 = Camera::isInDirectionOfCamera(p2);
    if(!isInDir1 && !isInDir2){
        //not in view at all
        return;
    }
    const Vector3D* p1p = &p1;
    const Vector3D* p2p = &p2;
    
    Vector3D viewPortIntersectPoint;
    if(!isInDir1 || !isInDir2){
        LinePlaneIntersection lineIntersectViewPort(p1,p2-p1,Camera::viewPortPos, Camera::viewPortAvect, Camera::viewPortBvect);
        lineIntersectViewPort.calculateIntersectionPoint();
        
        viewPortIntersectPoint = lineIntersectViewPort.getIntersectionPoint();
        
        if(!isInDir1){
            p1p = &viewPortIntersectPoint;
        }
        else if(!isInDir2){
            p2p = &viewPortIntersectPoint;
        }
    }
    
    
    LinePlaneIntersection p1int = Camera::projectOntoViewPort(*p1p);
    LinePlaneIntersection p2int = Camera::projectOntoViewPort(*p2p);
    
    p1int.calculateIntersectionPoint();
    p1int.calculateIntersectionOnPlane();
    p2int.calculateIntersectionPoint();
    p2int.calculateIntersectionOnPlane();
    drawLine2D(p1int.getIntersectionOnPlane(), p2int.getIntersectionOnPlane());
    
}
void drawWallOutline(Game::Wall* wall){
    const Vector3D& pos = wall->m_pos;
    const Vector3D& aVect = wall->m_aVect;
    const Vector3D& bVect = wall->m_bVect;
    Vector3D topleft = pos+aVect-bVect;
    Vector3D topright = pos+aVect+bVect;
    Vector3D botleft = pos-aVect-bVect;
    Vector3D botright = pos-aVect+bVect;
    
    
    
    Vector3D top = topright - topleft;
    Vector3D right = botright- topright;
    Vector3D bot = botleft - botright;
    Vector3D left = topleft - botleft;
    
    for(float i=0.0;i<=1.0f;i+=.05){
        draw3DPoint(topleft+top.scale(i), Color(255,255,255).color);
        draw3DPoint(topright+right.scale(i), Color(255,255,255).color);
        draw3DPoint(botright+bot.scale(i), Color(255,255,255).color);
        draw3DPoint(botleft+left.scale(i), Color(255,255,255).color);
        
        for(float j=0.0;j<=1.0f;j+=.05){
            draw3DPoint(botleft+aVect.scale(2*i)+bVect.scale(2*j), Color(255,255,255).color);
        }
    }
     /*
    drawLine3D(topleft, topright);
    drawLine3D(topright, botright);
    drawLine3D(botright, botleft);
    drawLine3D(botleft, topleft);
      */
    
    
}

void scaleDrawBitMapGame(int px, int py, const uint16_t* image, int bitmapWidth, int bitmapHeight, int drawWidth, int drawHeight);

void drawZombie(const Game::Zombie& zombie){
    const Vector3D& zombpos = zombie.m_pos;
    if(!Camera::isInDirectionOfCamera(zombpos)){
        return;
    }
    
		Vector3D topLeftPoint = zombie.m_pos+zombie.bVect-zombie.aVect;
		Vector3D botRightPoint = zombie.m_pos-zombie.bVect+zombie.aVect;
		
		LinePlaneIntersection lpi1 = Camera::projectOntoViewPort(topLeftPoint);
		LinePlaneIntersection lpi2 = Camera::projectOntoViewPort(botRightPoint);
		
		
		
		if(lpi1.doesIntersect() || lpi2.doesIntersect()){
			lpi1.calculateIntersectionPoint();
			lpi2.calculateIntersectionPoint();
			lpi1.calculateIntersectionOnPlane();
			lpi2.calculateIntersectionOnPlane();
			
			int p1x, p1y, p2x, p2y;
			
			viewportToScreen(lpi1.getIntersectionOnPlane(),&p1x, &p1y);
			viewportToScreen(lpi2.getIntersectionOnPlane(),&p2x, &p2y);
			
			int newheight = AKabs(p1y-p2y);
			int newwidth = newheight*ZOMBIE_TEXTURE_WIDTH/ZOMBIE_TEXTURE_HEIGHT;//calculated from newheight (to maintain zombie aspect ratio)
			scaleDrawBitMapGame(p1x,p1y,zombieTexture, ZOMBIE_TEXTURE_WIDTH, ZOMBIE_TEXTURE_HEIGHT, newwidth, newheight); 
		}
		
		
}

void drawAmmoCart(const Game::AmmoCart& cart){
    const Vector3D& cartpos = cart.m_pos;
    if(!Camera::isInDirectionOfCamera(cartpos)){
        return;
    }
    
		Vector3D topLeftPoint = cart.m_pos+cart.bVect-cart.aVect;
		Vector3D botRightPoint = cart.m_pos-cart.bVect+cart.aVect;
		
		LinePlaneIntersection lpi1 = Camera::projectOntoViewPort(topLeftPoint);
		LinePlaneIntersection lpi2 = Camera::projectOntoViewPort(botRightPoint);
		
		
		
		if(lpi1.doesIntersect() || lpi2.doesIntersect()){
			lpi1.calculateIntersectionPoint();
			lpi2.calculateIntersectionPoint();
			lpi1.calculateIntersectionOnPlane();
			lpi2.calculateIntersectionOnPlane();
			
			int p1x, p1y, p2x, p2y;
			
			viewportToScreen(lpi1.getIntersectionOnPlane(),&p1x, &p1y);
			viewportToScreen(lpi2.getIntersectionOnPlane(),&p2x, &p2y);
			
			int newwidth = AKabs(p1x-p2x);
			int newheight = newwidth*AMMOCART_TEXTURE_HEIGHT/AMMOCART_TEXTURE_WIDTH;//calculated from newheight (to maintain zombie aspect ratio)
			scaleDrawBitMapGame(p1x,p1y,ammocartTexture, AMMOCART_TEXTURE_WIDTH, AMMOCART_TEXTURE_HEIGHT, newwidth, newheight); 
		}
		
		
}



//draw like a normal bit map on screen with ST7735, starts at top left (0,0) and draws to the right up direction
void scaleDrawBitMapScreen(int px, int py, const uint16_t* image, int bitmapWidth, int bitmapHeight, int drawWidth, int drawHeight){
	py = py-drawHeight;
	for(int y=0; y <drawHeight;y++){
        for(int x=0; x<drawWidth;x++){
            
            int bitmapY = bitmapHeight-1-y*bitmapHeight/drawHeight;
            int bitmapX = x*bitmapWidth/drawWidth;
            const uint16_t color = image[bitmapY*bitmapWidth+bitmapX];
            
						if(color!=BLACK){
							rawSetColor(px+x, py+y, color);
						}
        }
    }
}

//draw with origin on bot leftand draws going down and right
void scaleDrawBitMapGame(int px, int py, const uint16_t* image, int bitmapWidth, int bitmapHeight, int drawWidth, int drawHeight){
		py = py-drawHeight;
    for(int y=0; y <drawHeight;y++){
				if(py+y<0 || py+y>=GAME_VIEW_HEIGHT){
					continue;
				}
        for(int x=0; x<drawWidth;x++){
            if(px+x<0 || px+x>=GAME_VIEW_WIDTH){
							continue;
						}
            int bitmapY = y*bitmapHeight/drawHeight;
            int bitmapX = x*bitmapWidth/drawWidth;
            const uint16_t color = image[bitmapY*bitmapWidth+bitmapX];
            if(color!=BLACK){
							
							setGameColor(px+x, py+y, color);
							
						}
        }
    }
}


#endif /* Drawing_h */
