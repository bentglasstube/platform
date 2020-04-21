#include "player.h"

Player::Player() : x_(128), y_(208), vx_(0), vy_(0), frame_(0), jumping_(true), sprites_("spaceman.png", 16, 8, 16)  {}

bool Player::update(const Platform& platform, Audio&, unsigned int elapsed) {
  vy_ = vy_ + kGravity * elapsed;
  if (vy_ > 0.1f) vy_ = 0.1f;

  const float ny = y_ + elapsed * vy_;

  if (y_ <= 208 && ny > 208 && touching(platform)) {
    jumping_ = false;
    y_ = 208;
    vy_ = 0;
  } else {
    y_ = ny;
  }

  x_ += elapsed * vx_;

  if (x_ < 4) x_ = 4;
  if (x_ > 252) x_ = 252;

  if (vx_ != 0 && !jumping()) {
    frame_ += elapsed;
    frame_ %= 300;
  }

  return y_ < 256;
}

void Player::draw(Graphics& graphics) const {
  int s = 0;
  if (vx_ != 0) s = frame_ < 150 ? 1 : 2;
  if (vy_ > 0) s = 3;
  sprites_.draw(graphics, s, (int)(x_ - 4), (int)(y_ - 16));
}

void Player::move(int dir) {
  vx_ += dir / 8.0f;
}

void Player::stop() {
  vx_ = 0;
}

void Player::jump(const Platform& platform, Audio& audio) {
  if (!jumping_ && vy_ == 0 && touching(platform)) {
    vy_ = -0.3;
    jumping_ = true;
    audio.play_sample("jump.wav");
  }
}

bool Player::jumping() const {
  return jumping_;
}

bool Player::touching(const Platform& platform) const {
  return platform.exists(x_ - 4) || platform.exists(x_ + 4);
}
