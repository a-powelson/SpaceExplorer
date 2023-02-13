/* 
   - CSCI 3161 Assignment 2
   -Ava Powelson, B00802243 
    Created: October, 2020

*/

// While the rings have been modified to elipses, the coresponding planets do not have a
// proper eliptical orbit

#include "util.h"

/* Following method from E.Angel,
	Interactive Computer Graphics
	A Top - Down Approach with OpenGL, Third Edition
	Addison - Wesley Longman, 2003 */

// Draws a spherical planet
void planet() {
	double x, y, z, thet, phi;
	double c;
	x = y = 0;
	z = 1;

	glBegin(GL_TRIANGLE_FAN);

	glVertex3d(x, y, z);
	c = 3.14159 / 180.0;
	z = sin(c * 80.0);

	for (thet = -180.0; thet <= 180.0; thet += 20.0)
	{
		x = sin(c * thet) * cos(c * 80.0);
		y = cos(c * thet) * cos(c * 80.0);
		glVertex3d(x, y, z);
	}

	glEnd();

	x = y = 0;
	z = -1;

	glBegin(GL_TRIANGLE_FAN);

	glVertex3d(x, y, z);
	z = -sin(c * 80.0);

	for (thet = -180.0; thet <= 180.0; thet += 20.0)
	{
		x = sin(c * thet) * cos(c * 80.0);
		y = cos(c * thet) * cos(c * 80.0);
		glVertex3d(x, y, z);
	}

	glEnd();

	for (phi = -80.0; phi <= 80.0; phi += 20.0)
	{
		glBegin(GL_QUAD_STRIP);

		for (thet = -180.0; thet <= 180.0; thet += 20.0)
		{
			x = sin(c * thet) * cos(c * phi);
			y = cos(c * thet) * cos(c * phi);
			z = sin(c * phi);
			glVertex3d(x, y, z);

			x = sin(c * thet) * cos(c * (phi + 20.0));
			y = cos(c * thet) * cos(c * (phi + 20.0));
			z = sin(c * (phi + 20.0));
			glVertex3d(x, y, z);
		}

		glEnd();
	}
}

/************************************************
Function: drawShield
Description: draw a shield around the enterprise
************************************************/
void drawShield() {
	glPushMatrix();
		glColor4f(0.4, 0.7, 1.0, 0.5);
		glTranslatef(cameraPos[0] - 1.2, cameraPos[1] - 2.25, cameraPos[2] - 5.25);
		glScalef(1.0, 1.0, 2.0);
		planet();
	glPopMatrix();

	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor4f(0.1, 0.3, 1.0, 0.7);
		glTranslatef(cameraPos[0] - 1.2, cameraPos[1] - 2.25, cameraPos[2] - 5.25);
		glScalef(1.025, 1.025, 2.025);
		planet();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPopMatrix();
	
}

/****************************
Function: drawLaser
Description: Draws a laser shooting from the enterprise
*****************************/
void drawLaser() {
	glLineWidth(5);

	glBegin(GL_LINES);
		glColor4f(0.0, 1.0, 0.0, 0.5);
		glVertex3f(cameraPos[0] - 1.2, cameraPos[1] - 2.5, cameraPos[2] - 5 - laserZ);
		glColor4f(0.0, 1.0, 0.0, 1.0);
		glVertex3f(cameraPos[0] - 1.2, cameraPos[1] - 2.5, cameraPos[2] - 8 - laserZ);
	glEnd();

	glLineWidth(1.0);
}

