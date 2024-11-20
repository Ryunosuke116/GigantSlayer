#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
    for (int i = 0; i < 4; i++)
    {
        object[i] = new Object();
    }
}

void ObjectManager::Initialize(Enemy& enemy)
{
    for (int i = 0; i < 4; i++)
    {
        object[i]->Initialize(enemy);
    }
}

void ObjectManager::Update(Enemy& enemy, Calculation& calculation, const Input& input)
{
    for (int i = 0; i < 4; i++)
    {
        if (!object[i]->GetIsObject())
        {
            object[i]->WhichOnObject(enemy.bullet->GetIsEmerge());
            break;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        if (object[i]->GetIsObject())
        {
            object[i]->Update(enemy, calculation, input);
        }
    }
    
}

void ObjectManager::Draw()
{
    for (int i = 0; i < 4; i++)
    {
        object[i]->Draw();
    }
}