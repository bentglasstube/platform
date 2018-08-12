#pragma once

#include "audio.h"
#include "graphics.h"

class Platform {
  public:

    Platform();
    void draw(Graphics& graphics) const;

    void hit(Audio& audio, float x);
    bool exists(float x) const;

  private:

    int chunks_[32];

};
