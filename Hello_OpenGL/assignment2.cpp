////// Assignment 2 for computer graphics ////
////////////////////////////////////////////

#include"glut.h"
#include<math.h>

float windowWidth = 1024;
float windowHeight = 768;

float aspect = windowWidth / windowHeight;

double eye[] = { 0, 0, 0 };
double center[] = { 0, 0, -1 };
double up[] = { 0, 1, 0 };

float Door = 0.0;
float fb_ward = 0.0;
float y_rot = 0.0;
float x_rot = 0.0;

void crossProduct(double a[], double b[], double c[])
{
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
}
void normalize(double a[])
{
	double norm;
	norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
	norm = sqrt(norm);
	a[0] /= norm;
	a[1] /= norm;
	a[2] /= norm;
}
void rotatePoint(double a[], double theta, double p[])
{
	double temp[3];
	temp[0] = p[0];
	temp[1] = p[1];
	temp[2] = p[2];

	temp[0] = -a[2] * p[1] + a[1] * p[2];
	temp[1] = a[2] * p[0] - a[0] * p[2];
	temp[2] = -a[1] * p[0] + a[0] * p[1];

	temp[0] *= sin(theta);
	temp[1] *= sin(theta);
	temp[2] *= sin(theta);

	temp[0] += (1 - cos(theta))*(a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
	temp[1] += (1 - cos(theta))*(a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
	temp[2] += (1 - cos(theta))*(a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

	temp[0] += cos(theta)*p[0];
	temp[1] += cos(theta)*p[1];
	temp[2] += cos(theta)*p[2];

	p[0] = temp[0];
	p[1] = temp[1];
	p[2] = temp[2];
}
void Left()
{
	double speed = 3.1415 / 20;
	rotatePoint(up, speed, center);
}
void Right()
{
	double speed = 3.1415 / 20;
	rotatePoint(up, -speed, center);
}
void Up()
{
	double speed = 3.1415 / 20;
	double rot_axis[3];
	double look[3];

	look[0] = center[0] - eye[0];
	look[1] = center[1] - eye[1];
	look[2] = center[2] - eye[2];

	crossProduct(look, up, rot_axis);

	normalize(rot_axis);

	rotatePoint(rot_axis, speed, eye);

	rotatePoint(rot_axis, speed, up);
}
void Down()
{
	double speed = 3.1415 / 20;
	double rot_axis[3];
	double look[3];

	look[0] = center[0] - eye[0];
	look[1] = center[1] - eye[1];
	look[2] = center[2] - eye[2];

	crossProduct(look, up, rot_axis);

	normalize(rot_axis);

	rotatePoint(rot_axis, -speed, eye);

	rotatePoint(rot_axis, -speed, up);
}
void moveForward()
{
	double speed = 0.1;
	double direction[3];
	direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];

	eye[0] += direction[0] * speed;
	eye[1] += direction[1] * speed;
	eye[2] += direction[2] * speed;

	center[0] += direction[0] * speed;
	center[1] += direction[1] * speed;
	center[2] += direction[2] * speed;

	glutPostRedisplay();
}
void moveBack()
{
	double speed = -0.1;
	double direction[3];
	direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];

	eye[0] += direction[0] * speed;
	eye[1] += direction[1] * speed;
	eye[2] += direction[2] * speed;

	center[0] += direction[0] * speed;
	center[1] += direction[1] * speed;
	center[2] += direction[2] * speed;
	glutPostRedisplay();
}
void init()
{
	glutInitWindowSize(windowWidth, windowHeight);
	// Request Double and Depth buffers
	glutInitDisplayMode(GLUT_RGBA | GL_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Hello Depth Buffer");
	// Enable Depth buffer
	glEnable(GL_DEPTH_TEST);
	// Enable Blending - Enable Alpha component 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void display()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	// Clear Depth and Color buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);

	/// camera movement
	glRotatef(x_rot, 1, 0, 0);
	glRotatef(y_rot, 0, 1, 0);
	glTranslatef(0.0, 0.0, fb_ward);

	glTranslatef(0.0, 0.0, -4);

	//// Draw wall of door
	glPushMatrix();
	glTranslatef(0.0, 2.25, 0.0);
	glScalef(4, 2.5, .1);
	glColor4f(0.8, 0.5, 0.7, 1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.25, .25, 0.0);
	glScalef(1.5, 1.5, .1);
	glColor4f(0.8, 0.5, 0.7, 1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.25, .25, 0.0);
	glScalef(1.5, 1.5, 0.1);
	glColor4f(0.8, 0.5, 0.7, 1);
	glutSolidCube(1);
	glPopMatrix();

	/// Draw Door
	glPushMatrix();

	glTranslatef(0.5, 0.0, 0.0);
	glRotatef(Door, 0, 1, 0);
	glTranslatef(-0.5, .25, 0.0);
	glScalef(1, 1.5, 0.1);
	glColor4f(0.0, 0.0, 1.0, 1);
	glutSolidCube(1);
	glPopMatrix();

	/// Draw two walls
	glPushMatrix();
	glTranslatef(0.0, 1.5, -5.0);
	glScalef(4, 4, 0.1);
	glColor4f(.9, 0.5, 0.2, 1);
	glutSolidCube(1);
	glPopMatrix();

	//glPushMatrix();
	//glTranslatef(0.0, 1.5, 5.0);
	//glScalef(4, 4, 0.1);
	//glColor4f(.9, 0.5,0.2,1);
	//glutSolidCube(1);
	//glPopMatrix();

	//// Draw wall of enter
	glPushMatrix();
	glTranslatef(0.0, 2.25, 5.0);
	glScalef(4, 2.5, .1);
	glColor4f(0.9, 0.5, 0.2, 1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.25, .25, 5.0);
	glScalef(1.5, 1.5, .1);
	glColor4f(0.9, 0.5, 0.2, 1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.25, .25, 5.0);
	glScalef(1.5, 1.5, 0.1);
	glColor4f(0.9, 0.5, 0.2, 1);
	glutSolidCube(1);
	glPopMatrix();

	////  Draw 4 long
	/// Draw two long walls
	glPushMatrix();
	glTranslatef(2.0, 1.5, 0.0);
	glScalef(0.1, 4, 10);
	glColor4f(0.0, 1.0, 0.0, 1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.0, 1.5, 0.0);
	glScalef(0.1, 4, 10);
	glColor4f(0.0, 1.0, 0.0, 1);
	glutSolidCube(1);
	glPopMatrix();

	/// Draw floor
	glPushMatrix();
	glTranslatef(0.0, -0.5, 0.0);
	glScalef(4, 0.1, 10);
	glColor4f(.7, .7, .7, 1);
	glutSolidCube(1);
	floorf(1);
	glPopMatrix();

	/// Draw ceil
	glPushMatrix();
	glTranslatef(0.0, 3.5, 0.0);
	glScalef(4, 0.1, 10);
	glColor4f(1.0, 1.0, 1.0, 1);
	glutSolidCube(1);
	glPopMatrix();

	// Swap between the two buffers
	glutSwapBuffers();
}
void Timer(int x)
{
	// Refresh and redraw
	glutPostRedisplay();
	glutTimerFunc(30, Timer, 0);
}
void open(int value)
{
	if (Door >= -90)
		Door -= 1;
	else
		return;
	glutTimerFunc(10, open, 0);
}
void close(int value)
{

	if (Door < 0)
		Door += 1;
	else
		return;
	glutTimerFunc(10, close, 0);
}
void Keyboard(unsigned char Key, int x, int y){
	switch (Key)
	{
	case '7':
		if (fb_ward < 8.5)
			fb_ward += .1;
		break;
	case '1':
		if (fb_ward > 0.1)
			fb_ward -= .1;
		break;
		///
	case '4':
		y_rot -= 2;
		break;
	case '6':
		y_rot += 2;
		break;
	case '8':
		if (x_rot >= -90)
			x_rot -= 2;
		break;
	case '2':
		if (x_rot <= 90)
			x_rot += 2;
		break;
		///
	case 'f':
		moveForward();
		break;
	case 'b':
		moveBack();
		break;
		///
	case '5':
		open(0);
		break;
	case '0':
		close(0);
		break;
	default:
		break;
	}
}

void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:Left(); break;
	case GLUT_KEY_RIGHT: Right(); break;
	case GLUT_KEY_UP:    Up(); break;
	case GLUT_KEY_DOWN:  Down(); break;
	}
}

int main(){
	init();
	glMatrixMode(GL_PROJECTION);
	// zNear > 0 to allow the depth buffer
	gluPerspective(60, aspect, 0.1, 50);
	glutDisplayFunc(display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(specialKeys);
	Timer(0);
	glutMainLoop();
	return 0;
}