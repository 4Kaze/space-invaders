#include "Controller.h"
#include "curses.h"

bool Controller::keysPressed[4];

Controller::Controller() {
  for(int i = 0; i < 4; i++) keysPressed[i] = false;
}

void Controller::update() {
  int c = getch();
  for(int i = 0; i < 4; i++) keysPressed[i] = false;
  if(c == ERR) return;

  switch(c) {
    case 'a':
    case 'A':
    keysPressed[0] = true;
    break;
    case 'd':
    case 'D':
    keysPressed[1] = true;
    break;
    case 32:
    keysPressed[2] = true;
    break;
    case 27:
    keysPressed[3] = true;
    break;
  }

}

bool Controller::isLeftPressed() {
  return keysPressed[0];
}

bool Controller::isRightPressed() {
  return keysPressed[1];
}

bool Controller::isFirePressed() {
  return keysPressed[2];
}

bool Controller::isEscPressed() {
  return keysPressed[3];
}
