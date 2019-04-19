#include <curses.h>
#include "Entity.h"
#include "Game.h"

Entity::Entity(int x, int y, Game* parent) {
  this->x = x;
  this->y = y;
  this->parent = parent;
  color = COLORS::WHITE;
  attributes = A_BOLD;
}

void Entity::render() {
  attron(COLOR_PAIR(color) | attributes);
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      if(x+j > 0 && x+j < Game::GAME_WIDTH && y+i > 0 && y+i < Game::GAME_HEIGHT) if(getBody()[i][j] != ' ') mvaddch(y+i,x+j,getBody()[i][j]);
    }
  }

  attroff(COLOR_PAIR(color) | attributes);
}

int Entity::getX() const {
  return x;
}

int Entity::getY() const {
  return y;
}

int Entity::getWidth() const {
  return width;
}

int Entity::getHeight() const {
  return height;
}
bool Entity::isToRemove() const {
  return toRemove;
}
void Entity::remove() {
  toRemove = true;
}

void Entity::setX(int x) {
  this->x = x;
}

void Entity::setY(int y) {
  this->y = y;
}
