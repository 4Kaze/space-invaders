#include "Explosion.h"
#include "Entity.h"
#include <string>

Explosion::Explosion(int x, int y, Game* parent):Entity(x, y, parent) {
  width = 11;
  height = 5;
  color = COLORS::YELLOW;

  std::string f[5][5] = {
    {
      "           ",
      "           ",
      "    @@)    ",
      "           ",
      "           "
    },
    {
      "           ",
      "     @     ",
      "  - @@@    ",
      "     @@ \\  ",
      "           "
    },
    {
      "   \\ |#    ",
      "  -#@# '   ",
      "  ,@@@  ~  ",
      "   ; \"     ",
      "           "
    },
    {
      " `   ^  .  ",
      " '  +    - ",
      ",    .     ",
      "   `   \\   ",
      "           "
    },
    {
      "   `       ",
      ",     .    ",
      "          .",
      "    '      ",
      "'          "
    }

  };

  for(int n = 0; n < 5; n++) {
    frames[n] = new char*[height];
    for(int i = 0; i < height; i++) {
      frames[n][i] = new char[width];
      for(int j = 0; j < width; j++) {
        frames[n][i][j] = f[n][i].at(j);
      }
    }
  }

}

void Explosion::recycle(int x, int y) {
  currentFrame = 0;
  frameTimer = 0;
  toRemove = false;
  this->x = x;
  this->y = y;
}

void Explosion::update(unsigned int time) {
  if(frameTimer == 0) frameTimer = time + 100;
  else if(time > frameTimer) {
    frameTimer = time + 100;
    currentFrame++;
  }

  if(currentFrame > 4) {
    toRemove = true;
    currentFrame = 4;
  }
}

char** Explosion::getBody(){
    return frames[currentFrame];
}

Explosion::~Explosion() {
  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < height; j++) {
      delete[] frames[i][j];
    }
    delete[] frames[i];
  }
}
