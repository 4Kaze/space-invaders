#pragma once
#include "Enemy.h"

class Game;

class Striker : public Enemy {
public:
  Striker(int x, int y, Game* parent);
  ~Striker();
  
protected:
  char** getBody() override;
private:
  char** body;
};
