#include "Game.h"
#include <curses.h>
#include "Projectile.h"
#include "Particle.h"
#include "Enemy.h"
#include "Player.h"
#include "Star.h"
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include "Log.h"
#include <iostream>

int Game::GAME_WIDTH = 0;
int Game::GAME_HEIGHT = 0;
bool Game::running = false;

void Game::init() {
  initscr();
  start_color();
  getmaxyx(stdscr, GAME_HEIGHT, GAME_WIDTH);
  raw();
  keypad(stdscr, true);
  nodelay(stdscr,true);
  noecho();
  curs_set(0);

  int bg = COLOR_BLACK;
  init_pair(COLORS::WHITE, COLOR_WHITE, bg);
  init_pair(COLORS::RED, COLOR_RED, bg);
  init_pair(COLORS::GREEN, COLOR_GREEN, bg);
  init_pair(COLORS::YELLOW, COLOR_YELLOW, bg);
  init_pair(COLORS::BLUE, COLOR_BLUE, bg);
  init_pair(COLORS::MAGENTA, COLOR_MAGENTA, bg);
  init_pair(COLORS::CYAN, COLOR_CYAN, bg);
  init_pair(COLORS::BLACK, COLOR_BLACK, bg);

  srand(time(0));
  generateSky();

  player = new Player(Game::GAME_WIDTH/2 - 3,Game::GAME_HEIGHT-5,100,4,10, this);

  hud.init();

  running = true;
}

Entity* Game::addEntity(Entity* entity) {
  if(dynamic_cast<Projectile*>(entity)) {
    projectiles.push_back(dynamic_cast<Projectile*>(entity));
  } else if(dynamic_cast<Particle*>(entity)) {
    particles.push_back(dynamic_cast<Particle*>(entity));
  } else if(dynamic_cast<Enemy*>(entity)) {
    enemies.push_back(dynamic_cast<Enemy*>(entity));
  }

  return entity;
}

Projectile* Game::getProjectileAt(int x1, int y1, int x2, int y2, bool enemy) {
  for(Projectile* p : projectiles) {
    if(p->isEnemyProjectile() == enemy && p->getY() >= y1 &&  p->getY() <= y2 && p->getX() >= x1 && p->getX() <= x2) return p;
  }
  return nullptr;
}

void Game::update(unsigned int time) {
  controller.update();
  if(Controller::isEscPressed()) running = false;


  for(auto it = projectiles.begin(); it < projectiles.end(); it++) {
    (*it)->update(time);
    if((*it)->isToRemove()) {
      delete (*it);
      projectiles.erase(it);
      it--;
    }
  }
  for(auto it = particles.begin(); it < particles.end(); it++) {
    (*it)->update(time);
    if((*it)->isToRemove()) {
      delete (*it);
      particles.erase(it);
      it--;
    }
  }

  for(auto it = enemies.begin(); it < enemies.end(); it++) {
    (*it)->update(time);
    if((*it)->isToRemove()) {
      delete (*it);
      enemies.erase(it);
      it--;
    }
  }

  if(time > timer) {
    this->gameTime++;
    timer = time+1000;
  }

  if(time > skyTimer) {
    skyTimer = time + 50;
    updateSky();
  }

  if(time > spawnTimer) {
    int level = gameTime > 120 ? 1 : (gameTime > 60 ? 2 : 3);
    spawnTimer = time + rand() % 2000 + 500;
    if(rand() % level == 0) {
      int t = rand() % 100;
      int x = rand() % GAME_WIDTH;
      int y = rand() % 5 - 3;
      Log::f << "Spawning at " << x <<", " << y << ", level is " << level;
      Log::nl();
      if(t > 50) {
        addEntity(new Enemy(x,y,2,this));
      } else if(t > 15) {
        addEntity(new Enemy(x,y,1,this));
      } else {
        addEntity(new Enemy(x,y,3,this));
      }
    }
  }

  player->update(time);
}

void Game::render() {
  for(Star* s : stars) {
    s->render();
  }
  for(Enemy* e : enemies) {
    e->render();
  }

  player->render();

  for(Projectile* p : projectiles) {
    p->render();
  }
  for(Particle* p : particles) {
    p->render();
  }

  hud.render(player->getHP(), gameTime);

  refresh();
  clear();
}

void Game::generateSky() {
  for(int i = 0; i < GAME_HEIGHT; i++) {
    int n = rand() % (GAME_WIDTH / 50);
    while(n-- > 0) {
      int x = rand() % GAME_WIDTH;
      stars.push_back(new Star(x,i,2));
    }
    n = rand() % (GAME_WIDTH / 30);
    while(n-- > 0) {
      int x = rand() % GAME_WIDTH;
      stars.push_back(new Star(x,i,1));
    }
    n = rand() % (GAME_WIDTH / 40);
    while(n-- > 0) {
      int x = rand() % GAME_WIDTH;
      stars.push_back(new Star(x,i,0));
    }
  }

}

void Game::updateSky() {
  for(auto it = stars.begin(); it < stars.end(); it++) {
    (*it)->update(0);
    if((*it)->isToRemove()) {
      delete (*it);
      stars.erase(it);
      it--;
    }
  }

  int n = rand() % (GAME_WIDTH / 50);
  while(n-- > 0) {
    int x = rand() % GAME_WIDTH;
    stars.push_back(new Star(x,0,2));
  }
  if(skipped % 2 == 0) {
    int n = rand() % (GAME_WIDTH / 30);
    while(n-- > 0) {
      int x = rand() % GAME_WIDTH;
      stars.push_back(new Star(x,0,1));
    }
  }
  if(skipped == 3) {
    int n = rand() % (GAME_WIDTH / 40);
    while(n-- > 0) {
      int x = rand() % GAME_WIDTH;
      stars.push_back(new Star(x,0,0));
    }
    skipped = -1;
  }
  skipped++;
}
Game::~Game() {
  for(Enemy* e : enemies) {
    delete e;
  }
  for(Projectile* p : projectiles) {
    delete p;
  }
  for(Particle* p : particles) {
    delete p;
  }
  for(Star* s : stars) {
    delete s;
  }
  delete player;

  endwin();

  std::cout << "Twoj czas: ";
  int minutes = gameTime / 60;
  int seconds = gameTime - (minutes * 60);
  if(minutes < 10) std::cout << "0" << minutes << ":";
  else std::cout << minutes << ":";
  if(seconds < 10) std::cout << "0" << seconds;
  else std::cout << seconds;
  std::cout << std::endl;
}
