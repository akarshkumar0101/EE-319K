//
//  main.cpp
//  Lab 10
//
//  Created by Akarsh Kumar on 4/22/19.
//  Copyright © 2019 Akarsh Kumar. All rights reserved.
//

#include <iostream>
#include <thread>
#include <unistd.h>
#include <chrono>
#include <ctime>
#include <vector>

#include <GLFW/glfw3.h>

#include "Math.h"
#include "Display.h"
#include "Game.h"
#include "Camera.h"
#include "Matrix3x3.h"
#include "Vector3D.h"
#include "VectorMath.h"


bool shouldDraw = false;

std::vector<Vector3D> teapotVertices;

void renderGLScreenFromBuffer(GLFWwindow* window){
    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    
    
    
    for(int x=0; x<windowWidth;x++){
        for(int y=0; y <windowHeight;y++){
            //float glx = floatScale((float)x, 0.0f, (float)width, -1.0f, 1.0f);
            //float gly = floatScale((float)y, 0.0f, (float)height, -1.0f, 1.0f);
            //glVertex2f(glx, gly);
        }
    }
    
    
    float pixWidth = 2.0f/DISPLAY_WIDTH;
    float pixHeight = 2.0f/DISPLAY_HEIGHT;
    
    for(int x=0; x<DISPLAY_WIDTH; x++){
        for(int y=0; y <DISPLAY_HEIGHT;y++){
            float glx = x * pixWidth - 1.0f;
            float gly = y * pixHeight - 1.0f;
            glBegin(GL_POLYGON);
            Color color = getColor(x, y);
            //glColor3b((int)color.r, (int)color.g, (int)color.b);
            glColor3d((double)color.r/255, (double)color.g/255, (double)color.b/255);

            glVertex2f(glx, gly);
            glVertex2f(glx+pixWidth, gly);
            glVertex2f(glx+pixWidth, gly+pixHeight);
            glVertex2f(glx, gly+pixHeight);

            glEnd();
        }
    }
    
    
    
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    const float angle = 1.0f*M_PI/180.0f;
    if (key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT||action==GLFW_PRESS)){
        Camera::dir = rotateVector(angle, Camera::dir, Camera::up);
        Camera::right = Camera::dir.cross(Camera::up);
    }
    if (key == GLFW_KEY_LEFT && (action == GLFW_REPEAT||action==GLFW_PRESS)){
        Camera::dir = rotateVector(-angle, Camera::dir, Camera::up);
        Camera::right = Camera::dir.cross(Camera::up);
    }
    if (key == GLFW_KEY_UP && (action == GLFW_REPEAT||action==GLFW_PRESS)){
        Camera::right = Camera::dir.cross(Camera::up);
        Camera::pos = Camera::pos+Camera::dir.scale(.01);
    }
    if (key == GLFW_KEY_DOWN && (action == GLFW_REPEAT||action==GLFW_PRESS)){
        Camera::right = Camera::dir.cross(Camera::up);
        Camera::pos = Camera::pos+Camera::dir.scale(-.01);
    }
}

GLFWwindow* window;
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

void startRenderingFromPixelBuffer(){
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        if(!shouldDraw){
            continue;
        }
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        renderGLScreenFromBuffer(window);
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        
        /* Poll for and process events */
        glfwPollEvents();
    }
    
    glfwTerminate();
}

void startGame(){
    
//    Vector3D v(1,0,0);
    Vector3D r(1,1,1);
//
//    for(float angle =0; angle<=2*M_PI+.01;angle+=M_PI/8){
//        std::cout<<angle*180/M_PI<<std::endl;
//        Vector3D ans = rotateVector(angle, v, r);
//        std::cout<<ans.x()<<std::endl;
//        std::cout<<ans.y()<<std::endl;
//        std::cout<<ans.z()<<std::endl;
//        std::cout<<std::endl;
//    }
    
    
    
    
    while(true){

    }

}

