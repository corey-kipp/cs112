#include "inputModule.h"
#include <iostream>
static int motionMode;
static int startX;
static int startY;

static bool antialising;
static bool lighting;

extern GLuint textureName;

void readKeyboard( unsigned char key, int x, int y ){
  switch( key ){
  case  0x1B: /* esc */
  case  'q':
    break;
  case ' ':

    break;
  case ',':

    break;
  case '.':

    break;
  case 'a':
    antialising = !antialising;

    if (antialising) {
      // TODO 11: enable multisample
		glEnable(GLUT_MULTISAMPLE);
		std::cout << "AA enabled" << std::endl;
    } else {
      // TODO 12: disable multisample
		glDisable(GLUT_MULTISAMPLE);
		std::cout << "AA disabled" << std::endl;
		
    }
    break;

  case 'l':
    lighting = !lighting;
    if (lighting) {
      glEnable(GL_LIGHTING);
    } else {
      glDisable(GL_LIGHTING);
    }
    break;
  case 'r':
    /* reset initial view parameters */
    angley = 20;
    anglex = 30;
    distanceX = 0.0;
    distanceY = 0.0;
    distanceZ = 5.0;
    break;
  default:
    break;
  }
  glutPostRedisplay( );
}

void readSpecialKeys( int key, int x, int y ){
  switch( key ){
  case GLUT_KEY_UP:

    break;
  case GLUT_KEY_DOWN:

    break;
  case GLUT_KEY_RIGHT:

    break;
  case GLUT_KEY_LEFT:

    break;
  }
  glutPostRedisplay( );
}

void mouseButtHandler(int button, int state, int x, int y)
{
  motionMode = 0;

  switch( button ){
  case GLUT_LEFT_BUTTON:
    if( state == GLUT_DOWN ){
      /* Rotate object */
      motionMode = 1;
      startX = x;
      startY = y;
    }
    break;
  case GLUT_MIDDLE_BUTTON:
    if( state == GLUT_DOWN ){
      /* Translate object */
      motionMode = 2;
      startX = x;
      startY = y;
    }
    break;
  case GLUT_RIGHT_BUTTON:
    if( state == GLUT_DOWN ){
      /* Zoom */
      motionMode = 3;
      startX = x;
      startY = y;
    }
    break;
  }
  glutPostRedisplay( );
}

void mouseMoveHandler( int x, int y ){
  switch(motionMode){
  case 0:
    /* No mouse button is pressed... do nothing */
    /* return; */
    break;

  case 1:
    /* Calculate the rotations */
    angley = angley + (x - startX);
    anglex = anglex + (y - startY);
    startX = x;
    startY = y;
    break;

  case 2:
    distanceX = distanceX - (x - startX)/100.0;
    distanceY = distanceY - (y - startY)/100.0;
    startX = x;
    startY = y;
    break;

  case 3:
    distanceZ = distanceZ - (y - startY)/10.0;
    startX = x;
    startY = y;
    break;
  }

  glutPostRedisplay( );
}