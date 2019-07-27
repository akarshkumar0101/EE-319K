//
//  Camera.h
//  Lab 10
//
//  Created by Akarsh Kumar on 4/22/19.
//  Copyright © 2019 Akarsh Kumar. All rights reserved.
//

#ifndef Camera_h
#define Camera_h

#include <math.h>

#include "Display.h"
#include "Vector3D.h"
#include "VectorMath.h"

#define M_PI 3.1415926

#define DEFAULT_VIEW_ANGLE_X 80*M_PI/180
#define DEFAULT_VIEW_ANGLE_Y 80*M_PI/180


namespace Camera{
    const float viewAngleX = DEFAULT_VIEW_ANGLE_X, viewAngleY = DEFAULT_VIEW_ANGLE_Y;
    
    
    Vector3D pos(0,0,0);
    Vector3D dir(1,0,0);
    
    Vector3D up(0,0,1);
    Vector3D right(0,-1,0);
    
    //viewport pos is the center of viewport and a vect and b vect point in up and right dir
    Vector3D viewPortPos(0,0,0),viewPortAvect(0,0,0),viewPortBvect(0,0,0);
    
    
    //x y range from -1 to 1 (both)
    Vector3D getPixelRay(float x, float y){
        float xAngle = x * viewAngleX / 2.0f;
        float yAngle = y * viewAngleY / 2.0f;
        
        //rotate -xangle with respect to up vector
        //rotate yangle with respect to right vector
        
        Vector3D xrot = rotateVector(-xAngle, dir, up);
        Vector3D result = rotateVector(yAngle, xrot, right);
        
        return result;
    }
    
    
    float viewportDistance = 10;
    void establishViewPort(){
        
        viewPortPos = pos+dir.normalize().scale(viewportDistance);
        viewPortAvect = up.normalize().scale(tan(viewAngleY/2.0f)).scale(viewportDistance);
        viewPortBvect = right.normalize().scale(tan(viewAngleX/2.0f)).scale(viewportDistance);
    }
    
    Vector3D getPixelRayWithViewPort(float x, float y){
        return viewPortPos+viewPortAvect.scale(y)+viewPortBvect.scale(x)-pos;
    }
    
    
    void projectOntoViewPort(const Vector3D& point, float* out_s, float* out_t, float* out_d){
        Vector3D intersect(0,0,0);
        
        intersectLinePlanePlaneCoordinateSystem(pos, point-pos, viewPortPos, viewPortAvect, viewPortBvect, out_s, out_t, &intersect, out_d);
    }
    
}

#endif /* Camera_h */
