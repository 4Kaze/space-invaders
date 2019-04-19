## SPACE INVADERS
This is a simple Space Invaders game made using ncurses.
To install ncurses on Ubuntu:
```
sudo apt install libncurses5-dev libncursesw5-dev
```
Then just create makefiles with cmake and compile the program with make.
The runnable binary is bin/SpaceInvaders

Also, boost is used for unit testing. If you don't have boost installed, just delete the unit test section from the cmake file.
