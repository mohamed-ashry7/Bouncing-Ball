#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <cstdio>
#include <math.h>
#include <string.h>
#include <string>
#include <glut.h>

#define ROOM_SIZE 10
#define BRICK_SIZE 2
#define NUMBER_OF_BRICKS (ROOM_SIZE/BRICK_SIZE)



class Color {
private :
	float r; 
	float g; 
	float b; 
public :
	Color(float rr, float gg, float bb) {
		r = rr/255.0; g = gg/255.0; b = bb/255.0;
	}
	float getRed() {
		return r; 
	}
	float getBlue() {
		return b; 
	}
	float getGreen() {
		return g; 
	}

};

class Wall {
private:
	int grid[NUMBER_OF_BRICKS][NUMBER_OF_BRICKS]; 
public :
	
	void setCell(int x , int y , int c ) {
		grid[x][y] = c; 
		
	}
	int getCellPoints(int x, int y) {
		return grid[x][y]; 
	}

};

Wall W1; // the right wall 
Wall W2; // the floor ;
Wall W3; // the left wall 
Wall W5;  // the ceiling 
Wall W4; 

int score = 0; 
float previousScore = 0; 
double MovHor = 0; 
double MovVer = 0; 
bool shot = false;


int a = 0;
int b = 0; 
int c = 0; 

float X0 = ROOM_SIZE;
float Y0 = 0.25*ROOM_SIZE;
float Z0 = ROOM_SIZE / 2;

float XF = 0;
float YF = ROOM_SIZE/2 ;
float ZF = ROOM_SIZE / 2;
 

float step = 0.003;
float stepX = step * a;
float stepY = step * b;
float stepZ = step * c;


float stepReplay = 0.0005;
float XReplay = 0; 
float YReplay = 0; 
float ZReplay = 0; 
bool hasBeenShot = false;
bool replay = false; 

int times = 0;


int mode = 0; 
void print(int x, int y, int z ,char* str)
{
	int len, i;
	glColor3f(0,0,0); 
	//set the position of the text in the window using the x and y coordinates
	glRasterPos3f(x, y,z);

	//get the length of the string to display
	len = (int)strlen(str);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
	}
}
void drawCircle(double cx, double cy, double cz, double r, int acc, int plane) { // 0 - >XY , 1 ->XZ  , 2 ->ZY



	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0); 
	if (plane == 0) {
		for (int i = 0; i < acc; i++) {
			double theta = 2.0f * 3.14159265359 * double(i) / double(acc);
			double x = cx + r * cosf(theta);
			double y = cy + r * sinf(theta);
			glVertex3f(x, y, cz);
		}
	}
	else if (plane == 1) {
		for (int i = 0; i < acc; i++) {
			double theta = 2.0f * 3.14159265359 * double(i) / double(acc);
			double x = cx + r * cosf(theta);
			double z = cz + r * sinf(theta);
			glVertex3f(x, cy, z);
		}
	}
	else {
		for (int i = 0; i < acc; i++) {
			double theta = 2.0f * 3.14159265359 * double(i) / double(acc);
			double z = cz + r * cosf(theta);
			double y = cy + r * sinf(theta);
			glVertex3f(cx, y, z);
		}
	}


	glEnd();
}
void axis(double length) { // draw a z-axis, with cone at end  
	

	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, length); // along the z-axis 
	glEnd();

	
}
//void drawRoom() {
//
//	glColor3f(0.0f, 0.0f, 0.0f);
//	glTranslatef(ROOM_SIZE /2, ROOM_SIZE /2, ROOM_SIZE /2);
//	glutWireCube(ROOM_SIZE);
//
//}

void drawBrick(int x , int y , int z, int whichPlane) { // 0 ->XY , 1 ->XZ 
		
	if (whichPlane == 0) {
		glBegin(GL_QUADS);
		glVertex3f(x, y, z);
		glVertex3f(x + BRICK_SIZE, y, z);
		glVertex3f(x + BRICK_SIZE, y + BRICK_SIZE, z);
		glVertex3f(x, y + BRICK_SIZE, z);
		glEnd();
	}
	else {
		glBegin(GL_QUADS);
		glVertex3f(x, y, z);
		glVertex3f(x + BRICK_SIZE, y,z );
		glVertex3f(x + BRICK_SIZE, y , z + BRICK_SIZE);
		glVertex3f(x, y , z + BRICK_SIZE);
		glEnd();
	}
	

}


