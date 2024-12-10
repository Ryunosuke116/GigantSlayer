#pragma once
#include "DxLib.h"
#include"EffekseerForDXLib.h"
#include "Effect.h"
#include <vector>

class Map
{
private:
    int backGroundHandle;
    int fieldHandle;
    int time;

    VECTOR position;
    VECTOR fieldPosition;
    VECTOR effectPosition;
    VECTOR rotationPosition;
    Effect* effect;
public:
    Map();
    ~Map();

    void Initialize();
    void Update();
    void Draw();
    int GetModelHandle() const { return fieldHandle; }
};

