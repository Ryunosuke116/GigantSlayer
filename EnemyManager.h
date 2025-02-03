#pragma once

class Enemy;
class Player;

class EnemyManager
{
public:

	void GetPlayerPos(Player& player, Enemy& enemy);

	void Update(Player& player, Enemy& enemy);
	void CircumferenceCalculation(float& x, float& z, const float& stack, const float& speed);
};

