#include "ObjectManager.h"
#include <iostream>
#include <array>

bool ObjectManager::Comparison(std::array<Object*, 4> object)
{
    //�S�ďo�����Ă���ꍇ�Afalse�ɂ���
    for (auto& objects : object)
    {
        if ((*objects).GetIsObject())
        {
            return true;
        }
    }
     return false;

}
