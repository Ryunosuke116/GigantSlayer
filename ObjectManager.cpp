#include "ObjectManager.h"
#include <iostream>
#include <array>

bool ObjectManager::Comparison(std::array<Object*, 4> object)
{
    //‘S‚ÄoŒ»‚µ‚Ä‚¢‚éê‡Afalse‚É‚·‚é
    for (auto& objects : object)
    {
        if ((*objects).GetIsObject())
        {
            return true;
        }
    }
     return false;

}