void drawWalls() {
	Color c1(79, 159, 108); //score 30 ; //dark Green
	Color c2(125, 158, 137); // 20 //baby green
	Color c3(229, 158, 58); // 5 ;  // pale yellow 
	Color c4(255, 98, 58); // -5  // baby red
	Color c5(255, 145, 0); // 1 // orange
	Color c6(255, 25, 0); // -15 // red
	Color c7(36, 97, 187); // 35 // blue 
	//The Right Wall ; 
	int cc = 0;
	for (int  i = 0; i < ROOM_SIZE; i += BRICK_SIZE) {
		for (int  j = 0; j < ROOM_SIZE; j += BRICK_SIZE) {
			int color =cc%7; 
			if (color == 0) {
				glColor3f(c1.getRed(), c1.getGreen(), c1.getBlue());
				W1.setCell(i/BRICK_SIZE,j/BRICK_SIZE,30); 
			}
			else if (color == 1) {
				glColor3f(c2.getRed(), c2.getGreen(), c2.getBlue());
				W1.setCell(i/BRICK_SIZE, j / BRICK_SIZE, 20);
			}
			else if (color == 2) {
				glColor3f(c3.getRed(), c3.getGreen(), c3.getBlue());
				W1.setCell(i / BRICK_SIZE, j / BRICK_SIZE, 5);
			}
			else if (color == 3) {
				glColor3f(c4.getRed(), c4.getGreen(), c4.getBlue());
				W1.setCell(i / BRICK_SIZE, j / BRICK_SIZE, -5);
			}
			else if (color == 4) {
				glColor3f(c5.getRed(), c5.getGreen(), c5.getBlue());
				W1.setCell(i / BRICK_SIZE, j / BRICK_SIZE, 1);
			}
			else if (color == 5) {
				glColor3f(c6.getRed(), c6.getGreen(), c6.getBlue());
				W1.setCell(i / BRICK_SIZE, j / BRICK_SIZE, -15);
			}
			else  {
				glColor3f(c7.getRed(), c7.getGreen(), c7.getBlue());
				W1.setCell(i / BRICK_SIZE, j / BRICK_SIZE, 35);
			}
			cc++; 
			drawBrick(i, j, 0 , 0 ); 
		}
	}
	//the Left Wall
	for (int i = 0; i < ROOM_SIZE; i += BRICK_SIZE) {
		for (int j = 0; j < ROOM_SIZE; j += BRICK_SIZE) {
			int color = cc % 7;
			if (color == 0) {
				glColor3f(c1.getRed(), c1.getGreen(), c1.getBlue());
				W3.setCell(i / BRICK_SIZE, j / BRICK_SIZE, 30);
			}
			else if (color == 1) {
				glColor3f(c2.getRed(), c2.getGreen(), c2.getBlue());
				W3.setCell(i / BRICK_SIZE, j / BRICK_SIZE, 20);
			}
			else if (color == 2) {
				glColor3f(c3.getRed(), c3.getGreen(), c3.getBlue());
				W3.setCell(i / BRICK_SIZE, j / BRICK_SIZE, 5);
			}
			else if (color == 3) {
				glColor3f(c4.getRed(), c4.getGreen(), c4.getBlue());
				W3.setCell(i / BRICK_SIZE, j / BRICK_SIZE, -5);
			}
			else if (color == 4) {
				glColor3f(c5.getRed(), c5.getGreen(), c5.getBlue());
				W3.setCell(i / BRICK_SIZE, j / BRICK_SIZE, 1);
			}
			else if (color == 5) {
				glColor3f(c6.getRed(), c6.getGreen(), c6.getBlue());
				W3.setCell(i / BRICK_SIZE, j / BRICK_SIZE, -15);
			}
			else {
				glColor3f(c7.getRed(), c7.getGreen(), c7.getBlue());
				W3.setCell(i / BRICK_SIZE, j / BRICK_SIZE, 35);
			}
			cc++;
			drawBrick(i, j, ROOM_SIZE, 0);
		}
	}
	// The floor 
	for (int i = 0; i < ROOM_SIZE; i += BRICK_SIZE) {
		for (int j = 0; j < ROOM_SIZE; j += BRICK_SIZE) {
			int color = cc % 7;
			if (color == 0) {
				glColor3f(c1.getRed(), c1.getGreen(), c1.getBlue());
				W2.setCell(i / BRICK_SIZE, j / BRICK_SIZE, 30);
			}
			else if (color == 1) {
				glColor3f(c2.getRed(), c2.getGreen(), c2.getBlue());
				W2.setCell(i / BRICK_SIZE, j / BRICK_SIZE, 20);
			}
			else if (color == 2) {
				glColor3f(c3.getRed(), c3.getGreen(), c3.getBlue());
				W2.setCell(i / BRICK_SIZE, j / BRICK_SIZE, 5);
			}
			else if (color == 3) {
				glColor3f(c4.getRed(), c4.getGreen(), c4.getBlue());
				W2.setCell(i / BRICK_SIZE, j / BRICK_SIZE, -5);
			}
			else if (color == 4) {
				glColor3f(c5.getRed(), c5.getGreen(), c5.getBlue());
				W2.setCell(i / BRICK_SIZE, j / BRICK_SIZE, 1);
			}
			else if (color == 5) {
				glColor3f(c6.getRed(), c6.getGreen(), c6.getBlue());
				W2.setCell(i / BRICK_SIZE, j / BRICK_SIZE, -15);
			}
			else {
				glColor3f(c7.getRed(), c7.getGreen(), c7.getBlue());
				W2.setCell(i / BRICK_SIZE, j / BRICK_SIZE, 35);
			}
			cc++;
			drawBrick(i, 0, j, 1);
		}
	}

	// The  ceiling  
	for (int i = 0; i < ROOM_SIZE; i += BRICK_SIZE) {
		for (int j = 0; j < ROOM_SIZE; j += BRICK_SIZE) {
			int color = cc % 7;
			if (color == 0) {
				glColor3f(c1.getRed(), c1.getGreen(), c1.getBlue());
				W5.setCell(i / BRICK_SIZE, j / BRICK_SIZE, 30);
			}
			else if (color == 1) {
				glColor3f(c2.getRed(), c2.getGreen(), c2.getBlue());
				W5.setCell(i / BRICK_SIZE, j / BRICK_SIZE, 20);
			}
			else if (color == 2) {
				glColor3f(c3.getRed(), c3.getGreen(), c3.getBlue());
				W5.setCell(i / BRICK_SIZE, j / BRICK_SIZE, 5);
			}
			else if (color == 3) {
				glColor3f(c4.getRed(), c4.getGreen(), c4.getBlue());
				W5.setCell(i / BRICK_SIZE, j / BRICK_SIZE, -5);
			}
			else if (color == 4) {
				glColor3f(c5.getRed(), c5.getGreen(), c5.getBlue());
				W5.setCell(i / BRICK_SIZE, j / BRICK_SIZE, 1);
			}
			else if (color == 5) {
				glColor3f(c6.getRed(), c6.getGreen(), c6.getBlue());
				W5.setCell(i / BRICK_SIZE, j / BRICK_SIZE, -15);
			}
			else {
				glColor3f(c7.getRed(), c7.getGreen(), c7.getBlue());
				W5.setCell(i / BRICK_SIZE, j / BRICK_SIZE, 35);
			}
			cc++;
			drawBrick(i, ROOM_SIZE, j, 1);

		}
	}
}
void drawShootingStation() {

	glColor3f(0.5, 0.5, 0.5);
	glTranslatef(1.5*ROOM_SIZE , ROOM_SIZE*0.3, ROOM_SIZE / 2);
	glRotatef(90+MovHor, 0, 1, 0);
	glRotatef(MovVer, 1, 0, 0);

	glScaled(0.1, 0.1, 2.0);
	glutWireSphere(5, 20, 20);
}


