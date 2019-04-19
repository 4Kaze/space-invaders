#pragma once
#include "Level.h"

class Bomber;

class TestLevel : public Level {
public:
  ~TestLevel();
  void init(Game* game) override;
  void update(unsigned int time) override;
  bool isFinished() override;

private:
  bool finished = false;
  Game* game;
  Bomber* enemy;
  unsigned int spawnTimer = 0;
};
