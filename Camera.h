#pragma once
#include "DxLib.h"
#include <vector>

class Camera
{
private:
    VECTOR AimPosition;
    VECTOR LookPosition;
    float a;
    float x, y, z;
    bool flg;
    bool isDistance;
public:

    Camera();
    ~Camera();

    void Initialize();
    void Update(const VECTOR& playerPosition, const VECTOR& enemyPosition);
    void TitleUpdate();
    void Draw();
    void Leap(const VECTOR& playerPos, const VECTOR& enemyPosition);

};

