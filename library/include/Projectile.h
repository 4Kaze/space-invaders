#pragma once
#include "Entity.h"

class Game;

class Projectile: public Entity {
public:
  Projectile(int x, int y, int type, Game* parent);
  ~Projectile();
  void update(unsigned int time) override;
  float getDamage() const;
  bool isEnemyProjectile();

protected:
  char** getBody() override;
private:
  char** body;
  bool enemy;
  float damage;
  int type;
  unsigned int counter = 0;
};
