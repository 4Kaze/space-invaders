#include <boost/test/unit_test.hpp>
#include "Bomber.h"
#include "Striker.h"
#include "Fighter.h"
#include "Game.h"
#include "Explosion.h"
#include "Projectile.h"
#include "Star.h"
#include "Menu.h"
#include "TestLevel.h"
#include <iostream>
#include "Log.h"

BOOST_AUTO_TEST_SUITE(SpaceInvadersTest)

BOOST_AUTO_TEST_CASE(bomber_initialized_checkPosition) {
    Bomber* e = new Bomber(10,15,nullptr);
    BOOST_CHECK_EQUAL(e->getX(),10);
    BOOST_CHECK_EQUAL(e->getY(),15);
    delete e;
}
BOOST_AUTO_TEST_CASE(striker_initialized_checkPosition) {
    Striker* e = new Striker(10,15,nullptr);
    BOOST_CHECK_EQUAL(e->getX(),10);
    BOOST_CHECK_EQUAL(e->getY(),15);
    delete e;
}
BOOST_AUTO_TEST_CASE(fighter_initialized_checkPosition) {
    Fighter* e = new Fighter(10,15,nullptr);
    BOOST_CHECK_EQUAL(e->getX(),10);
    BOOST_CHECK_EQUAL(e->getY(),15);
    delete e;
}

BOOST_AUTO_TEST_CASE(particle_initialized_checkPosition) {
    Explosion* p = new Explosion(10,15,nullptr);
    BOOST_CHECK_EQUAL(p->getX(),10);
    BOOST_CHECK_EQUAL(p->getY(),15);
    delete p;
}

BOOST_AUTO_TEST_CASE(projectile_initialized_checkPosition) {
    Projectile* e = new Projectile(10,15,1,nullptr);
    BOOST_CHECK_EQUAL(e->getX(),10);
    BOOST_CHECK_EQUAL(e->getY(),15);
    delete e;
}

BOOST_AUTO_TEST_CASE(projectile_initialized_checkNotEnemyStatus) {
    Projectile* e = new Projectile(10,15,0,nullptr);
    BOOST_TEST(!e->isEnemyProjectile());
    delete e;
}

BOOST_AUTO_TEST_CASE(projectile_initialized_checkEnemyStatus) {
    Projectile* e = new Projectile(10,15,2,nullptr);
    BOOST_TEST(e->isEnemyProjectile());
    delete e;
}

BOOST_AUTO_TEST_CASE(bomber_updating_checkPositionInBounds) {
  Game g;
  g.init();
    Bomber* e = new Bomber(10,15,&g);
    g.addEntity(e);
    for(int i = 0 ; i < 100; i++) {
      e->update(i*1000);
      BOOST_TEST(e->getX() >= -e->getWidth()/2);
    }
}

BOOST_AUTO_TEST_CASE(striker_updating_checkPositionInBounds) {
  Game g;
  g.init();
    Striker* e = new Striker(10,15,&g);
    g.addEntity(e);
    for(int i = 0 ; i < 100; i++) {
      e->update(i*1000);
      BOOST_TEST(e->getX() >= -e->getWidth()/2);
      BOOST_TEST(e->getX() <= Game::GAME_WIDTH - e->getWidth()/2);
    }
}

BOOST_AUTO_TEST_CASE(fighter_updating_checkPositionInBounds) {
  Game g;
  g.init();
    Fighter* e = new Fighter(10,15,&g);
    g.addEntity(e);
    for(int i = 0 ; i < 100; i++) {
      e->update(i*1000);
      BOOST_TEST(e->getX() >= -e->getWidth()/2);
      BOOST_TEST(e->getX() <= Game::GAME_WIDTH - e->getWidth()/2);
    }
}

BOOST_AUTO_TEST_CASE(bomber_removed_checkStatus) {
    Bomber* e = new Bomber(10,15,nullptr);
    e->remove();
    BOOST_TEST(e->isToRemove());
    delete e;
}

BOOST_AUTO_TEST_CASE(striker_removed_checkStatus) {
    Striker* e = new Striker(10,15,nullptr);
    e->remove();
    BOOST_TEST(e->isToRemove());
    delete e;
}

BOOST_AUTO_TEST_CASE(fighter_removed_checkStatus) {
    Fighter* e = new Fighter(10,15,nullptr);
    e->remove();
    BOOST_TEST(e->isToRemove());
    delete e;
}

BOOST_AUTO_TEST_CASE(projectile_removed_checkStatus) {
    Projectile* e = new Projectile(10,15,1,nullptr);
    e->remove();
    BOOST_TEST(e->isToRemove());
    delete e;
}

