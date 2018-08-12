#include "game_screen.h"

#include "title_screen.h"

GameScreen::GameScreen() : text_("text.png"), score_(0), timer_(3000), space_() {}

bool GameScreen::update(const Input& input, Audio& audio, unsigned int elapsed) {
  if (!player_.jumping()) {
    player_.stop();
    if (input.key_held(Input::Button::Left)) player_.move(-1);
    if (input.key_held(Input::Button::Right)) player_.move(1);
    if (input.key_pressed(Input::Button::A)) player_.jump(platform_);
  }

  const bool alive = player_.update(platform_, audio, elapsed);

  for (auto& m : meteors_) {
    if (m.update(player_, platform_, elapsed)) ++score_;
  }

  timer_ -= elapsed;
  if (timer_ < 0) {
    // TODO random decreasing time
    timer_ += 500;
    meteors_.emplace_back();
  }

  return alive;
}

void GameScreen::draw(Graphics& graphics) const {
  space_.draw(graphics);
  player_.draw(graphics);
  platform_.draw(graphics);
  text_.draw(graphics, std::to_string(score_), 256, 0, Text::Alignment::Right);

  for (const auto m : meteors_) {
    m.draw(graphics);
  }
}

Screen* GameScreen::next_screen() const {
  return new TitleScreen;
}
