#pragma once

#include "../../Modules/Modules.hpp"

namespace alce
{
    enum AnimationMode
    {
        LoopForwards,
        LoopBackwards,
        OnceForwards,
        OnceBackwards,
        FirstFrameOnly
    };

    enum OriginMode
    {
        TopLeft,
        TopMiddle,
        TopRight,
        MiddleLeft,
        Center,
        MiddleRight,
        BottomLeft,
        BottomMiddle,
        BottomRight
    };

    class Animation2d : public Component
    {
    public:

        Animation2d();

        void AddAnimation(String spritesheetFile, String name, int rows, int cols, int frameWidth, int frameHeight);

        void DeleteAnimation(String name);

        void SetOriginMode(OriginMode originMode);

        void PlayAnimation(String name, AnimationMode mode = AnimationMode::LoopForwards);

        void SetAnimationMode(AnimationMode mode);

        void SetTimePerFrame(Time timePerFrame);

        void Pause(bool flag = true);

        bool IsPlaying();

        Dictionary<String, Vector2Ptr> GetCardinals();

        String GetCurrentAnimation();

        void Render();

        void Update();

        Vector2 scale = Vector2(1, 1);

    private:

        Dictionary<String, List<RectShape*>> animations;
        Dictionary<String, sf::Sprite*> spritesheets;
        Dictionary<String, Vector2Ptr> cardinals;

        String currentAnimation;
        AnimationMode currentMode;
        bool isPlaying = false;
        OriginMode originMode = OriginMode::Center;

        int numFrames;
        int msPerFrame = 100;
        int msSinceLastFrame;
        int currentFrameNum;

        bool paused = false;
        bool flipHorizontal = false;
        bool flipVertical = false;

        void DetermineNumFrames();
        void DetermineFirstFrameNum();
        void DetermineNextFrameNum();
        void SetTextureRectForFrame();
        bool IsDrawable();
    };

    typedef std::shared_ptr<Animation2d> Animation2dPtr;
}