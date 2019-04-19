#pragma once
#include "Enemy.h"

class Game;

class Bomber : public Enemy {
public:
  Bomber(int x, int y, Game* parent);
  ~Bomber();
protected:
  char** getBody() override;
private:
  char** body;
};
