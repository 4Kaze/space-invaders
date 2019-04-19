#include "Game.h"
#include <curses.h>
#include "Projectile.h"
#include "Explosion.h"
#include "Enemy.h"
#include "Player.h"
#include "Star.h"
#include <algorithm>
#include "Log.h"
#include <iostream>
#include "Level.h"

int Game::GAME_WIDTH = 0;
int Game::GAME_HEIGHT = 0;
bool Game::running = false;

void Game::init() {
  initscr();
  if(!has_colors) {
    std::cout << "This terminal doesn't support colors!" << std::endl;
    exit(-1);
  }
  start_color();
  getmaxyx(stdscr, GAME_HEIGHT, GAME_WIDTH);
  if(GAME_HEIGHT < 30 || GAME_WIDTH < 100) {
    std::cout << "The terminal window is too small. The minimum size is 30x100." << std::endl;
    exit(-1);
  }
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

  player = new Player(Game::GAME_WIDTH/2 - 3,Game::GAME_HEIGHT-5,100,4,10, this);

  hud.init();
  sky.init();

  running = true;

  Log::get() << "Game initialized...";
  Log::get().nl();
}

Entity* Game::addEntity(Entity* entity) {
  if(dynamic_cast<Enemy*>(entity)) {
    enemies.push_back(dynamic_cast<Enemy*>(entity));
  } else if(dynamic_cast<Projectile*>(entity)) {
    projectiles.push_back(dynamic_cast<Projectile*>(entity));
  } else if(dynamic_cast<Explosion*>(entity)) {
    particles.push_back(dynamic_cast<Explosion*>(entity));
  }

  return entity;
}

void Game::addProjectile(int x, int y, int type) {
  if(projectileTrash.size() > 0) {
    Projectile* e = projectileTrash.back();
    e->recycle(x,y,type);
    projectiles.push_back(e);
    projectileTrash.pop_back();
  } else {
    projectiles.push_back(new Projectile(x,y,type,this));
  }
}
void Game::addExplosion(int x, int y) {
  if(particleTrash.size() > 0) {
    Explosion* e = particleTrash.back();
    e->recycle(x,y);
    particles.push_back(e);
    particleTrash.pop_back();
  } else {
    particles.push_back(new Explosion(x,y,this));
  }
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
      projectileTrash.push_back(*it);
      projectiles.erase(it);
      it--;
    }
  }
  for(auto it = particles.begin(); it < particles.end(); it++) {
    (*it)->update(time);
    if((*it)->isToRemove()) {
      particleTrash.push_back(*it);
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

  currentLevel->update(time);

  sky.update(time);

  player->update(time);

}

void Game::render() {
  sky.render();

  for(Enemy* e : enemies) {
    e->render();
  }

  player->render();

  for(Projectile* p : projectiles) {
    p->render();
  }
  for(Explosion* p : particles) {
    p->render();
  }

  hud.render(player->getHP(), gameTime);

  refresh();
  clear();
}

void Game::setLevel(Level* level) {
  delete currentLevel;
  currentLevel = level;
  level->init(this);
}

int Game::getEntityCount() const {
  return enemies.size() + projectiles.size() + particles.size() + 1;
}

Game::~Game() {
  for(Enemy* e : enemies) {
    delete e;
  }
  for(Projectile* p : projectiles) {
    delete p;
  }
  for(Projectile* p : projectileTrash) {
    delete p;
  }
  for(Explosion* p : particles) {
    delete p;
  }
  for(Explosion* p : particleTrash) {
    delete p;
  }
  delete player;
  delete currentLevel;

  endwin();

  std::cout << "Your time: ";
  int minutes = gameTime / 60;
  int seconds = gameTime - (minutes * 60);
  if(minutes < 10) std::cout << "0" << minutes << ":";
  else std::cout << minutes << ":";
  if(seconds < 10) std::cout << "0" << seconds;
  else std::cout << seconds;
  std::cout << std::endl;
}
