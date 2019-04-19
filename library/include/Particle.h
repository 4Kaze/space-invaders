#pragma once
#include "Entity.h"

class Game;

class Particle: public Entity {
public:
  Particle(int x, int y, Game* parent);
  ~Particle();
  void update(unsigned int time) override;
protected:
  char** getBody()override;
private:
  char** frames[5];
  int currentFrame = 0;
  int frameTimer = 0;
  
};
