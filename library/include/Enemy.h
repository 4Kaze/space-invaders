#pragma once
#include "Entity.h"

class Game;

class Enemy: public Entity {
public:
    Enemy(int x, int y, int type, Game* parent);
    ~Enemy();
    void update(unsigned int time) override;
    void takeDamage(int amount);
    void die();
    int getHP() const;
    int getProjectileType() const;

protected:
    char** getBody() override;
private:
    int health;
    int speed;
    int strength;
    int projectileType;
    char** body;
    int yTimer = 0;
    int xTimer = 0;
    int shootTimer = 0;
    int colorTimer = 0;
    short direction = 1;
    int xVelocity = 0;
    int backupColor;
};
