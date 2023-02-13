#ifndef CB_HEADER
#define CB_HEADER

#include "util.h"

/* Each planet = {scale, orbitSpeed, rotationSpeed, orbitRadius, tilt, orbitalTilt, elipticalModifier} */
typedef float planetInfo[7];

// Index references:
GLint   s = 0,   // scale
		oS = 1,  // orbit speed
		rS = 2,  // rotation speed
		oR = 3,  // orbit radius (planet)
		pl = 3,  // planet of orbit (moon)
		t = 4,   // rotation tilt
		oT = 5;  // orbital tilt
		eM = 6;  // eliptical modifier

// An array of planets, final three have eliptical orbits
static planetInfo planets[8] = { {0.2, 0.006, 0.08, 2.0, 0.02, 0.0, 0.0},	{0.4, 0.01, 0.2, 5.0, 0.5, 1.0, 0.0},
									{0.8, 0.002, 0.15, 7.0, 1.0, 0.0, 0.0},	 {0.6, 0.007, 0.2, 7.5, 0.0, -0.3, 0.0},
									 {0.5, 0.012, 0.1, 9.0, 0.0, 0.5, 0.0},	  {0.9, 0.01, 0.1, 11.0, 3.0, 0.0, 1.4},
									  {0.35, 0.015, 0.6, 13.0, 0.0, 0.1, 2},	   {1.0, 0.016, 0.02, 14.0, 0.0, -0.4, 1.6} };

// planet colours array
static GLfloat planetColours[8][3] = { {1.0, 0.6, 0.8}, {0.1, 0.7, 0.2}, {1.0, 0.0, 0.3},
										{0.0, 0.6, 0.8}, {1.0, 0.6, 0.8} , {1.0, 0.0, 0.8},
										 {0.3, 0.6, 0.4}, {0.2, 0.0, 0.75} };

// Orbit and rotations of planets, indeces correspond to planets array
static GLfloat orbitThetaP[8] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
static GLfloat rotationThetaP[8] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

// Each moon = {scale, orbitSpeed, rotationSpeed, planet that it orbits}
typedef float moonInfo[4];

// An array of moons
static moonInfo moons[4] = { {0.15, 0.05, 0.02, 1.0}, {0.2, 0.1, 0.02, 2.0},
											{0.1, 0.05, 0.02, 3.0}, {0.1, 0.05, 0.02, 4.0} };

// Moon orbits and rotations, indeces correspond to moons array
static GLfloat orbitThetaM[5] = { 0.0, 0.0, 0.0, 0.0, 0.0 };
static GLfloat rotationThetaM[5] = { 0.0, 0.0, 0.0, 0.0, 0.0 };

// stars have an x, y, and z coordinate
typedef int star[3];

// there are 2000 stars
star stars[2000];

// blackhole variables
GLfloat bScale[3] = { 1.0, 1.0, 1.0 };
GLfloat bPos[3] = { 0.0, 0.0, 0.0 };
GLfloat pos[20];
bool bRingPosInit = false;

// function defs
void planet();
void initbRingPos(float[]);
void drawCorona(float, float, float);
void drawBlackHole();
void idleBlackhole(int);
void drawPlanet(int);
void idleRotatePlanet(float[], int);
void drawMoon(int);
void idleRotateMoon(float[], int);
void drawStars();
void initStars(star[]);
void drawOrbit(int);

// so star coordinates are only determined once
bool starsInit = false;

// toggle feature variables
bool starsOn = false;
bool corona = false;
bool rings = false;
bool blackhole = false;
bool funkyRings = false;

#endif
