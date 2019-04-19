#include "Menu.h"
#include <string>
#include <curses.h>
#include <algorithm>
#include "Log.h"
#include <stdlib.h>
#include <time.h>
#include <stdexcept>

int Menu::width = 0;
int Menu::height = 0;

Menu::Menu() {
    std::string b1[5] = {
"      ### ###   ##   ### ####",
"     #    #  # #  # #    #",
"      ##  ###  #### #    ###",
"        # #    #  # #    #",
"     ###  #    #  #  ### ####"};
  std::string b2[5] = {
"#  ##  # #  #  ##  ###  #### ###   ###",
"#  # # # #  # #  # #  # #    #  # #",
"#  # # # #  # #### #  # ###  ###   ##",
"#  # # # #  # #  # #  # #    #  #    #",
"#  #  ##  ##  #  # ###  #### #  # ###"};

  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 31; j++) {
      upperBody[i][j] = b1[i].length() > j ? b1[i].at(j) : ' ';
    }
  }
  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 38; j++) {
      lowerBody[i][j] =b2[i].length() > j ? b2[i].at(j) : ' ';;
    }
  }

  srand(time(0));
}

void Menu::init() {
  initscr();
  if(!has_colors) {
    throw std::logic_error("Ten terminal nie obsługuje kolorów!");
  }
  start_color();
  getmaxyx(stdscr, height, width);
  if(height < 30 || width < 100) {
    throw std::logic_error("Okno terminala jest za małe. Minimalna wielkość to 30x100.");
  }
  raw();
  keypad(stdscr, true);
  nodelay(stdscr,true);
  noecho();
  curs_set(0);
  init_pair(30, COLOR_WHITE, COLOR_WHITE);
  init_pair(1, COLOR_RED, COLOR_RED);
  init_pair(2, COLOR_GREEN, COLOR_GREEN);
  init_pair(3, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(4, COLOR_BLUE, COLOR_BLUE);
  init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(0, COLOR_CYAN, COLOR_CYAN);
  init_pair(6, COLOR_WHITE, COLOR_BLACK);
  init_pair(7, COLOR_RED, COLOR_BLACK);
  init_pair(8, COLOR_GREEN, COLOR_BLACK);
  init_pair(9, COLOR_YELLOW, COLOR_BLACK);
  init_pair(10, COLOR_BLUE, COLOR_BLACK);
  init_pair(11, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(12, COLOR_CYAN, COLOR_BLACK);
  x = width/2 - 19;
  y = height/2 - 10;

  for(int i = 0; i < height; i++) {
    int n = rand() % (width / 20);
    while(n-- > 0) {
      int x = rand() % width;
      stars.push_back(new MenuStar(x,i));
    }
  }

}
void Menu::render() {
  for(MenuStar* s : stars) {
    s->render();
  }
  for(Dash* d : dashes) {
    d->render();
  }

  attron(COLOR_PAIR(30));
  int yoffset = 6;
  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 31; j++) {
      if(upperBody[i][j] != ' ') mvaddch(y+i,width/2 - 17 +j,upperBody[i][j]);
    }
  }

  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 38; j++) {
      if(lowerBody[i][j] != ' ') mvaddch(y+yoffset+i,width/2 - 19+j,lowerBody[i][j]);
    }
  }

  attroff(COLOR_PAIR(30));
  attron(A_BOLD);
  mvaddstr(y+yoffset+10, width/2 - 14, "<< press [space] to start >>");
  int x = 4;
  mvaddstr(height-6, x, "Controls:");
  mvaddstr(height-5, x, "[A] to go left");
  mvaddstr(height-4, x, "[D] to go right");
  mvaddstr(height-3, x, "[SPACE] to toggle shooting");
  mvaddstr(height-2, x, "[ESC] to quit");
  attroff(A_BOLD);

  refresh();
  clear();
}

