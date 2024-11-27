#pragma once
#include "DxLib.h"
#include"EffekseerForDXLib.h"
#include <vector>
#include "Player.h"
#include "Enemy.h"

class EnemyManager
{
public:

	void GetPlayerMoveSpeed(Player& player,Enemy& enemy);
	void GetPlayerPos(Player& player, Enemy& enemy);
	void GetIsMove(Player& player, Enemy& enemy);

	void Update(Player& player, Enemy& enemy);
	void CircumferenceCalculation(float& x, float& z, const float& stack, const float& speed);
};

