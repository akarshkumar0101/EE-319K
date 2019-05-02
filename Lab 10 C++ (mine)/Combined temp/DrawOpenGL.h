//
//  DrawOpenGL.h
//  Lab 10
//
//  Created by Akarsh Kumar on 4/23/19.
//  Copyright © 2019 Akarsh Kumar. All rights reserved.
//

#ifndef DrawOpenGL_h
#define DrawOpenGL_h

//#ifndef RELEASE



#include <math.h>
#include <GLFW/glfw3.h>

#include "Display.h"

#include "Camera.h"



static Color pixelBuffer1[DISPLAY_WIDTH*DISPLAY_HEIGHT];
static Color pixelBuffer2[DISPLAY_WIDTH*DISPLAY_HEIGHT];

static Color* solidPixelBuffer = pixelBuffer1;
static Color* changingPixelBuffer = pixelBuffer2;

inline void rawSetColor(int x, int y, const Color& color){
    changingPixelBuffer[y*DISPLAY_WIDTH+x].color = color.color;
}
void solidifyDisplay(){
    Color* temp = solidPixelBuffer;
    solidPixelBuffer = changingPixelBuffer;
    changingPixelBuffer = temp;
}

void displayInitScreen(){
    for(int x=0; x<DISPLAY_WIDTH;x++){
        for(int y=0; y <DISPLAY_HEIGHT;y++){
//          setColor(x,y, Color(x*255/DISPLAY_WIDTH, y*255/DISPLAY_HEIGHT, 128));
            rawSetColor(x, y, Color(x*255/DISPLAY_WIDTH, y*255/DISPLAY_HEIGHT, 128));
            
            //setColor(x,y, Color(128,0,0));
        }
    }
    //std::cout<<"lol";
    //std::cout<<pixels[DISPLAY_WIDTH/2][DISPLAY_HEIGHT/2]<<std::endl;
}

GLFWwindow* window;



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    const float rotateSpeed = 5.0f*M_PI/180.0f;
    const float translateSpeed = 0.1f;
    if (key == GLFW_KEY_UP && (action == GLFW_REPEAT||action==GLFW_PRESS)){
        Camera::pos = Camera::pos+Camera::dir.normalize().scale(translateSpeed);
        Camera::right = Camera::dir.cross(Camera::up);
    }
    if (key == GLFW_KEY_DOWN && (action == GLFW_REPEAT||action==GLFW_PRESS)){
        Camera::pos = Camera::pos+Camera::dir.normalize().scale(-translateSpeed);
        Camera::right = Camera::dir.cross(Camera::up);
    }
    if (key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT||action==GLFW_PRESS)){
        Camera::pos = Camera::pos+Camera::right.normalize().scale(translateSpeed);
        Camera::right = Camera::dir.cross(Camera::up);
    }
    if (key == GLFW_KEY_LEFT && (action == GLFW_REPEAT||action==GLFW_PRESS)){
        Camera::pos = Camera::pos+Camera::right.normalize().scale(-translateSpeed);
        Camera::right = Camera::dir.cross(Camera::up);
    }
    if (key == GLFW_KEY_SPACE && (action == GLFW_REPEAT||action==GLFW_PRESS)){
        Camera::pos = Camera::pos+Camera::up.normalize().scale(translateSpeed);
        Camera::right = Camera::dir.cross(Camera::up);
    }
    if (key == GLFW_KEY_LEFT_CONTROL && (action == GLFW_REPEAT||action==GLFW_PRESS)){
        Camera::pos = Camera::pos+Camera::up.normalize().scale(-translateSpeed);
        Camera::right = Camera::dir.cross(Camera::up);
    }
    
    
    if (key == GLFW_KEY_W && (action == GLFW_REPEAT||action==GLFW_PRESS)){
        Camera::dir = rotateVector(rotateSpeed, Camera::dir, Camera::right);
        Camera::up = Camera::right.cross(Camera::dir);
    }
    if (key == GLFW_KEY_S && (action == GLFW_REPEAT||action==GLFW_PRESS)){
        Camera::dir = rotateVector(-rotateSpeed, Camera::dir, Camera::right);
        Camera::up = Camera::right.cross(Camera::dir);
    }
    if (key == GLFW_KEY_A && (action == GLFW_REPEAT||action==GLFW_PRESS)){
        Camera::dir = rotateVector(rotateSpeed, Camera::dir, Camera::up);
        Camera::right = Camera::dir.cross(Camera::up);
    }
    if (key == GLFW_KEY_D && (action == GLFW_REPEAT||action==GLFW_PRESS)){
        Camera::dir = rotateVector(-rotateSpeed, Camera::dir, Camera::up);
        Camera::right = Camera::dir.cross(Camera::up);
    }
    
    
    
    
    
    //reset
    if (key == GLFW_KEY_R && (action == GLFW_REPEAT||action==GLFW_PRESS)){
        Camera::pos = Vector3D(0,0,0);
        Camera::dir = xhat;
        Camera::up = zhat;
        Camera::right = Camera::dir.cross(Camera::right);
    }
}



void displayInit(){
    /* Initialize the library */
    if (!glfwInit())
        return;
    
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    
    glfwSetKeyCallback(window, key_callback);
    
    if (!window)
    {
        glfwTerminate();
        return;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
}

const float pixWidth = 2.0f/DISPLAY_WIDTH;
const float pixHeight = 2.0f/DISPLAY_HEIGHT;

void drawPixel(int x, int y) {
    float glx = x * pixWidth - 1.0f;
    float gly = y * pixHeight - 1.0f;
    
    Color color = solidPixelBuffer[y*DISPLAY_WIDTH+x];
    //glColor3b((int)color.r, (int)color.g, (int)color.b);
    glColor3d((double)color.getR()/255, (double)color.getG()/255, (double)color.getB()/255);
    
    
    glBegin(GL_POLYGON);
    
    glVertex2f(glx, gly);
    glVertex2f(glx+pixWidth, gly);
    glVertex2f(glx+pixWidth, gly+pixHeight);
    glVertex2f(glx, gly+pixHeight);
    
    glEnd();
}

void setColor(int x, int y, const Color& color){
    if(!((x==DISPLAY_WIDTH/2 && std::abs(y-DISPLAY_HEIGHT/2) < CROSSHAIR_RADIUS)||(y==DISPLAY_HEIGHT/2 && std::abs(x-DISPLAY_WIDTH/2) < CROSSHAIR_RADIUS))){
        rawSetColor(x, y, color);
        //drawPixel(x,y);
    }
    else{
        //pixels[x][y] = Color(128,128,128);
    }
}


void startRenderingFromPixelBuffer(){
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        for(int x=0; x<DISPLAY_WIDTH;x++){
            for(int y=0; y <DISPLAY_HEIGHT;y++){
                drawPixel(x,y);
            }
        }
        
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        
        /* Poll for and process events */
        glfwPollEvents();
    }
    
    glfwTerminate();
}


//#endif

#endif /* DrawOpenGL_h */
