#pragma once

#include "audio.h"
#include "graphics.h"
#include "input.h"
#include "spritemap.h"

#include "platform.h"

class Player {
  public:

    Player();

    bool update(const Platform& platform, Audio& audio, unsigned int elapsed);
    void draw(Graphics& graphics) const;

    void move(int dir);
    void stop();
    void jump(const Platform& platform);
    bool jumping() const;

    float x() const { return x_; }
    float y() const { return y_; }

  private:

    enum class Facing { Left, Right };

    float x_, y_, vx_, vy_;
    Facing facing_;
    bool jumping_;
    SpriteMap sprites_;

    static constexpr float kGravity = 0.001;

    bool touching(const Platform& platform) const;

};
