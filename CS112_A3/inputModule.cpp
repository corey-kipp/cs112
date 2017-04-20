#include <sys/types.h>
#include "inputModule.h"
#include "PLY.h"

/* This File contains the KeyBoard and mouse handling routines */
static int motionMode;
static int startX;
static int startY;
static GLfloat angle = 20;    /* in degrees */
static GLfloat angle2 = 30;   /* in degrees */

GLfloat current_pos[] = { 0.0, 0.0, 5.0 };


int flat = 0;
int light = 1;
int wire = 0;

extern PLYObject* ply;

//added variables
bool light_interaction = false;
GLfloat lightAngle1 = 0;
GLfloat lightAngle2 = 0;
GLfloat lightPosition[] = { -100.0, 100.0, 100.0, 0.0 }; // same as initial position in main

void readKeyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case  0x1B:
	case  'q':
	case  'Q':
		exit(0);
		break;
	case '+':
		if (ply)
			ply->eat();
		break;
	case '-':
		if (ply)
			ply->starve();
		break;
	case 'd':
		if (ply)
			ply->dance();
		break;
	case 'i':
	case 'I':
		if (ply)
			ply->invertNormals();
		break;
	case 'l':
	case 'L':
		light = (light + 1) % 2;
		printf("%s lighting\n", (light ? "OpenGL" : "User"));
		break;
	case 't':
	case 'T':
		// A3: Change some variable here...
		if (light_interaction == false)
		{
			light_interaction = true;
			printf("T pressed down\n");
		}
		else
		{
			light_interaction = false;
			printf("T pressed back up\n");
		}
		break;
	case 'r':
	case 'R':
		// reset initial view parameters
		angle = 20;
		angle2 = 30;
		current_pos[0] = 0.0;
		current_pos[1] = 0.0;
		current_pos[2] = 5.0;
		lightAngle1 = 0;
		lightAngle2 = 0;
		lightPosition[0] = -100.0;
		lightPosition[1] = 100.0;
		lightPosition[2] = 100.0;
		break;
	case 'h':
	case 'H':
		printf("\tPress q/Q for Quit\n");
		printf("\tPress h/H to print this help\n");
		printf("\tPress l/L to turn on/off Lighting\n");
		printf("\tPress i/I to invert the normals\n");
		printf("\tPress r/R to revert ViewPoint to initial position\n");
		printf("\tPress + to make the bunny grow fatter\n");
		printf("\tPress - to make the bunny grow thinner\n");
		printf("\tPress d/D to make the bunny dance randomly\n");
	default:
		break;
	}
	glutPostRedisplay();
}


void readSpecialKeys(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:

		break;
	case GLUT_KEY_DOWN:

		break;
	case GLUT_KEY_RIGHT:

		break;
	case GLUT_KEY_LEFT:

		break;
	}
	glutPostRedisplay();
}


void mouseButtHandler(int button, int state, int x, int y)
{
	motionMode = 0;

	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			motionMode = 1;		// Rotate object
			startX = x;
			startY = y;
		}
		break;
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN) {
			motionMode = 2;		// Translate object
			startX = x;
			startY = y;
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) {
			motionMode = 3;		// Zoom
			startX = x;
			startY = y;
		}
		break;
	}
	glutPostRedisplay();
}


void mouseMoveHandler(int x, int y)
{

	// No mouse button is pressed... return 
	switch (motionMode) {
	case 0:
		return;
		break;

	case 1: // Calculate the rotations
		if (!light_interaction)
		{
			angle = angle + (x - startX);
			angle2 = angle2 + (y - startY);
		}
		else
		{
			lightAngle1 = lightAngle1 + (x - startX);
			lightAngle2 = lightAngle2 + (y - startY);
			//printf("rotating\n");
		}
		startX = x;
		startY = y;
		break;

	case 2:
		if (!light_interaction)
		{
			current_pos[0] = current_pos[0] - (x - startX) / 100.0;
			current_pos[1] = current_pos[1] - (y - startY) / 100.0;
		}
		else
		{
			lightPosition[0] = lightPosition[0] - (x - startX) / 100.0;
			lightPosition[1] = lightPosition[1] - (y - startY) / 100.0;
			//printf("translating\n");
		}
		startX = x;
		startY = y;
		break;

	case 3:
		if (!light_interaction)
		{
			current_pos[2] = current_pos[2] - (y - startY) / 10.0;
		}
		else
		{
			lightPosition[2] = lightPosition[2] - (y - startY) / 10.0;
			//printf("zooming\n");
		}
		startX = x;
		startY = y;
		break;
	}

	glutPostRedisplay();
}


void setUserView()
{
	glLoadIdentity();

	glTranslatef(-current_pos[0], current_pos[1], -current_pos[2]);
	glRotatef(angle2, 1.0, 0.0, 0.0);
	glRotatef(angle, 0.0, 1.0, 0.0);
}

void setLightInteraction()
{
	glTranslatef(-lightPosition[0], lightPosition[1], -lightPosition[2]);
	glRotatef(lightAngle2, 1.0, 0.0, 0.0);
	glRotatef(lightAngle1, 0.0, 1.0, 0.0);
}