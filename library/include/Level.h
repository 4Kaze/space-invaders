#pragma once

class Game;

class Level {
public:
  virtual ~Level(){};
  virtual void init(Game* game) = 0;
  virtual void update(unsigned int time) = 0;
  virtual bool isFinished() = 0;
};
