#include "ofApp.h"

void ofApp::addSourceFloat(float* current, float* prev, float dt) {
    for (int i = 0; i < NUM; i++) {
        current[i] += prev[i] * dt;
    }
}
void ofApp::addSourceVec(ofVec2f* current, ofVec2f* prev, float dt) {
    for (int i = 0; i < NUM; i++) {
        current[i] += prev[i] * dt;
    }
}
void ofApp::diffuseFloat(float* current, float* prev, float diffusionAmount, float dt) {
    int iter = 20;
    float amount = dt * diffusionAmount * 100 * 100;
    for (int k = 0; k < iter; k++) {
        for (int y = 1; y < 101; y++) {
            for (int x = 1; x < 101; x++) {
                current[getPos(x, y)] = (prev[getPos(x, y)] +
                                         amount * (
                                                   current[getPos(x-1, y)] +
                                                   current[getPos(x+1, y)] +
                                                   current[getPos(x, y-1)] +
                                                   current[getPos(x, y+1)])
                                         ) / (1 + 4*amount);
            }
        }
        setBoundaryFloat(current, 0);
    }
}

void ofApp::setBoundaryFloat(float* current, int side) {
    for (int i = 0; i < 100; i++) {
        current[getPos(0, i)] = side == 1 ? -current[getPos(1, i)] : current[getPos(1, i)];
        current[getPos(100+1, i)] = side == 1 ? -current[getPos(100, i)] : current[getPos(100, i)];
        current[getPos(i, 0)] = side == 2 ? -current[getPos(i, 1)] : current[getPos(i, 1)];
        current[getPos(i, 100+1)] = side == 2 ? -current[getPos(i, 100)] : current[getPos(i, 100)];
    }
    current[getPos(0, 0)] = 0.5 * (current[getPos(1, 0)] + current[getPos(0, 1)]);
    current[getPos(0, 100+1)] = 0.5 * (current[getPos(1, 100+1)] + current[getPos(0, 100)]);
    current[getPos(100+1, 0)] = 0.5 * (current[getPos(100, 0)] + current[getPos(100+1, 1)]);
    current[getPos(100+1, 100+1)] = 0.5 * (current[getPos(100, 100+1)] + current[getPos(100+1, 100)]);
}

void ofApp::setBoundaryVec(ofVec2f* current, int side) {
    for (int i = 0; i < 100; i++) {
        current[getPos(0, i)] = side == 1 ? -current[getPos(1, i)] : current[getPos(1, i)];
        current[getPos(100+1, i)] = side == 1 ? -current[getPos(100, i)] : current[getPos(100, i)];
        current[getPos(i, 0)] = side == 2 ? -current[getPos(i, 1)] : current[getPos(i, 1)];
        current[getPos(i, 100+1)] = side == 2 ? -current[getPos(i, 100)] : current[getPos(i, 100)];
    }
    current[getPos(0, 0)] = 0.5 * (current[getPos(1, 0)] + current[getPos(0, 1)]);
    current[getPos(0, 100+1)] = 0.5 * (current[getPos(1, 100+1)] + current[getPos(0, 100)]);
    current[getPos(100+1, 0)] = 0.5 * (current[getPos(100, 0)] + current[getPos(100+1, 1)]);
    current[getPos(100+1, 100+1)] = 0.5 * (current[getPos(100, 100+1)] + current[getPos(100+1, 100)]);
}
void ofApp::densityStep() {
    addSourceFloat(density, prev_density, dt);
    swap(density, prev_density);
    diffuseFloat(density, prev_density, diffusion, dt);
    swap(density, prev_density);
    advect(density, prev_density, velocity, dt);
}

void ofApp::velocityStep() {
    addSourceVec(velocity, prev_velocity, dt);
    swap(velocity, prev_velocity);
    diffuseVec(velocity, prev_velocity, diffusion, dt);
    //project
//    project(velocity, prev_velocity);
//    swap(velocity, prev_velocity);
//    advectVel(velocity, prev_velocity, dt);
    //project
//    project(velocity, prev_velocity);
    
}

