#ifdef WIN32
#include <windows.h>
#endif

#include <math.h>
#include <stdlib.h> 
#include <iostream>
#include <GL/gl.h>

// Defines maximum stack capacity.
#define STACK_CAP 16
// Defines pi for converting angles.
#define PI 3.14159265359

// Structure for the matrix stack, top specifies current top position on the stack, initially zero (which means one matrix in the stack).
struct matrix_stack
{
	GLdouble m[STACK_CAP][16];
	int top;
};

// Define a macro for retrieving current matrix from top of current stack.
#define current_matrix (current_stack->m[current_stack->top])

// Identity matrix constant.
const GLdouble identity[16] =
{ 1, 0, 0, 0,
0, 1, 0, 0,
0, 0, 1, 0,
0, 0, 0, 1 };

// The model view matrix stack.
struct matrix_stack model_view = { { { 0 } }, 0 };
// The projection matrix stack.
struct matrix_stack projection = { { { 0 } }, 0 };
// The current stack pointer that specifies the matrix mode.
struct matrix_stack *current_stack = &model_view;

void I_my_glLoadMatrixd(const GLdouble *m);

// Multiplies current matrix with matrix b, put the result in current matrix.
void matrix_multiply(const GLdouble *b)
{
	GLdouble result[16];
	for (int i = 0; i < 4; i++)
	{
		result[i * 4] = ( //[a]
			(current_matrix[i * 4] * b[0]) //0 //0 -->
			+ (current_matrix[i * 4 + 1] * b[4]) //1 //4 -->
			+ (current_matrix[i * 4 + 2] * b[8]) //2 //8 -->
			+ (current_matrix[i * 4 + 3] * b[12])); //3 //12 -->

		result[i * 4 + 1] = ( //b
			(current_matrix[i * 4] * b[1])
			+ (current_matrix[i * 4 + 1] * b[5])
			+ (current_matrix[i * 4 + 2] * b[9])
			+ (current_matrix[i * 4 + 3] * b[13]));

		result[i * 4 + 2] = ( //c
			(current_matrix[i * 4] * b[2])
			+ (current_matrix[i * 4 + 1] * b[6])
			+ (current_matrix[i * 4 + 2] * b[10])
			+ (current_matrix[i * 4 + 3] * b[14]));

		result[i * 4 + 3] = ( //d  
			(current_matrix[i * 4] * b[3])
			+ (current_matrix[i * 4 + 1] * b[7])
			+ (current_matrix[i * 4 + 2] * b[11])
			+ (current_matrix[i * 4 + 3] * b[15]));
	}

	/*for (int i = 0; i < 16; i++)
	{
		current_matrix[i] = result[i];
	}*/
	I_my_glLoadMatrixd(result);
}
void transpose_matrix(GLdouble * b)
{
	GLdouble tempMatrix[16];

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tempMatrix[4 * j + i] = b[4 * i + j];

		}
	}
	I_my_glLoadMatrixd(tempMatrix);
	/*for (int i = 0; i < 16; i++)
	{
		current_matrix[i] = tempMatrix[i];
	}*/
}
// Calculates cross product of b and c, put the result in a
// a = b x c.
void cross_product(GLdouble *ax, GLdouble *ay, GLdouble *az,
	GLdouble bx, GLdouble by, GLdouble bz,
	GLdouble cx, GLdouble cy, GLdouble cz)
{
	// ...
	*ax = (by * cz) - (bz * cy);
	*ay = (bz * cx) - (bx * cz);
	*az = (bx * cy) - (by * cz);
}

// Normalizes vector (x, y, z).
void normalize(GLdouble *x, GLdouble *y, GLdouble *z)
{
	double length = fabs(sqrt((*x * *x) + (*y * *y) + (*z * *z)));
	//To normalize a vector, you divide each element by the square root of the sum of the squares (as in your first example).
	*x = *x / length;
	*y = *y / length;
	*z = *z / length;
	//fabs???	
}

// Switches matrix mode by changing the current stack pointer.
void I_my_glMatrixMode(GLenum mode)
{
	if (mode == GL_MODELVIEW)
	{
		current_stack = &model_view;
	}
	else if (mode == GL_PROJECTION)
	{
		current_stack = &projection;
	}
}

// Overwrites current matrix with identity matrix.
void I_my_glLoadIdentity(void)
{
	for (int i = 0; i < 16; i++)
	{
		current_matrix[i] = identity[i];
	}
}

// Pushes current matrix onto current stack, report error if the stack is already full.
void I_my_glPushMatrix(void)
{
	if (current_stack->top >= STACK_CAP)
	{
		std::cout << "Can't Push, stack already full" << std::endl;
	}
	else
	{
		for (int i = 0; i < 16; i++)
		{
			current_stack->m[current_stack->top + 1][i] = current_matrix[i];
		}
		current_stack->top++;
	}
}

// Pops current matrix from current stack, report error if the stack has only one matrix left.
void I_my_glPopMatrix(void)
{
	if (current_stack->top <= 0)
	{
		std::cout << "Can't Pop, stack is empty" << std::endl;
	}
	else
	{
		current_stack->top--;
	}
}

// Overwrites currentmatrix with m.
void I_my_glLoadMatrixf(const GLfloat *m)
{
	for (int i = 0; i < 16; i++) 
	{ 
		current_matrix[i] = (GLdouble)m[i]; 
	}
}

