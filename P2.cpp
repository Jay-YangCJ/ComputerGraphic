//Chang Jie Yang

#include <gl/glut.h>
#include <string>
using namespace std;

int width = 800, height = 500, x, y = 247;
float lineColors[3][3] = { {1.0,0.0,0.0}, {0.0,1.0,0.0}, {0.0,0.0,1.0} };
float barColors[3][3] = { {0.502,0.502,0.502},{0.502,0.502,0.502},{0.502,0.502,0.502} };
char notation[3] = { 'R', 'G', 'B' };

//declare and initialize an int array to store vertice of bottom left vertex of each slide bar
float vert[3][2] = { { 45,240 },{ 145,240 },{ 245,240 } };

//declare and initialize a bool array called 't' to indicate if the cursor is over the slide bar
//a bool called 'flag' to indicate if the left button of the mouse is held down
//a bool called 'r' to indicate if the cursor is over the rectangular region
bool t[3] = { false, false, false }, flag = false, r = false;

//a bool array called 's' to show if the user presses 'l' key or 'r' key
bool s[2] = { false,false };

//a float array to store and update color information that will be applied for square region and rectangular region
float rcolor[6][3] = { {0.502,0.502,0.502},{0.0,0.0,0.0},{0.0,0.0,0.0},{0.502,0.502,0.502},{0.0,0.0,0.0},{0.502, 0.502,0.502} };

//a int array to store and update information about displaying rectangular region
int infor[3] = { 450,5,450 };

// provide visual feedback
void onoroff(bool signal, int i) {
	if (signal) {
		barColors[i][0] = 1.0;
		barColors[i][1] = 1.0;
		barColors[i][2] = 1.0;
	}
	else {
		barColors[i][0] = 0.502;
		barColors[i][1] = 0.502;
		barColors[i][2] = 0.502;
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	int lx1 = 60, lx2 = 55;
	for (int i = 0; i < 3; i++) {
		glColor3fv(lineColors[i]);
		glRasterPos2f(lx2, 100);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, notation[i]);
		glRasterPos2f(lx2, 395);
		string temp = to_string((int)(vert[i][1]-113));
		for (int j = 0; j < temp.length(); j++) {
			char digit = temp[j];
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, digit);
		}
		glBegin(GL_LINES);
		glVertex2f(lx1, 120);
		glVertex2f(lx1, 375);
		lx1 += 100;
		lx2 += 100;
		glEnd();

		glColor3fv(barColors[i]);
		glBegin(GL_QUADS);
		glVertex2f(vert[i][0], vert[i][1]);
		glVertex2f(vert[i][0], vert[i][1] + 14);
		glVertex2f(vert[i][0] + 30, vert[i][1] + 14);
		glVertex2f(vert[i][0] + 30, vert[i][1]);
		glEnd();
	}
	
	//store current color of square region for further processing
	rcolor[0][0] = (vert[0][1] - 120) / 255;
	rcolor[0][1] = (vert[1][1] - 120) / 255;
	rcolor[0][2] = (vert[2][1] - 120) / 255;
	glBegin(GL_QUADS);
	glColor3fv(rcolor[0]);
	glVertex2f(500, 250);
	glVertex2f(500, 400);
	glVertex2f(650, 400);
	glVertex2f(650, 250);
	glEnd();

	int count = (700 - 450) / 5;
	if (s[0]) {
		infor[0] = 450;
		infor[1] = 5;
		infor[2] = 450;
	}
	else if (s[1]) {
		infor[0] = 700;
		infor[1] = -5;
		infor[2] = 700;
	}
	
	//reset color and initial x coordinate of rectangular region
	rcolor[3][0] = rcolor[5][0];
	rcolor[3][1] = rcolor[5][1];
	rcolor[3][2] = rcolor[5][2];
	infor[0] = infor[2];
	
	while (count > 0) {
		glColor3fv(rcolor[3]);
		glBegin(GL_QUADS);
		glVertex2f(infor[0], 120);
		glVertex2f(infor[0], 155);
		glVertex2f(infor[0] + infor[1], 155);
		glVertex2f(infor[0] + infor[1], 120);
		glEnd();
		count--;
		infor[0] += infor[1];
		rcolor[3][0] -= rcolor[4][0];
		rcolor[3][1] -= rcolor[4][1];
		rcolor[3][2] -= rcolor[4][2];
	}
	glFlush();
}

void mouse(int button, int state, int mouseX, int mouseY) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			flag = true;
			int c = 0;
			if (x >= 450 && x <= 700 && y >= 120 && y <= 155) {
				if (r && flag) {
					for (int i = 450; i < 700; i += 5) {
						if (x >= i && x <= i + 5) {
							break;
						}
						else
							c++;
					}
					if (s[0])
						c = c;
					else if (s[1])
						c = 49 - c;
					for (int i = 0; i < 3; i++)
						vert[i][1] = (rcolor[5][i] - c*rcolor[4][i]) * 255 + 120;
				}
			}
			glutPostRedisplay();
		}
		else
			flag = false;
		break;
		glutPostRedisplay();
	}
}

void motion(int mouseX, int mouseY) {
	x = mouseX;
	y = height - 1 - mouseY;
	for (int i = 0; i < 3; i++) {
		if (t[i] && flag) {
			if (y > 375)
				y = 375;
			else if (y < 120)
				y = 120;
			vert[i][1] = y - 7;

			// disconnect the application if the cursor moves a certain distance away from sliders
			if (x >= vert[i][0] - 45 && x <= vert[i][0] + 75) {
				break;
			}
			else {
				t[i] = false;
				onoroff(t[i], i);
			}
		}
	}
	glutPostRedisplay();
}

void passive(int mouseX, int mouseY) {
	x = mouseX;
	y = height - 1 - mouseY;
	for (int i = 0; i < 3; i++) {
		if (x >= vert[i][0] && x <= vert[i][0] + 30 && y >= vert[i][1] && y <= vert[i][1] + 14) {
			t[i] = true;
			onoroff(t[i], i);
			break;
		}

		else {
			t[i] = false;
			onoroff(t[i], i);
		}
	}

	//check if the cursor moves over rectangular region
	if (x >= 450 && x <= 700 && y >= 120 && y <= 155)
		r = true;
	else
		r = false;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'l':
		s[0] = true;
		s[1] = false;
		for (int i = 0; i < 3; i++) {
			rcolor[1][i] = rcolor[0][i];
			rcolor[3][i] = rcolor[1][i];
			rcolor[5][i] = rcolor[3][i];
			rcolor[4][i] = (rcolor[3][i] - rcolor[2][i]) / 50;
		}
		break;
	case 'r':
		s[1] = true;
		s[0] = false;
		for (int i = 0; i < 3; i++) {
			rcolor[2][i] = rcolor[0][i];
			rcolor[3][i] = rcolor[2][i];
			rcolor[5][i] = rcolor[3][i];
			rcolor[4][i] = (rcolor[3][i] - rcolor[1][i]) / 50;
		}
		break;
	}
	glutPostRedisplay();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Project2");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(passive);
	glutMainLoop();
}