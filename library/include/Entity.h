#pragma once
enum COLORS {
  WHITE = 0,
  RED = 1,
  GREEN = 2,
  YELLOW = 3,
  BLUE = 4,
  MAGENTA = 5,
  CYAN = 6,
  BLACK = 7
};

class Game;

class Entity {
public:
  Entity(int x, int y, Game* parent);
  virtual ~Entity() {};
  virtual void update(unsigned int time) = 0;
  virtual void render();
  void remove();
  int getWidth() const;
  int getHeight() const;
  int getX() const;
  int getY() const;
  void setX(int x);
  void setY(int y);
  bool isToRemove() const;

protected:
  int x, y, width, height;
  virtual char** getBody() = 0;
  int attributes;
  int color = WHITE;
  Game* parent;
  bool toRemove = false;
};