void I_my_glLoadMatrixd(const GLdouble *m)
{
	for (int i = 0; i < 16; i++) 
	{ 
		current_matrix[i] = m[i]; 
	}
}

void I_my_glTranslated(GLdouble x, GLdouble y, GLdouble z)
{
	GLdouble translationMatrix[16] = { 
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1 };
	transpose_matrix(translationMatrix);
	matrix_multiply(translationMatrix);
}

void I_my_glTranslatef(GLfloat x, GLfloat y, GLfloat z)
{
	I_my_glTranslated((GLdouble)x, (GLdouble)y, (GLdouble)z);
}

// Remembers to normalize vector (x, y, z), and to convert angle from degree to radius before calling sin and cos.
void I_my_glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z)
{
	normalize(&x, &y, &z); //normalize
	GLdouble theta = (angle * (GLdouble)PI) / ((GLdouble)180); //convert degrees to radians
	GLdouble xx = x * x, xy = x * y, xz = x * z,
		yy = y * y, yz = y * z,
		zz = z * z;

	GLdouble c = (GLdouble)cos(theta);
	GLdouble s = (GLdouble)sin(theta);

	GLdouble rotationMatrix[16] = {
		xx*(1 - c) + c, xy*(1 - c) - z*s, xz*(1 - c) + y*s, 0,
		xy*(1 - c) + z*s, yy*(1 - c) + c, yz*(1 - c) - x*s, 0,
		xz*(1 - c) - y*s, yz*(1 - c) + x*s, zz*(1 - c) + c, 0,
		0, 0, 0, 1 };

	GLdouble backup[16];
	for (int i = 0; i < 16; i++)
	{
		backup[i] = current_matrix[i];
	}

	transpose_matrix(rotationMatrix);
	I_my_glLoadMatrixd(rotationMatrix);
	matrix_multiply(backup);
}

void I_my_glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) //doesnt work for floats
{
	I_my_glRotated((GLdouble)angle, (GLdouble)x, (GLdouble)y, (GLdouble)z);
}

void I_my_glScaled(GLdouble x, GLdouble y, GLdouble z)
{
	GLdouble scaleMatrix[16] = {
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1 };

	transpose_matrix(scaleMatrix);
	matrix_multiply(scaleMatrix);
}

void I_my_glScalef(GLfloat x, GLfloat y, GLfloat z)
{
	I_my_glScaled((GLdouble)x, (GLdouble)y, (GLdouble)z);
}

// Copies current matrix to m.
void I_my_glGetMatrixf(GLfloat *m)
{
	for (int i = 0; i < 16; i++)
	{
		m[i] = (GLfloat)current_matrix[i];
	}
}

void I_my_glGetMatrixd(GLdouble *m)
{
	for (int i = 0; i < 16; i++)
	{
		m[i] = current_matrix[i];
	}
}

// Remember to normalize vectors.
void I_my_gluLookAt(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ,
	GLdouble centerX, GLdouble centerY, GLdouble centerZ,
	GLdouble upX, GLdouble upY, GLdouble upZ)
{
	// f = normalize x,y,z; s = f x up, u =s x f

	GLdouble fx, fy, fz, sx, sy, sz;
	fx = centerX - eyeX;
	fy = centerY - eyeY;
	fz = centerZ - eyeZ;

	normalize(&fx, &fy, &fz); // f

	cross_product(&sx, &sy, &sz, fx, fy, fz, upX, upY, upZ); //s
	normalize(&sx, &sy, &sz);

	cross_product(&upX, &upY, &upZ, sx, sy, sz, fx, fy, fz);
	//already normalized

	GLdouble look_at_matrix[16] = {
		sx, sy, sz, 0,
		upX, upY, upZ, 0,
		-fx, -fy, -fz, 0,
		0, 0, 0, 1 };

	transpose_matrix(look_at_matrix);
	matrix_multiply(look_at_matrix);

	I_my_glTranslated(-eyeX, -eyeY, -eyeZ); //eye to origin
}

void I_my_glFrustum(GLdouble left, GLdouble right, GLdouble bottom,
	GLdouble top, GLdouble zNear, GLdouble zFar)
{
	GLdouble a = (right + left) / (right - left);
	GLdouble b = (top + bottom) / (top - bottom);
	GLdouble c = -((zFar + zNear) / (zFar - zNear));
	GLdouble d = -((2 * zFar*zNear) / (zFar - zNear));
	GLdouble e = (2 * zNear) / (right - left);
	GLdouble f = (2 * zNear) / (top - bottom);

	GLdouble frustumMatrix[16] = {
		e, 0, a, 0,
		0, f, b, 0,
		0, 0, c, d,
		0, 0, -1, 0 };

	transpose_matrix(frustumMatrix);
	matrix_multiply(frustumMatrix);

}

// Based on the inputs, calculate left, right, bottom, top, and call I_my_glFrustum accordingly
// remember to convert fovy from degree to radius before calling tan.
void I_my_gluPerspective(GLdouble fovy, GLdouble aspect,
	GLdouble zNear, GLdouble zFar)
{
	GLdouble left, right, bottom, top;

	top = zNear * tan(fovy * PI / 360);
	bottom = -top;
	left = bottom * aspect;
	right = top * aspect;

	I_my_glFrustum(left, right, bottom, top, zNear, zFar);
}
