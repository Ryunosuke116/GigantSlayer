#pragma once
#include "DxLib.h"
#include <vector>
#include "Enemy.h"

class Camera
{
private:
    VECTOR AimPosition;
    VECTOR LookPosition;
    float a;
    float x, y, z;
    float addY;
    int time;
    bool flg;
    bool isDistance;
    bool isChangeUpdate;
public:

    Camera();
    ~Camera();

    void Initialize();
    void Update(const VECTOR& playerPosition, const VECTOR& enemyPosition);
    void TitleUpdate();
    void StartUpdate(Enemy& enemy);
    void Draw();
    void Leap(const VECTOR& playerPos, const VECTOR& enemyPosition);
    void EndUpdate(const VECTOR& enemyPosition);
    int GetTime() { return time; }
    bool GetIsChange() { return isChangeUpdate; }

};

