#include "RandomLevel.h"
#include "Bomber.h"
#include "Striker.h"
#include "Fighter.h"
#include "Game.h"
#include <stdlib.h>
#include "Log.h"

void RandomLevel::init(Game *game) { this->game = game; }

void RandomLevel::update(unsigned int time) {
  if (time > spawnTimer) {
    spawnTimer = time + rand() % 5000 + 500;
    int t = rand() % 100;
    int x = rand() % Game::GAME_WIDTH;
    Enemy *e;
    if (t > 50) {
      e = new Striker(x, 0, game);
    } else if (t > 20) {
      e = new Bomber(x, 0, game);
    } else {
      e = new Fighter(x, 0, game);
    }


    e->setY(1 - e->getHeight());

    game->addEntity(e);
  }

}

bool RandomLevel::isFinished() { return finished; }

RandomLevel::~RandomLevel() {}
