#include <glut.h>
#include <math.h>

#define ROOM_SIZE 10
#define BRICK_SIZE 2

double MovHor = 0; 
double MovVer = 0; 
bool shot = false;


int a = 0;
int b = 0; 
int c = 0; 
float t = 0; 

float X0 = ROOM_SIZE;
float Y0 = 2;
float Z0 = ROOM_SIZE / 2;

float XF = 0;
float YF = ROOM_SIZE/2 ;
float ZF = ROOM_SIZE / 2;
 
float YDrawn = Y0 + t * b; 
float ZDrawn = Z0 + t * c; 

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
void drawRoom() {

	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(ROOM_SIZE /2, ROOM_SIZE /2, ROOM_SIZE /2);
	glutWireCube(ROOM_SIZE);

}

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

	float r1 = 210 / 255.0;
	float g1 = 105 / 255.0;
	float b1 = 30 / 255.0;

	float r2 = 205 / 255.0;
	float g2 = 133 / 255.0;
	float b2 = 63 / 255.0;

	float r3 = 188 / 255.0;
	float g3 = 143 / 255.0;
	float b3 = 143 / 255.0;

	float r4 = 244 / 255.0;
	float g4 = 164 / 255.0;
	float b4 = 96 / 255.0;

	float r5 = 139 / 255.0;
	float g5 = 69 / 255.0;
	float b5 = 19 / 255.0;

	float r6 = 255 / 255.0;
	float g6 = 228 / 255.0;
	float b6 = 181 / 255.0;

	float r7 = 255 / 255.0;
	float g7 = 228 / 255.0;
	float b7 = 225 / 255.0;

	//The Right Wall ; 
	int cc = 0;
	for (int  i = 0; i < ROOM_SIZE; i += BRICK_SIZE) {
		for (int  j = 0; j < ROOM_SIZE; j += BRICK_SIZE) {
			int color =cc%7; 
			float r = 0; 
			float g = 0; 
			float b = 0; 
			
			if (color == 0) {
				 r = r1;
				 g = g1;
				 b = b1;
			}
			else if (color == 1) {
				 r = r2;
				 g = g2;
				 b = b2;
			}
			else if (color == 2) {
				 r = r3;
				 g = g3;
				 b = b3;
			}
			else if (color == 3) {
				 r = r4;
				 g = g4;
				 b = b4;
			}
			else if (color == 4) {
				 r = r5;
				 g = g5;
				 b = b5;
			}
			else if (color == 5) {
				 r = r6;
				 g = g6;
				 b = b6;
			}
			else  {
				 r = r7;
				 g = g7;
				 b = b7;
			}
			cc++; 
			glColor3f(r, g, b);
			drawBrick(i, j, 0 , 0 ); 
		}
	}
	//the Left Wall
	for (int i = 0; i < ROOM_SIZE; i += BRICK_SIZE) {
		for (int j = 0; j < ROOM_SIZE; j += BRICK_SIZE) {
			int color = cc % 7;
			float r = 0;
			float g = 0;
			float b = 0;

			if (color == 0) {
				r = r1;
				g = g1;
				b = b1;
			}
			else if (color == 1) {
				r = r2;
				g = g2;
				b = b2;
			}
			else if (color == 2) {
				r = r3;
				g = g3;
				b = b3;
			}
			else if (color == 3) {
				r = r4;
				g = g4;
				b = b4;
			}
			else if (color == 4) {
				r = r5;
				g = g5;
				b = b5;
			}
			else if (color == 5) {
				r = r6;
				g = g6;
				b = b6;
			}
			else {
				r = r7;
				g = g7;
				b = b7;
			}
			cc++;
			glColor3f(r, g, b);
			drawBrick(i, j, ROOM_SIZE, 0);
		}
	}
	// The Lower Wall 
	for (int i = 0; i < ROOM_SIZE; i += BRICK_SIZE) {
		for (int j = 0; j < ROOM_SIZE; j += BRICK_SIZE) {
			int color = cc % 7;
			float r = 0;
			float g = 0;
			float b = 0;

			if (color == 0) {
				r = r1;
				g = g1;
				b = b1;
			}
			else if (color == 1) {
				r = r2;
				g = g2;
				b = b2;
			}
			else if (color == 2) {
				r = r3;
				g = g3;
				b = b3;
			}
			else if (color == 3) {
				r = r4;
				g = g4;
				b = b4;
			}
			else if (color == 4) {
				r = r5;
				g = g5;
				b = b5;
			}
			else if (color == 5) {
				r = r6;
				g = g6;
				b = b6;
			}
			else {
				r = r7;
				g = g7;
				b = b7;
			}
			cc++;
			glColor3f(r, g, b);
			drawBrick(i, 0, j, 1);
		}
	}
	// The upper Wall 
	for (int i = 0; i < ROOM_SIZE; i += BRICK_SIZE) {
		for (int j = 0; j < ROOM_SIZE; j += BRICK_SIZE) {
			int color = cc % 7;
			float r = 0;
			float g = 0;
			float b = 0;

			if (color == 0) {
				r = r1;
				g = g1;
				b = b1;
			}
			else if (color == 1) {
				r = r2;
				g = g2;
				b = b2;
			}
			else if (color == 2) {
				r = r3;
				g = g3;
				b = b3;
			}
			else if (color == 3) {
				r = r4;
				g = g4;
				b = b4;
			}
			else if (color == 4) {
				r = r5;
				g = g5;
				b = b5;
			}
			else if (color == 5) {
				r = r6;
				g = g6;
				b = b6;
			}
			else {
				r = r7;
				g = g7;
				b = b7;
			}
			cc++;
			glColor3f(r, g, b);
			drawBrick(i, ROOM_SIZE, j, 1);

		}
	}
}
void drawShootingStation() {

	glColor3f(0.5, 0.5, 0.5);
	glTranslatef(ROOM_SIZE + 5, ROOM_SIZE*0.3, ROOM_SIZE / 2);
	glRotatef(90+MovHor, 0, 1, 0);
	glRotatef(MovVer, 1, 0, 0);

	glScaled(0.1, 0.1, 2.0);
	glutWireSphere(5, 20, 20);
}

