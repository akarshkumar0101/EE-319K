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

#ifndef RELEASE

#include <iostream>

#endif


struct Vector2D {
public:
    Vector2D(){
        this->m_x = 0;
        m_y = 0;
    }
    Vector2D(const float& x, const float& y){
        m_x = x;
        m_y = y;
    }
    Vector2D(const Vector2D& another){
        m_x = another.x();
        m_y = another.y();
    }
    
    
    float x() const{
        return this->m_x;
    }
    float y() const{
        return this->m_y;
    }
    
    
    float dot(const Vector2D& vect) const{
        return x()*vect.x()+y()*vect.y();
    }
    float len() const{
        return sqrt(this->dot(*this));
    }
    float dist(const Vector2D& vect) const {
        return ((*this)-vect).len();
    }
    Vector2D scale(float sc) const{
        Vector2D vect(x()*sc, y()*sc);
        return vect;
    }
    Vector2D normalize() const{
        float length = len();
        Vector2D vect(x()/length, y()/length);
        return vect;
    }
    
    float component(const Vector2D& base) const {
        return dot(base)/base.len();
    }
    Vector2D project(const Vector2D& base) const{
        return base.normalize().scale(component(base));
    }
    
    
    Vector2D& operator=(const Vector2D& vect) {
        m_x = vect.x();
        m_y = vect.y();
        return *this;
    }
    Vector2D operator+(const Vector2D& b) const {
        Vector2D vect(x()+b.x(), y()+b.y());
        return vect;
    }
    Vector2D operator-(const Vector2D& b) const {
        Vector2D vect(x()-b.x(), y()-b.y());
        return vect;
    }
    
    
private:
    float m_x, m_y;
    
};



struct Vector3D {
public:
    Vector3D(){
        m_x = 0;
        m_y = 0;
        m_z = 0;
    }
    Vector3D(const float& x, const float& y, const float& z){
        m_x = x;
        m_y = y;
        m_z = z;
    }
    
    Vector3D(const Vector3D& another){
        m_x = another.x();
        m_y = another.y();
        m_z = another.z();
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
    
    float component(const Vector3D& base) const {
        return dot(base)/base.len();
    }
    Vector3D project(const Vector3D& base) const{
        return base.normalize().scale(component(base));
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

#ifndef RELEASE
std::ostream& operator<<(std::ostream& os, const Vector3D& v){
    os<< "<"<<v.x()<<", "<<v.y()<<", " <<v.z()<<">";
    return os;
}
std::ostream& operator<<(std::ostream& os, const Vector2D& v){
    os<< "<"<<v.x()<<", "<<v.y()<<">";
    return os;
}
#endif

const Vector3D xhat(1,0,0);
const Vector3D yhat(0,1,0);
const Vector3D zhat(0,0,1);






#endif /* Vector3D_h */
