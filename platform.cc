#include "platform.h"

#include <random>

#include "util.h"

Platform::Platform() {
  for (int i = 0; i < 32; ++i) {
    chunks_[i] = 1;
  }

  chunks_[0] = 2;
  chunks_[31] = 2;

  std::uniform_int_distribution<int> d(0, 31);
  std::mt19937 rand;
  rand.seed(Util::random_seed());

  int supports = 3;
  while (supports > 0) {
    const int i = d(rand);
    if (chunks_[i] == 1) {
      chunks_[i] = 2;
      --supports;
    }
  }
}

void Platform::update(unsigned int elapsed) {
  for (int i = 0; i < 32; ++i) {
    if (chunks_[i] < 0) {
      chunks_[i] -= elapsed;
      if (chunks_[i] < -1000) chunks_[i] = 0;
    }
  }

  for (int i = 0; i < 32; ++i) {
    if (!attached(i)) chunks_[i] = -1;
  }
}

void Platform::draw(Graphics& graphics) const {
  for (int i = 0; i < 32; ++i) {
    int y = 0, h = 4;
    if (chunks_[i] > 0) y = 208;
    else if (chunks_[i] < 0) y = 208 - chunks_[i] / 25;
    if (chunks_[i] == 2) h = 34;

    if (y > 0) {
      SDL_Rect r = { i * 8, y, 8, h };
      graphics.draw_rect(&r, 0x000000ff, true);
      graphics.draw_rect(&r, 0xffffffff, false);
    }
  }
}

void Platform::hit(Audio& audio, float x) {
  const int piece = x / 8;

  if (piece < 0) return;
  if (piece >= 32) return;

  if (chunks_[piece] == 1) {
    audio.play_sample("break.wav");
    chunks_[piece] = -1;
  }
}

bool Platform::exists(float x) const {
  const int piece = x / 8;

  if (piece < 0) return false;
  if (piece >= 32) return false;

  return chunks_[piece] > 0;
}

bool Platform::attached(int i) const {
  if (chunks_[i] != 1) return true;

  for (int j = i; j >= 0; --j) {
    if (chunks_[j] == 2) return true;
    if (chunks_[j] <= 0) break;
  }

  for (int j = i + 1; j < 32; ++j) {
    if (chunks_[j] == 2) return true;
    if (chunks_[j] <= 0) break;
  }

  return false;
}
