#pragma once
#include "Entity.h"

class Game;

class Enemy: public Entity {
public:
    virtual ~Enemy() {};
    virtual void update(unsigned int time) override;
    int getHP() const;
    int getProjectileType() const;

protected:
    Enemy(int x, int y, Game* parent);
    virtual char** getBody() = 0;
    void takeDamage(int x, int y, int amount);
    void die();
    int health;
    int speed;
    int strength;
    int projectileType;
private:
    int backupColor = -1;
    int yTimer = 0;
    int xTimer = 0;
    int shootTimer = 0;
    int colorTimer = 0;
    short direction = 1;
    int xVelocity = 0;
};
