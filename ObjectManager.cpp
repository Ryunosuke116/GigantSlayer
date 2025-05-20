#include "Include.h"


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

void ObjectManager::Update(std::array<Object*, 4> object,
    Player& player, Calculation& calculation)
{
    for (auto& objects : object)
    {
        //playerに接触しているかつオブジェクトを掴める状態
        if (objects->GetIsPickUp() && objects->GetIsCanCatch())
        {
            //持ち上げ始めたらtrue
            objects->SetIsDoingPickUp(true);

            VECTOR targetPosition = player.GetTopPosition();
            targetPosition.y += 6.0f;

            VECTOR subTargetPosition = VSub(targetPosition, objects->GetPosition());

            VECTOR scaleTargetPosition = VScale(subTargetPosition, 0.1f);
            
            //徐々に上へと持ち上げる
            objects->SetPosition(VAdd(objects->GetPosition(),
                scaleTargetPosition));

            //差が限りなく小さくなったら座標を連動させる
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
/// object同士が重ならないようにする
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
               //objectが接触しているとき
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
/// playerが転がったら後ろに飛ばす
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