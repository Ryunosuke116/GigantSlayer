#pragma once


class Title :public BaseScene
{
public:

    Title(SceneManager& manager);
    ~Title();

    void Initialize();
    void Update();
    void Draw();
private:
    int titleHandle;
    int movieHandle;
    int backGroundHandle;
    int start_font;
    int alpha;
    int addAlpha;
    int alpha_bright;
    int font_back;
    bool isPush;
    Camera* camera = NULL;
    Input* input = NULL;
    BlackOut* blackOut = NULL;
};

