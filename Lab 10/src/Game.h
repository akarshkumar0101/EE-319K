//
//  Game.h
//  Lab 10
//
//  Created by Akarsh Kumar on 4/22/19.
//  Copyright © 2019 Akarsh Kumar. All rights reserved.
//

#ifndef Game_h
#define Game_h


//#include <vector>


#include "Texture.h"
#include "Display.h"
#include "Vector.h"
#include "VectorMath.h"
#include "AKMath.h"
#include "List.h"
#include "Camera.h"
#include "random.h"
#include "DAC.h"


#define CHARACTER_HEIGHT 1

namespace Game {
    bool gameOver;
    
    static int round;
    // total remaining in the level
    static int numZombiesRemaining;
    // still need to spawn
    static int numZombiesNeededToSpawn;
	
		int numNukesAvailable;
	
		int numZombiesKilled;
    
		int numGameTicks;
	
		bool isShooting;
		bool showShooting;
	
		int numBullets;
	
		int health;
		
    class Wall{
			public:
			Color color;
        //middle up and right
			Vector3D m_pos, m_aVect, m_bVect;
    public:
			Wall(){}
        //pass in corners as bottom left, bottom right, top right, top left
        //(counter clockwise
        Wall(Color color_, const Vector3D& corner1, const Vector3D& corner2,const Vector3D& corner3,const Vector3D& corner4){
					
					m_pos = corner1+(corner2-corner1).scale(.5)+(corner4-corner1).scale(.5);
					m_aVect = (corner4-corner1).scale(.5);
					m_bVect = (corner2-corner1).scale(.5);
					this->color = color_;
				}
        
        LinePlaneIntersection intersect(const Vector3D& rayPos, const Vector3D& rayDirection) const {
            return LinePlaneIntersection(rayPos, rayDirection, m_pos, m_aVect, m_bVect);
        }
    };
    
    class Zombie {
    public:
#define ZOMBIE_RADIUS 0.1f
#define ZOMBIE_SPEED 0.02f
        
        //the middle of the zombies body
        Vector3D m_pos;
        
        float height;
        float width;
        float speed;
        
        //points to the right and the top
        Vector3D aVect;
        Vector3D bVect;
        
    public:
        Zombie(){
            m_pos = Vector3D();
            height = CHARACTER_HEIGHT*1.61446f;
            width = CHARACTER_HEIGHT;
            speed = ZOMBIE_SPEED;
            
        }
        Zombie(const Vector3D& pos){
            m_pos = pos;
            height = CHARACTER_HEIGHT*1.61446f;
            width = CHARACTER_HEIGHT;
            speed = ZOMBIE_SPEED;
        }
        
        void updateView(){
            Vector3D radVect = (m_pos-Camera::pos).cross(zhat).normalize();
						radVect = radVect.scale(-1);
            aVect = radVect.scale(-width/2);
            bVect = zhat.scale(height/2);
        }
        
        LinePlaneIntersection intersect(const Vector3D& rayPos, const Vector3D& rayDirection) const {
           return LinePlaneIntersection(rayPos, rayDirection, m_pos, aVect, bVect);
        }
        
    };
		
		class AmmoCart {
    public:
        
        //the middle of the zombies body
        Vector3D m_pos;
        
        float height;
        float width;
        
        //points to the right and the top
        Vector3D aVect;
        Vector3D bVect;
        
    public:
        AmmoCart(){
            m_pos = Vector3D();
            height = CHARACTER_HEIGHT*0.806f/2.0f;
            width = (float)CHARACTER_HEIGHT/2;
            
        }
        AmmoCart(const Vector3D& pos){
            m_pos = pos;
            height = CHARACTER_HEIGHT*0.806f/2.0f;
            width = (float)CHARACTER_HEIGHT/2;
        }
        
        void updateView(){
            Vector3D radVect = (m_pos-Camera::pos).cross(zhat).normalize();
						radVect = radVect.scale(-1);
            aVect = radVect.scale(-width/2);
            bVect = zhat.scale(height/2);
        }
        
        LinePlaneIntersection intersect(const Vector3D& rayPos, const Vector3D& rayDirection) const {
           return LinePlaneIntersection(rayPos, rayDirection, m_pos, aVect, bVect);
        }
        
    };
		
		
    
    
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
    
    Game::Zombie zombie1(Vector3D(2,0,(float)CHARACTER_HEIGHT/2));
    
    
    //std::vector<Game::GameObject*> gameObjects;
    //Wall gameObjects[6];
    List<Wall, 10> gameWalls;
		
    List<Zombie, 100> gameZombies;
		List<AmmoCart, 100> gameAmmoCarts;
    
    
    int levelScale = 20;
    int zombieSpawnTimeElapsed;
		
    void initGame() {
				gameOver = false;
        Camera::pos = Vector3D(0,0,CHARACTER_HEIGHT);
        Camera::dir = xhat;
        Camera::up = zhat;
        Camera::right = yhat.scale(-1);
			
			numNukesAvailable = 1;
			numZombiesKilled=0;
        
			numGameTicks = 0;
			
			isShooting = false;
			showShooting = false;
			
			numBullets = 8;
			
			health = 3;

			//Camera::dir = yhat;
        
        //gameObjects.push_back(&wall1);
			//gameObjects[0] = wall1;
        gameWalls.add(wall1);
        //gameObjects.push_back(&wall2);
			//gameObjects[1] = wall2;
        gameWalls.add(wall2);
			
        //gameObjects.push_back(&wall3);
        //gameObjects.push_back(&wall4);
        //gameObjects.push_back(&wall5);
			
        //gameObjects.push_back(&wall6);
			//gameObjects[2] = wall6;
        gameWalls.add(wall6);
        
        //gameObjects.push_back(&zombie1);
			
        gameZombies.add(zombie1);
        
        
        Game::Wall gameWall1 = Wall(Color(255,255,255), Vector3D(0,0,0), Vector3D(levelScale,0,0), Vector3D(levelScale,levelScale,0), Vector3D(0,levelScale,0));
        //gameWalls.add(gameWall1);
				
				
				
				AmmoCart cart(Vector3D(0,0,0));
				gameAmmoCarts.add(cart);
				
        
        zombieSpawnTimeElapsed = 0;
    }
    void nextRound(){
        round++;
        numZombiesRemaining = AKmin(2*round+5, 100);
        numZombiesNeededToSpawn = numZombiesRemaining;
    }
    
    
    