void drawMissile() {


	glutSolidSphere(0.5, 20, 20);
	
}
void showingScore(int x=10 , int y=10 , int z =10) {

	
	char* result[20];
	sprintf((char*)result, "Score :%d ", score);
	print(x, y, z, (char*)result);
}
void updateScore(float x, float y, float z, int wall) { // wall 1 ->Right  , 2 ->floor , 3 ->Left , 4->Ceil  

	//int numberOfBricks = ROOM_SIZE / BRICK_SIZE; 
	int indeX = ceil(ceil(x) / BRICK_SIZE) - 1;
	int indeY = ceil(ceil(y) / BRICK_SIZE) - 1;
	int indeZ = ceil(ceil(z) / BRICK_SIZE) - 1;
	if (wall == 1) {
		score += W1.getCellPoints(indeX, indeY);
		printf("W1 -> %d , %d\n", indeX, indeY);
	}
	if (wall == 3) {
		score += W3.getCellPoints(indeX, indeY);
		printf("W3 -> %d , %d\n", indeX, indeY);

	}
	if (wall == 2) {
		score += W2.getCellPoints(indeX, indeZ);
		printf("W2 -> %d , %d\n", indeX, indeZ);


	}
	if (wall == 4) {
		score += W5.getCellPoints(indeX, indeZ);
		printf("W5 -> %d , %d\n", indeX, indeZ);

	}

}
void setupCamera() {
	
	if (mode == 0) {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(ROOM_SIZE * 2.3, ROOM_SIZE * 0.5, ROOM_SIZE / 2, 0.0f, ROOM_SIZE / 2, ROOM_SIZE / 2, 0.0f, 1.0f, 0.0f);
	}
	else if (mode == 1) { //simple
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(ROOM_SIZE * 1.3+X0, ROOM_SIZE * 0.5, ROOM_SIZE / 2, 0.0f, ROOM_SIZE / 2, ROOM_SIZE / 2, 0.0f, 1.0f, 0.0f);
	}
	else {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(ROOM_SIZE * 2.0 + X0 - 0.7*ROOM_SIZE, ROOM_SIZE * 0.4, ROOM_SIZE *0.5, X0, Y0, Z0, 0.0f, 1.0f, 0.0f);
	}
	
}
void Display(void) {
	setupCamera();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if (times >= 3) {
		
		if (replay) {
			glPushMatrix();
			drawWalls();
			glPopMatrix();

			glPushMatrix();
			glColor3f(0, 0, 0);
			glTranslatef(X0, Y0, Z0);
			drawMissile();
			glPopMatrix();
		}
		else {
			showingScore(11,5,5);
		}
	}
	else {


		glPushMatrix();
		drawWalls();
		glPopMatrix();



		if (!replay) {
			glPushMatrix();
			drawShootingStation();
			glPopMatrix();
		}


		if (shot || replay) {
			glPushMatrix();
			glColor3f(0, 0, 0);
			glTranslatef(X0, Y0, Z0);
			drawMissile();
			glPopMatrix();
		}

		showingScore(10,10,10);

		glPushMatrix();
		glColor3d(0, 1, 0); // draw black lines       
		axis(20);      // z-axis 
		glPopMatrix();



		glPushMatrix();
		glColor3d(0, 0, 1); // x-axis     
		glRotatef(90, 0, 1, 0);
		axis(20);
		glPopMatrix();

		glPushMatrix();
		glColor3d(1, 0, 0); // y-axis     
		glRotatef(-90, 1, 0, 0);
		axis(20);
		glPopMatrix();
	}
	glFlush();
}



