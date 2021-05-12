//
//  ofApp.h
//
//  Created by クワシマ・ユウキ on 2021/04/26.
//

#pragma once

#include "ofMain.h"
#include "Fluid.hpp"

#define NUM 102*102

class ofApp : public ofBaseApp{
    
private:
    Fluid fluid;

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
