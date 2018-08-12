#pragma once

#include "graphics.h"

class Platform {
  public:

    Platform();
    void draw(Graphics& graphics) const;

    void hit(float x);
    bool exists(float x) const;

  private:

    int chunks_[32];

};
