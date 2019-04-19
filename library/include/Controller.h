#pragma once

class Controller {
public:
  Controller();
  void update();
  static bool isLeftPressed();
  static bool isRightPressed();
  static bool isFirePressed();
  static bool isEscPressed();

private:
  static bool keysPressed[4];
};
