#ifndef UTIL_HEAD
#define UTIL_HEAD

/* enterprise.txt provided by
	Dr. Stephen Brooks, Dalhousie 2020 */

#include <freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "celestialBodies.h"
#include "spaceship.h"

#pragma warning(disable : 4996)

void toggle(bool*, char, char);
void keys(unsigned char, int, int);
void specialKeys(int, int, int);
void specialKeysUp(int, int, int);
void cameraReposition(int, int);
void initializeGL();
void display();
void idle();

// Camera position
GLfloat cameraPos[3] = { 0.0, 5.0, 27.0 };

// looking at
GLfloat lookingAt[3] = { 0, 0, 0 };

// keysPressed array
GLint keysPressed[6] = { 0, 0, 0, 0, 0, 0 };

#endif