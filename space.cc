#include "space.h"

#include "util.h"

#include <random>

Space::Space() {
  std::uniform_int_distribution<int> xd(0, 255);
  std::uniform_int_distribution<int> yd(0, 239);
  std::uniform_int_distribution<int> cd(0, 63);

  std::mt19937 rand;
  rand.seed(Util::random_seed());

  for (int i = 0; i < 256; ++i) {
    Star s;
    s.x = xd(rand);
    s.y = yd(rand);
    s.r = cd(rand);
    s.g = cd(rand);
    s.b = cd(rand);

    stars_.push_back(s);
  }
}


void Space::draw(Graphics& graphics) const {
  std::uniform_int_distribution<int> twinkle(0, 64);
  std::mt19937 rand;
  rand.seed(Util::random_seed());

  for (const auto s : stars_) {
    const int c = s.r << 24 | s.g << 16 | s.b << 8 | 0xc0c0c0ff;

    if (twinkle(rand) != 0) graphics.draw_pixel(s.x, s.y, c);
  }
}
