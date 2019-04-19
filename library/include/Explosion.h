#pragma once
#include "Entity.h"

class Game;

class Explosion: public Entity {
public:
  Explosion(int x, int y, Game* parent);
  ~Explosion();
  void recycle(int x, int y);
  void update(unsigned int time) override;

protected:
  char** getBody()override;
private:
  char** frames[5];
  int currentFrame = 0;
  int frameTimer = 0;

};
