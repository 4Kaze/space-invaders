#pragma once
#include "Entity.h"

class Game;

class Player: public Entity {
public:
  Player(int x, int y, int health, int speed, int strength, Game* parent);
  ~Player();
  void update(unsigned int time) override;
  int getHP() const;

protected:
  char** getBody() override;
  void takeDamage(int x, int y, int amount);
  void die();

private:
  char** body;
  unsigned int shootTimer = 0;
  int health;
  int speed;
  int strength;
  int deathTimer = 0;
  bool shooting = false;
  int velocity = 0;
  int backupColor;
  int colorTimer;
};
