#pragma once

class HUD {
public:
  void init();
  void render(int health, int time);
private:
  int lastHealth = 100;
  int blinkTimer = 0;
};
