#include "title_screen.h"

#include "game_screen.h"

TitleScreen::TitleScreen() : text_("text.png"), title_("title.png", 0, 0, 256, 64) {}

bool TitleScreen::update(const Input& input, Audio& audio, unsigned int) {
  if (!audio.music_playing()) audio.play_music("space.ogg");
  return !input.any_pressed();
}

void TitleScreen::draw(Graphics& graphics) const {
  space_.draw(graphics);
  platform_.draw(graphics);

  title_.draw(graphics, 0, 16);

  text_.draw(graphics, "Defend the platform", 128, 120, Text::Alignment::Center);
  text_.draw(graphics, "Arrows - Move", 128, 136, Text::Alignment::Center);
  text_.draw(graphics, "Space - Jump", 128, 152, Text::Alignment::Center);

  text_.draw(graphics, "Press Any Key", 128, 192, Text::Alignment::Center);
}

Screen* TitleScreen::next_screen() const {
  return new GameScreen;
}