void ofApp::diffuseVec(ofVec2f* current, ofVec2f* prev, float diffusionAmount, float dt) {
    int iter = 20;
    float amount = dt * diffusionAmount * 100 * 100;
    for (int k = 0; k < iter; k++) {
        for (int y = 1; y < 101; y++) {
            for (int x = 1; x < 101; x++) {
                current[getPos(x, y)] = (prev[getPos(x, y)] +
                                         amount * (
                                                   current[getPos(x-1, y)] +
                                                   current[getPos(x+1, y)] +
                                                   current[getPos(x, y-1)] +
                                                   current[getPos(x, y+1)])
                                         ) / (1 + 4*amount);
            }
        }
        setBoundaryVec(current, 0);
    }
}

void ofApp::advect(float* currentDensity, float* prevDensity, ofVec2f* currentVelocity, float dt) {
    float dt0 = dt * 100;
    for (int x = 1; x < 101; x++) {
        for (int y = 1; y < 101; y++) {
            float tempX = x - dt0 * currentVelocity[getPos(x, y)].x;
            float tempY = y - dt0 * currentVelocity[getPos(x, y)].y;
            
            if (tempX < 0.5) tempX = 0.5;
            if (tempX > 100 + 0.5) tempX = 100 + 0.5;
            int x0 = tempX;
            int x1 = x0 + 1;
            
            if (tempY < 0.5) tempY = 0.5;
            if (tempY > 100 + 0.5) tempY = 100 + 0.5;
            int y0 = tempY;
            int y1 = y0 + 1;
            
            float s1 = tempX - x0;
            float s0 = 1 - s1;
            float t1 = tempY - y0;
            float t0 = 1 - t1;
            
            currentDensity[getPos(x, y)] =
            s0 * (t0 * prevDensity[getPos(x0, y0)] + t1 * prevDensity[getPos(x0, y1)]) +
            s1 * (t0 * prevDensity[getPos(x1, y0)] + t1 * prevDensity[getPos(x1, y1)]);
        }
    }
    setBoundaryFloat(currentDensity, 0);
}
void ofApp::advectVel(ofVec2f* currentVelocity, ofVec2f* prevVelocity, float dt) {
    float dt0 = dt * 100;
    for (int x = 1; x < 101; x++) {
        for (int y = 1; y < 101; y++) {
            float tempX = x - dt0 * prevVelocity[getPos(x, y)].x;
            float tempY = y - dt0 * prevVelocity[getPos(x, y)].y;
            
            if (tempX < 0.5) tempX = 0.5;
            if (tempX > 100 + 0.5) tempX = 100 + 0.5;
            int x0 = tempX;
            int x1 = x0 + 1;
            
            if (tempY < 0.5) tempY = 0.5;
            if (tempY > 100 + 0.5) tempY = 100 + 0.5;
            int y0 = tempY;
            int y1 = y0 + 1;
            
            float s1 = tempX - x0;
            float s0 = 1 - s1;
            float t1 = tempY - y0;
            float t0 = 1 - t1;
            
            currentVelocity[getPos(x, y)].x =
            s0 * (t0 * prevVelocity[getPos(x0, y0)].x + t1 * prevVelocity[getPos(x0, y1)].x) +
            s1 * (t0 * prevVelocity[getPos(x1, y0)].x + t1 * prevVelocity[getPos(x1, y1)].x);
            currentVelocity[getPos(x, y)].y =
            s0 * (t0 * prevVelocity[getPos(x0, y0)].y + t1 * prevVelocity[getPos(x0, y1)].y) +
            s1 * (t0 * prevVelocity[getPos(x1, y0)].y + t1 * prevVelocity[getPos(x1, y1)].y);
        }
    }
    setBoundaryVec(currentVelocity, 0);
}