void Menu::update(unsigned int time) {
  chtype c = getch();
  if(c == 27) {
    endwin();
    exit(0);
  } else if(c == 32) {
    greenLight = true;
  }

    for(int i = 0; i < 31; i++) {
      if(upperBody[4][i] != ' ') if(rand() % 3 == 0) addDash(width/2 - 17 + i,y+5);
    }
    for(int i = 0; i < 38; i++) {
      if(lowerBody[4][i] != ' ') if(rand() % 3 == 0) addDash(width/2 - 19+i, y+11);
    }

  for(auto it = dashes.begin(); it < dashes.end(); it++) {
    (*it)->update();
    if((*it)->toRemove) {
      dashTrash.push_back(*it);
      dashes.erase(it);
      it--;
    }
  }

  for(auto it = stars.begin(); it < stars.end(); it++) {
    (*it)->update();
    if((*it)->toRemove) {
      starTrash.push_back(*it);
      stars.erase(it);
      it--;
    }
  }

  if(counter == 0) {
      int n = rand() % (width / 20);
      while(n-- > 0) {
        int x = rand() % width;
        addStar(x,0);
      }
    counter = 1;
  } else counter--;
}

bool Menu::getGreenLight() {
  return greenLight;
}

void Menu::addDash(int x, int y) {
  if(dashTrash.size() > 0) {
    Dash* e = dashTrash.back();
    e->recycle(x,y);
    dashes.push_back(e);
    dashTrash.pop_back();
  } else {
    dashes.push_back(new Dash(x,y, this));
  }
}

void Menu::addStar(int x, int y) {
  if(starTrash.size() > 0) {
    MenuStar* e = starTrash.back();
    e->recycle(x,y);
    stars.push_back(e);
    starTrash.pop_back();
  } else {
    stars.push_back(new MenuStar(x,y));
  }
}

Menu::~Menu() {
  for(Dash* d : dashes) {
    delete d;
  }
  for(MenuStar* s : stars) {
    delete s;
  }
  for(Dash* d : dashTrash) {
    delete d;
  }
  for(MenuStar* s : starTrash) {
    delete s;
  }
  endwin();
}

Dash::Dash(int x, int y, Menu* parent) {
  init(x, y);
  this->parent = parent;
}

void Dash::recycle(int x, int y) {
  init(x, y);
  skipped = false;
  toRemove = false;
}

void Dash::init(int x, int y) {
  this->x = x;
  this->y = y;
  life = rand() % (Menu::height / 3) + (Menu::height / 7);
  color = rand() % 6;
}

void Dash::render() {
  attron(COLOR_PAIR(color));
  mvaddch(y,x,' ');
  attroff(COLOR_PAIR(color));
}

void Dash::update() {
  if(skipped) {
    skipped = false;
    y++;
    life--;
    if(life < 0) {
      toRemove = true;
    }
  } else skipped = true;
}

MenuStar::MenuStar(int x, int y) {
  init(x, y);
}

void MenuStar::recycle(int x, int y) {
  init(x, y);
  skipped = 0;
  toRemove = false;
}

void MenuStar::init(int x, int y) {
  this->x = x;
  this->y = y;
  this-> color = rand() % 7 + 6;
  int a = rand() %3;
  if(a == 0) attr = 0;
  else if(a == 1) attr = A_BOLD;
  else attr = A_DIM;
}

void MenuStar::render() {
  attron(COLOR_PAIR(color) | attr);
  mvaddch(y,x,'+');
  attroff(COLOR_PAIR(color) | attr);
}

void MenuStar::update() {
  if(attr == A_BOLD) y++;
  else if(attr == 0) {
    if(skipped == 0) {
      y++;
      skipped = 1;
    } else {
      skipped --;
    }
  } else {
    if(skipped == 0) {
      y++;
      skipped = 4;
    } else {
      skipped--;
    }
  }

  if(y > Menu::height) toRemove = true;
}
