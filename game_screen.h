#pragma once

#include <vector>

#include "graphics.h"
#include "input.h"
#include "screen.h"
#include "text.h"

#include "meteor.h"
#include "platform.h"
#include "player.h"
#include "space.h"

class GameScreen : public Screen {
  public:

    GameScreen();

    bool update(const Input& input, Audio& audio, unsigned int elapsed) override;
    void draw(Graphics& graphics) const override;

    Screen* next_screen() const override;

  private:

    Text text_;
    int score_, timer_;
    Player player_;
    Space space_;
    Platform platform_;
    std::vector<Meteor> meteors_;
};
