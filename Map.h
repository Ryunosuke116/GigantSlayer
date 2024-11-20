#pragma once
#include "DxLib.h"
#include"EffekseerForDXLib.h"
#include <vector>

class Map
{
private:
    int backGroundHandle;
    int fieldHandle;

    VECTOR position;
    VECTOR fieldPosition;
public:
    Map();
    ~Map();

    void Initialize();
    void Update();
    void Draw();
};

