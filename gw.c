#include <GL/glut.h>
#include <GL/glu.h> 
#include <GL/gl.h>
#include <stdlib.h>
//#include <glut.h>
//#include <glu.h> 
//#include <gl.h>
#include <cmath>
#include<stdio.h>
//#include<glut.h>
#define M_PI 3.1414
#define WHEEL 1
#define CABIN 2

GLfloat global_ambient[] = { 0.3f,0.3f,0.3f,1.0f };

GLfloat dir_ambient[] = { 0.6f,0.6f,0.6f,1.0f };
GLfloat dir_diffuse[] = { 0.8f,0.8f,0.8f,1.0f };
GLfloat dir_specular[] = { 1.0f,1.0f,1.0f,1.0f };

GLfloat dir_position[] = { 0.0f,1.0f,1.0f,0.0f };

// Color Material - Specular
GLfloat mat_specular[] = { 0.6,0.6,0.6,1.0 };

GLfloat rotx = 0;
GLfloat roty = 0;

GLint n_bars = 16;
GLfloat c_radius;

GLfloat w_rot;
GLfloat w_speed = 0.25;

bool anim = false;
bool inv_rot = false;

float toRad(float deg)
{
	return (deg * M_PI) / 180;
}

void init(void)
{

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

	glLightfv(GL_LIGHT0, GL_AMBIENT, dir_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dir_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, dir_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, dir_position);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMateriali(GL_FRONT, GL_SHININESS, 30);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glShadeModel(GL_SMOOTH);

	glNewList(WHEEL, GL_COMPILE);
	glColor3f(0.8, 0, 0.0);
	// Center front
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, 15);
	for (float angle = 0; angle <= 360; angle += 0.1)
	{
		glVertex3f(5 * cos(toRad(angle)), 5 * sin(toRad(angle)), 15);
	}
	glEnd();
	// Center 
	glBegin(GL_QUAD_STRIP);
	for (float angle = 0; angle <= 360; angle += 0.1) {
		glVertex3f(5 * cos(toRad(angle)), 5 * sin(toRad(angle)), 15);
		glVertex3f(5 * cos(toRad(angle)), 5 * sin(toRad(angle)), -15);
	}
	glEnd();

	// Center back
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, -15);
	for (float angle = 0; angle <= 360; angle += 0.1) {
		glVertex3f(5 * cos(toRad(angle)), 5 * sin(toRad(angle)), -15);
	}
	glEnd();

	// Wheel structure front
	for (float angle = 0; angle <= 360; angle += 0.1) {
		glBegin(GL_POLYGON);
		glVertex3f(30 * cos(toRad(angle)), 30 * sin(toRad(angle)), 4);
		glVertex3f(28 * cos(toRad(angle)), 28 * sin(toRad(angle)), 4);
		glVertex3f(28 * cos(toRad(angle + 0.2)), 28 * sin(toRad(angle + 0.2)), 4);
		glVertex3f(30 * cos(toRad(angle + 0.2)), 30 * sin(toRad(angle + 0.2)), 4);
		glEnd();
	}

	glBegin(GL_QUAD_STRIP);
	for (float angle = 0; angle <= 360; angle += 0.1) {
		glVertex3f(30 * cos(toRad(angle)), 30 * sin(toRad(angle)), 4);
		glVertex3f(30 * cos(toRad(angle)), 30 * sin(toRad(angle)), 3.5);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (float angle = 0; angle <= 360; angle += 0.1) {
		glVertex3f(28 * cos(toRad(angle)), 28 * sin(toRad(angle)), 4);
		glVertex3f(28 * cos(toRad(angle)), 28 * sin(toRad(angle)), 3.5);
	}
	glEnd();

	// Wheel structure front
	for (float angle = 0; angle <= 360; angle += 0.1) {
		glBegin(GL_POLYGON);
		glVertex3f(30 * cos(toRad(angle)), 30 * sin(toRad(angle)), 3.5);
		glVertex3f(28 * cos(toRad(angle)), 28 * sin(toRad(angle)), 3.5);
		glVertex3f(28 * cos(toRad(angle + 0.2)), 28 * sin(toRad(angle + 0.2)), 3.5);
		glVertex3f(30 * cos(toRad(angle + 0.2)), 30 * sin(toRad(angle + 0.2)), 3.5);
		glEnd();
	}



	// Wheel structure back
	for (float angle = 0; angle <= 360; angle += 0.1) {
		glBegin(GL_POLYGON);
		glVertex3f(30 * cos(toRad(angle)), 30 * sin(toRad(angle)), -4);
		glVertex3f(28 * cos(toRad(angle)), 28 * sin(toRad(angle)), -4);
		glVertex3f(28 * cos(toRad(angle + 0.2)), 28 * sin(toRad(angle + 0.2)), -4);
		glVertex3f(30 * cos(toRad(angle + 0.2)), 30 * sin(toRad(angle + 0.2)), -4);
		glEnd();
	}

	glBegin(GL_QUAD_STRIP);
	for (float angle = 0; angle <= 360; angle += 0.1) {
		glVertex3f(30 * cos(toRad(angle)), 30 * sin(toRad(angle)), -4);
		glVertex3f(30 * cos(toRad(angle)), 30 * sin(toRad(angle)), -3.5);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (float angle = 0; angle <= 360; angle += 0.1) {
		glVertex3f(28 * cos(toRad(angle)), 28 * sin(toRad(angle)), -4);
		glVertex3f(28 * cos(toRad(angle)), 28 * sin(toRad(angle)), -3.5);
	}
	glEnd();

	// Wheel structure back
	for (float angle = 0; angle <= 360; angle += 0.1) {
		glBegin(GL_POLYGON);
		glVertex3f(30 * cos(toRad(angle)), 30 * sin(toRad(angle)), -3.5);
		glVertex3f(28 * cos(toRad(angle)), 28 * sin(toRad(angle)), -3.5);
		glVertex3f(28 * cos(toRad(angle + 0.2)), 28 * sin(toRad(angle + 0.2)), -3.5);
		glVertex3f(30 * cos(toRad(angle + 0.2)), 30 * sin(toRad(angle + 0.2)), -3.5);
		glEnd();
	}

	glEndList();

	// Cabin
	glNewList(CABIN, GL_COMPILE);
	glColor3f(0.5, 0, 0);
	// Bar
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, -4);
	for (float angle = 0; angle <= 360; angle += 0.1) {
		glVertex3f(0.5 * cos(toRad(angle)), 0.5 * sin(toRad(angle)), -4);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (float angle = 0; angle <= 360; angle += 0.1) {
		glVertex3f(0.5 * cos(toRad(angle)), 0.5 * sin(toRad(angle)), -3.5);
		glVertex3f(0.5 * cos(toRad(angle)), 0.5 * sin(toRad(angle)), 3.5);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, 4);
	for (float angle = 0; angle <= 360; angle += 0.1) {
		glVertex3f(0.5 * cos(toRad(angle)), 0.5 * sin(toRad(angle)), 4);
	}
	glEnd();


	// Cono (Bell attached to ferris wheel)
	glPushMatrix();
	glColor3f(0.95, 0.67, 2.06);//
	glTranslatef(0, -5, 0);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(2, 5, 50, 50);
	glPopMatrix();

	glEndList();
}

void draw_scene() {
	glPushMatrix();
	glColor3f(0.02, 0.22, 0.02);   //change color (base of ferris wheel)
	glTranslatef(0, -40, 0);
	glScalef(50, 2, 50);
	glutSolidCube(2);
	glPopMatrix();

	glPushMatrix();
	glCallList(WHEEL);
	glPopMatrix();

	glPushMatrix();
	glRotatef(w_rot, 0, 0, 1);
	for (int i = 0; i < n_bars; i++) {
		c_radius = (360.0 / n_bars) * i;
		glPushMatrix();
		// Axis
		glPushMatrix();
		glColor3f(0.92, 0.12, 0.12); //change color (spokes of ferris wheel)-------frontside
		glRotatef(c_radius, 0, 0, 1);
		glRotatef(-11, 1, 0, 0);
		glTranslatef(0, 14.5, 10);
		glScalef(1, 28, 0.5);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.92, 0.12, 0.12); //change color (spokes of ferris wheel)------backside
		glRotatef(c_radius, 0, 0, 1);
		glRotatef(11, 1, 0, 0);
		glTranslatef(0, 14.5, -10);
		glScalef(1, 28, 0.5);
		glutSolidCube(1);
		glPopMatrix();

		glTranslatef(28 * cos(toRad(c_radius)), 28 * sin(toRad(c_radius)), 0);
		glRotatef(-w_rot, 0, 0, 1);
		glCallList(CABIN);
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3, 0.3, 0.3); //change color (front: left stand of ferris wheel)
	glRotatef(-30, 0, 0, 1);
	glTranslatef(0, -25, 12);
	glScalef(3, 40, 2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3, 0.3, 0.3); //change color (front: right stand of ferris wheel)
	glRotatef(30, 0, 0, 1);
	glTranslatef(0, -25, 12);
	glScalef(3, 40, 2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3, 0.3, 0.3); //change color (back: left stand of ferris wheel)
	glRotatef(-30, 0, 0, 1);
	glTranslatef(0, -25, -12);
	glScalef(3, 40, 2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3, 0.3, 0.3); //change color (back: right stand of ferris wheel)
	glRotatef(30, 0, 0, 1);
	glTranslatef(0, -25, -12);
	glScalef(3, 40, 2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20, -30, 30);
	glColor3f(1, 0, 0);    //change color (cap of man)
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(2, 2, 50, 50);
	glPopMatrix();
	glColor3f(1, 0.5, 0.5);   //change color (body of man)
	glutSolidSphere(1, 50, 50);//
	glPushMatrix();
	glTranslatef(0, -2, 0);
	glScalef(0.5, 4, 0.5);  //change the side of main body of man(breadth,height,depth)
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.9, -6, 0);
	glRotatef(-20, 0, 0, 1);
	glScalef(0.5, 5, 0.5);  //change the side of left leg of man(breadth,height,depth)
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.9, -6, 0);
	glRotatef(20, 0, 0, 1);
	glScalef(0.5, 5, 0.5);   //change the side of right leg of man(breadth,height,depth)
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.9, -2, 0);
	glRotatef(-120, 0, 0, 1);
	glScalef(0.5, 2, 0.5);  //change the side of left hand of man(breadth,height,depth)
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.9, -2, 0);
	glRotatef(120, 0, 0, 1);
	glScalef(0.5, 2, 0.5);  //change the side of right hand of man(breadth,height,depth)
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
}


