#pragma once
#include <vector>

class Star;

class Sky {
public:
  ~Sky();
  void init();
  void update(unsigned int time);
  void render();
private:
  std::vector<Star*> stars;
  std::vector<Star*> starTrash;
  void addStar(int x, int y, char type);
  int skyTimer = 0;
  int skipped = 0;
};
