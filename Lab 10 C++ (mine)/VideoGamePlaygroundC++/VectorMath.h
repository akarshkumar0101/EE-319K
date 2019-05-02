//
//  VectorMath.h
//  Lab 10
//
//  Created by Akarsh Kumar on 4/22/19.
//  Copyright © 2019 Akarsh Kumar. All rights reserved.
//

#ifndef VectorMath_h
#define VectorMath_h

#include "Math.h"
#include "Vector3D.h"
#include "Matrix3x3.h"

Vector3D rotateVector(float angle,const Vector3D& vect, const Vector3D& axis){
    Matrix3x3 rotM = getRotationalMatrix(angle, axis);
    
    return rotM.mul(vect);
}

Vector3D intersectLinePlane(const Vector3D& linePos, const Vector3D& lineDir, const Vector3D& planePos,const Vector3D& planeNormal, float* out_d){
    float num = (planePos-linePos).dot(planeNormal);
    float denum = lineDir.dot(planeNormal);
    
    
    if(isEqual(denum, 0.0f)){
        if(isEqual(num,0.0f)){
            *out_d = infin;
        }
        else{
            *out_d = -infin;
        }
        return Vector3D(0,0,0);
    }
    else{
        *out_d = num/denum;
        
        Vector3D intersectPoint = lineDir.scale(*out_d)+linePos;
        
        return intersectPoint;
    }
}

//s is the percentage of the planeAVect
//t is the percentage of planeBVect
void intersectLinePlanePlaneCoordinateSystem(const Vector3D& linePos, const Vector3D& lineDir, const Vector3D& planeCenter, const Vector3D& planeAVect,const Vector3D& planeBVect, float* out_s, float* out_t, Vector3D* out_intersectPoint, float* out_d){
    
    Vector3D intersectPoint = intersectLinePlane(linePos, lineDir, planeCenter, planeAVect.cross(planeBVect), out_d);
    
    if((*out_d)!=infin && (*out_d)!=-infin){
        
        //intersect point ON the plane
        Vector3D intersectPointOnPlane = intersectPoint-planeCenter;
        *out_s = ((intersectPointOnPlane).dot(planeAVect))/planeAVect.len()/planeAVect.len();
        *out_t = ((intersectPointOnPlane).dot(planeBVect))/planeBVect.len()/planeBVect.len();
        
        *out_intersectPoint = intersectPoint;
    }
}

float lineLineDist(const Vector3D& a0, const Vector3D& aDir,const Vector3D& b0,const Vector3D& bDir){
    const Vector3D n = aDir.cross(bDir);
    if(n.len()==0){
        
    }
    return 0;
}



#endif /* VectorMath_h */
