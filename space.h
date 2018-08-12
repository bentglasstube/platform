#pragma once

#include <vector>

#include "graphics.h"

class Space {
  public:
    Space();

    void draw(Graphics& graphics) const;

  private:

    struct Star { int x, y, r, g, b; };
    std::vector<Star> stars_;
};