void temp_paintPoint(Vector3D coor){
    float s, t, d;
    Camera::projectOntoViewPort(coor, &s, &t, &d);
    
    Vector3D viewPortN = Camera::viewPortAvect.cross(Camera::viewPortBvect);
    
    Vector3D coorVP = coor-Camera::pos;
    if(coorVP.dot(viewPortN)>0 && d!=infin && d!=-infin){
        int px = ((t+1.0f)/2.0f)*DISPLAY_WIDTH;
        int py = ((s+1.0f)/2.0f)*DISPLAY_HEIGHT;
        
        if(px>=0&&px<DISPLAY_WIDTH&&py>=0&&py<DISPLAY_HEIGHT){
            setColor(px, py, Color(255,255,255));
        }
    }
}
void startRendering(){
    int x =0;
    Vector3D w1a(1, 1, -1), w1b(1, -1, -1), w1c(1, -1, 1), w1d(1, 1, 1);
    Vector3D w2a(1, -1, -1), w2b(-1, -1, -1), w2c(-1, -1, 1), w2d(1, -1, 1);
    Vector3D w3a(-1, -1, -1), w3b(-1, 1, -1), w3c(-1, 1, 1), w3d(-1, -1, 1);
    Vector3D w4a(-1, 1, -1), w4b(1, 1, -1), w4c(1, 1, 1), w4d(-1, 1, 1);
    Vector3D w5a(1, 1, 1), w5b(1, -1, 1), w5c(-1, -1, 1), w5d(-1, 1, 1);
    Vector3D w6a(-1, 1, -1), w6b(-1, -1, -1), w6c(1, -1, -1), w6d(1, 1, -1);
    
    Game::Wall wall1(Color(255,255,255), w1a, w1b, w1c, w1d);
    Game::Wall wall2(Color(255,255,0), w2a, w2b, w2c, w2d);
    Game::Wall wall3(Color(255,0,255), w3a, w3b, w3c, w3d);
    Game::Wall wall4(Color(0,255,255), w4a, w4b, w4c, w4d);
    Game::Wall wall5(Color(0,0,255), w5a, w5b, w5c, w5d);
    Game::Wall wall6(Color(0,255,0), w6a, w6b, w6c, w6d);
    
    
    std::vector<Game::Wall> walls;
    walls.push_back(wall1);
    walls.push_back(wall2);
    walls.push_back(wall3);
    walls.push_back(wall4);
    walls.push_back(wall5);
    walls.push_back(wall6);
    
    
    //Camera::dir = Vector3D(0,1,0);
    //Camera::right = Camera::dir.cross(Camera::up);
    
    while(true){
        usleep(100000);
        
        
        Camera::establishViewPort();
        
        shouldDraw = false;
        
        for(int px = 0;px<DISPLAY_WIDTH;px++){
            for(int py = 0;py<DISPLAY_HEIGHT;py++){
                setColor(px, py, Color(0,0,0));
            }
        }
        
        for(int px = 0;px<DISPLAY_WIDTH;px++){
            for(int py = 0;py<DISPLAY_HEIGHT;py++){
                Color col (0,0,0);
                float cx = (2.0f*(float)px-(float)DISPLAY_WIDTH)/(float)DISPLAY_WIDTH;
                float cy = (2.0f*(float)py-(float)DISPLAY_HEIGHT)/(float)DISPLAY_HEIGHT;
                
                //Vector3D dir = Camera::getPixelRay(cx, cy);
                Vector3D dir = Camera::getPixelRayWithViewPort(cx, cy);
                
                
                
                for(auto it = walls.begin(); it!=walls.end();it++){
                    Game::RayIntersect rayInt = it->intersect(Camera::pos, dir);
                    if(rayInt.didIntersect){
                        col = rayInt.color;
                    }
                }
                
            }
        }
        
        
        //established viewport already
        for(auto it = walls.begin(); it!=walls.end();it++){
            temp_paintPoint(it->m_posCorner1);
            temp_paintPoint(it->m_posCorner1+it->m_aVect);
            temp_paintPoint(it->m_posCorner1+it->m_bVect);
            temp_paintPoint(it->m_posCorner1+it->m_aVect+it->m_bVect);
            
        }
        shouldDraw = true;
        
        
    }
}

int main(int argc, const char * argv[]) {
    
    initPixels();
    
    if(initWindow() == -1){
        return -1;
    }
    
    std::thread gameThread(startGame);
    std::thread renderingThread(startRendering);
    
    startRenderingFromPixelBuffer();
    
    return 0;
}



