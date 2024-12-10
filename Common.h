#pragma once
#include "DxLib.h"
#include"Map.h"
#include "Player.h"
#include "Enemy.h"

class Common
{
private:
	static constexpr float	ShadowSize = 3.0f;		// �e�̑傫��
	static constexpr float	ShadowHeight = 90.0f;	// �e�������鍂��
	int shadowHandle;
public:

	Common();
	void Draw(Map& map, const VECTOR& PlayerPosition, const Enemy& enemy);

	void DrawShadow(const Map& map, const VECTOR& position);
};

