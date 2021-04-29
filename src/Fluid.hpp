//
//  fluid.hpp
//
//  Created by クワシマ・ユウキ on 2021/04/28.
//

#ifndef Fluid_hpp
#define Fluid_hpp

#include <stdio.h>

#endif

#include <ofMain.h>

//100*100のグリッド + 壁
#define NUM 102*102

class Fluid {
private:
    
    //速度
    ofVec2f velocity[NUM];
    ofVec2f prev_velocity[NUM];
    
    //密度
    float density[NUM];
    float prev_density[NUM];
    
    //微小時間を設定
    float dt = 0.01;
    
    //拡散する速さ（量）を設定
    float diffusion = 0.001;
    
    //セルの辺の長さを設定
    float cellSize = 10;
    
    //マウスをドラッグした際の入力半径を設定
    float inputSize = 5.0;
    
    //二次元座標から配列のindexを取得
    int getPos(int x, int y);
    
    //addSource
    void addSourceFloat(float* current, float* prev, float dt);
    void addSourceVec(ofVec2f* current, ofVec2f* prev, float dt);
    
    //拡散
    void diffuseFloat(float* current, float* prev, float diffusionAmount, float dt);
    void diffuseVec(ofVec2f* current, ofVec2f* prev, float diffusionAmount, float dt);
    
    //移流
    void advect(float* currentDensity, float* prevDensity, ofVec2f* currentVelocity, float dt);
    void advectVel(ofVec2f* currentVelocity, ofVec2f* prevVelocity, float dt);
    
    //壁の設定
    void setBoundaryFloat(float* current, int side);
    void setBoundaryVec(ofVec2f* current, int side);
    
    //project
    void project(ofVec2f* currentVelocity, ofVec2f* prevVelocity);
    
    //密度の計算ステップ
    void densityStep();
    
    //速度の計算ステップ
    void velocityStep();
    
    //ユーザーインタラクション
    void get_from_ui();
    
public:
    
    //マウスの入力判定
    bool isMousePressed = false;
    bool isLeftButton = true;
    
    //初期化
    void setup();
    
    //更新
    void update();
    
    //密度を描画
    void drawDensity();
    
    //速度を描画
    void drawVelocity();
        
};