/*********************************************************************************
Function: drawEnterprise
Description: Draw the ship the enterprise in the bottom left of the view
				- Ship moves with camera and tilts with the direction it is moving
*********************************************************************************/
void drawEnterprise() {
	glPushMatrix();
		glTranslatef(cameraPos[0] - 1.2, cameraPos[1] - 2.5, cameraPos[2] - 5);
		glScalef(1.5, 1.5, 1.5);

		// pull this out as "rotateEnterprise" or something?
		if (keysPressed[0] == 1)
			glRotatef(-5.0, 1.0, 0.0, 0.0);
		if (keysPressed[1] == 1) 
			glRotatef(5.0, 1.0, 0.0, 0.0);
		if (keysPressed[2] == 1)
			glRotatef(5.0, 1.0, 0.0, 0.0);
		if (keysPressed[3] == 1)
			glRotatef(-10.0, 1.0, 0.0, 0.0);
		if (keysPressed[4] == 1)
			glRotatef(10.0, 0.0, 1.0, 1.0);
		if (keysPressed[5] == 1)
			glRotatef(-10.0, 0.0, 1.0, 1.0);

		glBegin(GL_TRIANGLES);
		for (int i = 0; i < 1989; i++) {
			glColor4f((float)(i+200)/1989, (float)(i+200)/1989, (float)(i+200)/1989, 1.0);
			glVertex3fv(vertices[faces[i][0] - 1]);
			glVertex3fv(vertices[faces[i][1] - 1]);
			glVertex3fv(vertices[faces[i][2] - 1]);
		}
		glEnd();
	glPopMatrix();
}

/****************************
Function: initEnterprise
Description: This reads in the values from the text file containing vertices & faces of triangles
				and stores them in vertices[][] and faces[][]
*****************************/
void initEnterprise() {
	char first;
	int counter = 0;
	float x, y, z;
	int p1, p2, p3;
	FILE* filepointer = fopen("enterprise.txt", "r");

	while (counter < 1201) {
		fscanf(filepointer, "%c %f %f %f", &first, &x, &y, &z);

		vertices[counter][0] = x;
		vertices[counter][1] = y;
		vertices[counter][2] = z;

		counter++;

		fscanf(filepointer, "%c", &first);
	}

	counter = 0;

	while (fscanf(filepointer, "%c %d %d %d", &first, &p1, &p2, &p3)) {
		faces[counter][0] = p1;
		faces[counter][1] = p2;
		faces[counter][2] = p3;

		if (fscanf(filepointer, "%c", &first) == EOF)
			break;

		counter++;
	}

	fclose(filepointer);

	enterpriseInit = 1;
}

/*****************************************************************************
Function: drawOtherShip & dialogue
Description: Makes another enterprise pass by with some commentary from the crew
******************************************************************************/
void drawOtherShip(){
	glPushMatrix();
		glTranslatef(shipX, 6.0 + (shipX/10), 0.0);
		glRotatef(90, 0.0, 1.0, 0.0);
		glScalef(2.0, 2.0, 2.0);

		glBegin(GL_TRIANGLES);
			for (int i = 0; i < 1989; i++) {
				glColor4f((float)(i + 200) / 1989, (float)(i + 200)*2 / 1989, (float)(i + 200)*1.5 / 1989, 1.0);
				glVertex3fv(vertices[faces[i][0] - 1]);
				glVertex3fv(vertices[faces[i][1] - 1]);
				glVertex3fv(vertices[faces[i][2] - 1]);
			}
		glEnd();
	glPopMatrix();
}

