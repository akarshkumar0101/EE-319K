//
//  main.cpp
//  Lab 10
//
//  Created by Akarsh Kumar on 4/22/19.
//  Copyright © 2019 Akarsh Kumar. All rights reserved.
//


//#define RELEASE

#include <iostream>
#include <thread>
#include <unistd.h>
#include <chrono>
#include <ctime>
#include <vector>

#include "Math.h"
#include "Game.h"
#include "Camera.h"
#include "Matrix3x3.h"
#include "Vector3D.h"
#include "VectorMath.h"


#include "Display.h"
#ifndef RELEASE
#include "DrawOpenGL.h"
#else
#include "DrawST7735.h"
#endif


void startGame(){
    
//    Vector3D v(1,0,0);
    Vector3D r(1,1,1);
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
    float s, t, d;
    Camera::projectOntoViewPort(coor, &s, &t, &d);
    
    Vector3D viewPortN = Camera::viewPortAvect.cross(Camera::viewPortBvect);
    
    Vector3D coorVP = coor-Camera::pos;
    if(coorVP.dot(viewPortN)>0 && d!=infin && d!=-infin){
        int px = ((t+1.0f)/2.0f)*DISPLAY_WIDTH;
        int py = ((s+1.0f)/2.0f)*DISPLAY_HEIGHT;
        
        if(px>=0&&px<DISPLAY_WIDTH&&py>=0&&py<DISPLAY_HEIGHT){
            setColor(px, py, color);
        }
    }
}
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
        smin = std::min(smin, s1);
        smax = std::max(smax, s1);
        tmin = std::min(tmin, t1);
        tmax = std::max(tmax, t1);
    }
    if(d2!=infin && d2!=-infin){
        smin = std::min(smin, s2);
        smax = std::max(smax, s2);
        tmin = std::min(tmin, t2);
        tmax = std::max(tmax, t2);
    }
    if(d3!=infin && d3!=-infin){
        smin = std::min(smin, s3);
        smax = std::max(smax, s3);
        tmin = std::min(tmin, t3);
        tmax = std::max(tmax, t3);
    }
    if(d4!=infin && d4!=-infin){
        smin = std::min(smin, s4);
        smax = std::max(smax, s4);
        tmin = std::min(tmin, t4);
        tmax = std::max(tmax, t4);
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

void startRendering(){
    //Camera::dir = Vector3D(0,1,0);
    //Camera::right = Camera::dir.cross(Camera::up);
    
    Camera::pos = Vector3D(-1,0,0);
    std::chrono::system_clock::time_point current;
    std::chrono::duration<double> diff;
    
    std::chrono::system_clock::time_point fpsStart = std::chrono::system_clock::now();
    int fpsCount=0;
    while(true){
        std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
        //usleep(1);
        
        //Camera::dir = rotateVector(1*M_PI/180, Camera::dir, Camera::up);
        Camera::right = Camera::dir.cross(Camera::up);
        
        Camera::establishViewPort();
        
        
        for(int px = 0;px<DISPLAY_WIDTH;px++){
            for(int py = 0;py<DISPLAY_HEIGHT;py++){
                //setColor(px, py, Color(0,0,0));
            }
        }
        
        
        if(true){
        for(int px = 0;px<DISPLAY_WIDTH;px+=1){
            for(int py = 0;py<DISPLAY_HEIGHT;py+=1){
                start = std::chrono::system_clock::now();
                
                
                Color col (0,0,0);
                float cx = (2.0f*(float)px-(float)DISPLAY_WIDTH)/(float)DISPLAY_WIDTH;
                float cy = (2.0f*(float)py-(float)DISPLAY_HEIGHT)/(float)DISPLAY_HEIGHT;
                
                //Vector3D dir = Camera::getPixelRay(cx, cy);
                Vector3D dir = Camera::getPixelRayWithViewPort(cx, cy);
                
                
                current = std::chrono::system_clock::now();
                diff = (current - start)*1000000;
                //std::cout<<diff.count()<<std::endl;
                
                
                //53 units to calc
                float dist = infin;
                for(std::vector<Game::GameObject*>::iterator it = Game::gameObjects.begin(); it!=Game::gameObjects.end();it++){
                    Game::RayIntersect rayInt = (*it)->intersect(Camera::pos, dir);
                    float newdist = rayInt.intersectLocation.dist(Camera::pos);
                    if(rayInt.didIntersect && newdist<dist){
                        col = rayInt.color;
                        dist = newdist;
                    }
                    //1break;
                }
                
                current = std::chrono::system_clock::now();
                diff = (current - start)*1000000;
                //std::cout<<diff.count()<<std::endl;
                
                //11 units to calc
//                Game::RayIntersect rayInt = Game::zombie1.intersect(Camera::pos, dir);
//                float newdist = rayInt.intersectLocation.dist(Camera::pos);
//                if(rayInt.didIntersect && newdist<dist){
//                    col = rayInt.color;
//                    dist = newdist;
//                }
                
                current = std::chrono::system_clock::now();
                diff = (current - start)*1000000;
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
                    //setColor(px+1, py, col);
                    //setColor(px, py+1, col);
                    //setColor(px+1, py+1, col);
                    
                }
                
                current = std::chrono::system_clock::now();
                diff = (current - start)*1000000;
                //std::cout<<diff.count()<<std::endl;
            }
        }
        }
        
        //established viewport already
        for(std::vector<Game::GameObject*>::iterator it = Game::gameObjects.begin(); it!= Game::gameObjects.end();it++){
           //drawObject(*it);
        }
        
        
        
        solidifyDisplay();
        
        Vector3D dxZombie = (Camera::pos-Game::zombie1.m_axis) - Game::zombie1.m_pos;
        dxZombie = dxZombie.normalize().scale(.01);
        Game::zombie1.m_pos = Game::zombie1.m_pos+dxZombie;
        
        
        
        
        current = std::chrono::system_clock::now();
        diff = current-start;
        
        
        //std::cout << "Time to render one frame : " << diff.count() << " s\n";
        
        current = std::chrono::system_clock::now();
        diff = (current -start)*1000000;
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
    return 0;
}
int mainOpenGL(){
    
    
    
    std::thread gameThread(startGame);
    std::thread renderingThread(startRendering);
    
    startRenderingFromPixelBuffer();
    
    return 0;
}






int main(int argc, const char * argv[]) {
    displayInit();
    
    displayInitScreen();
    
    solidifyDisplay();
    Game::initGame();
    
    #include "Display.h"
    #ifndef RELEASE
    return mainOpenGL();
    #else
    return mainTM4C();
    #endif
}