//
//void drawLaserPoint() {
//	if ()
//	drawCircle(); 
//}
void drawMissile() {

	glColor3f(0.5, 0.5, 0.5);

	glTranslatef(X0 + t*a, YDrawn, ZDrawn);

	glutSolidSphere(1, 20, 20);
	
}
void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glPushMatrix(); 
	drawRoom(); 
	glPopMatrix(); 


	glPushMatrix();
	//drawWalls();
	glPopMatrix();
	


	glPushMatrix();
	drawShootingStation(); 
	glPopMatrix();


	if (shot) {
		glPushMatrix();
		drawMissile();
		glPopMatrix();
	}






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
	glFlush();
}

void Anim() {
	if (shot)
		t+=0.005;
	else
		t = 0; 


	if ( Y0 + t * b < 0)
		YDrawn  = -(Y0+t*b); 
	else if (Y0 + t * b > ROOM_SIZE) {
		YDrawn = -((Y0 + t * b) - ROOM_SIZE) + ROOM_SIZE;
	}
	else {
		YDrawn = (Y0 + t * b);
	}


	if (Z0 + t * c < 0)
		ZDrawn = -(Z0+t*c);
	else if (Z0 + t * c > ROOM_SIZE) {
		ZDrawn = -((Z0 + t * c)-ROOM_SIZE) + ROOM_SIZE;
	}
	else {
		ZDrawn = (Z0 + t * c);
	}


	if (X0 + t * a <= 0) {
		shot = false;
	}

	glutPostRedisplay();
	
	
}

void Controllers(unsigned char k, int x, int y)
{
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
	a = XF - X0; 
	b = YF - Y0; 
	c = ZF - Z0; 

	YDrawn = Y0 + t * b;
	ZDrawn = Z0 + t * c;
	if (k == ' ')
		shot = true;

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

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(18.0f, ROOM_SIZE*0.5, ROOM_SIZE / 2, 0.0f, ROOM_SIZE / 2, ROOM_SIZE / 2, 0.0f, 1.0f, 0.0f);

	glutMainLoop();
}
