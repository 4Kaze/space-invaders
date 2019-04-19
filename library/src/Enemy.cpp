#include <string>
#include "Enemy.h"
#include "Entity.h"
#include "Game.h"
#include "Projectile.h"
#include "Particle.h"

Enemy::Enemy(int x, int y, int type, Game* parent):Entity(x, y, parent) {
    switch(type){
        case 1:
        {
            this->height = 3;
            this->width = 5;
            this->health = 50;
            this->speed = 2;
            this->strength = 2;
            projectileType = 3;
            std::string l[3] = {
                    " vVv ",
                    "=x=x=",
                    "V^*^V"
            };
            body = new char*[height];

            for(int i = 0; i < height; i++) {
                body[i] = new char[width];
                for(int j = 0; j < width; j++) {
                    body[i][j] = l[i].at(j);
                }
            }

            color = COLORS::MAGENTA;
            break;
        }

        case 2:
        default:{
            this->height = 3;
            this->width = 5;
            this->health = 30;
            this->speed = 3;
            this->strength = 5;
            projectileType = 1;
            std::string l[3] = {
                    ".V_V.",
                    ":xXx:",
                    "X ^ X"
            };
            body = new char*[height];

            for(int i = 0; i < height; i++) {
                body[i] = new char[width];
                for(int j = 0; j < width; j++) {
                    body[i][j] = l[i].at(j);
                }
            }
            color = COLORS::BLUE;
            break;
        }
        case 3: {
            this->height = 3;
            this->width = 5;
            this->health = 20;
            this->speed = 5;
            this->strength = 10;
            projectileType = 2;
            std::string l[3] = {
                    "\\_ _/",
                    "  I  ",
                    "_/ \\_"
            };
            body = new char*[height];
            for(int i = 0; i < height; i++) {
                body[i] = new char[width];
                for(int j = 0; j < width; j++) {
                    body[i][j] = l[i].at(j);
                }
            }

            color = COLORS::CYAN;
            break;
        }
    }



    backupColor = color;
}

void Enemy::update(unsigned int time) {
  Projectile* p;
  p = parent->getProjectileAt(x, y, x+width, y+height, false);
  if(p != nullptr) {
    takeDamage(p->getDamage());
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
    parent->addEntity(new Projectile(x+width/2, y+height,projectileType,parent));
  }

  if(colorTimer > 0) {
    colorTimer--;
    if(colorTimer == 0) color = backupColor;
  }

}

void Enemy::takeDamage(int amount) {
  health -= amount;
  parent->addEntity(new Particle(x+width/2-3,y+height-2,parent));
  if(health < 1) die();
  else {
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

char** Enemy::getBody(){
    return body;
}
Enemy::~Enemy() {
    for(int i = 0; i < height; i++) {
        delete body[i];
    }
    delete body;
}
