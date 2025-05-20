#include "Include.h"


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

void ObjectManager::Update(std::array<Object*, 4> object,
    Player& player, Calculation& calculation)
{
    for (auto& objects : object)
    {
        //player�ɐڐG���Ă��邩�I�u�W�F�N�g��͂߂���
        if (objects->GetIsPickUp() && objects->GetIsCanCatch())
        {
            //�����グ�n�߂���true
            objects->SetIsDoingPickUp(true);

            VECTOR targetPosition = player.GetTopPosition();
            targetPosition.y += 6.0f;

            VECTOR subTargetPosition = VSub(targetPosition, objects->GetPosition());

            VECTOR scaleTargetPosition = VScale(subTargetPosition, 0.1f);
            
            //���X�ɏ�ւƎ����グ��
            objects->SetPosition(VAdd(objects->GetPosition(),
                scaleTargetPosition));

            //��������Ȃ��������Ȃ�������W��A��������
            if (0.03f> targetPosition.y - objects->GetPosition().y)
            {
                objects->SetIsDoingPickUp(false);
                objects->SetIsCanCatch(false);
            }

        }

        if (objects->GetIsPlayerHold() && !objects->GetIsDoingPickUp())
        {
            VECTOR holdPosition = player.GetTopPosition();
            holdPosition.y += 6.0f;

            HoldObject(*objects, holdPosition,
                player.GetTargetMoveDirection_Norm());
        }

    }

    LetGoObject(object,calculation);

    LeanBackObject(object, player);
}

/// <summary>
/// 
/// </summary>
/// <param name="object"></param>
/// <param name="playerPosition"></param>
/// <param name="angle"></param>
void ObjectManager::HoldObject(Object& object,VECTOR playerPosition,VECTOR angle)
{
    object.SetPosition(playerPosition);
    object.SetAngle(angle);
}

/// <summary>
/// object���m���d�Ȃ�Ȃ��悤�ɂ���
/// </summary>
/// <param name="object"></param>
/// <param name="calculation"></param>
void ObjectManager::LetGoObject(std::array<Object*, 4> object, Calculation& calculation)
{
    const int maxObject = 4;

    for (int i = 0; i < maxObject; i++)
    {
        for (int j = 0; j < maxObject; j++)
        {
            if (i != j)
            {
               //object���ڐG���Ă���Ƃ�
                if (calculation.HitConfirmation(object[i]->GetPosition(), object[j]->GetPosition(),
                    object[i]->GetRadius(), object[j]->GetRadius()))
                {
                    object[i]->LetGoCalculation(object[j]->GetPosition());
                    object[j]->LetGoCalculation(object[i]->GetPosition());
                }

            }
        }
    }
}

/// <summary>
/// player���]����������ɔ�΂�
/// </summary>
/// <param name="object"></param>
/// <param name="player"></param>
void ObjectManager::LeanBackObject(std::array<Object*, 4> object, Player& player)
{
    const int down = 7;

    if (player.GetMotionNum() == down)
    {
        for (auto& objects : object)
        {
            if (!objects->GetIsDrop() && 
                objects->GetIsPlayerHold())
            {
                objects->SetIsLeanBack(true);
            }
        }
        
    }

    for (auto& objects : object)
    {
        objects->LeanBackObject();
    }
}