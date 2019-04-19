#include "Enemy.h"
#include "Entity.h"
#include "Game.h"
#include "Projectile.h"

Enemy::Enemy(int x, int y, Game* parent):Entity(x, y, parent) {};

void Enemy::update(unsigned int time) {
  Projectile* p;
  p = parent->getProjectileAt(x, y, x+width, y+height, false);
  if(p != nullptr) {
    takeDamage(p->getX(), p->getY(), p->getDamage());
    p->remove();
  }

  if(time > yTimer) {
    if(y < Game::GAME_HEIGHT / 2) y++;
    yTimer = time + speed * 500;
  }

  if(time > xTimer) {
    xVelocity += direction;
    if(xVelocity == direction*speed) {
      xTimer = time + 1000;
    }
  } else {
    if(xVelocity != 0) xVelocity -= direction;
  }

  x += xVelocity;

  if(x < 0) {
    x = 0;
    direction *= -1;
    if(xVelocity != 0) xVelocity *= -1;
  } else if(x > Game::GAME_WIDTH - width/2) {
    x = Game::GAME_WIDTH - width/2;
    direction *= -1;
    if(xVelocity != 0) xVelocity *= -1;
  }

  if(time > shootTimer) {
    shootTimer = time + (1000/strength)*2;
    parent->addProjectile(x+width/2, y+height,projectileType);
  }

  if(colorTimer > 0) {
    colorTimer--;
    if(colorTimer == 0) color = backupColor;
  }

}

void Enemy::takeDamage(int x, int y, int amount) {
  health -= amount;
  parent->addExplosion(x-5,y-2);
  if(health < 1) die();
  else {
    if(backupColor == -1) backupColor = color;
    color = COLORS::RED;
    colorTimer = 15;
  }

}

void Enemy::die() {
  toRemove = true;
}

int Enemy::getProjectileType() const{
    return projectileType;
}

int Enemy::getHP() const{
    return health;
}
