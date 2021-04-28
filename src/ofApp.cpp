//
//  ofApp.cpp
//
//  Created by クワシマ・ユウキ on 2021/04/26.
//

#include "ofApp.h"

void ofApp::setup(){
    fluid = Fluid();
    fluid.setup();
}

void ofApp::update() {
    fluid.update();
}

void ofApp::draw(){
    ofSetColor(0, 0, 0, 0);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    fluid.drawDensity();
    fluid.drawVelocity();
}

void ofApp::keyPressed(int key){

}

void ofApp::keyReleased(int key){

}

void ofApp::mouseMoved(int x, int y ){

}

void ofApp::mouseDragged(int x, int y, int button){

}

void ofApp::mousePressed(int x, int y, int button){
    fluid.isMousePressed = true;
    if (button == 0) fluid.isLeftButton = true;
    if (button == 2) fluid.isLeftButton = false;
}

void ofApp::mouseReleased(int x, int y, int button){
    fluid.isMousePressed = false;
}

void ofApp::mouseEntered(int x, int y){

}

void ofApp::mouseExited(int x, int y){

}
 
void ofApp::windowResized(int w, int h){

}

void ofApp::gotMessage(ofMessage msg){

}

void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
