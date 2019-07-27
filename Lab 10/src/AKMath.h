//
//  AKMath.h
//  Lab 10
//
//  Created by Akarsh Kumar on 4/22/19.
//  Copyright © 2019 Akarsh Kumar. All rights reserved.
//

#ifndef AKMath_h
#define AKMath_h

#define M_PI 3.1415926

#ifndef NULL
#define NULL (0)
#endif

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



float AKmin(float a, float b){
    if(a<b){
        return a;
    }
    else{
        return b;
    }
}
float AKmax(float a, float b){
    if(a>b){
        return a;
    }
    else{
        return b;
    }
}

int AKmin(int a, int b){
    if(a<b){
        return a;
    }
    else{
        return b;
    }
}
int AKmax(int a, int b){
    if(a>b){
        return a;
    }
    else{
        return b;
    }
}
float AKabs(float a){
    if(a<0){
        return -a;
    }
    else{
        return a;
    }
}
int AKabs(int a){
    if(a<0){
        return -a;
    }
    else{
        return a;
    }
}

#endif /* Math_h */
