#include "Fighter.h"
#include <string>

Fighter::Fighter(int x, int y, Game* parent) : Enemy(x, y, parent) {
  height = 3;
  width = 5;
  health = 20;
  speed = 5;
  strength = 10;
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
}

char** Fighter::getBody(){
    return body;
}

Fighter::~Fighter() {
    for(int i = 0; i < height; i++) {
        delete[] body[i];
    }
    delete[] body;
}
