#include "ObjectManager.h"
#include <iostream>
#include <array>

bool ObjectManager::Comparison(std::array<Object*, 4> object)
{
    //全て出現している場合、falseにする
    for (auto& objects : object)
    {
        if ((*objects).GetIsObject())
        {
            return true;
        }
    }
     return false;

}
