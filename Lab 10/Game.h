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
        const Vector3D m_posCorner1, m_aVect, m_bVect;
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
    
    //Wall walls[] = {};
    //Wall wall1(Color(255, 255, 255), Vector3D(1, 1, -1), Vector3D(1, -1, -1), Vector3D(1, -1, 1), Vector3D(1, 1, 1));
    
    
}


#endif /* Game_h */
