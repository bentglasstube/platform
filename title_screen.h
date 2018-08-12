#pragma once

#include "graphics.h"
#include "input.h"
#include "screen.h"
#include "text.h"

#include "space.h"
#include "platform.h"

class TitleScreen : public Screen {
  public:

    TitleScreen();

    bool update(const Input& input, Audio& audio, unsigned int elapsed) override;
    void draw(Graphics& graphics) const override;

    Screen* next_screen() const override;

  private:

    Text text_;
    Space space_;
    Platform platform_;
};
