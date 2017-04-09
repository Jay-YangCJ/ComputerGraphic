//Chang Jie Yang
#include <iostream>
using namespace std;
#include <gl/glut.h>

GLint width = 1100, height = 500, axis = 0;
GLfloat pos[] = { 12,5,-3,1 }, amb[] = { 0.2,0.2,0.2,1.0 }, spe[] = { 0.1,0.1,0.1,1.0 },
color[8][3] = { {0.0,1.0,0.0},{0.941,0.902,0.549},{0.863,0.078,0.235},{1.0,1.0,0.0},{0.678, 1.0, 0.184},{0.827,0.827,0.827},{1.0,1.0,1.0},{0.0,1.0,1.0} };
GLfloat theta = 0, dt = 0.05, dz = 0, disz = 0, dx = 0, disx = 0;
bool carSignal = false, carSignal1 = false;


void drawPolygon(GLint colorNum) {
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color[colorNum]);
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, color[colorNum]);
	glBegin(GL_POLYGON);
	glVertex3f(-100, -1, 110);
	glVertex3f(-100, -1, -110);
	glVertex3f(100, -1, -110);
	glVertex3f(100, -1, 110);
	glEnd();
}

void drawCube(GLint colorNum) {
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color[colorNum]);
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, color[colorNum]);
	glPushMatrix();
	glTranslatef(0, -0.11, 0);
	glRotatef(-90, 1, 0, 0);
	glutSolidCube(0.25);
	glPopMatrix();
}

void drawTorus(void) {
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color[3]);
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, color[3]);
	glPushMatrix();
	glTranslatef(-0.135, -0.17, 0.15);
	glRotatef(-90, 0, 1, 0);
	glutSolidTorus(0.017, 0.017, 50, 50);
	glPopMatrix();
}

void drawVane(void) {
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(-0.4, 0.07, -4);
	glVertex3f(-0.7, 0.07, -4);
	glVertex3f(-0.7, 0.15, -4);
	glEnd();
}

void meadow(void) {
	drawPolygon(0);
}

void road() {
	glPushMatrix();
	glTranslatef(4, -0.94, 0);
	glScalef(0.006, 0.05, 0.5);
	drawPolygon(5);
	
	glPushMatrix();
	glScalef(0.1, 0, 0.015);

	for (int i = 7000; i >= -7000; i-=500) {
		glPushMatrix();
		glTranslatef(0, -0.93, i);
		drawPolygon(6);
		glPopMatrix();
	}

	glPopMatrix();
	glPopMatrix();
}

void car() {
	
	//car movement
	glPushMatrix();
	glTranslatef(disx, 0, disz);

	glPushMatrix();
	glTranslatef(0, 0.03, 0);

	//bottom body
	glPushMatrix();
	glScalef(1, 0.5, 2.2);
	glTranslatef(2, -1.8, -1);
	glRotatef(90, 1, 0, 0);
	drawCube(2);
		
	//wheels
	drawTorus();
	glTranslatef(0, 0.12, 0);
	drawTorus();
	glTranslatef(0.25, 0.01, 0);
	drawTorus();
	glTranslatef(0, -0.12, 0);
	drawTorus();
	glPopMatrix();

	//top body
	glPushMatrix();
	glScalef(0.8, 0.4, 1.1);
	glTranslatef(2.5, -2, -2.1);
	glRotatef(90, 1, 0, 0);
	drawCube(2);
	
	//windows
	glPushMatrix();
	glTranslatef(0, -0.02, -0.04);
	glScalef(1.02, 0.3, 0.5);
	drawCube(7);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -0.14, -0.04);
	glScalef(1.02, 0.3, 0.5);
	drawCube(7);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0, -0.04);
	glScalef(0.8, 1.02, 0.4);
	drawCube(7);
	glPopMatrix();

	//lights
	glPushMatrix();
	glTranslatef(-0.08, 0.1, 0.26);
	glScalef(0.25, 2.1, 0.25);
	drawCube(3);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.08, 0.1, 0.26);
	glScalef(0.25, 2.1, 0.25);
	drawCube(3);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
}

void house(void) {
	glPushMatrix();
	glTranslatef(1, -0.5, -4);

	//roof
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color[2]);
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, color[2]);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(0.2, 0.2, 30, 30);
	glPopMatrix();

	//body
	drawCube(1);

	//door
	glPushMatrix();
	glScalef(0.3, 0.3, 0.3);
	glTranslatef(0, -0.55, 0.3);
	drawCube(3);
	glPopMatrix();

	//windows
	glPushMatrix();
	glScalef(0.25, 0.25, 0.25);
	glTranslatef(0.25, -0.1, 0.38);
	drawCube(4);
	glPopMatrix();
	glPushMatrix();
	glScalef(0.25, 0.25, 0.25);
	glTranslatef(-0.25, -0.1, 0.38);
	drawCube(4);
	glPopMatrix();

	glPopMatrix();
}