//--------------------------------------------------------------
void ofApp::setup(){
//    for (int i = 0; i < 100; i++) {
//        density[i] = 0;
//        prev_density[i] = 0;
//    }
    for (int i = 0; i < NUM; i++) {
        velocity[i] = ofVec2f(0, 0);
        prev_velocity[i] = ofVec2f(0, 0);
        density[i] = 0;
        prev_density[i] = 0;
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    get_from_ui();
    velocityStep();
    densityStep();
}

void ofApp::get_from_ui() {
//    printf("test1");
    for (int i = 0; i < NUM; i++) {
        prev_velocity[i] = ofVec2f(0, 0);
        prev_density[i] = 0;
    }
    
    int x = (int) mouseX / 10;
    int y = (int) mouseY / 10;
    
    int index = getPos(x, y);
    
    if (index < 0) return;
    if (index >= NUM) return;
//    printf("oooooo");
    if (!isMousePressed) return;
    
//    printf("oooooo");
    
    if (isLeftButton) {
//        density[index] = 1;
        for (int ty = -inputSize; ty < inputSize; ty++) {
            for (int tx = -inputSize; tx < inputSize; tx++) {
                if (!(x + tx > 100 || x + tx < 0)) {
                    if (!(y + ty > 100 || y + ty < 0)) {
                        density[getPos(x + tx, y+ty)] = 1;
                    }
                }
            }
        }
    } else {
//        density[index] = 0;
        for (int ty = -inputSize; ty < inputSize; ty++) {
            for (int tx = -inputSize; tx < inputSize; tx++) {
                if (!(x + tx > 100 || x + tx < 0)) {
                    if (!(y + ty > 100 || y + ty < 0)) {
                        density[getPos(x + tx, y+ty)] = 0;
                    }
                }
            }
        }
    }
    prev_velocity[index] = ofVec2f(((float)ofGetMouseX() - (float)ofGetPreviousMouseX()) * 100, ((float)ofGetMouseY() - (float)ofGetPreviousMouseY()) * 100);
    
    
    
}
//--------------------------------------------------------------
void ofApp::draw(){
    
    drawDensity();
    drawVelocity();
    
//    for (int y = 0; y < NUM / cellSize; y++) {
//        for (int x = 0; x < NUM / cellSize; x++) {
//            ofSetColor(255, 0, 0);
//            ofDrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize);
//        }
//    }
    
//    float cellSize = 100;
//    for (int y = 0; y < 10; y++) {
//        for (int x = 0; x < 10; x++) {
//            ofSetColor(255, 0, 0);
//            ofDrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize);
//        }
//    }
}

//void ofApp::addVelocitySource() {
//    for (int i = 0; i < NUM; i++) {
//        velocity[i] += prev_velocity[i] * dt;
//    }
//}

//void ofApp::addDensitySource() {
//    for (int i = 0; i < NUM; i++) {
//        density[i] += prev_density[i] * dt;
//    }
//    for (int i = 0; i < 100; i++) {
//        density[i] += source[i] * dt;
//    }
//}
//
//void ofApp::diffuse(float dt, float diff) {
//    float a = dt * diff * 10 * 10;
//    for (int k = 0; k < 20; k++) {
//        for (int y = 0; y < 10; y++) {
//            for (int x = 0; x < 10; x++) {
//                density[getPos(x, y)] = (prev_density[getPos(x, y)] + a * (density[getPos(x-1, y)] + density[getPos(x+1, y)] + density[getPos(x, y-1)] + density[getPos(x, y+1)])) / (1 + 4 * a);
//            }
//        }
//    }
//}
//
int ofApp::getPos(int x, int y) {
    return y * 102 + x;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    isMousePressed = true;
    if (button == 0) isLeftButton = true;
    if (button == 2) isLeftButton = false;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    isMousePressed = false;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::drawDensity() {
//    printf("%f", density[getPos(20, 20)]);
    for (int y = 0; y < NUM / (cellSize * cellSize); y++) {
        for (int x = 0; x < NUM / (cellSize * cellSize); x++) {
            ofSetColor(density[getPos(x, y)] * 255, 50, 50);
            ofDrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize);
        }
    }
}

void ofApp::project(ofVec2f* currentVelocity, ofVec2f* prevVelocity) {
//    float h = 1 / 100;
//    for (int x = 1; x < 101; x++) {
//        for (int y = 1; y < 101; y++) {
//            prevVelocity[getPos(x, y)].y = -0.5 * h * (currentVelocity[getPos(x+1, y)].x -
//                                                       currentVelocity[getPos(x-1, y)].x +
//                                                       currentVelocity[getPos(x, y+1)].y +
//                                                       currentVelocity[getPos(x, y-1)].y);
//            prevVelocity[getPos(x, y)].x = 0;
//        }
//    }
//    setBoundaryVec(prevVelocity, 0);
//
//    for (int k = 0; k < 20; k++) {
//        for (int x = 1; x < 101; x++) {
//            for (int y = 1; y < 101; y++) {
//                prevVelocity[getPos(x, y)].x =  (prevVelocity[getPos(x, y)].y +
//                                                 prevVelocity[getPos(x-1, y)].x +
//                                                 prevVelocity[getPos(x+1, y)].x +
//                                                 prevVelocity[getPos(x, y-1)].x +
//                                                 prevVelocity[getPos(x, y+1)].x) / 4;
//            }
//        }
//        setBoundaryVec(prevVelocity, 0);
//    }
//    for (int x = 1; x < 101; x++) {
//        for (int y = 1; y < 101; y++) {
//            currentVelocity[getPos(x, y)].x -= 0.5 * (prevVelocity[getPos(x+1, y)].x - prevVelocity[getPos(x-1, y)].x) / h;
//            currentVelocity[getPos(x, y)].y -= 0.5 * (prevVelocity[getPos(x, y+1)].x - prevVelocity[getPos(x, y-1)].x) / h;
//        }
//    }
//    setBoundaryVec(currentVelocity, 0);
    
}



//void ofApp::velocityStep() {
//    addVelocitySource();
//    diffuseVelocity();
//}

void ofApp::drawVelocity() {
    ofSetColor(0, 255, 0, 100);
    for (int y = 0; y < 100; y++) {
        for(int x = 0; x < 100; x++) {
            ofDrawLine(x * cellSize + cellSize/2,
                       y * cellSize + cellSize / 2,
                       x * cellSize + cellSize/2 + velocity[getPos(x, y)].x * 50,
                       y * cellSize + cellSize / 2 + velocity[getPos(x, y)].y * 50);
        }
    }
    
    printf("%f,%f\n", velocity[getPos(50, 50)].x,velocity[getPos(50, 50)].y);
}

//void ofApp::project() {
//    for (int y = 0; y < 100; y++) {
//        for(int x = 0; x < 100; x++) {
//            prev_velocity[getPos(x, y)] = -0.5f * (velocity[getPos(x+1, y)] - velocity[getPos(x-1, y)] + velocity[getPos(x, y+1)] - velocity[getPos(x+1, y-1)]) / 100;
//        }
//    }
//    setPrevVelocityBoundary();
//
//    int iter = 20;
//    int a = 1;
//    for (int k = 0; k < iter; k++) {
//        for (int y = 0; y < 100; y++) {
//            for(int x = 0; x < 100; x++) {
//                ve[getPos(x, y)] = prev_velocity[getPos(x, y)] + a * (velocity[getPos(x-1, y)] + velocity[getPos(x+1, y)] + velocity[getPos(x, y-1)] + velocity[getPos(x, y+1)]) / 4;
//            }
//        }
//    }
//
//
//}

//void ofApp::setPrevVelocityBoundary() {
//    for (int i = 0; i < 102; i++) {
//        prev_velocity[i] = ofVec2f(0);
//        prev_velocity[102 * 101 + i] = ofVec2f(0);
//        prev_velocity[i * 102] = ofVec2f(0);
//        prev_velocity[i*102 + 102] = ofVec2f(0);
//    }
//}
//
//void ofApp::diffuseVelocity() {
//    float a = dt * diffusion * NUM;
//    int iter = 20;
//
//    //swap
//    for (int i = 0; i < NUM; i++) {
//        ofVec2f temp = prev_velocity[i];
//        prev_velocity[i] = velocity[i];
//        velocity[i] = temp;
//    }
//
//    for (int k = 0; k < iter; k++) {
//        for (int y = 0; y < 100; y++) {
//            for(int x = 0; x < 100; x++) {
//                velocity[getPos(x, y)] = prev_velocity[getPos(x, y)] + a * (velocity[getPos(x-1, y)] + velocity[getPos(x+1, y)] + velocity[getPos(x, y-1)] + velocity[getPos(x, y+1)]) / (1 + 4 * a);
//            }
//        }
//    }
//}
