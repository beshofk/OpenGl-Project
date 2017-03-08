////// Assignment 3 for computer graphics ////
//////////////////////////////////////////////
//
//#include <iostream>
//#include <stdlib.h>
//#include<math.h>
//#include <glut.h>
//#include "imageloader.h"
//extern "C"
//	{
//		#include"glm.h"
//	}
//
//float Door = 0.0;
//float fb_ward = 0.0;
//float y_rot = 0.0;
//float x_rot = 0.0;
//float spin = 0;
//GLuint _textureId1;
//GLuint _textureId2;
//GLuint _textureId3;
//
//GLuint obj1, obj2, obj3, obj4, obj5, obj6;
//GLMmodel * pmodel;
//
//int windowWidth = 1024;
//int windowHeight = 768;
//
//float aspect = float(windowWidth) / float(windowHeight);
//
//double eye[] = { 0, 0, 0 };
//double center[] = { 0, 0, -1 };
//double up[] = { 0, 1, 0 };
//
//void crossProduct(double a[], double b[], double c[])
//{
//	c[0] = a[1] * b[2] - a[2] * b[1];
//	c[1] = a[2] * b[0] - a[0] * b[2];
//	c[2] = a[0] * b[1] - a[1] * b[0];
//}
//
//void normalize(double a[])
//{
//	double norm;
//	norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
//	norm = sqrt(norm);
//	a[0] /= norm;
//	a[1] /= norm;
//	a[2] /= norm;
//}
//
//void rotatePoint(double a[], double theta, double p[])
//{
//
//	double temp[3];
//	temp[0] = p[0];
//	temp[1] = p[1];
//	temp[2] = p[2];
//
//	temp[0] = -a[2] * p[1] + a[1] * p[2];
//	temp[1] = a[2] * p[0] - a[0] * p[2];
//	temp[2] = -a[1] * p[0] + a[0] * p[1];
//
//	temp[0] *= sin(theta);
//	temp[1] *= sin(theta);
//	temp[2] *= sin(theta);
//
//	temp[0] += (1 - cos(theta))*(a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
//	temp[1] += (1 - cos(theta))*(a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
//	temp[2] += (1 - cos(theta))*(a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);
//
//	temp[0] += cos(theta)*p[0];
//	temp[1] += cos(theta)*p[1];
//	temp[2] += cos(theta)*p[2];
//
//	p[0] = temp[0];
//	p[1] = temp[1];
//	p[2] = temp[2];
//
//}
//
//void Left()
//{
//	double speed = 3.1415 / 16;
//	center[0] = center[0] - eye[0];
//	center[2] = center[2] - eye[2];
//	rotatePoint(up, speed, center);
//	center[0] = center[0] + eye[0];
//	center[2] = center[2] + eye[2];
//}
//
//void Right()
//{
//	double speed = 3.1415 / 16;
//	//glTranslatef(0, center[1], 0);
//	center[0] = center[0] - eye[0];
//	center[2] = center[2] - eye[2];
//	rotatePoint(up, -speed, center);
//	//glTranslatef(0, -center[1], 0);
//	center[0] = center[0] + eye[0];
//	center[2] = center[2] + eye[2];
//}
//
//void Up()
//{
//	double speed = 3.1415 / 12;
//	double rot_axis[3];
//	double look[3];
//
//	look[0] = center[0] - eye[0];
//	look[1] = center[1] - eye[1];
//	look[2] = center[2] - eye[2];
//
//	crossProduct(look, up, rot_axis);
//
//	normalize(rot_axis);
//
//	rotatePoint(rot_axis, speed, center);
//
//	rotatePoint(rot_axis, speed, up);
//
//}
//
//void Down()
//{
//	double speed = 3.1415 / 8;
//	double rot_axis[3];
//	double look[3];
//
//	look[0] = center[0] - eye[0];
//	look[1] = center[1] - eye[1];
//	look[2] = center[2] - eye[2];
//
//	crossProduct(look, up, rot_axis);
//
//	normalize(rot_axis);
//
//	rotatePoint(rot_axis, -speed, center);
//
//	rotatePoint(rot_axis, -speed, up);
//
//}
//
//void moveForward()
//{
//	double speed = 0.1;
//	double direction[3];
//	direction[0] = center[0] - eye[0];
//	direction[1] = center[1] - eye[1];
//	direction[2] = center[2] - eye[2];
//
//	normalize(direction);
//
//	eye[0] += direction[0] * speed;
//	//eye[1] += direction[1] * speed;
//	eye[2] += direction[2] * speed;
//
//	center[0] += direction[0] * speed;
//	//center[1] += direction[1] * speed;
//	center[2] += direction[2] * speed;
//	glutPostRedisplay();
//}
//
//void moveBack()
//{
//	double speed = -0.1;
//	double direction[3];
//	direction[0] = center[0] - eye[0];
//	direction[1] = center[1] - eye[1];
//	direction[2] = center[2] - eye[2];
//
//	normalize(direction);
//
//	eye[0] += direction[0] * speed;
//	//eye[1] += direction[1] * speed;
//	eye[2] += direction[2] * speed;
//
//	center[0] += direction[0] * speed;
//	//center[1] += direction[1] * speed;
//	center[2] += direction[2] * speed;
//	glutPostRedisplay();
//}
//
////Makes the image into a texture, and returns the id of the texture
//GLuint loadTexture(Image* image) 
//{
//	GLuint textureId;
//	glGenTextures(1, &textureId); 
//	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
//	//Map the image to the texture
//	glTexImage2D(GL_TEXTURE_2D,		                //type of the texture
//					0,				                //used for mipmapping should be zero otherwise
//					3,						        //elements per texel, usually 3 (RGB) or 4 (RGBA)
//					image->width, image->height,	//Width and height of the image
//					0,								//The border of the image
//					GL_RGB,							// Texels Format
//					GL_UNSIGNED_BYTE,				// type
//					image->pixels);				    //The actual pixel data
//	return textureId;		//Returns the id of the texture
//}
//
//void loading(GLMmodel * pmodel1, float s)
//{
//	glmUnitize(pmodel1);
//	glmFacetNormals(pmodel1);
//	glmVertexNormals(pmodel1, 90.0);
//	glmScale(pmodel1, s);
//	glmDraw(pmodel1, GLM_SMOOTH | GLM_MATERIAL);
//}
//
//void init()
//{
//	glutInitWindowSize(windowWidth, windowHeight);
//	//Request Double and Depth buffers
//	glutInitDisplayMode(GLUT_RGBA | GL_DOUBLE | GLUT_DEPTH);
//	glutCreateWindow("ASSIGNMENT 3");
//	//Enable Depth buffer
//	glEnable(GL_DEPTH_TEST);
//	//Enable Blending - Enable Alpha component 
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//	// load your images
//	Image* image1 = loadBMP("floor.bmp");
//	Image* image2 = loadBMP("fishes.bmp");
//	Image* image3 = loadBMP("as3.bmp");
//
//	// get the IDs
//	_textureId1 = loadTexture(image1);
//	_textureId2 = loadTexture(image2);
//	_textureId3 = loadTexture(image3);
//
//	// Free the memory
//	delete image1;
//	delete image2;
//	delete image3;
//
//	glEnable(GL_LIGHTING); //Enable lighting
//	glEnable(GL_LIGHT0); //Enable light #0
//	glEnable(GL_LIGHT1); //Enable light #1
//	glEnable(GL_LIGHT2); //Enable light #2
//	glEnable(GL_NORMALIZE); //Automatically normalize normals
//	glShadeModel(GL_SMOOTH); //Enable smooth shading
//
//	obj1 = glGenLists(1);
//	pmodel = glmReadOBJ("data/rose+vase.obj");
//	glNewList(obj1, GL_COMPILE);
//	loading (pmodel, .35);
//	glEndList();
//
//	obj2 = glGenLists(1);
//	pmodel = glmReadOBJ("data/al.obj");
//	glNewList(obj2, GL_COMPILE);
//	loading(pmodel, .5);
//	glEndList();
//
//	obj3 = glGenLists(1);
//	pmodel = glmReadOBJ("data/porsche.obj");
//	glNewList(obj3, GL_COMPILE);
//	loading(pmodel, 1.2);
//	glEndList();
//
//	obj4 = glGenLists(1);
//	pmodel = glmReadOBJ("data/flowers.obj");
//	glNewList(obj4, GL_COMPILE);
//	loading(pmodel, .5);
//	glEndList();
//
//	obj5 = glGenLists(1);
//	pmodel = glmReadOBJ("data/soccerball.obj");
//	glNewList(obj5, GL_COMPILE);
//	loading(pmodel, 0.12);
//	glEndList();
//
//	obj6 = glGenLists(1);
//	pmodel = glmReadOBJ("data/dolphins.obj");
//	glNewList(obj6, GL_COMPILE);
//	loading(pmodel, 0.2);
//	glEndList();
//}
//
//void display()
//{
//	glClearColor(0.0, 0.0, 0.0, 0.0);
//	// Clear Depth and Color buffers
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	//glPushMatrix();
//	//GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
//	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//	//glPopMatrix();
//
//	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);
//
//		
//	//Add ambient light
//	GLfloat ambientColor[] = { 0.3, 0.3, 0.3, 1. }; //Color (0.2, 0.2, 0.2)
//	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
//
//	//Add directed light
//	GLfloat lightColor5[] = { 0.3, 0.3, 0.3, 1 }; //Color (0.5, 0.2, 0.2)
//	//Coming from the direction (-1, 0.5, 0.5)
//	GLfloat lightPos5[] = { 8, -10, 0, 0 };
//	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor5);
//	glLightfv(GL_LIGHT2, GL_POSITION, lightPos5);
//
//	//Add directed light
//	GLfloat lightColor3[] = { 0.3, 0.3, 0.3, 1 }; //Color (0.5, 0.2, 0.2)
//	//Coming from the direction (-1, 0.5, 0.5)
//	GLfloat lightPos3[] = { -8, 10, 0, 0 };
//	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor3);
//	glLightfv(GL_LIGHT1, GL_POSITION, lightPos3);
//
//	glEnable(GL_COLOR_MATERIAL);
//
//	/// camera movement
//	glRotatef(x_rot, 1, 0, 0);
//	glRotatef(y_rot, 0, 1, 0);
//	glTranslatef(0.0, 0.0, fb_ward);
//
//	glTranslatef(0.0, 0.0, -4);
//
//	//// Draw wall of door
//	glPushMatrix();
//	glTranslatef(0.0, 2.25, 0.0);
//	glScalef(4, 2.5, .1);
//	glColor4f(0, 1, 1, 1);
//	glutSolidCube(1);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(1.25, .25, 0.0);
//	glScalef(1.5, 1.5, .1);
//	glColor4f(0, 1, 1, 1);
//	glutSolidCube(1);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(-1.25, .25, 0.0);
//	glScalef(1.5, 1.5, 0.1);
//	glColor4f(0, 1, 1, 1);
//	glutSolidCube(1);
//	glPopMatrix();
//
//	/// Draw Door
//	glPushMatrix();
//	glTranslatef(0.5, 0.0, 0.0);
//	glRotatef(Door, 0, 1, 0);
//	glTranslatef(-0.5, .25, 0.0);
//	glScalef(1, 1.5, 0.1);
//	glColor4f(0, .5, .5, 1);
//	glutSolidCube(1);
//	glPopMatrix();
//	
//	/// Draw two walls
//	glPushMatrix();
//	glTranslatef(0.0, 1.5, -5.0);
//	glScalef(4, 4, 0.1);
//	glColor4f(0, 1, 1, 1);
//	glutSolidCube(1);
//	glPopMatrix();
//
//	//glPushMatrix();
//	//glTranslatef(0.0, 1.5, 5.0);
//	//glScalef(4, 4, 0.1);
//	//glColor4f(0, 1, 1, 1);
//	//glutSolidCube(1);
//	//glPopMatrix();
//
//	//// Draw wall of enter
//	glPushMatrix();
//	glTranslatef(0.0, 2.25, 5.0);
//	glScalef(4, 2.5, .1);
//	glColor4f(0, 1, 1, 1);
//	glutSolidCube(1);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(1.35, .25, 5.0);
//	glScalef(1.3, 1.5, .1);
//	glColor4f(0, 1, 1, 1);
//	glutSolidCube(1);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(-1.35, .25, 5.0);
//	glScalef(1.3, 1.5, 0.1);
//	glColor4f(0, 1, 1, 1);
//	glutSolidCube(1);
//	glPopMatrix();
//
//	////  Draw 4 long
//	/// Draw two long walls
//	glPushMatrix();
//	glTranslatef(2.0, 1.5, 0.0);
//	glScalef(0.1, 4, 10);
//	glColor4f(0, 1, 1, 1);
//	glutSolidCube(1);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(-2.0, 1.5, 0.0);
//	glScalef(0.1, 4, 10);
//	glColor4f(0, 1, 1, 1);
//	glutSolidCube(1);
//	glPopMatrix();
//
//	///////////////////////////
//	/// texure mapping of assignment3
//	glPushMatrix();
//	glEnable(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_2D, _textureId3);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glColor3f(1, 1, 1);
//	glBegin(GL_POLYGON);
//	glTexCoord2f(0, 1);
//	glVertex3f(-1.0, 2, 0.051);
//	glTexCoord2f(1, 1);
//	glVertex3f(1, 2, 0.051);
//	glTexCoord2f(1, 0);
//	glVertex3f(1, 1.3, 0.051);
//	glTexCoord2f(0, 0);
//	glVertex3f(-1, 1.3, 0.051);
//	glEnd();
//	glDisable(GL_TEXTURE_2D);
//	glPopMatrix();
//
//	/// texure mapping of fish
//	glPushMatrix();
//	glEnable(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_2D, _textureId2);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glColor3f(1, 1, 1);
//	glBegin(GL_POLYGON);
//	glTexCoord2f(1, 1);
//	glVertex3f(-1.0, 2.5, -4.945);
//	glTexCoord2f(0, 1);
//	glVertex3f(1, 2.5, -4.945);
//	glTexCoord2f(0, 0);
//	glVertex3f(1, 1.5, -4.945);
//	glTexCoord2f(1, 0);
//	glVertex3f(-1, 1.5, -4.945);
//	glEnd();
//	glDisable(GL_TEXTURE_2D);
//	glPopMatrix();
//
//	/// texure mapping of floor
//	glPushMatrix();
//	glEnable(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_2D, _textureId1);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glColor3f(0, 1, 1);
//	glBegin(GL_POLYGON);
//	glTexCoord2f(6, 12);
//	glVertex3f(2.0, -0.449, 5.0);
//	glTexCoord2f(0.0, 12);
//	glVertex3f(-2.0, -0.449, 5.0);
//	glTexCoord2f(0.0, 0.0);
//	glVertex3f(-2.0, -0.449, -5.0);
//	glTexCoord2f(6, 0.0);
//	glVertex3f(2.0, -0.449, -5.0);
//	glEnd();
//	glDisable(GL_TEXTURE_2D);
//	glPopMatrix();
//
//	///draw floor
//	glPushMatrix();
//	glTranslatef(0.0, -0.5, 0.0);
//	glScalef(4, 0.1, 10);
//	glColor4f(1, 1, 1, 1);
//	glutSolidCube(1);
//	glPopMatrix();
//
//	/// Draw ceil
//	glPushMatrix();
//	glTranslatef(0.0, 3.5, 0.0);
//	glScalef(4, 0.1, 10);
//	glColor4f(1, 1, 1, 1);
//	glutSolidCube(1);
//	glPopMatrix();
//
//
//	//// shelf
//	////1
//	glPushMatrix();
//	glTranslatef(1.0, .5, -4.6);
//	glScalef(2, 0.05, .8);
//	glColor4f(.7, .2, .2, 1);
//	glutSolidCube(1);
//	glPopMatrix();
//	////2
//	glPushMatrix();
//	glTranslatef(-1.6, .5, -4.6);
//	glScalef(.8, 0.05, .8);
//	glColor4f(.7, .2, .2, 1);
//	glutSolidCube(1);
//	glPopMatrix();
//	////3
//	glPushMatrix();
//	glTranslatef(-1.6, .1, -.4);
//	glScalef(.8, 0.05, .8);
//	glColor4f(.7, .2, .2, 1);
//	glutSolidCube(1);
//	glPopMatrix();
//
//	//Loading objects
//	//rose
//	glPushMatrix();
//	glTranslatef(-1.55, 0.877, -4.5);
//	glCallList(obj1);
//	glPopMatrix();
//
//	//man
//	glPushMatrix();	
//	glTranslatef(-.2, 0, 1.5);
//	glRotatef(-70, 0.0, 1.0, 0.0);
//	glCallList(obj2);
//	glPopMatrix();
//
//	//car
//	glPushMatrix();
//	glTranslatef(-1, -0.1, 2.0);
//	glCallList(obj3);
//	glPopMatrix();
//
//	//flowers
//	glPushMatrix();
//	glTranslatef(1.7, 0.05, 4.7 );
//	glCallList(obj4);
//	glPopMatrix();
//
//	//ball
//	glPushMatrix();
//	glTranslatef(-.19, -0.07, 1.71);
//	glCallList(obj5);
//	glPopMatrix();
//
//	//dolphins
//	glPushMatrix();
//	glTranslatef(-1.55, 0.365, -.4);
//	glRotatef(spin, 0, 0, 1);
//	glCallList(obj6);
//	glPopMatrix();
//	
//	////aquarium for dolphins
//	glPushMatrix();
//	GLfloat materialSpecular1[] = { 0, 0, 0, 1 };
//	GLfloat materialcolor1[] = { 0, 0, 1, .4 };
//	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialcolor1);
//	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular1);
//	glTranslatef(-1.55, 0.35, -.4);
//	glScalef(.5, .5, .5);
//	glutSolidCube(1);
//	glPopMatrix();
//	glDisable(GL_COLOR_MATERIAL);
//	
//	//// 3 teapots
//	//Ambient teapot
//	glPushMatrix();
//	GLfloat materialSpecular[] = { 0, 0, 0, 1 };
//	GLfloat materialcolor[] = { 0, 1, 0, .8 };
//	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialcolor);
//	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
//	glTranslatef(.5, 0.6, -4.5);
//	glutSolidTeapot(0.1);
//	glPopMatrix();
//
//	//specular metal teapot 
//	glPushMatrix();
//	GLfloat  shininess = { 20.0f };
//	GLfloat materialSpecular2[] = { 1, 1, 1, 1 };
//	GLfloat materialcolor2[] = { 0.3, 0.3, 0.3, 1 };
//	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess); //The shininess parameter
//	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialcolor2);
//	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular2);
//	glTranslatef(1, 0.62, -4.5);
//	glutSolidTeapot(0.125);
//	glPopMatrix();
//
//	//diffuse teapot 
//	glPushMatrix();
//	GLfloat materialSpecular3[] = { 0, 0, 0, 1 };
//	GLfloat materialcolor3[] = { .5, .5, 0, 1};
//	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialcolor3);
//	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular3);
//	glTranslatef(1.5, 0.64, -4.5);	
//	glutSolidTeapot(0.15);
//	glPopMatrix();
//
//	//Swap between the two buffers
//	glutSwapBuffers();
//}
//
//void Timer(int x)
//{
//	spin  += 2;
//	//Refresh and redraw	
//	glutPostRedisplay();
//	glutTimerFunc(30, Timer, 0);
//}
//
//void open(int value)
//{
//	if (Door >= -90)
//		Door -= 1;
//	else
//		return;
//	glutTimerFunc(10, open, 0);
//}
//
//void close(int value)
//{
//
//	if (Door < 0)
//		Door += 1;
//	else
//		return;
//	glutTimerFunc(10, close, 0);
//}
//
//void Keyboard(unsigned char Key, int x, int y){
//	switch (Key)
//	{
//	case '7':
//		if (fb_ward < 8.5)
//			fb_ward += .1;
//		break;
//	case '1':
//		if (fb_ward > 0.1)
//			fb_ward -= .1;
//		break;
//	case '4':
//		y_rot -= 2;
//		break;
//	case '6':
//		y_rot += 2;
//		break;
//	case '8':
//		if (x_rot >= -90)
//			x_rot -= 2;
//		break;
//	case '2':
//		if (x_rot <= 90)
//			x_rot += 2;
//		break;
//	///moving
//	case 'f':
//		moveForward();
//		break;
//	case 'b':
//		moveBack();
//		break;
//	///Door
//	case '5':
//		open(0);
//		break;
//	case '0':
//		close(0);
//		break;
//	default:
//		break;
//	}
//}
//
//void specialKeys(int key, int x, int y)
//{
//	switch (key)
//	{
//		case GLUT_KEY_LEFT	: Left ()	; break;
//		case GLUT_KEY_RIGHT	: Right()	; break;
//		case GLUT_KEY_UP	: center[1] += .05; break;
//		case GLUT_KEY_DOWN	: center[1] -= .05; break;
//	}
//	// Refresh the window
//	glutPostRedisplay();
//}
//
//int main(){
//	init();
//	glMatrixMode(GL_PROJECTION);
//	//zNear > 0 to allow the depth buffer
//	gluPerspective(60, aspect, 0.1, 10);
//	glutDisplayFunc(display);
//	glutKeyboardFunc(Keyboard);
//	glutSpecialFunc(specialKeys);
//	Timer(0);
//	glutMainLoop();
//	return 0;
//}