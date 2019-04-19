#pragma once
#include <vector>
#include "Controller.h"
#include "HUD.h"
#include "Sky.h"

class Entity;
class Enemy;
class Player;
class Projectile;
class Explosion;
class Level;

class Game {
public:
  ~Game();
  static bool running;
  static int GAME_WIDTH;
  static int GAME_HEIGHT;
  void init();
  void update(unsigned int time);
  void render();
  Entity* addEntity(Entity* entity);
  Projectile* getProjectileAt(int x1, int y1, int x2, int y2, bool enemy);
  void addProjectile(int x, int y, int type);
  void addExplosion(int x, int y);
  void setLevel(Level* level);
  int getEntityCount() const;

private:
  std::vector<Enemy*> enemies;
  std::vector<Projectile*> projectiles;
  std::vector<Explosion*> particles;
  std::vector<Projectile*> projectileTrash;
  std::vector<Explosion*> particleTrash;
  Controller controller;
  Level* currentLevel = nullptr;
  HUD hud;
  Sky sky;
  Player* player;
  double timer = 0;
  int gameTime = 0;
};
