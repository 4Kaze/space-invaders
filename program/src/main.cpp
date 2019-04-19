#include <iostream>
#include <chrono>
#include <thread>
#include "Game.h"
#include "Player.h"
#include "Menu.h"
#include "Log.h"

int main() {
  Log::init();
  {
    Menu m;
    m.init();

    std::chrono::time_point<std::chrono::steady_clock> nextTime;
    std::chrono::time_point<std::chrono::steady_clock> prevTime = std::chrono::steady_clock::now();;
    unsigned int time = 0;

    while(!m.getGreenLight()) {
      time += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - prevTime).count();
      m.update(time);
      m.render();
      prevTime = std::chrono::steady_clock::now();
      nextTime = prevTime + std::chrono::milliseconds(33);
      std::this_thread::sleep_until(nextTime);
    }
  }

  {
    Game game;
    game.init();

    std::chrono::time_point<std::chrono::steady_clock> nextTime;
    std::chrono::time_point<std::chrono::steady_clock> prevTime = std::chrono::steady_clock::now();;
    unsigned int time = 0;

    while(game.running) {
      time += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - prevTime).count();
      game.update(time);
      game.render();
      prevTime = std::chrono::steady_clock::now();
      nextTime = prevTime + std::chrono::milliseconds(33);
      std::this_thread::sleep_until(nextTime);
    }

  }

  return 0;
}
