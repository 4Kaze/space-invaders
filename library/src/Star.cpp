#include <curses.h>
#include "Star.h"
#include "Log.h"
#include <iostream>
#include "Game.h"

Star::Star(int x, int y, char type): Entity(x, y, nullptr) {
  this->height = 1;
  this->width = 1;
  if(type == 0) attributes = A_DIM;
  if(type == 1) attributes = 0;
  this->type = type;
  body = new char*[1];
  body[0] = new char[1] {'*'};
};

char** Star::getBody() {
  return body;
}

void Star::update(unsigned int time) {
  if(type == 0) {
    if(skipped == 0) {
      y++;
      skipped = 4;
    } else {
      skipped--;
    }
  }  else if(type == 1) {
    if(skipped == 0) {
      y++;
      skipped = 1;
    } else {
      skipped --;
    }
  } else {
    y++;
  }


  if(y > Game::GAME_HEIGHT) toRemove = true;
}

Star::~Star() {
  delete body[0];
  delete body;
}
