#include "TestLevel.h"
#include "Bomber.h"
#include "Game.h"
#include "Log.h"
void TestLevel::init(Game *game) {
  this->game = game;
  Bomber* b = new Bomber(0,0,game);
  enemy = b;
  game->addEntity(b);
}

void TestLevel::update(unsigned int time) {
  if (time >= spawnTimer) {
    spawnTimer = 0;
    if(enemy->getHP() > 10) game->addProjectile(enemy->getX()+1, enemy->getY()+1, 0);
    else finished = true;
  }
}

bool TestLevel::isFinished() { return finished; }

TestLevel::~TestLevel() {}
