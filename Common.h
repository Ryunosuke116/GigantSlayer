#pragma once


class Common
{
private:
	static constexpr float	ShadowSize = 3.0f;		// �e�̑傫��
	static constexpr float	ShadowHeight = 90.0f;	// �e�������鍂��
	int shadowHandle;
public:

	Common();
	~Common();
	void Update(Player& player, std::array<Object*, 4> objects);
	void MovableCalculation(VECTOR& position);
	void Draw(Map& map, const VECTOR& PlayerPosition, const Enemy& enemy);

	void DrawShadow(const Map& map, const VECTOR& position);
};