void dialogue() {
	glPushMatrix();
		glRasterPos3f(cameraPos[0] - 2, cameraPos[1] + 1, cameraPos[2] - 5);

		char text[] = "Wow, that spaceship sure looks familiar... ";
		glColor3f(1.0, 1.0, 1.0);

		for (int i = 0; text[i] != '\0'; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	glPopMatrix();
}

/****************************
Function: initbRingPos
Description: Creates a little displacement for each black hole ring so that
				they are not all in sync
*****************************/
void initbRingPos(float pos[]) {
	for (int i = 0; i < 20; i++) {
		int chance_x = rand() % 2;

		// random ring displacement
		int x = rand() % 2;

		if (chance_x == 0)
			x *= -1;

		pos[i] = x;
	}

	bRingPosInit = true;
}

/****************************
Function: drawCorona
Description: Draws the corona around the sun
*****************************/
void drawCorona(float t1, float t2, float depth) {

	glLineWidth(6);

	glColor4f(1.0, 0.8, 0.0, t1);
	glBegin(GL_LINES);
	for (int i = 0; i < 30; i++) {
		glVertex3f(0, 0, depth);

		int chance = rand() % 2;
		int a = rand() * 3.14 * 2;

		if (chance == 0)
			a *= -1;

		glColor4f(1.0, 0.7, 0.0, t2);
		glVertex2f(cos(a) * 1.5, sin(a) * 1.5);
	}
	glEnd();

	// return to defaults
	glLineWidth(1);
	glColor4f(1.0, 1.0, 1.0, 1.0);
}

/****************************
Function: drawBlackHole
Description: Draws a black hole at the origin and a little behind, which sucks
				in everything and exits the program
*****************************/
void drawBlackHole() {
	glPushMatrix();
	glLineWidth(7);
	glColor3f(1.0, 0.6, 0.0);

	glRotatef(orbitThetaP[7], 0, 0, 1);
	glTranslatef(0, 0, -10);

	for (int j = 1; j <= 20; j++) {

		glBegin(GL_LINE_LOOP);
		for (int i = 1; i <= 30; i++)
		{

			float theta = (float)(2 * 3.141596 * i / 30); //get the current angle

			float x = (10/j)*cos(theta);//calculate the x component
			float y = (10/j)*sin(theta);//calculate the y component

			glVertex3f(x, y, -j/2); //output vertex

		}
		glEnd();

		glRotatef(orbitThetaP[0]/5, 0, 0, 1);
		glTranslatef(pos[j-1]/j, 0, 0);
	}

	glPopMatrix();

	glPushMatrix();
		glScalef(5, 5, 3);
		glTranslatef(0, 0.2, 0);
		drawCorona(0.0, 1.0, -6);
	glPopMatrix();

	// return to defaults
	glLineWidth(1);
	glColor4f(1.0, 1.0, 1.0, 1.0);
}


/****************************
Function: drawPlanet
Description: uses planet() to draw a planet capabale of rotation and orbiting the sun using
				info stored in the planets array
*****************************/
void drawPlanet(int planetNum) {
	glColor3fv(planetColours[planetNum]);
	float degToRad = 3.14159 / 180.0;
	glPushMatrix();
		glRotatef(orbitThetaP[planetNum], planets[planetNum][oT], 1.0, 0.0);
		glTranslatef(0.0, 0.0, planets[planetNum][oR]);
		glRotatef(rotationThetaP[planetNum], planets[planetNum][t], 1.0, 0.0);
		glScalef(planets[planetNum][s], planets[planetNum][s], planets[planetNum][s]);
	planet();
	glPopMatrix();
}

/****************************
Function: drawMoon
Description: altered drawPlanet to have them rotate about a specific planet, as a moon would
*****************************/
void drawMoon(int moonNum) {
	if (moonNum == 0)
		glColor3f(0.0, 0.7, 1.0);
	else
		glColor3f((float)moonNum / 4, (float)moonNum / 4, (float)moonNum );

	glPushMatrix();
		glRotatef(orbitThetaP[(int)moons[moonNum][pl]], planets[(int)moons[moonNum][pl]][oT], 1.0, 0.0);
		glTranslatef(0.0, 0.0, planets[(int)moons[moonNum][pl]][oR]);
		glRotatef(orbitThetaM[moonNum], 0, 1.0, 0.0);
		glTranslatef(0.0, 0.0, planets[(int)moons[moonNum][pl]][s]*1.5);
		glRotatef(rotationThetaM[moonNum], 0.0, 1.0, 0.0);
		glScalef(moons[moonNum][s], moons[moonNum][s], moons[moonNum][s]);
	planet();
	glPopMatrix();
}

/****************************
Function: drawStars
Description: Use the stars array to randomly draw 1000 stars within a 40x40ish area
*****************************/
void drawStars() {
	glPointSize(2);
	glBegin(GL_POINTS);
	for (int i = 0; i < 1000; i++) {
		glColor3f(rand() % 10, rand() % 10, rand() % 10);
		glVertex3i(stars[i][0], stars[i][1], stars[i][2]);
	}
	glEnd();
}

/****************************
Function: initStars
Description: Used so that stars are given the same position in every frame,
				initializes them as points within a 45x45x40 cube
*****************************/
void initStars(star stars[]) {

	for (int i = 0; i < 2000; i++) {
		int chance_x = rand() % 2;
		int chance_y = rand() % 2;
		int chance_z = rand() % 2;

		// random star coordinates
		int x = rand() % 45;
		int y = rand() % 45;
		int z = rand() % 40;

		if (chance_x == 0)
			x *= -1;
		if (chance_y == 0)
			y *= -1;
		if (chance_z == 0)
			z *= -1;

		stars[i][0] = x;
		stars[i][1] = y;
		stars[i][2] = z;
	}

	starsInit = true;
}

/****************************
Function: drawOrbit
Description: Draws the orbit paths of each planet as a white ring
*****************************/
void drawOrbit(int planetNum)
{
	glPushMatrix();

	glColor4f(1.0, 1.0, 1.0, 1.0);

	// rotate it to match planet's orbit tilt
	float deg = atan(1/planets[planetNum][oT]) * (180 / 3.141596);
	if(funkyRings)
		glRotatef(orbitThetaP[planetNum], planets[planetNum][oT], 1.0, 0.0);
	else
	glRotatef(deg, 0.0, 0.0, 1.0);


	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 30; i++)
	{
		float theta = (float)(2 * 3.141596 * i / 30); //get the current angle

		float y = planets[planetNum][oR] * cos(theta);//calculate the y component
		float z = planets[planetNum][oR] * sin(theta);//calculate the z component

		// modify drawing if orbit is elliptical
		if (planets[planetNum][eM] != 0)
			y *= planets[planetNum][eM];

		glVertex3f(0, y, z); //output vertex

	}
	glEnd();
	glPopMatrix();
}

