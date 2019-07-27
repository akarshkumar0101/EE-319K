//
//  Math.h
//  Lab 10
//
//  Created by Akarsh Kumar on 4/22/19.
//  Copyright © 2019 Akarsh Kumar. All rights reserved.
//

#ifndef Math_h
#define Math_h

float floatScale(float num, float scale1a, float scale1b, float scale2a, float scale2b){
    float scale = (scale2b-scale2a)/(scale1b-scale1a);
    num-=scale1a;
    num*=scale;
    num+=scale2a;
    return num;
}


bool isEqual(float a, float b){
    float c = a-b;
    return (c>-.0001&&c<.0001);
}

float infin = 1002020;//std::numeric_limits<float>::infinity();




#endif /* Math_h */
