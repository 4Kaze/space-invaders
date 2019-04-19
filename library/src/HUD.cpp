#include "HUD.h"
#include "Game.h"
#include <curses.h>
#include <string>
#include <sstream>

void HUD::init() {
  init_pair(20, COLOR_WHITE, COLOR_RED);
  init_pair(21, COLOR_RED, COLOR_WHITE);
}

void HUD::render(int health, int time) {
  if(health < lastHealth) blinkTimer = 15;
  attron(A_STANDOUT);

  if(blinkTimer > 0) {
    attroff(A_STANDOUT);
    if((blinkTimer / 5) % 2 == 0) {
      attron(COLOR_PAIR(20) | A_BOLD);
    } else {
      attron(COLOR_PAIR(21) | A_BOLD);
    }
  }

  move(Game::GAME_HEIGHT - 1, 0);
  hline(' ', Game::GAME_WIDTH);

  std::stringstream ss;
  ss << "  HP: " << health << "%  ";
  mvaddstr(Game::GAME_HEIGHT - 1, 0, ss.str().c_str());

  ss.str("");
  ss.clear();

  ss << "  TIME: ";
  int minutes = time / 60;
  int seconds = time - (minutes * 60);
  if(minutes < 10) ss << "0" << minutes << ":";
  else ss << minutes << ":";
  if(seconds < 10) ss << "0" << seconds << "  ";
  else ss << seconds << "  ";

  mvaddstr(Game::GAME_HEIGHT - 1, Game::GAME_WIDTH - 15, ss.str().c_str());

  if(blinkTimer > 0) {
    blinkTimer--;
    attroff(COLOR_PAIR(20) | A_BOLD);
    attroff(COLOR_PAIR(21) | A_BOLD);
  } else{
    attroff(A_STANDOUT);
  }

  lastHealth = health;
}
