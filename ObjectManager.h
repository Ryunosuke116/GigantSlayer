#pragma once
#include "Object.h"
#include <iostream>
#include <array>

class Object;

class ObjectManager
{
public:
    void Update();
    bool Comparison(std::array<Object*, 4> object);
private:
   
};

