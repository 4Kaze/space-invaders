#include "Bomber.h"
#include <string>

Bomber::Bomber(int x, int y, Game* parent) : Enemy(x, y, parent) {
  height = 3;
  width = 5;
  health = 50;
  speed = 2;
  strength = 2;
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
}

char** Bomber::getBody(){
    return body;
}

Bomber::~Bomber() {
    for(int i = 0; i < height; i++) {
        delete[] body[i];
    }
    delete[] body;
}
