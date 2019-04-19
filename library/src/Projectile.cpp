#include "Projectile.h"
#include "Entity.h"
#include "Game.h"
#include "Log.h"

//type 0 - shot by player
//different type - shot by an enemy
Projectile::Projectile(int x, int y, int type, Game* parent):Entity(x, y, parent) {
  width = 1;
  height = 1;

  if(type == 0) {
    enemy = false;
    body = new char*[1];
    body[0] = new char[1] {'q'};
    damage = 10;
    color = COLORS::YELLOW;
  } else if(type == 1){
    enemy = true;
    body = new char*[1];
    body[0] = new char[1] {'b'};
    damage = 15;
    color = COLORS::YELLOW;
  } else if(type == 2) {
    enemy = true;
    body = new char*[1];
    body[0] = new char[1] {'!'};
    color = COLORS::MAGENTA;
    damage = 10;
  } else if(type == 3) {
    enemy = true;
    body = new char*[1];
    body[0] = new char[1] {'@'};
    damage = 30;
    color = COLORS::CYAN;
  }

  this->type = type;

}

void Projectile::update(unsigned int time) {
  if(enemy) {
    if(type == 3 && counter%2 == 0) y++;
    else if(type == 1 || type == 2) y++;
  } else y--;

  if(y < 0 || y > Game::GAME_HEIGHT) toRemove = true;

}

float Projectile::getDamage() const {
  return damage;
}

char** Projectile::getBody(){
    return body;
}

bool Projectile::isEnemyProjectile() {
  return enemy;
}
Projectile::~Projectile() {
    delete body[0];
    delete body;
}