void Anim() {
	if (shot||replay) {
		X0 += stepX; 
		Y0 += stepY	;
		Z0 += stepZ; 
	}
	if (Y0 > ROOM_SIZE || Y0 < 0) {
		if (shot) {
			if (Y0 > ROOM_SIZE) {
				updateScore(X0, ROOM_SIZE, Z0, 4);
			}
			else {
				updateScore(X0, 0, Z0, 2);

			}
		}
		printf("%d\n", score);
		stepY = -stepY; 
	}
	if (Z0 > ROOM_SIZE || Z0 < 0) {
		if (shot) {
			if (Z0 > ROOM_SIZE) {
				updateScore(X0, Y0, ROOM_SIZE, 3);
			}
			else {
				updateScore(X0, Y0, 0, 1);

			}
		}
		printf("%d\n", score);
		stepZ = -stepZ;
	}

	if (X0  <= 0) {
		if (shot)
		//times++;
		shot = false;
		replay = false;
		X0 = ROOM_SIZE; 
		Y0 = ROOM_SIZE*0.25; 
		Z0 = ROOM_SIZE / 2;
		hasBeenShot = true; 
	}

	glutPostRedisplay();
	
	
}

void Controllers(unsigned char k, int x, int y)
{

	if (k == 'h') {
		mode = 0;
	}
	if (k == 'j') {
		mode = 1;
	}
	if (k == 'k') {
		mode = 2;
	}
		if (!shot && !replay) {
			if (k == 'r' && hasBeenShot) {
				a = XReplay - X0;
				b = YReplay - Y0;
				c = ZReplay - Z0;
				stepX = stepReplay * a;
				stepY = stepReplay * b;
				stepZ = stepReplay * c;
				replay = true;
			}
	 
			else if (times < 3) {
				if (k == 'd') {
					MovHor -= 1;
					ZF--;
				}
				if (k == 'a') {
					MovHor += 1;
					ZF++;
				}
				if (k == 'w') {
					MovVer += 1;
					YF++;
				}
				if (k == 's') {
					MovVer -= 1;
					YF--;
				}

				/*printf("%f\n", YF); */
				a = XF - X0;
				b = YF - Y0;
				c = ZF - Z0;
				stepX = step * a;
				stepY = step * b;
				stepZ = step * c;

				if (k == ' ') {
					shot = true;
					XReplay = XF;
					YReplay = YF;
					ZReplay = ZF;

				}
			
		}
	}

}

void main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(1000, 800);
	glutInitWindowPosition(150, 150);

	glutCreateWindow("OpenGL - 3D Template");


	glutDisplayFunc(Display);
	glutIdleFunc(Anim);
	glutKeyboardFunc(Controllers);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, 16 / 9, 0.1f, 300.0f);



	glutMainLoop();
}


