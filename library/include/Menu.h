#pragma once
#include <vector>

class Menu;

struct MenuStar {
  MenuStar(int x, int y);
  void render();
  void update();
  void recycle(int x, int y);
  bool toRemove = false;
  int skipped = 0;
  int x, y, color, attr;
private:
  void init(int x, int y);
};

struct Dash {
  int x, y, life, color;
  bool skipped = false;
  bool toRemove = false;
  Menu* parent;
  void render();
  void update();
  void recycle(int x, int y);
  Dash(int x, int y, Menu* parent);
private:
  void init(int x, int y);
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
  void addDash(int x, int y);
  void addStar(int x, int y);
  std::vector<Dash*> dashes;
  std::vector<MenuStar*> stars;
  std::vector<Dash*> dashTrash;
  std::vector<MenuStar*> starTrash;
  char upperBody[5][31];
  char lowerBody[5][38];
  bool greenLight = false;
  int x, y;
  int counter = 0;
};
