#include "Projectile.h"
#include "Entity.h"
#include "Game.h"

int Projectile::count = 0;

//type 0 - wystrzelony przez gracza
//type inny - wystrzelony przez wroga
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

  count++;

}

void Projectile::recycle(int x, int y, int type) {
  if(this->type != type) {
    if(type == 0) {
      enemy = false;
      body[0][0] = 'q';
      damage = 10;
      color = COLORS::YELLOW;
    } else if(type == 1){
      enemy = true;
      body[0][0] = 'b';
      damage = 15;
      color = COLORS::YELLOW;
    } else if(type == 2) {
      enemy = true;
      body[0][0] = '!';
      color = COLORS::MAGENTA;
      damage = 10;
    } else if(type == 3) {
      enemy = true;
      body[0][0] = '@';
      damage = 30;
      color = COLORS::CYAN;
    }

    this->type = type;
  }

  this->x = x;
  this->y = y;
  toRemove = false;
  counter = 0;
}

void Projectile::update(unsigned int time) {
  if(enemy) {
    if(type == 3 && counter%2 == 0) y++;
    else if(type == 1 || type == 2) y++;
  } else y--;

  if(y < 0 || y > Game::GAME_HEIGHT) toRemove = true;

  counter++;
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
    delete[] body[0];
    delete[] body;
}
