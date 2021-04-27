#pragma once

#include "ofMain.h"

#define NUM 102*102

class ofApp : public ofBaseApp{
private:
//    ofVec2f velocity[100];
//    float density[100];
//    float prev_density[100];
//    void addSource(float source[], float dt);
//    void diffuse(float dt, float diff);
//    int getPos(int x, int y);
    
    ofVec2f velocity[NUM];
    ofVec2f prev_velocity[NUM];
    float density[NUM];
    float prev_density[NUM];
    float dt = 0.01;
    float diffusion = 0.001;
    float visc = 0.0;
    
    void get_from_ui();
    int getPos(int x, int y);
    bool isMousePressed = false;
    bool isLeftButton = true;
    void drawDensity();
    
    float inputSize = 5.0;
    
//    void addDensitySource();
//    void addVelocitySource();
    void velocityStep();
//    void diffuseVelocity();
    void drawVelocity();
    
//    void project();
//    void setPrevVelocityBoundary();
    void diffuseFloat(float* current, float* prev, float diffusionAmount, float dt);
    void diffuseVec(ofVec2f* current, ofVec2f* prev, float diffusionAmount, float dt);
    void setBoundaryFloat(float* current, int side);
    void setBoundaryVec(ofVec2f* current, int side);
    
    void advect(float* currentDensity, float* prevDensity, ofVec2f* currentVelocity, float dt);
    void advectVel(ofVec2f* currentVelocity, ofVec2f* prevVelocity, float dt);
    
    
    void project(ofVec2f* currentVelocity, ofVec2f* prevVelocity);
    
    
    
    
    void addSourceFloat(float* current, float* prev, float dt);
    void addSourceVec(ofVec2f* current, ofVec2f* prev, float dt);
    
    
    void densityStep();
    
    float cellSize = 10;

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
