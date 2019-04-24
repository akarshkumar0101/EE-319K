//
//  main.cpp
//  Lab 10
//
//  Created by Akarsh Kumar on 4/22/19.
//  Copyright © 2019 Akarsh Kumar. All rights reserved.
//

#include <iostream>
#include <thread>
#include <unistd.h>
#include <chrono>
#include <ctime>
#include <vector>

#include "DrawOpenGL.h"
#include "Math.h"
#include "Display.h"
#include "Game.h"
#include "Camera.h"
#include "Matrix3x3.h"
#include "Vector3D.h"
#include "VectorMath.h"




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

void temp_paintPoint(Vector3D coor){
    float s, t, d;
    Camera::projectOntoViewPort(coor, &s, &t, &d);
    
    Vector3D viewPortN = Camera::viewPortAvect.cross(Camera::viewPortBvect);
    
    Vector3D coorVP = coor-Camera::pos;
    if(coorVP.dot(viewPortN)>0 && d!=infin && d!=-infin){
        int px = ((t+1.0f)/2.0f)*DISPLAY_WIDTH;
        int py = ((s+1.0f)/2.0f)*DISPLAY_HEIGHT;
        
        if(px>=0&&px<DISPLAY_WIDTH&&py>=0&&py<DISPLAY_HEIGHT){
            setColor(px, py, Color(255,0,0));
        }
    }
}
void startRendering(){
    
    
    //Camera::dir = Vector3D(0,1,0);
    //Camera::right = Camera::dir.cross(Camera::up);
    
    
    
    auto fpsStart = std::chrono::system_clock::now();
    int fpsCount=0;
    while(true){
        auto start = std::chrono::system_clock::now();
        //usleep(1);
        
        //Camera::dir = rotateVector(1*M_PI/180, Camera::dir, Camera::up);
        Camera::right = Camera::dir.cross(Camera::up);
        
        Camera::establishViewPort();
        
//        for(int px = 0;px<DISPLAY_WIDTH;px++){
//            for(int py = 0;py<DISPLAY_HEIGHT;py++){
//                //setColor(px, py, Color(0,0,0));
//            }
//        }
        
        for(int px = 0;px<DISPLAY_WIDTH-3;px+=1){
            for(int py = 0;py<DISPLAY_HEIGHT-3;py+=1){
                Color col (0,0,0);
                float cx = (2.0f*(float)px-(float)DISPLAY_WIDTH)/(float)DISPLAY_WIDTH;
                float cy = (2.0f*(float)py-(float)DISPLAY_HEIGHT)/(float)DISPLAY_HEIGHT;
                
                //Vector3D dir = Camera::getPixelRay(cx, cy);
                Vector3D dir = Camera::getPixelRayWithViewPort(cx, cy);
                
                
                
                float dist = infin;
                for(auto it = Game::walls.begin(); it!=Game::walls.end();it++){
                    Game::RayIntersect rayInt = it->intersect(Camera::pos, dir);
                    float newdist = rayInt.intersectLocation.dist(Camera::pos);
                    if(rayInt.didIntersect && newdist<dist){
                        col = rayInt.color;
                        dist = newdist;
                    }
                    //1break;
                }
                
                setColor(px, py, col);
                for(int ix=0; ix <3;ix++){
                    for(int iy=0;iy<3;iy++){
                        //setColor(px+ix, py+iy, col);
                    }
                }
            }
        }
        
        //established viewport already
        for(auto it = Game::walls.begin(); it!=Game::walls.end();it++){
            temp_paintPoint(it->m_posCorner1);
            temp_paintPoint(it->m_posCorner1+it->m_aVect);
            temp_paintPoint(it->m_posCorner1+it->m_bVect);
            temp_paintPoint(it->m_posCorner1+it->m_aVect+it->m_bVect);
            
        }
        
        
        auto current = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = current-start;
        
        
        //std::cout << "Time to render one frame : " << diff.count() << " s\n";
        
        current = std::chrono::system_clock::now();
        diff = current-fpsStart;
        
        fpsCount++;
        if(diff.count()>=1){
            std::cout << "FPS : " << fpsCount << " s\n";
            fpsCount=0;
            fpsStart = std::chrono::system_clock::now();
        }
        
        
        
        
    }
}

int main(int argc, const char * argv[]) {
    
    
    initPixels();
    Game::initGame();
    
    if(initWindow() == -1){
        return -1;
    }
    
    //std::thread gameThread(startGame);
    std::thread renderingThread(startRendering);
    
    startRenderingFromPixelBuffer();
    
    return 0;
}



