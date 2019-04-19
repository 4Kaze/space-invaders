#pragma once
#include <vector>
#include "Controller.h"
#include "HUD.h"

class Entity;
class Enemy;
class Player;
class Projectile;
class Particle;
class Star;

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

private:
  std::vector<Enemy*> enemies;
  std::vector<Projectile*> projectiles;
  std::vector<Particle*> particles;
  std::vector<Star*> stars;
  Controller controller;
  HUD hud;
  Player* player;
  double timer = 0;
  double skyTimer = 0;
  int spawnTimer = 0;
  int gameTime = 0;
  int skipped = 0;

  void generateSky();
  void updateSky();

};
