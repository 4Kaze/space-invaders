#pragma once
#include "Enemy.h"

class Game;

class Fighter : public Enemy {
public:
  Fighter(int x, int y, Game* parent);
  ~Fighter();
protected:
  char** getBody() override;
private:
  char** body;
};