void windmill(void) {
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color[7]);
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, color[7]);
	
	//body
	glPushMatrix();
	glTranslatef(-0.4, -0.7, -4);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(0.05, 0.8, 10, 10);
	glPopMatrix();
	
	//rotor
	glPushMatrix();
	glTranslatef(-0.4, 0.07, -4);
	glutSolidSphere(0.03,10,10);
	glPopMatrix();

	//rotation
	glPushMatrix();
	glTranslatef(-0.4, 0.07, 0.02);
	glRotatef(theta, 0, 0, 1);
	glTranslatef(0.4, -0.07, 0);
	
	//vanes
	drawVane();
	glPushMatrix();
	glTranslatef(-0.65, -0.22, 0);
	glRotatef(-120, 0, 0, 1);
	drawVane();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.52, 0.43, 0);
	glRotatef(-240, 0, 0, 1);
	drawVane();
	glPopMatrix();

	glPopMatrix();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glRotatef(axis, 0, 1, 0);
	
	glPushMatrix();
	glTranslatef(0, 0, -disz);

	glPushMatrix();
	glRotatef(20,0,1,0);
	
	glPushMatrix();
	glTranslatef(2.2, 0, -6);
	house();
	windmill();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.1, 0, -3);
	house();
	windmill();
	glPopMatrix();
	
	house();
	windmill();

	glPushMatrix();
	glTranslatef(-1.1, 0, 3);
	house();
	windmill();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-2.2, 0, 6);
	house();
	windmill();
	glPopMatrix();

	glPopMatrix();
	
	car();

	glPushMatrix();
	glTranslatef(-2, 0, 0);
	road();
	glPopMatrix();
	
	meadow();
	glPopMatrix();
	glPopMatrix();
	
	glutSwapBuffers();
}

void idle(void) {
	theta = (theta <= 360) ? theta + dt : dt;
	if (carSignal) {
		disz = (disz >= -40 && disz <= 40) ? disz + dz : disz;
		if (disz >= 40)
			disz = 40;
		if (disz <= -40)
			disz = -40;
	}
	if (carSignal1 && carSignal) {
		disx = (disx >= -0.35 && disx <= 0.35) ? disx + dx : disx;
		if (disx >= 0.35)
			disx = 0.35;
		if (disx <= -0.35)
			disx = -0.35;
		carSignal1 = false;
	}
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'l': axis++; break;
	case 'r': axis--; break;
	case ' ': 
		axis = 0; 
		theta = 0; 
		dt = 0.05; 
		disz = 0;
		disx = 0;
		dz = 0;
		dx = 0;
		carSignal = false;
		carSignal1 = false;
		break;
	case 'w': 
		dt += 0.05; 
		if (dt >= 2)
			dt = 2;
		break;
	case 's': 
		dt -= 0.05; 
		if (dt <= -2)
			dt = -2; 
		break;
	case 'c': 
		carSignal = true; 
		dz = -0.005;
		break;
	case 'x':
		carSignal = true;
		dz = 0.005;
		break;
	case 'o':
		carSignal1 = true;
		dx = -0.05;
		break;
	case 'p':
		carSignal1 = true;
		dx = 0.05;
		break;
	case 'v': carSignal = false; break;
	}
	glutPostRedisplay();
}

void manual() {
	cout << "The user's instruction" << endl << endl
		<< "1.Press 'w': increase right/decrease left rotation speed of vanes" << endl
		<< "2.Press 's': decrease right/increase right rotation speed of vanes" << endl
		<<"rotation will stop when the speed reaches zero" << endl
		<< "3.Press 'l': left rotation along y-axis" << endl
		<< "4.Press 'r': right rotation along y-axis" << endl
		<< "5.Press 'spacebar': reset everything" << endl
		<< "6.Press 'c': the car starts moving forward" << endl
		<< "7.Press 'x': the car starts moving backward" << endl
		<< "8.Press 'o': the car moves left along x-axis" << endl
		<< "9.Press 'p': the car moves right along x-axis" << endl
		<< "the car can not move outside the road" << endl
		<< "the car is allowed to move left or right while the car is in motion" << endl
		<< "10.Press 'v': the car stops moving";
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Project3");
	glClearColor(0.7, 0.9, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, 2.2, 1, 50);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 75);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0, 0, -5);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	manual();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();
} 