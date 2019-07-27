//
//  Texture.h
//  Lab 10
//
//  Created by Akarsh Kumar on 4/28/19.
//  Copyright © 2019 Akarsh Kumar. All rights reserved.
//

#ifndef Texture_h
#define Texture_h

#include "Display.h"

class Texture {
public:
    int width, height;
    
    //should be accessed as texture[x][y]
    Color** texture;
    
    Texture(int width, int height){
        this->width = width;
        this->height = height;
        texture = NULL;
    }
    Texture(int width, int height, Color** texture){
        this->width = width;
        this->height = height;
        setTexture(texture);
    }
    
    virtual Color get(int x, int y){
        return texture[x][y];
    }
    
    void setTexture(Color** texture){
        this->texture = texture;
    }
};
class OneColorTexture: public Texture {
    
public:
    Color m_color;
    OneColorTexture(Color color): Texture(1, 1, NULL) {
        m_color.color = color.color;
    }
    
    virtual Color get(int x, int y){
        return m_color;
    }
    
};


#endif /* Texture_h */
