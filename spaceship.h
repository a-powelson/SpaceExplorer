#ifndef SHIP_HEADER
#define SHIP_HEADER

#include "util.h"

//enterprise
float vertices[1201][3];
GLint faces[1989][3];
int enterpriseInit = 0;

// feature toggles
bool shipOn = false;
bool laserOn = false;
bool shieldOn = false;

// for other ship
float shipX = 40;
// laser
float laserZ = 0;

// forward defs
void drawShield();
void drawLaser();
void drawEnterprise();
void initEnterprise();
void drawOtherShip();
void dialogue();

#endif
