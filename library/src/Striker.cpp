#include "Striker.h"
#include <string>

Striker::Striker(int x, int y, Game* parent) : Enemy(x, y, parent) {
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
}

char** Striker::getBody(){
    return body;
}

Striker::~Striker() {
    for(int i = 0; i < height; i++) {
        delete[] body[i];
    }
    delete[] body;
}
