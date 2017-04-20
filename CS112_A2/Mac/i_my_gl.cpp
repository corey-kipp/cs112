

#ifdef WIN32
#include <windows.h>
#endif

#include <GLUT/GLUT.h>

// Defines maximum stack capacity.
#define STACK_CAP 16
// Defines pi for converting angles.
#define PI 3.14159265359

// Structure for the matrix stack, top specifies current top position on the stack, initially zero (which means one matrix in the stack)
struct matrix_stack
{
    GLdouble m[STACK_CAP][16];
    int top;
};

// Define a macro for retrieving current matrix from top of current stack.
#define current_matrix (current_stack->m[current_stack->top])

// Identity matrix constant.
const GLdouble identity[16] =
{1, 0, 0, 0,
 0, 1, 0, 0,
 0, 0, 1, 0,
 0, 0, 0, 1};

// the model view matrix stack.
struct matrix_stack model_view = {{{0}}, 0};
// the projection matrix stack.
struct matrix_stack projection = {{{0}}, 0};
// The current stack pointer that specifies the matrix mode.
struct matrix_stack *current_stack = &model_view;

// Multiplies current matrix with matrix b, put the result in current matrix.
// current = current * b
void matrix_multiply(const GLdouble *b)
{
    // ...
}

// Calculates cross product of b and c, put the result in a
// a = b x c
void cross_product(GLdouble *ax, GLdouble *ay, GLdouble *az,
    GLdouble bx, GLdouble by, GLdouble bz,
    GLdouble cx, GLdouble cy, GLdouble cz)
{
    // ...
}

// Normalizes vector (x, y, z).
void normalize(GLdouble *x, GLdouble *y, GLdouble *z)
{
    // ...
}

// Switches matrix mode by changing the current stack pointer.
void I_my_glMatrixMode(GLenum mode)
{
    // ...
}

// Overwrites current matrix with identity matrix.
void I_my_glLoadIdentity(void)
{
    // ...
}

// Pushes current matrix onto current stack, report error if the stack is already full.
void I_my_glPushMatrix(void)
{
    // ...
}

// Pops current matrix from current stack, report error if the stack has only one matrix left.
void I_my_glPopMatrix(void)
{
    // ...
}

// Overwrites currentmatrix with m.
void I_my_glLoadMatrixf(const GLfloat *m)
{
    // ...
}

void I_my_glLoadMatrixd(const GLdouble *m)
{
    // ...
}

void I_my_glTranslated(GLdouble x, GLdouble y, GLdouble z)
{
    // ...
}

void I_my_glTranslatef(GLfloat x, GLfloat y, GLfloat z)
{
    I_my_glTranslated((GLdouble)x, (GLdouble)y, (GLdouble)z);
}

// Remember to normalize vector (x, y, z), and to convert angle from degree to radius before calling sin and cos.
void I_my_glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z)
{
    // ...
}

void I_my_glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
    I_my_glRotated((GLdouble)angle, (GLdouble)x, (GLdouble)y, (GLdouble)z);
}

void I_my_glScaled(GLdouble x, GLdouble y, GLdouble z)
{
    // ...
}

void I_my_glScalef(GLfloat x, GLfloat y, GLfloat z)
{
    I_my_glScaled((GLdouble)x, (GLdouble)y, (GLdouble)z);
}

// Copes current matrix to m.
void I_my_glGetMatrixf(GLfloat *m)
{
    // ...
}

void I_my_glGetMatrixd(GLdouble *m)
{
    // ...
}

// Remember to normalize vectors.
void I_my_gluLookAt(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ, 
    GLdouble centerX, GLdouble centerY, GLdouble centerZ, 
    GLdouble upX, GLdouble upY, GLdouble upZ)
{
    // ...
}

void I_my_glFrustum(GLdouble left, GLdouble right, GLdouble bottom,
    GLdouble top, GLdouble zNear, GLdouble zFar)
{
    // ...
}

// Based on the inputs, calculate left, right, bottom, top, and call I_my_glFrustum accordingly
// remember to convert fovy from degree to radius before calling tan
void I_my_gluPerspective(GLdouble fovy, GLdouble aspect, 
    GLdouble zNear, GLdouble zFar)
{
    // ...
}
