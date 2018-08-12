#pragma once

#include "graphics.h"
#include "spritemap.h"

#include "player.h"
#include "platform.h"

class Meteor {
  public:

    Meteor();
    bool update(const Player& player, Platform& platform, unsigned int elapsed);
    void draw(Graphics& graphics) const;

  private:

    float x_, y_, vx_, vy_;
    bool hit_;
    int which_;
    SpriteMap sprites_;

};
