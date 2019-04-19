#pragma once
#include "Level.h"

class Game;

class RandomLevel : public Level {
public:
  ~RandomLevel();
  void init(Game* game) override;
  void update(unsigned int time) override;
  bool isFinished() override;

private:
  bool finished = false;
  Game* game;
  unsigned int spawnTimer = 0;
};
