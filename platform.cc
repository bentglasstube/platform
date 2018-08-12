#include "platform.h"

Platform::Platform() {
  for (int i = 0; i < 32; ++i) {
    chunks_[i] = 1;
  }
}

void Platform::draw(Graphics& graphics) const {
  for (int i = 0; i < 32; ++i) {
    if (chunks_[i] > 0) {
      SDL_Rect r = { i * 8 , 208, 8, 4 };
      graphics.draw_rect(&r, 0xffffffff, false);
    }
  }
}

void Platform::hit(Audio& audio, float x) {
  const int piece = x / 8;

  if (piece < 0) return;
  if (piece >= 32) return;

  if (chunks_[piece] > 0) {
    audio.play_sample("break.wav");
    chunks_[piece] = 0;
  }
}

bool Platform::exists(float x) const {
  const int piece = x / 8;

  if (piece < 0) return false;
  if (piece >= 32) return false;

  return chunks_[piece] > 0;
}
