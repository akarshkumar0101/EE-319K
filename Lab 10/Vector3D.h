//
//  Vector3D.h
//  Lab 10
//
//  Created by Akarsh Kumar on 4/22/19.
//  Copyright © 2019 Akarsh Kumar. All rights reserved.
//

#ifndef Vector3D_h
#define Vector3D_h

#include <math.h>




class Vector3D {
public:
    Vector3D(float x, float y, float z) : m_x(x), m_y(y), m_z(z){
    }
    Vector3D(const Vector3D& another) : m_x(another.x()), m_y(another.y()), m_z(another.z()){
    }
    
    
    float x() const{
        return this->m_x;
    }
    float y() const{
        return this->m_y;
    }
    float z() const{
        return this->m_z;
    }
    
    
    float dot(const Vector3D& vect) const{
        return x()*vect.x()+y()*vect.y()+z()*vect.z();
    }
    float len() const{
        return sqrt(this->dot(*this));
    }
    float dist(const Vector3D& vect) const {
        return ((*this)-vect).len();
    }
    Vector3D scale(float sc) const{
        Vector3D vect(x()*sc, y()*sc,z()*sc);
        return vect;
    }
    Vector3D normalize() const{
        float length = len();
        Vector3D vect(x()/length, y()/length,z()/length);
        return vect;
    }
    
    Vector3D cross(const Vector3D& vect) const{
        float xx = y() * vect.z() - z() * vect.y();
        float yy = z() * vect.x() - x() * vect.z();
        float zz = x() * vect.y() - y() * vect.x();
        
        return Vector3D(xx, yy, zz);
    }
    
    Vector3D& operator=(const Vector3D& vect) {
        m_x = vect.x();
        m_y = vect.y();
        m_z = vect.z();
        return *this;
    }
    Vector3D operator+(const Vector3D& b) const {
        Vector3D vect(x()+b.x(), y()+b.y(),z()+b.z());
        return vect;
    }
    Vector3D operator-(const Vector3D& b) const {
        Vector3D vect(x()-b.x(), y()-b.y(),z()-b.z());
        return vect;
    }
    
    
private:
    float m_x, m_y, m_z;
    
};


std::ostream& operator<<(std::ostream& os, const Vector3D& v)
{
    os<< "<"<<v.x()<<", "<<v.y()<<", " <<v.z()<<">";
    return os;
}

Vector3D xhat = Vector3D(1,0,0);
Vector3D yhat = Vector3D(0,1,0);
Vector3D zhat = Vector3D(0,0,1);






#endif /* Vector3D_h */