    void spawnZombie(){
        numZombiesNeededToSpawn--;
        //spawn it
        
        int xLocation, yLocation;
        do{
						xLocation = levelScale*Random()/255-levelScale/2+Camera::pos.x();
            yLocation = levelScale*Random()/255-levelScale/2+Camera::pos.y();
					}while(Vector3D(xLocation,yLocation,0).dist(Camera::pos)<3.0f);
        
        //std::cout<<xLocation<<std::endl;
        //std::cout<<yLocation<<std::endl;
        //std::cout<<std::endl;
        
        Zombie zomb(Vector3D(xLocation, yLocation, (float)CHARACTER_HEIGHT/2));
        gameZombies.add(zomb);
    }
    
    //dt in milliseconds
    void gameTick(void){
			
			int dt = 1;
			
			for(int i=0; i < gameAmmoCarts.length();i++){
            AmmoCart& cart = gameAmmoCarts.get(i);
            
            
            cart.updateView();
						if((Vector3D(cart.m_pos.x(), cart.m_pos.y(),CHARACTER_HEIGHT)).dist(Camera::pos)<.4){
							int bullets = 6+(Random()%8);
							numBullets += bullets;
							gameAmmoCarts.remove(i);
							i--;
							updateHUDInfo();
						}
        }
        for(int i=0; i < gameZombies.length();i++){
            Zombie& zomb = gameZombies.get(i);
            
            Vector3D dx = (Camera::pos - zomb.m_pos).normalize().scale((float)zomb.speed*dt);
            dx = Vector3D(dx.x(), dx.y(), 0);
            
            zomb.m_pos = zomb.m_pos + dx;
            
            zomb.updateView();
						if((zomb.m_pos+zomb.bVect).dist(Camera::pos)<.4){
							health--;
							if(health<=0){
									gameOver=true;
							}
							else{
								renderHUD();
								gameZombies.remove(i);
								i--;
								if(gameZombies.length()==0){
									nextRound();
								}
							}
							
						}
        }
        if(numZombiesNeededToSpawn>0){
						
						
            if(zombieSpawnTimeElapsed>5 && Random()<30){
								spawnZombie();
                zombieSpawnTimeElapsed = 0;
            }
            else{
                zombieSpawnTimeElapsed += dt;
            }
        }
				numGameTicks++;
    }
    
    
    
    void shoot(){
			if(numBullets>0){
				numBullets--;
				Game::isShooting = true;
				Game::showShooting = true;
				playGunSound();
        for(int i=0; i < gameZombies.length();i++){
            Zombie& zomb = gameZombies.get(i);
            
            LinePlaneIntersection intersect = zomb.intersect(Camera::pos, Camera::dir);
            
            
            
            //std::cout<<point<<std::endl;
            if(intersect.doesIntersect()) {
                intersect.calculateIntersectionPoint();
                intersect.calculateIntersectionOnPlane();
                
                const Vector2D& point = intersect.getIntersectionOnPlane();
                
                if(intersect.intersectsNormalPlane()){
                    gameZombies.remove(i);
                    i--;
									
										if(Random()<25){
												gameAmmoCarts.add(AmmoCart(zomb.m_pos-zomb.bVect.scale(.5)));
												
										}
										
										numZombiesKilled++;
                    if(gameZombies.length()==0 || numZombiesNeededToSpawn==0){
                        nextRound();
                    }
                }
            }
            
        }
				
				updateHUDInfo();
			}
    }
		void nuke(){
			if(numNukesAvailable>0){
				for(int i=0; i <Game::gameZombies.length();i++){
					Game::gameZombies.remove(0);
				}
				playExplosionSound();
				Game::numNukesAvailable--;
				if(numZombiesNeededToSpawn==0){
					Game::nextRound();
				}
				
				updateHUDInfo();
			}
		}
		
    
    
    void moveForward(float amount){
			Vector3D forward = Camera::dir;
			forward = Vector3D(forward.x(),forward.y(),0);
			if(forward.len()>.01){
        Camera::pos = Camera::pos+forward.normalize().scale(amount);
        Camera::right = Camera::dir.cross(Camera::up).normalize();
			}
    }
    void moveSide(float amount){
			Vector3D side = Camera::right;
			side = Vector3D(side.x(),side.y(),0);
			if(side.len()>.01){
        Camera::pos = Camera::pos+side.normalize().scale(amount);
        Camera::right = Camera::dir.cross(Camera::up).normalize();
			}
    }
    void rotateHorizontal(float degrees){
        Camera::dir = rotateVector(degrees, Camera::dir, Camera::up);
        Camera::right = Camera::dir.cross(Camera::up).normalize();
    }
    void rotateVertical(float degrees){
        Camera::dir = rotateVector(degrees, Camera::dir, Camera::right);
        //Camera::up = Camera::right.cross(Camera::up);
    }
    
}

#endif /* Game_h */


