//
//  DrawOpenGL.h
//  Lab 10
//
//  Created by Akarsh Kumar on 4/23/19.
//  Copyright © 2019 Akarsh Kumar. All rights reserved.
//

#ifndef DrawOpenGL_h
#define DrawOpenGL_h

#include <math.h>
#include <GLFW/glfw3.h>

#include "Display.h"

#include "Camera.h"




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



int initWindow(){
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    
    glfwSetKeyCallback(window, key_callback);
    
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    return 0;
}

const float pixWidth = 2.0f/DISPLAY_WIDTH;
const float pixHeight = 2.0f/DISPLAY_HEIGHT;

void drawPixel(int x, int y) {
    float glx = x * pixWidth - 1.0f;
    float gly = y * pixHeight - 1.0f;
    
    Color color = getColor(x, y);
    //glColor3b((int)color.r, (int)color.g, (int)color.b);
    glColor3d((double)color.r/255, (double)color.g/255, (double)color.b/255);
    
    
    glBegin(GL_POLYGON);
    
    glVertex2f(glx, gly);
    glVertex2f(glx+pixWidth, gly);
    glVertex2f(glx+pixWidth, gly+pixHeight);
    glVertex2f(glx, gly+pixHeight);
    
    glEnd();
}


void startRenderingFromPixelBuffer(){
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
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



#endif /* DrawOpenGL_h */
