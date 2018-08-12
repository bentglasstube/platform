#include "title_screen.h"

#include "game_screen.h"

TitleScreen::TitleScreen() : text_("text.png") {}

bool TitleScreen::update(const Input& input, Audio&, unsigned int) {
  return !input.any_pressed();
}

void TitleScreen::draw(Graphics& graphics) const {
  text_.draw(graphics, "Press Any Key", 128, 176, Text::Alignment::Center);
}

Screen* TitleScreen::next_screen() const {
  return new GameScreen;
}