BOOST_AUTO_TEST_CASE(particle_removed_checkStatus) {
    Explosion* e = new Explosion(10,15,nullptr);
    e->remove();
    BOOST_TEST(e->isToRemove());
    delete e;
}

BOOST_AUTO_TEST_CASE(star_removed_checkStatus) {
    Star* e = new Star(10,15,0);
    e->remove();
    BOOST_TEST(e->isToRemove());
    delete e;
}

BOOST_AUTO_TEST_CASE(projectile_updating_isMarkedForRemoval) {
  Game g;
  g.init();
    Projectile* e = new Projectile(10,5,0,&g);
    g.addEntity(e);
    for(int i = 0; i <6; i++) {
      e->update(1000 * i);
    }
    BOOST_TEST(e->isToRemove());
}




BOOST_AUTO_TEST_CASE(striker_collisionWithProjectile_isHPLost) {
    Game g;
    g.init();
    Striker* e = new Striker(10,5,&g);
    Projectile* e2 = new Projectile(11,6,0,&g);
    int health = e->getHP();
    g.addEntity(e);
    g.addEntity(e2);
    e->update(0);

    BOOST_CHECK_EQUAL(e->getHP(), health - e2->getDamage());
}

BOOST_AUTO_TEST_CASE(striker_collisionWithProjectile_isDead) {
    Game g;
    g.init();
    Striker* e = new Striker(10,5,&g);
    Projectile* e2 = new Projectile(11,6,0,&g);
    g.addEntity(e);
    g.addEntity(e2);
    int health = e->getHP();
    int n = health / e2->getDamage();
    n++;
    for(int i = 0; i < n; i++) {
      e->update(0);
    }
    BOOST_TEST(e->isToRemove());
}


    BOOST_AUTO_TEST_CASE(bomber_collisionWithProjectile_isHPLost) {
        Game g;
        g.init();
        Bomber* e = new Bomber(10,5,&g);
        Projectile* e2 = new Projectile(11,6,0,&g);
        int health = e->getHP();
        g.addEntity(e);
        g.addEntity(e2);
        e->update(0);

        BOOST_CHECK_EQUAL(e->getHP(), health - e2->getDamage());
    }

    BOOST_AUTO_TEST_CASE(bomber_collisionWithProjectile_isDead) {
        Game g;
        g.init();
        Bomber* e = new Bomber(10,5,&g);
        Projectile* e2 = new Projectile(11,6,0,&g);
        g.addEntity(e);
        g.addEntity(e2);
        int health = e->getHP();
        int n = health / e2->getDamage();
        n++;
        for(int i = 0; i < n; i++) {
            e->update(0);
        }
        BOOST_TEST(e->isToRemove());
    }

    BOOST_AUTO_TEST_CASE(fighter_collisionWithProjectile_isHPLost) {
        Game g;
        g.init();
        Fighter* e = new Fighter(10,5,&g);
        Projectile* e2 = new Projectile(11,6,0,&g);
        int health = e->getHP();
        g.addEntity(e);
        g.addEntity(e2);
        e->update(0);

        BOOST_CHECK_EQUAL(e->getHP(), health - e2->getDamage());
    }

    BOOST_AUTO_TEST_CASE(fighter_collisionWithProjectile_isDead) {
        Game g;
        g.init();
        Fighter* e = new Fighter(10,5,&g);
        Projectile* e2 = new Projectile(11,6,0,&g);
        g.addEntity(e);
        g.addEntity(e2);
        int health = e->getHP();
        int n = health / e2->getDamage();
        n++;
        for(int i = 0; i < n; i++) {
            e->update(0);
        }
        BOOST_TEST(e->isToRemove());
    }


BOOST_AUTO_TEST_CASE(particle_updating_isMarkedForRemoval) {
    Game g;
    g.init();
    Explosion* e = new Explosion(10,5,&g);
    g.addEntity(e);
    for(int i = 0; i < 6; i++) {
      e->update(1000 * i);
    }
    BOOST_TEST(e->isToRemove());
}

BOOST_AUTO_TEST_CASE(level_initialized_isEntityCountONe) {
    Game g;
    g.init();
    g.setLevel(new TestLevel());
    BOOST_CHECK_EQUAL(g.getEntityCount(), 2);
}

BOOST_AUTO_TEST_CASE(levelInGame_updating_isEnemyRemoved) {
    Game g;
    g.init();
    g.setLevel(new TestLevel());
    for(int i = 0; i < 6; i++) g.update(0);
    BOOST_CHECK_EQUAL(g.getEntityCount(), 6);
}

BOOST_AUTO_TEST_SUITE_END()
