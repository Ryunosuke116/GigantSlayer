#pragma once


class Common
{
private:
	static constexpr float	ShadowSize = 3.0f;		// ‰e‚Ì‘å‚«‚³
	static constexpr float  bulletShadowSize = 9.0f;
	static constexpr float	ShadowHeight = 180.0f;	// ‰e‚ª—‚¿‚é‚‚³
	static constexpr float  bulletShadowHeight = 300.0f;
	int shadowHandle;
	int bulletShadowHandle;
public:

	Common(const char* path);
	~Common();
	void Update(Player& player, std::array<Object*, 4> objects);
	void MovableCalculation(VECTOR& position);
	void Draw(Map& map, const VECTOR& PlayerPosition, const Enemy& enemy);

	void DrawShadow(const int ShadowSize, const int ShadowHeight, const int shadowHandle, const Map& map, const VECTOR& position);
};

