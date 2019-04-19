#include "Player.h"
#include <string>
#include "ncurses.h"
#include "Controller.h"
#include "Game.h"
#include "Projectile.h"

Player::Player(int x, int y, int health, int speed, int strength, Game* parent): Entity(x, y, parent), health(health), speed(speed), strength(strength) {
  this->height = 2;
  this->width = 7;
  std::string l[2] = {
    ",  ^  ,",
    "[==U==]"
  };
  body = new char*[height];

  for(int i = 0; i < height; i++) {
    body[i] = new char[width];
    for(int j = 0; j < width; j++) {
      body[i][j] = l[i].at(j);
    }
  }

  color = COLORS::GREEN;
  backupColor = color;
}

void Player::update(unsigned int time) {
  if(deathTimer > 0) {
    deathTimer --;
    if(deathTimer == 0) {
      Game::running = false;
    } else if(deathTimer % 10 == 0) {
      parent->addExplosion(x-1,y-1);
    }
    health = 0;
    color = COLORS::RED;
    return;
  }

  Projectile* p;
  p = parent->getProjectileAt(x, y, x+width, y+height, true);
  if(p != nullptr) {
    takeDamage(p->getX(), p->getY(), p->getDamage());
    p->remove();
  }

  if(Controller::isLeftPressed()) {
    velocity = -speed;
  } else if(Controller::isRightPressed()) {
    velocity = speed;
  } else if(velocity != 0){
    if(velocity < 0) velocity++;
    else velocity--;
  }

  if(Controller::isFirePressed()) shooting = !shooting;

  x += velocity;
  if(x < -width/2 - 1) x = -width/2;
  if(x > Game::GAME_WIDTH - width/2 + 1) x =  Game::GAME_WIDTH - width/2;

  if(time > shootTimer && shooting) {
  parent->addProjectile(x + width/2,y-1,0);
  shootTimer = time + (1000/strength)*2;
  }

  if(colorTimer > 0) {
    colorTimer--;
    if(colorTimer == 0) color = backupColor;
  }

}

char** Player::getBody() {
  return body;
}

void Player::takeDamage(int x, int y, int amount) {
  health -= amount;
  parent->addExplosion(x-5,y-2);
  if(health < 1) die();
  else {
    colorTimer = 10;
    color = COLORS::RED;
  }
}

void Player::die() {
  deathTimer = 100;
}

int Player::getHP() const {
  return health;
}
Player::~Player() {
  for(int i = 0; i < height; i++) {
    delete[] body[i];
  }
  delete[] body;
}