/***************************************************************
Function: idleRotatePlanet and idleRotateMoon
Description: Used to cause the planets' and moons' orbit in idle
****************************************************************/
void idleRotatePlanet(float objRotation[], int speed) {
	for (int i = 0; i < 8; i++) {
		objRotation[i] += planets[i][speed];
		if (objRotation[i] >= 360.0) objRotation[i] -= 360.0;
	}
}

void idleRotateMoon(float objRotation[], int speed) {
	for (int i = 0; i < 4; i++) {
		objRotation[i] += moons[i][speed];
		if (objRotation[i] >= 360.0) objRotation[i] -= 360.0;
	}
}


/****************************
Function: idleBlackHole
Description: Move around the black hole in idle
*****************************/
void idleBlackhole(int init) {
	if (init) {
		for (int i = 0; i < 3; i++) {
			if (bScale[i] > 0)
				bScale[i] -= 0.0002;
			else
				exit(0);
		}
		bPos[1] += 0.004;
		bPos[2] -= 0.002;
	}
}


void idle()
{
	// if stars array hasn't been filled with coordinates, do so
	if (!starsInit)
		initStars(stars);

	if (!bRingPosInit)
		initbRingPos(pos);

	if (!enterpriseInit)
		initEnterprise();

	/* orbits & rotations */
	idleRotatePlanet(orbitThetaP, oS); // orbit planets about sun
	idleRotatePlanet(rotationThetaP, rS); // rotate planets
	idleRotateMoon(orbitThetaM, oS); // orbit moons about planets
	idleRotateMoon(rotationThetaM, rS); // rotate moons

	/* Change Camera Position */
	cameraReposition(0, 2);
	cameraReposition(1, 2);
	cameraReposition(2, 1);
	cameraReposition(3, 1);
	cameraReposition(4, 0);
	cameraReposition(5, 0);

	if (laserOn) {
		laserZ += 0.1;
		if (laserZ > 30) {
			laserOn = false;
			laserZ = 0;
		}
	}
	if (!laserOn)
		laserZ = 0;

	if (shipOn) {
		shipX -= 0.04;
		if (shipX <= -80) {
			shipX = 40;
			shipOn = false;
		}
	}

	// suck solar sys into black hole
	idleBlackhole(blackhole);

	glutPostRedisplay();
}

void toggle(bool* var, char key, char func) {
	if (tolower(key) == func) {
		if (*var)
			*var = false;
		else
			*var = true;
	}
}

void keys(unsigned char key, int x, int y) {
	// quit program with q key
	if (key == 'q' || key == 'Q')
		exit(0);

	toggle(&starsOn, key, 's'); // toggle stars with s key
	toggle(&corona, key, 'c'); // toggle corona with c key
	toggle(&rings, key, 'r'); // toggle rings with r key
	toggle(&laserOn, key, 'f'); //shoot laser with f key
	toggle(&shieldOn, key, 'z'); // toggle shield with z key
	toggle(&funkyRings, key, 'a'); // toggle funky ring movement
	toggle(&shipOn, key, 'd'); // toggle other ship

	// turn on blackhole with b key
	if (key == 'b' || key == 'B')
		blackhole = true;

}

