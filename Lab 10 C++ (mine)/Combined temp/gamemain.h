//
//  main.cpp
//  Lab 10
//
//  Created by Akarsh Kumar on 4/22/19.
//  Copyright � 2019 Akarsh Kumar. All rights reserved.
//



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


#ifdef RELEASE

#include "DrawST7735.h"

#else

#include <iostream>
#include <thread>
#include "DrawOpenGL.h"



#endif








void mystartGame(){
    //displayInitScreen();
//    Vector3D v(1,0,0);
    //Vector3D r(1,1,1);
//
//    for(float angle =0; angle<=2*M_PI+.01;angle+=M_PI/8){
//        std::cout<<angle*180/M_PI<<std::endl;
//        Vector3D ans = rotateVector(angle, v, r);
//        std::cout<<ans.x()<<std::endl;
//        std::cout<<ans.y()<<std::endl;
//        std::cout<<ans.z()<<std::endl;
//        std::cout<<std::endl;
//    }
    
    

}

void draw3DPoint(Vector3D coor, const Color& color){
    //float s, t, d;
    LinePlaneIntersection vpintersect = Camera::projectOntoViewPort(coor);
    
    Vector3D viewPortN = Camera::viewPortBvect.cross(Camera::viewPortAvect);
    
    Vector3D coorVP = coor-Camera::pos;
    if(coorVP.dot(viewPortN)>0 && vpintersect.doesIntersect()){
        
        vpintersect.calculateIntersectionPoint();
        vpintersect.calculateIntersectionOnPlane();
        
        int px = ((vpintersect.getIntersectionOnPlane().x()+1.0f)/2.0f)*DISPLAY_WIDTH;
        int py = ((vpintersect.getIntersectionOnPlane().y()+1.0f)/2.0f)*DISPLAY_HEIGHT;
        
        if(px>=0&&px<DISPLAY_WIDTH&&py>=0&&py<DISPLAY_HEIGHT){
            setColor(px, py, color);
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
    int p1x = ((p1.x()+1.0f)/2.0f)*DISPLAY_WIDTH;
    int p1y = ((p1.y()+1.0f)/2.0f)*DISPLAY_HEIGHT;
    int p2x = ((p2.x()+1.0f)/2.0f)*DISPLAY_WIDTH;
    int p2y = ((p2.y()+1.0f)/2.0f)*DISPLAY_HEIGHT;
    
    drawLine(p1x, p1y, p2x, p2y);
    
}
void drawLine3D(const Vector3D& p1, const Vector3D& p2){
    LinePlaneIntersection p1int = Camera::projectOntoViewPort(p1);
    LinePlaneIntersection p2int = Camera::projectOntoViewPort(p2);
    if(p1int.doesIntersect() && p2int.doesIntersect()){
        p1int.calculateIntersectionPoint();
        p1int.calculateIntersectionOnPlane();
        p2int.calculateIntersectionPoint();
        p2int.calculateIntersectionOnPlane();
        drawLine2D(p1int.getIntersectionOnPlane(), p2int.getIntersectionOnPlane());
    }
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
//        draw3DPoint(topleft+top.scale(i), Color(255,255,255));
//        draw3DPoint(topright+right.scale(i), Color(255,255,255));
//        draw3DPoint(botright+bot.scale(i), Color(255,255,255));
//        draw3DPoint(botleft+left.scale(i), Color(255,255,255));
        

    }
    drawLine3D(topleft, topright);
    drawLine3D(topright, botright);
    drawLine3D(botright, botleft);
    drawLine3D(botleft, topleft);
    
    
}
void render(){
    
}
void startRendering(){
    //Camera::dir = Vector3D(0,1,0);
    //Camera::right = Camera::dir.cross(Camera::up);
    
    Camera::pos = Vector3D(-1,0,0);
    std::chrono::system_clock::time_point current;
    std::chrono::duration<double> diff;
    
    std::chrono::system_clock::time_point fpsStart = std::chrono::system_clock::now();
    int fpsCount=0;
    while(true){
        //std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
        //usleep(100000);
        
				//Camera::pos = Camera::pos-xhat.scale(.01);
        //Camera::dir = rotateVector(-1*M_PI/180, Camera::dir, Camera::up);
        Camera::right = Camera::dir.cross(Camera::up);
        
        Camera::establishViewPort();
        
        
        //draw3DPoint(Vector3D(1,1,1), Color(255,255,255));
    
        
        for(int px = 0;px<DISPLAY_WIDTH;px++){
            for(int py = 0;py<DISPLAY_HEIGHT;py++){
                setColor(px, py, Color(0,0,0));
            }
        }
			
        //clearScreen();
        
        
        if(false){
        for(int px = 0;px<DISPLAY_WIDTH;px+=2){
            for(int py = 0;py<DISPLAY_HEIGHT;py+=2){
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
                float dist = infin;
                for(int i=0;i<Game::gameWalls.length();i++){
                        //drawObject(&(Game::gameObjects[i]));
                    Game::RayIntersect rayInt = (Game::gameWalls.get(i)).intersect(Camera::pos, dir);
                    float newdist = rayInt.intersectLocation.dist(Camera::pos);
                    if(rayInt.didIntersect && newdist<dist){
                        col = rayInt.color;
                        dist = newdist;
                    }
                    //1break;
                }
                
                //current = std::chrono::system_clock::now();
                //diff = (current - start)*1000000;
                //std::cout<<diff.count()<<std::endl;
                
                //11 units to calc
//                Game::RayIntersect rayInt = Game::zombie1.intersect(Camera::pos, dir);
//                float newdist = rayInt.intersectLocation.dist(Camera::pos);
//                if(rayInt.didIntersect && newdist<dist){
//                    col = rayInt.color;
//                    dist = newdist;
//                }
                
                //current = std::chrono::system_clock::now();
                //diff = (current - start)*1000000;
                //std::cout<<diff.count()<<std::endl;
                
                
                //7 units to calc
                setColor(px, py, col);
                for(int ix=0; ix <3;ix++){
                    for(int iy=0;iy<3;iy++){
                        //setColor(px+ix, py+iy, col);
                    }
                }
                
                if(true){
                    //0-0
                    //---
                    //0-0
                    setColor(px+1, py, col);
                    setColor(px, py+1, col);
                    setColor(px+1, py+1, col);
                    
                }
                
//                current = std::chrono::system_clock::now();
//                diff = (current - start)*1000000;
//                std::cout<<diff.count()<<std::endl;
            }
        }
        }
        
        //established viewport already
        for(int i=0;i<Game::gameWalls.length();i++){
            //drawObject(&(Game::gameObjects[i]));
            drawWallOutline(&(Game::gameWalls.get(i)));
        }
        
        
        
        solidifyDisplay();
        
        Vector3D dxZombie = (Camera::pos-Game::zombie1.m_axis) - Game::zombie1.m_pos;
        dxZombie = dxZombie.normalize().scale(.01);
        Game::zombie1.m_pos = Game::zombie1.m_pos+dxZombie;
        
        
        
        
        //current = std::chrono::system_clock::now();
        //diff = current-start;
        
        
        //std::cout << "Time to render one frame : " << diff.count() << " s\n";
        
        current = std::chrono::system_clock::now();
        //diff = (current -start)*1000000;
        //std::cout<<diff.count()<<std::endl;
        //std::cout<<"\n\n\n\n\n\n";
        
        diff = current-fpsStart;
        
        fpsCount++;
        if(diff.count()>=1){
            std::cout << "FPS : " << fpsCount << "\n";
            fpsCount = 0;
            fpsStart = std::chrono::system_clock::now();
        }
    }
}



int mainTM4C(){
#ifdef RELEASE
    startRendering();
    
#endif
    return 0;
}
int mainOpenGL(){
#ifndef RELEASE
    
    
    std::thread gameThread(mystartGame);
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
    
    mainOpenGL();
	
    return 0;
}



