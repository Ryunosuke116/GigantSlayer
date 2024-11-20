#pragma once
#include "Enemy.h"
#include"Object.h"

class ObjectManager
{
public:

    ObjectManager();
    ~ObjectManager();

    void Initialize(Enemy& enemy);
    void Update(Enemy& enemy, Calculation& calculation, const Input& input);
    void Draw();
    Object* object[4] = { NULL };
private:

};

