#include "Sky.h"
#include "Game.h"
#include "Star.h"
#include <stdlib.h>
#include <time.h>

void Sky::init() {
  srand(time(0));

  for (int i = 0; i < Game::GAME_HEIGHT; i++) {
    int n = rand() % (Game::GAME_WIDTH / 50);
    while (n-- > 0) {
      int x = rand() % Game::GAME_WIDTH;
      stars.push_back(new Star(x, i, 2));
    }
    n = rand() % (Game::GAME_WIDTH / 30);
    while (n-- > 0) {
      int x = rand() % Game::GAME_WIDTH;
      stars.push_back(new Star(x, i, 1));
    }
    n = rand() % (Game::GAME_WIDTH / 40);
    while (n-- > 0) {
      int x = rand() % Game::GAME_WIDTH;
      stars.push_back(new Star(x, i, 0));
    }
  }
}

void Sky::update(unsigned int time) {
  if (time > skyTimer) {
    skyTimer = time + 50;
    for (auto it = stars.begin(); it < stars.end(); it++) {
      (*it)->update(0);
      if ((*it)->isToRemove()) {
        starTrash.push_back(*it);
        stars.erase(it);
        it--;
      }
    }

    int n = rand() % (Game::GAME_WIDTH / 50);
    while (n-- > 0) {
      int x = rand() % Game::GAME_WIDTH;
      addStar(x,0,2);
    }
    if (skipped % 2 == 0) {
      int n = rand() % (Game::GAME_WIDTH / 30);
      while (n-- > 0) {
        int x = rand() % Game::GAME_WIDTH;
        addStar(x,0,1);
      }
    }
    if (skipped == 3) {
      int n = rand() % (Game::GAME_WIDTH / 40);
      while (n-- > 0) {
        int x = rand() % Game::GAME_WIDTH;
        addStar(x,0,0);
      }
      skipped = -1;
    }
    skipped++;
  }
}

void Sky::addStar(int x, int y, char type) {
  if(starTrash.size() > 0) {
    Star* s = starTrash.back();
    s->recycle(x,y,type);
    stars.push_back(s);
    starTrash.pop_back();
  } else {
    stars.push_back(new Star(x,y,type));
  }
}

void Sky::render() {
  for(Star* s : stars) {
    s->render();
  }
}

Sky::~Sky() {
  for(Star* s : stars) {
    delete s;
  }
  for(Star* s : starTrash) {
    delete s;
  }
}
