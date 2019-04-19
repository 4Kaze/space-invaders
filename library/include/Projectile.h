#pragma once
#include "Entity.h"

class Game;

class Projectile: public Entity {
public:
  Projectile(int x, int y, int type, Game* parent);
  ~Projectile();
  void recycle(int x, int y, int type);
  void update(unsigned int time) override;
  float getDamage() const;
  bool isEnemyProjectile();
  static int count;

protected:
  char** getBody() override;
private:
  char** body;
  bool enemy;
  float damage;
  int type;
  unsigned int counter = 0;
};
