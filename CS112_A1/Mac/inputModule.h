/*
 * OpenGL demonstration program for UCI ICS Computer Graphics courses
 *
 */

#include <GLUT/GLUT.h>

/*---------------external entities from sceneModule-----------------*/
extern GLfloat angley;   
extern GLfloat anglex;  
extern GLfloat distanceX;
extern GLfloat distanceY;
extern GLfloat distanceZ;

/*---------------external entities from main-------------------------*/
extern void cleanup();

void readKeyboard( unsigned char key, int x, int y );
void readSpecialKeys( int key, int x, int y );
void mouseButtHandler( int button, int state, int x, int y );
void mouseMoveHandler( int x, int y );