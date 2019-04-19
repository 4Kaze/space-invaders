#pragma once
#include "Entity.h"

class Game;

class Star: public Entity {
public:
  Star(int x, int y, int type);
  ~Star();
  void recycle(int x, int y, int type);
  void update(unsigned int time) override;

protected:
  char** getBody() override;
private:
  char** body;
  int skipped = 0;
  int type;
};
