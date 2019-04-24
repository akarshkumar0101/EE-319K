//
//  Game.h
//  Lab 10
//
//  Created by Akarsh Kumar on 4/22/19.
//  Copyright © 2019 Akarsh Kumar. All rights reserved.
//

#ifndef Game_h
#define Game_h



#include "Display.h"
#include "Vector3D.h"
#include "VectorMath.h"
#include "Math.h"

namespace Game {
    
    struct RayIntersect {
        bool didIntersect;
        Vector3D intersectLocation;
        Color color;
        
        RayIntersect(): didIntersect(false), intersectLocation(0,0,0), color(){
        }
    };
    class GameObject {
        
    public:
        virtual RayIntersect intersect(const Vector3D& start, const Vector3D& direction) const;
        
        
    };
    class Wall {
    public:
        Vector3D m_posCorner1, m_aVect, m_bVect;
        Color color;
    public:
        
        //pass in corners as bottom left, bottom right, top right, top left
        //(counter clockwise
        Wall(Color color_, const Vector3D& corner1, const Vector3D& corner2,const Vector3D& corner3,const Vector3D& corner4): color(color_), m_posCorner1(corner1),m_aVect(corner4-corner1),m_bVect(corner2-corner1){}
        
        RayIntersect intersect(const Vector3D& rayPos, const Vector3D& rayDirection) const {
            RayIntersect rayInt;
            
            float s;
            float t;
            Vector3D intersectPoint(0,0,0);
            
            float d=0;
            
            intersectLinePlanePlaneCoordinateSystem(rayPos, rayDirection, m_posCorner1, m_aVect, m_bVect, &s, &t, &intersectPoint,&d);
            
            rayInt.didIntersect = (s>=0 && s<=1 && t>=0 && t<=1) && d>0 && (d!=-infin && d!=infin);
            rayInt.intersectLocation = intersectPoint;
            rayInt.color = color;
            
            return rayInt;
        }
    };
    
    Vector3D w1a(1, 1, -1), w1b(1, -1, -1), w1c(1, -1, 1), w1d(1, 1, 1);
    Vector3D w2a(1, -1, -1), w2b(-1, -1, -1), w2c(-1, -1, 1), w2d(1, -1, 1);
    Vector3D w3a(-1, -1, -1), w3b(-1, 1, -1), w3c(-1, 1, 1), w3d(-1, -1, 1);
    Vector3D w4a(-1, 1, -1), w4b(1, 1, -1), w4c(1, 1, 1), w4d(-1, 1, 1);
    Vector3D w5a(1, 1, 1), w5b(1, -1, 1), w5c(-1, -1, 1), w5d(-1, 1, 1);
    Vector3D w6a(-1, 1, -1), w6b(-1, -1, -1), w6c(1, -1, -1), w6d(1, 1, -1);
    
    Game::Wall wall1(Color(255,255,255), w1a, w1b, w1c, w1d);
    Game::Wall wall2(Color(255,255,0), w2a, w2b, w2c, w2d);
    Game::Wall wall3(Color(255,0,255), w3a, w3b, w3c, w3d);
    Game::Wall wall4(Color(0,255,255), w4a, w4b, w4c, w4d);
    Game::Wall wall5(Color(0,0,255), w5a, w5b, w5c, w5d);
    Game::Wall wall6(Color(0,255,0), w6a, w6b, w6c, w6d);
    
    
    std::vector<Game::Wall> walls;
    
    void initGame(){
        walls.push_back(wall1);
        walls.push_back(wall2);
        //walls.push_back(wall3);
        //walls.push_back(wall4);
        //walls.push_back(wall5);
        walls.push_back(wall6);
        
        
//        for(auto it = walls.begin();it!=walls.end();it++){
//            it->m_posCorner1 = it->m_posCorner1.scale(2);
//        }
    }
    
}


#endif /* Game_h */
