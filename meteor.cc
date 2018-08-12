#include "meteor.h"

#include <cmath>
#include <random>

Meteor::Meteor() {
  std::uniform_int_distribution<int> pd(0, 32);
  std::uniform_int_distribution<int> xd(0, 256);

  std::mt19937 rand;
  rand.seed(Util::random_seed());

  const float tx = pd(rand) * 8.0f + 4.0f;

  x_ = xd(rand);
  y_ = -16.0f;

  const float angle = std::atan2(208 - y_, tx - x_);
  vx_ = std::cos(angle) * 0.1f;
  vy_ = std::sin(angle) * 0.1f;

  hit_ = false;
}

bool Meteor::update(const Player& player, Platform& platform, unsigned int elapsed) {
  x_ += vx_ * elapsed;
  y_ += vy_ * elapsed;

  if (!hit_) {
    const float dx = player.x() - x_;
    const float dy = player.y() - 8 - y_;

    if (dx * dx + dy * dy < 81.0f) {
      const float angle = std::atan2(dy, dx);
      vx_ = std::cos(angle) * -0.15f;
      vy_ = std::sin(angle) * -0.15f;

      hit_ = true;
      return true;
    }
  }

  if (y_ > 204 && y_ < 212) {
    platform.hit(x_);
  }

  return false;
}

void Meteor::draw(Graphics& graphics) const {
  graphics.draw_circle(x_, y_, 4, 0xffffffff, false);
};
