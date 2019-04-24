//
//  Matrix3x3.h
//  Lab 10
//
//  Created by Akarsh Kumar on 4/22/19.
//  Copyright © 2019 Akarsh Kumar. All rights reserved.
//

#ifndef Matrix3x3_h
#define Matrix3x3_h

#include <math.h>

#include "Vector3D.h"



class Matrix3x3 {
private:
    //matrix[0] should give the first ROW
    float matrix[3][3];
    
public:
    Matrix3x3(float v00, float v01, float v02, float v10, float v11, float v12,float v20, float v21, float v22){
        matrix[0][0] = v00;
        matrix[0][1] = v01;
        matrix[0][2] = v02;
        
        matrix[1][0] = v10;
        matrix[1][1] = v11;
        matrix[1][2] = v12;
        
        matrix[2][0] = v20;
        matrix[2][1] = v21;
        matrix[2][2] = v22;
    }
    Matrix3x3(){
        for(int x=0;x<2;x++){
            for(int y=0; y <2;y++){
                matrix[x][y] = 0.0f;
            }
        }
    }
    
    Matrix3x3 mul(const Matrix3x3& another) {
        Matrix3x3 result;
        
        result.matrix[0][0] = matrix[0][0]*another.matrix[0][0] + matrix[0][1]*another.matrix[1][0] + matrix[0][2]*another.matrix[2][0];
        
        result.matrix[0][1] = matrix[0][0]*another.matrix[0][1] + matrix[0][1]*another.matrix[1][1] + matrix[0][2]*another.matrix[2][1];
        
        result.matrix[0][2] = matrix[0][0]*another.matrix[0][2] + matrix[0][1]*another.matrix[1][2] + matrix[0][2]*another.matrix[2][2];
        
        
        result.matrix[1][0] = matrix[1][0]*another.matrix[0][0] + matrix[1][1]*another.matrix[1][0] + matrix[1][2]*another.matrix[2][0];
        
        result.matrix[1][1] = matrix[1][0]*another.matrix[0][1] + matrix[1][1]*another.matrix[1][1] + matrix[1][2]*another.matrix[2][1];
        
        result.matrix[1][2] = matrix[1][0]*another.matrix[0][2] + matrix[1][1]*another.matrix[1][2] + matrix[1][2]*another.matrix[2][2];
        
        
        
        result.matrix[2][0] = matrix[2][0]*another.matrix[0][0] + matrix[2][1]*another.matrix[1][0] + matrix[2][2]*another.matrix[2][0];
        
        result.matrix[2][1] = matrix[2][0]*another.matrix[0][1] + matrix[2][1]*another.matrix[1][1] + matrix[2][2]*another.matrix[2][1];
        
        result.matrix[2][2] = matrix[2][0]*another.matrix[0][2] + matrix[2][1]*another.matrix[1][2] + matrix[2][2]*another.matrix[2][2];
        
        return result;
    }
    Vector3D mul(const Vector3D& vec) {
        float xx = matrix[0][0]*vec.x()+matrix[0][1]*vec.y()+matrix[0][2]*vec.z();
        float yy = matrix[1][0]*vec.x()+matrix[1][1]*vec.y()+matrix[1][2]*vec.z();
        float zz = matrix[2][0]*vec.x()+matrix[2][1]*vec.y()+matrix[2][2]*vec.z();
        return Vector3D(xx, yy, zz);
    }
    
    friend Matrix3x3 getRotationalMatrix(float angle, const Vector3D& axis);
    
};

Matrix3x3 getRotationalMatrix(float angle, const Vector3D& axis){
    Matrix3x3 m;
    
    float sinv = sin(angle);
    float cosv = cos(angle);
    float x = axis.x();
    float y = axis.y();
    float z = axis.z();
    
    m.matrix[0][0] = cosv+ x*x * (1-cosv);
    m.matrix[0][1] = x*y * (1-cosv) - z*sinv;
    m.matrix[0][2] = y*sinv + x*z * (1-cosv);
    
    
    m.matrix[1][0] = z* sinv+ x*y *(1-cosv);
    m.matrix[1][1] = cosv+y*y*(1-cosv);
    m.matrix[1][2] = -x*sinv+y*z*(1-cosv);
    
    m.matrix[2][0] = -y*sinv+x*z*(1-cosv);
    m.matrix[2][1] = x*sinv +y*z*(1-cosv);
    m.matrix[2][2] = cosv+z*z*(1-cosv);
    
    return m;
}

#endif /* Matrix3x3_h */
