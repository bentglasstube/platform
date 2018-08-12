#include "title_screen.h"

#include "game_screen.h"

TitleScreen::TitleScreen() : text_("text.png") {}

bool TitleScreen::update(const Input& input, Audio& audio, unsigned int) {
  if (!audio.music_playing()) audio.play_music("space.ogg");
  return !input.any_pressed();
}

void TitleScreen::draw(Graphics& graphics) const {
  space_.draw(graphics);
  platform_.draw(graphics);
  text_.draw(graphics, "Press Any Key", 128, 176, Text::Alignment::Center);
}

Screen* TitleScreen::next_screen() const {
  return new GameScreen;
}
