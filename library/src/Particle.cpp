#include "Particle.h"
#include "Entity.h"
#include <string>

Particle::Particle(int x, int y, Game* parent):Entity(x, y, parent) {
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

void Particle::update(unsigned int time) {
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

char** Particle::getBody(){
    return frames[currentFrame];
}

Particle::~Particle() {
  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < height; j++) {
      delete frames[i][j];
    }
    delete frames[i];
  }
}
