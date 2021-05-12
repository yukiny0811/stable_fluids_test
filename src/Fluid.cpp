//
//  fluid.cpp
//
//  Created by クワシマ・ユウキ on 2021/04/28.
//

#include "Fluid.hpp"

//addSource
void Fluid::addSourceFloat(float* current, float* prev, float dt) {
    for (int i = 0; i < NUM; i++) {
        current[i] += prev[i] * dt;
    }
}
void Fluid::addSourceVec(ofVec2f* current, ofVec2f* prev, float dt) {
    for (int i = 0; i < NUM; i++) {
        current[i] += prev[i] * dt;
    }
}

//拡散
void Fluid::diffuseFloat(float* current, float* prev, float diffusionAmount, float dt) {
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
void Fluid::diffuseVec(ofVec2f* current, ofVec2f* prev, float diffusionAmount, float dt) {
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
        setBoundaryVec(current, 1);
        setBoundaryVec(current, 2);
    }
}

//壁の計算
void Fluid::setBoundaryFloat(float* current, int side) {
    for (int i = 1; i < 101; i++) {
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
void Fluid::setBoundaryVec(ofVec2f* current, int side) {
    if (side == 1) {
        for (int i = 1; i < 101; i++) {
            current[getPos(0, i)].x = -current[getPos(1, i)].x;
            current[getPos(100+1, i)].x = -current[getPos(100, i)].x;
            current[getPos(i, 0)].x = current[getPos(i, 1)].x;
            current[getPos(i, 100+1)].x = current[getPos(i, 100)].x;
        }
        current[getPos(0, 0)].x = 0.5 * (current[getPos(1, 0)].x + current[getPos(0, 1)].x);
        current[getPos(0, 100+1)].x = 0.5 * (current[getPos(1, 100+1)].x + current[getPos(0, 100)].x);
        current[getPos(100+1, 0)].x = 0.5 * (current[getPos(100, 0)].x + current[getPos(100+1, 1)].x);
        current[getPos(100+1, 100+1)].x = 0.5 * (current[getPos(100, 100+1)].x + current[getPos(100+1, 100)].x);
    } else if (side == 2) {
        for (int i = 1; i < 101; i++) {
            current[getPos(0, i)].y = current[getPos(1, i)].y;
            current[getPos(100+1, i)].y = current[getPos(100, i)].y;
            current[getPos(i, 0)].y = -current[getPos(i, 1)].y;
            current[getPos(i, 100+1)].y = -current[getPos(i, 100)].y;
        }
        current[getPos(0, 0)].y = 0.5 * (current[getPos(1, 0)].y + current[getPos(0, 1)].y);
        current[getPos(0, 100+1)].y = 0.5 * (current[getPos(1, 100+1)].y + current[getPos(0, 100)].y);
        current[getPos(100+1, 0)].y = 0.5 * (current[getPos(100, 0)].y + current[getPos(100+1, 1)].y);
        current[getPos(100+1, 100+1)].y = 0.5 * (current[getPos(100, 100+1)].y + current[getPos(100+1, 100)].y);
    } else {
        for (int i = 1; i < 101; i++) {
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
}

//移流
void Fluid::advect(float* currentDensity, float* prevDensity, ofVec2f* currentVelocity, float dt) {
    float dt0 = dt * 100;
    for (int x = 1; x < 101; x++) {
        for (int y = 1; y < 101; y++) {
            float tempX = (float)x - dt0 * currentVelocity[getPos(x, y)].x;
            float tempY = (float)y - dt0 * currentVelocity[getPos(x, y)].y;
            
            if (tempX < 0.5) tempX = 0.5;
            if (tempX > 100 + 0.5) tempX = 100.0 + 0.5;
            int x0 = tempX;
            int x1 = x0 + 1;
            
            if (tempY < 0.5) tempY = 0.5;
            if (tempY > 100 + 0.5) tempY = 100.0 + 0.5;
            int y0 = tempY;
            int y1 = y0 + 1;
            
            float s1 = tempX - (float)x0;
            float s0 = 1.0 - s1;
            float t1 = tempY - (float)y0;
            float t0 = 1.0 - t1;
            
            currentDensity[getPos(x, y)] =
            s0 * (t0 * prevDensity[getPos(x0, y0)] + t1 * prevDensity[getPos(x0, y1)]) +
            s1 * (t0 * prevDensity[getPos(x1, y0)] + t1 * prevDensity[getPos(x1, y1)]);
        }
    }
    setBoundaryFloat(currentDensity, 0);
}
void Fluid::advectVel(ofVec2f* currentVelocity, ofVec2f* prevVelocity, float dt) {
    float dt0 = dt * 100;
    for (int x = 1; x < 101; x++) {
        for (int y = 1; y < 101; y++) {
            float tempX = (float)x - dt0 * prevVelocity[getPos(x, y)].x;
            float tempY = (float)y - dt0 * prevVelocity[getPos(x, y)].y;
            
            if (tempX < 0.5) tempX = 0.5;
            if (tempX > 100 + 0.5) tempX = 100 + 0.5;
            int x0 = tempX;
            int x1 = x0 + 1;
            
            if (tempY < 0.5) tempY = 0.5;
            if (tempY > 100 + 0.5) tempY = 100 + 0.5;
            int y0 = tempY;
            int y1 = y0 + 1;
            
            float s1 = tempX - (float)x0;
            float s0 = 1.0 - s1;
            float t1 = tempY - (float)y0;
            float t0 = 1.0 - t1;
            
            currentVelocity[getPos(x, y)].x =
            s0 * (t0 * prevVelocity[getPos(x0, y0)].x + t1 * prevVelocity[getPos(x0, y1)].x) +
            s1 * (t0 * prevVelocity[getPos(x1, y0)].x + t1 * prevVelocity[getPos(x1, y1)].x);
            currentVelocity[getPos(x, y)].y =
            s0 * (t0 * prevVelocity[getPos(x0, y0)].y + t1 * prevVelocity[getPos(x0, y1)].y) +
            s1 * (t0 * prevVelocity[getPos(x1, y0)].y + t1 * prevVelocity[getPos(x1, y1)].y);
        }
    }
    setBoundaryVec(currentVelocity, 1);
    setBoundaryVec(currentVelocity, 2);
}

//project
void Fluid::project(ofVec2f* currentVelocity, ofVec2f* prevVelocity) {
    float h = 1.0 / 100;
    for (int x = 1; x < 101; x++) {
        for (int y = 1; y < 101; y++) {
            prevVelocity[getPos(x, y)].y = -0.5 * h * (currentVelocity[getPos(x+1, y)].x -
                                                       currentVelocity[getPos(x-1, y)].x +
                                                       currentVelocity[getPos(x, y+1)].y -
                                                       currentVelocity[getPos(x, y-1)].y);
            prevVelocity[getPos(x, y)].x = 0;
        }
    }
    setBoundaryVec(prevVelocity, 0);

    for (int k = 0; k < 20; k++) {
        for (int x = 1; x < 101; x++) {
            for (int y = 1; y < 101; y++) {
                prevVelocity[getPos(x, y)].x =  (prevVelocity[getPos(x, y)].y +
                                                 prevVelocity[getPos(x-1, y)].x +
                                                 prevVelocity[getPos(x+1, y)].x +
                                                 prevVelocity[getPos(x, y-1)].x +
                                                 prevVelocity[getPos(x, y+1)].x) / 4.0;
            }
        }
        setBoundaryVec(prevVelocity, 0);
    }
    for (int x = 1; x < 101; x++) {
        for (int y = 1; y < 101; y++) {
            currentVelocity[getPos(x, y)].x -= 0.5 * (prevVelocity[getPos(x+1, y)].x - prevVelocity[getPos(x-1, y)].x) / h;
            currentVelocity[getPos(x, y)].y -= 0.5 * (prevVelocity[getPos(x, y+1)].x - prevVelocity[getPos(x, y-1)].x) / h;
        }
    }
    setBoundaryVec(currentVelocity, 1);
    setBoundaryVec(currentVelocity, 2);
}

//二次元座標をindexに変換
int Fluid::getPos(int x, int y) {
    return y * 102 + x;
}

//密度を描画
void Fluid::drawDensity() {
    for (int y = 0; y < NUM / (cellSize * cellSize); y++) {
        for (int x = 0; x < NUM / (cellSize * cellSize); x++) {
            ofSetColor(density[getPos(x, y)] * 150, density[getPos(x, y)] * 200,density[getPos(x, y)] * 255);
            ofDrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize);
        }
    }
}

//速度を描画
void Fluid::drawVelocity() {
    ofSetColor(255, 255, 255, 50);
    for (int y = 0; y < 102; y++) {
        for(int x = 0; x < 102; x++) {
            ofDrawLine(x * cellSize + cellSize/2,
                       y * cellSize + cellSize / 2,
                       x * cellSize + cellSize/2 + velocity[getPos(x, y)].x * 50,
                       y * cellSize + cellSize / 2 + velocity[getPos(x, y)].y * 50);
        }
    }
}

//速度の更新
void Fluid::velocityStep() {
    addSourceVec(velocity, prev_velocity, dt);
    swap(velocity, prev_velocity);
    diffuseVec(velocity, prev_velocity, diffusion, dt);
    project(velocity, prev_velocity);
    swap(velocity, prev_velocity);
    advectVel(velocity, prev_velocity, dt);
    project(velocity, prev_velocity);
}

//密度の更新
void Fluid::densityStep() {
    addSourceFloat(density, prev_density, dt);
    swap(density, prev_density);
    diffuseFloat(density, prev_density, diffusion, dt);
    swap(density, prev_density);
    advect(density, prev_density, velocity, dt);
}

//マウスインプット
void Fluid::get_from_ui() {
    for (int i = 0; i < NUM; i++) {
        prev_velocity[i] = ofVec2f(0, 0);
        prev_density[i] = 0;
    }
    
    int x = ofGetMouseX() / 10;
    int y = ofGetMouseY() / 10;
    
    int index = getPos(x, y);
    
    if (index < 0) return;
    if (index >= NUM) return;
    if (!isMousePressed) return;
    
    if (isLeftButton) {
        for (int ty = -inputSize; ty < inputSize; ty++) {
            for (int tx = -inputSize; tx < inputSize; tx++) {
                if (!(x + tx > 100 || x + tx < 0)) {
                    if (!(y + ty > 100 || y + ty < 0)) {
                        prev_density[getPos(x + tx, y+ty)] = 10;
                    }
                }
            }
        }
    } else {
        for (int ty = -inputSize; ty < inputSize; ty++) {
            for (int tx = -inputSize; tx < inputSize; tx++) {
                if (!(x + tx > 100 || x + tx < 0)) {
                    if (!(y + ty > 100 || y + ty < 0)) {
                        prev_density[getPos(x + tx, y+ty)] = -10;
                    }
                }
            }
        }
    }
    prev_velocity[index] = ofVec2f(((float)ofGetMouseX() - (float)ofGetPreviousMouseX()) * 1000, ((float)ofGetMouseY() - (float)ofGetPreviousMouseY()) * 1000);
}

//初期化
void Fluid::setup() {
    for (int i = 0; i < NUM; i++) {
        velocity[i] = ofVec2f(0, 0);
        prev_velocity[i] = ofVec2f(0, 0);
        density[i] = 0;
        prev_density[i] = 0;
    }
}

//更新
void Fluid::update() {
    get_from_ui();
    velocityStep();
    densityStep();
}
