#include "game_screen.h"

#include "title_screen.h"

GameScreen::GameScreen() : text_("text.png"), score_(0), timer_(3000), spawn_timer_(2500), space_(), rand_() {
  rand_.seed(Util::random_seed());
}

bool GameScreen::update(const Input& input, Audio& audio, unsigned int elapsed) {
  if (!player_.jumping()) {
    player_.stop();
    if (input.key_held(Input::Button::Left)) player_.move(-1);
    if (input.key_held(Input::Button::Right)) player_.move(1);
    if (input.key_pressed(Input::Button::A)) player_.jump(platform_, audio);
  }

  const bool alive = player_.update(platform_, audio, elapsed);

  for (auto& m : meteors_) {
    if (m.update(player_, platform_, audio, elapsed)) {
      ++score_;
      if (score_ % 10 == 0) {
        spawn_timer_ -= 250;
        if (spawn_timer_ < 500) spawn_timer_ = 500;
      }
    }
  }

  platform_.update(elapsed);

  timer_ -= elapsed;
  if (timer_ < 0) {
    std::uniform_int_distribution<int> d(-50, 50);
    timer_ += spawn_timer_ + d(rand_);
    meteors_.emplace_back();
  }

  if (!alive) {
    audio.play_sample("gameover.wav");
    return false;
  }

  return true;
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