void specialKeys(int key, int x, int y) {
	if (key == GLUT_KEY_PAGE_UP)
		keysPressed[0] = 1;
	if (key == GLUT_KEY_PAGE_DOWN)
		keysPressed[1] = 1;
	if (key == GLUT_KEY_UP)
		keysPressed[2] = 1;
	if (key == GLUT_KEY_DOWN)
		keysPressed[3] = 1;
	if (key == GLUT_KEY_LEFT)
		keysPressed[4] = 1;
	if (key == GLUT_KEY_RIGHT)
		keysPressed[5] = 1;
}

void specialKeysUp(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_PAGE_UP:
		keysPressed[0] = 0;
		break;
	case GLUT_KEY_PAGE_DOWN:
		keysPressed[1] = 0;
		break;
	case GLUT_KEY_UP:
		keysPressed[2] = 0;
		break;
	case GLUT_KEY_DOWN:
		keysPressed[3] = 0;
		break;
	case GLUT_KEY_LEFT:
		keysPressed[4] = 0;
		break;
	case GLUT_KEY_RIGHT:
		keysPressed[5] = 0;
		break;
	}
}

void initializeGL()
{
	// turn on transparency blending
	glEnable(GL_BLEND);
	// set the blending mode to be controlled by ALPHA
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);

	// enable depth testing
	glEnable(GL_DEPTH_TEST);

	// set background color to be black
	glClearColor(0, 0, 0, 1.0);

	// change into projection mode so that we can change the camera properties
	glMatrixMode(GL_PROJECTION);

	// load the identity matrix into the projection matrix
	glLoadIdentity();

	// Set viewing volume
	glOrtho(-10.0, 10.0, -10.0, 10.0, 1.0, 50.0);

	// change into model-view mode so that we can change the object positions
	glMatrixMode(GL_MODELVIEW);

	// Print controls
	printf(" SCENE CONTROLS\n-------------------\n");
	printf("r: toggle rings\nc: toggle corona\ns: toggle stars\nq: exit program\nd: another spaceship will fly by\n");
	printf("b: exit with black hole\nf: fire laser\nz: turn shield on/off\na: turn on funky ring movement (rings must be on)");
	printf("\n\nCAMERA CONTROLS\n------------------\n");
	printf("UP arrow: move up\nDOWN arrow: move down\nRIGHT arrow: move right\nLEFT arrow: move left\n");
	printf("PAGE UP: move forward\nPAGE DOWN: move backward");

}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	if (blackhole) {
		drawBlackHole();
		glScalef(bScale[0], bScale[1], bScale[2]);
		glTranslatef(bPos[0], bPos[1], bPos[2]);
	}

	if (rings) {
		for (int i = 0; i < 8; i++)
			drawOrbit(i);
	}

	if (starsOn)
		drawStars();

	if (laserOn)
		drawLaser();

	// Sun
	glColor3f(1.0, 0.8, 0.0);
	planet();

	for (int i = 0; i < 8; i++)
		drawPlanet(i);

	for (int i = 0; i < 5; i++)
		drawMoon(i);

	if (corona)
		drawCorona(1.0, 0.2, 0);

	drawEnterprise();
	if (shieldOn)
		drawShield();

	if (shipOn) {
		drawOtherShip();
		dialogue();
	}

	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, 1.0, 2.0, 60.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2],
		lookingAt[0], lookingAt[1], lookingAt[2],
		0.0, 1.0, 0.0);

	glFlush();
	glutSwapBuffers();
}

void cameraReposition(int key, int index) {
	if (key == 0 || key == 3 || key == 4) {
		if (keysPressed[key]) {
			cameraPos[index] -= 0.05;
			lookingAt[index] -= 0.05;
		}
	}
	else {
		if (keysPressed[key]) {
			cameraPos[index] += 0.05;
			lookingAt[index] += 0.05;
		}
	}
}

/****************************************************************
Function: main
Description: Create the window, enter the main display loop, etc
*****************************************************************/
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	/* need both double buffering and z buffer */
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 25);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Assignment 2");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutSpecialFunc(specialKeys);
	glutSpecialUpFunc(specialKeysUp);
	glutKeyboardFunc(keys);
	initializeGL();
	glutMainLoop();
}