//display the whole thing
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.64, 0.71, 0.9, 1);
	glPushMatrix();
	glTranslatef(0, 0, -100); //position th wheel accordingly(x axis, y axix, depth)
	glRotatef(rotx, 1, 0, 0);
	glRotatef(roty, 0, 1, 0);
	draw_scene();
	glPopMatrix();
	glutSwapBuffers();
}

void idle() {
	if (anim) {
		if (inv_rot)
			w_rot -= w_speed;
		else
			w_rot += w_speed;
		glutPostRedisplay();
	}
}

void reshape(int w, int h) {
	// Prevent a divide by zero
	if (h == 0)
		h = 1;

	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);

	// Calculate aspect ratio of the window
	float fAspect = (GLfloat)w / (GLfloat)h;

	// Set the perspective coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 800.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
	case 'W':
		rotx += 2.0;
		break;
	case 's':
	case 'S':
		rotx -= 2.0;
		break;
	case 'a':
	case 'A':
		roty += 2.0;
		break;
	case 'd':
	case 'D':
		roty -= 2.0;
		break;
	case '+':
	case '1':
		if (n_bars < 24)
			n_bars++;
		break;
	case '-':
	case '0':
		if (n_bars > 8)
			n_bars--;
		break;
	case 'x':
	case 'X':
		w_speed = w_speed - 0.05;
		break;
	case 'v':
	case 'V':
		w_speed = w_speed + 0.05;
		break;
	case 'c':
	case 'C':
		anim = !anim;
		break;
	case 'i':
	case 'I':
		inv_rot = !inv_rot;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	
	printf("\n****************************************************\n\n");
	printf("\n	Top Movement               :w or W\n");
	printf("\n	Bottom Movement            :s or S\n");
	printf("\n	Rotate Right               :a or A\n");
	printf("\n	Rotate Left                :d or D\n");
	printf("\n	Wheel Rotation             :c or C\n");
	printf("\n	Clockwise & Anti-clockwise :i or I\n");
	//printf("\n	Wheel Rotation             :c or C\n");
	printf("\n	Increase Speed             :v or V\n");
	printf("\n	Decrease Speed             :x or X\n");
	printf("\n	Increase No. of Cabin      :+ or 1\n");
	printf("\n	Decrease No. of Cabin      :- or 0\n");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 700);
	glutInitWindowPosition(500, 100);
	glutCreateWindow("GAINT WHEEL");
	init();
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
