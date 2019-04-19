#pragma once
#include <vector>

class Menu;

struct MenuStar {
  MenuStar(int x, int y);
  void render();
  void update();
  bool toRemove = false;
  int skipped = 0;
  int x, y, color, attr;
};

struct Dash {
  int x, y, life, color;
  bool skipped = false;
  bool toRemove = false;
  Menu* parent;
  void render();
  void update();
  Dash(int x, int y, Menu* parent);
};

class Menu {
public:
  Menu();
  ~Menu();
  void update(unsigned int time);
  void render();
  void init();
  bool getGreenLight();
  static int width, height;

private:
  void removeDash(Dash* d);
  void removeStar(MenuStar* s);
  std::vector<Dash*> dashes;
  std::vector<MenuStar*> stars;
  char upperBody[5][31];
  char lowerBody[5][38];
  bool greenLight = false;
  int x, y;
  int counter = 0;
};
