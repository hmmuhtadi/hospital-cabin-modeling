#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include<GL/glut.h>

#define BLACK 0, 0, 0
#define WHITE 1, 1, 1
#define PI 3.141592654

#define ROOM_LENGTH 400
#define ROOM_WIDTH  400
#define ROOM_HEIGHT 150


#define BED_LENGTH  90
#define BED_WIDTH 240
#define BED_HEIGHT 14



#define TABLE_HEIGHT 35
#define TABLE_WIDTH 6
#define TABLE_RAD 16

#define PILLOW_LENGTH  70
#define PILLOW_WIDTH 50

#define WHEEL_1_RAD  20
#define WHEEL_2_RAD  15

#define WHEEL_CHAIR_LENGTH  52
#define WHEEL_CHAIR_WIDTH 36
#define WHEEL_CHAIR_HEIGHT 30

#define SALINE_STAND_HEIGHT 130

double BED_X, BED_Y, BED_Z;
double BED_SLIDING_ANGLE_1, BED_SLIDING_ANGLE_2, DELTA_BED_SLIDING_ANGLE_1;
double WHEEL_ROTATING_ANGLE;
double WHEEL_X, WHEEL_Y, WHEEL_Z, FOOT_REST_ROTATION_ANGEL, BED_X_AXIS_VAL, CAMERA_ANGEL;

int BED_SIDE_RELLING_LEN;
int BED_END_RELLING_LEN;
double CAMERA_ANGLE;
double CAMERA_HEIGHT;
double CAMERA_RAD;
double CAMERA_SPEED;

void Box(double x, double y, double z, double l, double w, double h)
{
	glBegin(GL_QUADS); {
		glVertex3f(x, y + w, z + h);
		glVertex3f(x + l, y + w, z + h);
		glVertex3f(x + l, y + w, z);
		glVertex3f(x, y + w, z);
	}glEnd();
	glBegin(GL_QUADS); {
		glVertex3f(x + l, y + w, z + h);
		glVertex3f(x + l, y + w, z);
		glVertex3f(x + l, y, z);
		glVertex3f(x + l, y, z + h);
	}glEnd();
	glBegin(GL_QUADS); {
		glVertex3f(x, y + w, z + h);
		glVertex3f(x + l, y + w, z + h);
		glVertex3f(x + l, y, z + h);
		glVertex3f(x, y, z + h);
	}glEnd();
	glBegin(GL_QUADS); {
		glVertex3f(x, y, z + h);
		glVertex3f(x, y, z);
		glVertex3f(x + l, y, z);
		glVertex3f(x + l, y, z + h);
	}glEnd();
	glBegin(GL_QUADS); {
		glVertex3f(x, y + w, z + h);
		glVertex3f(x, y + w, z);
		glVertex3f(x, y, z);
		glVertex3f(x, y, z + h);
	}glEnd();
	glBegin(GL_QUADS); {
		glVertex3f(x, y, z);
		glVertex3f(x + l, y, z);
		glVertex3f(x + l, y + w, z);
		glVertex3f(x, y + w, z);
	}glEnd();
}
void DrawCylinder(float height, double rad)
{
	GLUquadricObj* cyl1;
	cyl1 = gluNewQuadric();
	gluQuadricDrawStyle(cyl1, GLU_FILL);
	gluCylinder(cyl1, rad, rad, height, 100, 100);
}
void DrawDisk(double rad, double inner_rad)
{

	GLUquadricObj* cyl1;
	cyl1 = gluNewQuadric();
	gluQuadricDrawStyle(cyl1, GLU_FILL);
	gluDisk(cyl1, inner_rad, rad, 100, 100);
}

void Box_with_border(double x, double y, double z, double l, double w, double h)
{
	glBegin(GL_QUADS); {
		glVertex3f(x, y + w, z + h);
		glVertex3f(x + l, y + w, z + h);
		glVertex3f(x + l, y + w, z);
		glVertex3f(x, y + w, z);
	}glEnd();
	glBegin(GL_QUADS); {
		glVertex3f(x + l, y + w, z + h);
		glVertex3f(x + l, y + w, z);
		glVertex3f(x + l, y, z);
		glVertex3f(x + l, y, z + h);
	}glEnd();
	glBegin(GL_QUADS); {
		glVertex3f(x, y + w, z + h);
		glVertex3f(x + l, y + w, z + h);
		glVertex3f(x + l, y, z + h);
		glVertex3f(x, y, z + h);
	}glEnd();
	glBegin(GL_QUADS); {
		glVertex3f(x, y, z + h);
		glVertex3f(x, y, z);
		glVertex3f(x + l, y, z);
		glVertex3f(x + l, y, z + h);
	}glEnd();
	glBegin(GL_QUADS); {
		glVertex3f(x, y + w, z + h);
		glVertex3f(x, y + w, z);
		glVertex3f(x, y, z);
		glVertex3f(x, y, z + h);
	}glEnd();
	glBegin(GL_QUADS); {
		glVertex3f(x, y, z);
		glVertex3f(x + l, y, z);
		glVertex3f(x + l, y + w, z);
		glVertex3f(x, y + w, z);
	}glEnd();

	//////////////////////////borders//////////////////////////////
	glColor3f(0, 0, 0);
	glBegin(GL_LINES); {
		//floor borders
		glVertex3f(x, y, z);
		glVertex3f(x + l, y, z);

		glVertex3f(x + l, y, z);
		glVertex3f(x + l, y + w, z);

		glVertex3f(x + l, y + w, z);
		glVertex3f(x, y + w, z);

		glVertex3f(x, y + w, z);
		glVertex3f(x, y, z);
		//ceilling borders
		glVertex3f(x, y, z + h);
		glVertex3f(x + l, y, z + h);

		glVertex3f(x + l, y, z + h);
		glVertex3f(x + l, y + w, z + h);

		glVertex3f(x + l, y + w, z + h);
		glVertex3f(x, y + w, z + h);

		glVertex3f(x, y + w, z + h);
		glVertex3f(x, y, z + h);
		//left side walls borders

		glVertex3f(x, y, z);
		glVertex3f(x, y + w, z);

		glVertex3f(x, y + w, z);
		glVertex3f(x, y + w, z + h);

		glVertex3f(x, y + w, z + h);
		glVertex3f(x, y, z + h);

		glVertex3f(x, y, z + h);
		glVertex3f(x, y, z);

		//right side walls borders

		glVertex3f(x + l, y, z);
		glVertex3f(x + l, y + w, z);

		glVertex3f(x + l, y + w, z);
		glVertex3f(x + l, y + w, z + h);

		glVertex3f(x + l, y + w, z + h);
		glVertex3f(x + l, y, z + h);

		glVertex3f(x + l, y, z + h);
		glVertex3f(x + l, y, z);

	}glEnd();


}

void drawSalineStand(float x, float y, float z)
{
	//Box_with_border(x,y ,z ,3 ,3 , SALINE_STAND_HEIGHT);
	//main cylinder
	glPushMatrix();
	glTranslatef(x, y, z);
	glColor3f(.6, .6, .6);
	DrawCylinder(SALINE_STAND_HEIGHT, 1.5);
	glPopMatrix();
	//base disk
	glPushMatrix();
	glTranslatef(x, y, z + 4);
	glColor3f(.55, .55, .55);
	DrawDisk(7, 1);
	glPopMatrix();
	//////////////////

	glPushMatrix();
	glColor3f(.6, .6, .6);
	glTranslatef(x, y, z);
	glRotatef(90, 0, 0, 1);
	Box_with_border(0, 1, 0, 20, -3, 2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.6, .6, .6);
	glTranslatef(x, y, z);
	glRotatef(210, 0, 0, 1);
	Box_with_border(0, 0, 0, 20, -3, 2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.6, .6, .6);
	glTranslatef(x, y, z);
	glRotatef(330, 0, 0, 1);
	Box_with_border(0, 0, 0, 20, 3, 2);
	glPopMatrix();

	//base cylinder
	glPushMatrix();
	glTranslatef(x, y, z);
	glColor3f(.6, .6, .6);
	DrawCylinder(4, 7);
	glPopMatrix();

	//hook
	glColor3f(.6, .6, .6);
	Box_with_border(x - 12, y, z + SALINE_STAND_HEIGHT - 10, 24, .5, .5);
	//hook to saline
	glColor3f(.6, .6, .6);
	Box_with_border(x - 10, y, z + SALINE_STAND_HEIGHT - 10, .05, .05, -12);
	//sphere
	glPushMatrix();
	glTranslatef(x - 10, y, z + SALINE_STAND_HEIGHT - 20);
	glColor3f(.75, .75, .75);
	glutSolidSphere(3, 16, 16);
	glPopMatrix();
	//upper small sphere
	glPushMatrix();
	glTranslatef(x - 10, y, z + SALINE_STAND_HEIGHT - 20 + 3);
	glColor3f(.75, .75, .75);
	glutSolidSphere(.75, 16, 16);
	glPopMatrix();


	//saline cylinder
	glPushMatrix();
	glTranslatef(x - 10, y, z + SALINE_STAND_HEIGHT - 30);
	glColor3f(.6, .6, .6);
	DrawCylinder(10, 3);
	glPopMatrix();
	//sphere
	glPushMatrix();
	glTranslatef(x - 10, y, z + SALINE_STAND_HEIGHT - 30);
	glColor3f(.75, .75, .75);
	glutSolidSphere(3, 16, 16);
	glPopMatrix();


}
void DrawFirstSlider(float x, float y, float z, float length, float width, float height)
{
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(x, y, z);
	glRotatef(BED_SLIDING_ANGLE_1, 1, 0, 0);
	Box_with_border(0, 0, 0, length, width, height);
	glPopMatrix();
}

void DrawSecondSlider(float x, float y, float z, float length, float width, float height)//(float x1,float y1,float z1,float firstSliderLength,float secondSliderLength,float width)
{
	glPushMatrix();

	glColor3f(1, 1, 1);
	glTranslatef(x, y, z);
	glRotatef(BED_SLIDING_ANGLE_1, 1, 0, 0);
	glTranslatef(0, BED_WIDTH / 4, 0);
	glRotatef(BED_SLIDING_ANGLE_2, 1, 0, 0);
	Box_with_border(0, 0, 0, length, width, height);
	glColor3f(.95, .95, .95);
	Box_with_border(10, 5, BED_HEIGHT, PILLOW_LENGTH, 50, 9);
	glPopMatrix();

}

void DrawRoom()
{
	//floor
	glColor3f(1, .8, .6);
	//glColor3f(.98,	.98,	.9);  
	glBegin(GL_QUADS); {
		glVertex3f(-ROOM_LENGTH / 2, -ROOM_WIDTH / 2, 0);
		glVertex3f(ROOM_LENGTH / 2, -ROOM_WIDTH / 2, 0);
		glVertex3f(ROOM_LENGTH / 2, ROOM_WIDTH / 2, 0);
		glVertex3f(-ROOM_LENGTH / 2, ROOM_WIDTH / 2, 0);
	}glEnd();
	//front wall
	glColor3f(.98, .98, .94);
	glBegin(GL_QUADS); {
		glVertex3f(-ROOM_LENGTH / 2, -ROOM_WIDTH / 2, 0);
		glVertex3f(ROOM_LENGTH / 2, -ROOM_WIDTH / 2, 0);
		glVertex3f(ROOM_LENGTH / 2, -ROOM_WIDTH / 2, ROOM_HEIGHT);
		glVertex3f(-ROOM_LENGTH / 2, -ROOM_WIDTH / 2, ROOM_HEIGHT);
	}glEnd();


	//left wall
	//glColor3f(.9,	.9,	.9);     
	glColor3f(.98, .98, .9);
	glBegin(GL_QUADS); {
		glVertex3f(-ROOM_LENGTH / 2, -ROOM_WIDTH / 2, 0);
		glVertex3f(-ROOM_LENGTH / 2, -ROOM_WIDTH / 2, ROOM_HEIGHT);
		glVertex3f(-ROOM_LENGTH / 2, ROOM_WIDTH / 2, ROOM_HEIGHT);
		glVertex3f(-ROOM_LENGTH / 2, ROOM_WIDTH / 2, 0);
	}glEnd();

	glColor3f(.2, .2, .2);
	Box(-ROOM_LENGTH / 2, -210, 0, 1, 420, 1);
	//back wall
	//glColor3f(.85,	.85,	.85);  
	glColor3f(.98, .98, .94);
	glBegin(GL_QUADS); {
		glVertex3f(-ROOM_LENGTH / 2, ROOM_WIDTH / 2, 0);
		glVertex3f(-ROOM_LENGTH / 2, ROOM_WIDTH / 2, ROOM_HEIGHT);
		glVertex3f(ROOM_LENGTH / 2, ROOM_WIDTH / 2, ROOM_HEIGHT);
		glVertex3f(ROOM_LENGTH / 2, ROOM_WIDTH / 2, 0);
	}glEnd();
	glColor3f(.2, .2, .2);
	Box(-ROOM_LENGTH / 2, ROOM_WIDTH / 2 - 1, 0, 420, 23, 1);

	//right wall
	//glColor3f(.8,	.8,	.8); 
	glColor3f(.98, .98, .9);
	glBegin(GL_QUADS); {
		glVertex3f(ROOM_LENGTH / 2, ROOM_WIDTH / 2, 0);
		glVertex3f(ROOM_LENGTH / 2, ROOM_WIDTH / 2, ROOM_HEIGHT);
		glVertex3f(ROOM_LENGTH / 2, -ROOM_WIDTH / 2, ROOM_HEIGHT);
		glVertex3f(ROOM_LENGTH / 2, -ROOM_WIDTH / 2, 0);
	}glEnd();
	glColor3f(.2, .2, .2);
	Box(ROOM_LENGTH / 2 - 1, -ROOM_WIDTH / 2, 0, 1, 420, 1);
	//ceilling
	glColor3f(0, .2, .4);
	glBegin(GL_QUADS); {
		glVertex3f(-ROOM_LENGTH / 2, -ROOM_WIDTH / 2, ROOM_HEIGHT);
		glVertex3f(ROOM_LENGTH / 2, -ROOM_WIDTH / 2, ROOM_HEIGHT);
		glVertex3f(ROOM_LENGTH / 2, ROOM_WIDTH / 2, ROOM_HEIGHT);
		glVertex3f(-ROOM_LENGTH / 2, ROOM_WIDTH / 2, ROOM_HEIGHT);
	}glEnd();
	////////////////////////////////////////////borders between walls////////////////////////////////////////////////////////
	glColor3f(0, 0, 0);
	glBegin(GL_LINES); {
		//floor borders
		glVertex3f(-ROOM_LENGTH / 2, -ROOM_WIDTH / 2, 0);
		glVertex3f(-ROOM_LENGTH / 2, ROOM_WIDTH / 2, 0);

		glVertex3f(-ROOM_LENGTH / 2, -ROOM_WIDTH / 2, 0);
		glVertex3f(ROOM_LENGTH / 2, -ROOM_WIDTH / 2, 0);

		glVertex3f(ROOM_LENGTH / 2, -ROOM_WIDTH / 2, 0);
		glVertex3f(ROOM_LENGTH / 2, ROOM_WIDTH / 2, 0);

		glVertex3f(ROOM_LENGTH / 2, ROOM_WIDTH / 2, 0);
		glVertex3f(-ROOM_LENGTH / 2, ROOM_WIDTH / 2, 0);

		//ceilling borders
		glVertex3f(-ROOM_LENGTH / 2, -ROOM_WIDTH / 2, ROOM_HEIGHT);
		glVertex3f(-ROOM_LENGTH / 2, ROOM_WIDTH / 2, ROOM_HEIGHT);

		glVertex3f(-ROOM_LENGTH / 2, -ROOM_WIDTH / 2, ROOM_HEIGHT);
		glVertex3f(ROOM_LENGTH / 2, -ROOM_WIDTH / 2, ROOM_HEIGHT);

		glVertex3f(ROOM_LENGTH / 2, -ROOM_WIDTH / 2, ROOM_HEIGHT);
		glVertex3f(ROOM_LENGTH / 2, ROOM_WIDTH / 2, ROOM_HEIGHT);

		glVertex3f(ROOM_LENGTH / 2, ROOM_WIDTH / 2, ROOM_HEIGHT);
		glVertex3f(-ROOM_LENGTH / 2, ROOM_WIDTH / 2, ROOM_HEIGHT);
		//side walls borders

		glVertex3f(-ROOM_LENGTH / 2, -ROOM_WIDTH / 2, 0);
		glVertex3f(-ROOM_LENGTH / 2, -ROOM_WIDTH / 2, ROOM_HEIGHT);

		glVertex3f(ROOM_LENGTH / 2, -ROOM_WIDTH / 2, 0);
		glVertex3f(ROOM_LENGTH / 2, -ROOM_WIDTH / 2, ROOM_HEIGHT);

		glVertex3f(ROOM_LENGTH / 2, ROOM_WIDTH / 2, 0);
		glVertex3f(ROOM_LENGTH / 2, ROOM_WIDTH / 2, ROOM_HEIGHT);

		glVertex3f(-ROOM_LENGTH / 2, ROOM_WIDTH / 2, 0);
		glVertex3f(-ROOM_LENGTH / 2, ROOM_WIDTH / 2, ROOM_HEIGHT);

	}glEnd();

}
void drawBedSideRelling(int x, int y, int z, int l, int number, int h, int gap, int totLen)
{
	glColor3f(.75, .75, .75);
	int localY = y;
	for (int i = 0; i< number; i++)
	{
		Box_with_border(x, localY, z, l, l, h);
		localY += l + gap;
		glColor3f(.75, .75, .75);
	}
	Box_with_border(x, y, z + h, l, totLen, l * 2);

}
void drawBedEndRelling(int x, int y, int z, int l, int number, int h, int gap, int totLen)
{
	glColor3f(.75, .75, .75);
	int localX = x;
	for (int i = 0; i< number; i++)
	{
		Box_with_border(localX, y, z, l, l, h);
		localX += l + gap;
		glColor3f(.75, .75, .75);
	}
	Box_with_border(x, y, z + h, totLen, l, l * 2);

}

void drawWheel(float x, float y, float z, int rad)
{

	//outer cylinder of wheel1
	glPushMatrix(); {
		glTranslatef(x, y, rad);
		glRotatef(90, 0, -1, 0);
		glRotatef(WHEEL_ROTATING_ANGLE, 0, 0, 1);
		glColor3f(.2, .2, .2);
		DrawCylinder(4, rad);


		//inner cylinder of wheel1

		glColor3f(.2, .2, .2);
		DrawCylinder(4, rad - 3);


		//spokes

		glColor3f(.6, .6, .6);
		Box_with_border(0, -rad, z + 2, 1, rad * 2, 1);
		glColor3f(.6, .6, .6);
		Box_with_border(rad, 0, z + 2, -rad * 2, 1, 1);

	}glPopMatrix();

	//disk1
	glColor3f(.6, .6, .6);
	glPushMatrix(); {
		glTranslatef(x, y, rad);
		glRotatef(90, 0, -1, 0);
		glRotatef(WHEEL_ROTATING_ANGLE, 0, 0, 1);
		DrawDisk(rad, rad - 3);
	}glPopMatrix();

	//disk 2
	glColor3f(.6, .6, .6);
	glPushMatrix(); {
		glTranslatef(x - 4, y, rad);
		glRotatef(90, 0, 1, 0);
		glRotatef(WHEEL_ROTATING_ANGLE, 0, 0, 1);
		DrawDisk(rad, rad - 3);
	}glPopMatrix();
}
void drawWheel1(float x, float y, float z, int rad)
{

	//outer cylinder of wheel1
	glPushMatrix(); {
		glTranslatef(x, y, rad);
		glRotatef(90, 0, -1, 0);
		glRotatef(WHEEL_ROTATING_ANGLE, 0, 0, 1);
		glColor3f(.2, .2, .2);
		DrawCylinder(4, rad);


		//inner cylinder of wheel1

		glColor3f(.2, .2, .2);
		DrawCylinder(4, rad - 3);


		//spokes

		glColor3f(.6, .6, .6);
		Box_with_border(0, -rad, z + 2, 1, rad * 2, 1);
		glColor3f(.6, .6, .6);
		Box_with_border(rad, 0, z + 2, -rad * 2, 1, 1);

	}glPopMatrix();

	//disk1
	glColor3f(.55, .55, .55);
	glPushMatrix(); {
		glTranslatef(x, y, rad);
		glRotatef(90, 0, -1, 0);
		glRotatef(WHEEL_ROTATING_ANGLE, 0, 0, 1);
		DrawDisk(rad, 1);
	}glPopMatrix();

	//disk 2
	glColor3f(.55, .55, .55);
	glPushMatrix(); {
		glTranslatef(x - 4, y, rad);
		glRotatef(90, 0, 1, 0);
		glRotatef(WHEEL_ROTATING_ANGLE, 0, 0, 1);
		DrawDisk(rad, 1);
	}glPopMatrix();
}
void drawBedStand(float x, float y, float z)
{

	glPushMatrix(); {
		glTranslatef(x, y, 5);
		glRotatef(90, 0, 1, 0);
		glColor3f(.2, .2, .2);
		DrawCylinder(3, 5);
	}glPopMatrix();

	glColor3f(0, .87, .87);
	glPushMatrix(); {
		glTranslatef(x + 3, y, 5);
		glRotatef(90, 0, 1, 0);
		glColor3f(.2, .2, .2);
		DrawDisk(5, 1);
		glColor3f(.4, .4, .4);
		Box_with_border(0, -1, 0, -10, 1, 1);

	}glPopMatrix();

	glColor3f(.2, .2, .2);
	glPushMatrix(); {
		glTranslatef(x, y, 5);
		glRotatef(90, 0, 1, 0);
		DrawDisk(5, 1);
		glColor3f(.4, .4, .4);
		Box_with_border(0, -1, -1, -10, 1, 1);
		glColor3f(.75, .75, .75);
		Box_with_border(-10, -4, -2, -25, 8, 8);

	}glPopMatrix();
}
void drawBed()
{
	//glColor3f(.87,	.87,	.87);
	glColor3f(1, 1, 1);

	double x = BED_X;//previous 30
	double y = BED_Y;//prev 35
	double z = BED_Z;
	Box_with_border(x, y, z, BED_LENGTH, BED_WIDTH / 2, BED_HEIGHT);

	glColor3f(1, 1, 1);
	//Box_with_border(x,y + BED_WIDTH/2 ,z ,BED_LENGTH ,BED_WIDTH /4 , BED_HEIGHT);
	DrawFirstSlider(x, y + BED_WIDTH / 2, z, BED_LENGTH, BED_WIDTH / 4, BED_HEIGHT);
	DrawSecondSlider(x, y + BED_WIDTH / 2, z, BED_LENGTH, BED_WIDTH / 4, BED_HEIGHT);

	//base of bed
	glColor3f(.75, .75, .75);
	Box_with_border(x - 4, y - 4, 33, BED_LENGTH + 8, BED_WIDTH + 8, 7);

	//side relling
	glColor3f(.75, .75, .75);
	drawBedSideRelling(x + BED_LENGTH + 1, y + BED_WIDTH / 2 - BED_SIDE_RELLING_LEN / 2, 33, 2, 8, 30, 6, BED_SIDE_RELLING_LEN);
	drawBedSideRelling(x - 3, y + BED_WIDTH / 2 - BED_SIDE_RELLING_LEN / 2, 33, 2, 8, 30, 6, BED_SIDE_RELLING_LEN);

	//payer diker relling
	drawBedEndRelling(x, y - 3, 33, 2, 9, 30, 9, BED_END_RELLING_LEN);
	drawBedEndRelling(x, y + 1 + BED_WIDTH, 33, 2, 9, 40, 9, BED_END_RELLING_LEN);



	drawBedStand(BED_X, BED_Y, BED_Z);
	drawBedStand(BED_X + BED_LENGTH - 4, BED_Y, BED_Z);
	drawBedStand(BED_X + BED_LENGTH - 4, BED_Y + BED_WIDTH - 4, BED_Z);
	drawBedStand(BED_X, BED_Y + BED_WIDTH - 4, BED_Z);
}



void MoveAntiClockWiseSliding1()
{
	if (BED_SLIDING_ANGLE_1 + 2 >= 35)
		return;
	BED_SLIDING_ANGLE_1 += 2;
	glutPostRedisplay();
}

void MoveClockWiseSliding1()
{
	if (BED_SLIDING_ANGLE_1 - 2<0)
		return;
	BED_SLIDING_ANGLE_1 -= 2;
	glutPostRedisplay();
}

void MoveAntiClockWiseSliding2()
{
	if (BED_SLIDING_ANGLE_2 + 2>30)
		return;
	BED_SLIDING_ANGLE_2 += 2;
	glutPostRedisplay();
}
void MoveClockWiseSliding2()
{
	if (BED_SLIDING_ANGLE_2 - 2<0)
		return;
	BED_SLIDING_ANGLE_2 -= 2;
	glutPostRedisplay();
}

void MoveWheelChairForward()
{
	if (WHEEL_ROTATING_ANGLE + 5 >= 360)
		WHEEL_ROTATING_ANGLE = 0;
	else
		WHEEL_ROTATING_ANGLE = WHEEL_ROTATING_ANGLE + 5;

	WHEEL_Y = WHEEL_Y + 5 * (2 * 3.1416*WHEEL_1_RAD / 360);
	glutPostRedisplay();
}


void MoveWheelChairBackward()
{
	if (WHEEL_ROTATING_ANGLE - 5<0)
		WHEEL_ROTATING_ANGLE = 360;
	else
		WHEEL_ROTATING_ANGLE = WHEEL_ROTATING_ANGLE - 5;
	WHEEL_Y = WHEEL_Y - 5 * (2 * 3.1416*WHEEL_1_RAD / 360);
	glutPostRedisplay();
}

void RotateFootStandClockwise()
{
	if (FOOT_REST_ROTATION_ANGEL + 1>20)
		return;
	FOOT_REST_ROTATION_ANGEL = FOOT_REST_ROTATION_ANGEL + 1;
	glutPostRedisplay();
}


void RotateFootStandAntiClockwise()
{
	if (FOOT_REST_ROTATION_ANGEL - 1<-10)
		return;
	FOOT_REST_ROTATION_ANGEL = FOOT_REST_ROTATION_ANGEL - 1;
	glutPostRedisplay();
}
void MoveBedForward()
{
	if (BED_Y + BED_WIDTH + 1 > ROOM_WIDTH / 2 - 10)
		return;
	BED_Y += 1;
	glutPostRedisplay();
}

void MoveBedBackward()
{
	if (BED_Y - 1 < -ROOM_WIDTH / 2 + 10)
		return;
	BED_Y -= 1;
	glutPostRedisplay();
}
void keyboardListener(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		MoveAntiClockWiseSliding1();
		break;
	case '2':
		MoveClockWiseSliding1();
		break;
	case '3':
		MoveAntiClockWiseSliding2();
		break;
	case '4':
		MoveClockWiseSliding2();
		break;
	case '5':
		MoveWheelChairForward();
		break;
	case '6':
		MoveWheelChairBackward();
		break;
	case '7':
		RotateFootStandClockwise();
		break;
	case '8':
		RotateFootStandAntiClockwise();
		break;
	case '9':
		MoveBedForward();
		break;
	case '0':
		MoveBedBackward();
		break;
	case 'f':
		CAMERA_SPEED -= .01;
		break;
	case 'g':
		CAMERA_SPEED += .01;
		break;
	case 'a':
		CAMERA_RAD += 1;
		break;
	case 'd':
		CAMERA_RAD -= 1;
		break;
	case 'w':
		CAMERA_HEIGHT += 1;
		break;
	case 's':
		CAMERA_HEIGHT -= 1;
		break;
	default:
		break;
	}
}

void drawTable(double x, double y, double z)
{
	glPushMatrix(); {
		glTranslatef(x - TABLE_RAD * 2 + 3, y, z);
		glColor3f(.2, .2, .2);
		DrawCylinder(TABLE_HEIGHT, 2);
	}glPopMatrix();

	glPushMatrix(); {
		glTranslatef(x + TABLE_RAD * 2 - 3 - 2, y, z);
		glColor3f(.2, .2, .2);
		DrawCylinder(TABLE_HEIGHT, 2);
	}glPopMatrix();

	glPushMatrix(); {
		glTranslatef(x, y + TABLE_RAD*1.4 - 3 - 2, z);
		glColor3f(.2, .2, .2);
		DrawCylinder(TABLE_HEIGHT, 2);
	}glPopMatrix();

	glPushMatrix(); {
		glTranslatef(x, y - TABLE_RAD*1.4 + 3, z);
		glColor3f(.2, .2, .2);
		DrawCylinder(TABLE_HEIGHT, 2);
	}glPopMatrix();
	//base cylinder
	glPushMatrix(); {
		glTranslatef(x, y, z + TABLE_HEIGHT);

		glColor3f(.2, .2, .2);
		glScalef(2, 1.4, 1);
		DrawCylinder(TABLE_WIDTH, TABLE_RAD);
	}glPopMatrix();

	//tabler uporer disk
	glPushMatrix(); {
		glTranslatef(x, y, z + TABLE_HEIGHT + TABLE_WIDTH);
		glColor3f(.3, .2, 0);
		glScalef(2, 1.4, 1);
		DrawDisk(TABLE_RAD - 2, 0);
	}glPopMatrix();

	glPushMatrix(); {
		glTranslatef(x, y, z + TABLE_HEIGHT + TABLE_WIDTH);
		glColor3f(.4, .2, 0);
		glScalef(2, 1.4, 1);
		DrawDisk(TABLE_RAD, TABLE_RAD - 2);
	}glPopMatrix();


	//table er nicher disk
	glPushMatrix(); {
		glTranslatef(x, y, z + TABLE_HEIGHT);
		glColor3f(.4, .2, 0);
		glScalef(2, 1.4, 1);
		DrawDisk(TABLE_RAD, 0);
	}glPopMatrix();

}
void drawWheelChair(double x, double y, double z)
{
	drawWheel(x, y, z, WHEEL_1_RAD);
	drawWheel(x + WHEEL_CHAIR_LENGTH, y, z, WHEEL_1_RAD);

	drawWheel1(x, y - WHEEL_CHAIR_WIDTH, z, 7);
	drawWheel1(x + WHEEL_CHAIR_LENGTH, y - WHEEL_CHAIR_WIDTH, z, 7);

	glColor3f(.2, .2, .2);
	glPushMatrix();
	{

		glTranslatef(x - 4, y, z);
		glRotatef(90, 0, 1, 0);

		//draw seat
		glColor3f(0, .2, .4);
		Box_with_border(-WHEEL_1_RAD * 2, 1, (4 + 2), -5, -WHEEL_CHAIR_WIDTH, WHEEL_CHAIR_LENGTH - 8);
		//draw back of the seat
		glColor3f(0, .2, .3);
		Box_with_border(-WHEEL_1_RAD * 2 - 5, 1, 4 + 2, -WHEEL_CHAIR_HEIGHT, -3, WHEEL_CHAIR_LENGTH - 8);

		//thelar handle
		glColor3f(0, .2, .3);
		Box_with_border(-WHEEL_1_RAD * 2 - WHEEL_CHAIR_HEIGHT, 1, 4 + 2 + 2, 2, 8, 2);

		glColor3f(0, .2, .3);
		Box_with_border(-WHEEL_1_RAD * 2 - WHEEL_CHAIR_HEIGHT, 1, 4 + WHEEL_CHAIR_LENGTH - 8, 2, 8, -2);

		//draw handles
		//right
		glColor3f(.4, .4, .4);
		Box_with_border(-WHEEL_1_RAD * 2 - 18, -2, 4 + 2, -2, -WHEEL_CHAIR_WIDTH, 4);

		//left
		glColor3f(.4, .4, .4);
		Box_with_border(-WHEEL_1_RAD * 2 - 18, -2, 4 + 2 + WHEEL_CHAIR_LENGTH - 8, -2, -WHEEL_CHAIR_WIDTH, -4);

		glColor3f(.4, .4, .4);
		Box_with_border(-WHEEL_1_RAD * 2, -WHEEL_CHAIR_WIDTH + 5, 4 + 2 + 1, -18, 2, 2);

		glColor3f(.4, .4, .4);
		Box_with_border(-WHEEL_1_RAD * 2, -WHEEL_CHAIR_WIDTH + 5, 4 + 2 + WHEEL_CHAIR_LENGTH - 8 - 1, -18, 2, -2);

		//boro wheel r chair er connector
		//daner
		glColor3f(.4, .4, .4);
		Box_with_border(-WHEEL_1_RAD * 2, -1, 4 + 2 + 1, WHEEL_1_RAD, 2, 2);
		//bamer
		glColor3f(.4, .4, .4);
		Box_with_border(-WHEEL_1_RAD * 2, -1, 4 + 2 + WHEEL_CHAIR_LENGTH - 8 - 1, WHEEL_1_RAD, 2, -2);
		//nicher
		glColor3f(.4, .4, .4);
		Box_with_border(-WHEEL_1_RAD + 1, -1, 1, -2, 2, WHEEL_CHAIR_LENGTH + 3);

		//choto chakar connector
		glColor3f(.4, .4, .4);
		Box_with_border(-WHEEL_1_RAD * 2, 1 - WHEEL_CHAIR_WIDTH, 4 + 2 + 1, WHEEL_1_RAD * 2 - 5, 2, 2);

		glColor3f(.4, .4, .4);
		Box_with_border(-WHEEL_1_RAD * 2, 1 - WHEEL_CHAIR_WIDTH, 4 + 2 + WHEEL_CHAIR_LENGTH - 1 - 8, WHEEL_1_RAD * 2 - 5, 2, -2);
		//chhoto chakar nicher connector
		//right
		glColor3f(.4, .4, .4);
		Box_with_border(-7, 1 - WHEEL_CHAIR_WIDTH, 4 + 2 + WHEEL_CHAIR_LENGTH - 1 - 8, 1, -1, 6);

		//left
		glColor3f(.4, .4, .4);
		Box_with_border(-7, 1 - WHEEL_CHAIR_WIDTH, 4 + 2 - 1 + 2, 1, -1, -6);

	}glPopMatrix();

	//foot  stand
	glPushMatrix();
	{
		glTranslatef(x - 4 + 4 + 2 + 3, y + 1 - WHEEL_CHAIR_WIDTH + 2 + 4, z + 7);

		glRotatef(FOOT_REST_ROTATION_ANGEL, 1, 0, 0);
		//right
		glColor3f(.4, .4, .4);
		Box_with_border(0, 0, 0, 15, -18, 1);


	}glPopMatrix();
	glPushMatrix();
	{
		//left
		glTranslatef(x - 4 + 4 + 2 + WHEEL_CHAIR_LENGTH - 26, y + 1 - WHEEL_CHAIR_WIDTH + 2 + 4, z + 7);
		glRotatef(FOOT_REST_ROTATION_ANGEL, 1, 0, 0);
		glColor3f(.4, .4, .4);
		Box_with_border(0, 0, 0, 15, -18, 1);
	}glPopMatrix();
}
void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(BLACK, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	//gluLookAt(200*cos(CAMERA_ANGLE), 200*sin(CAMERA_ANGLE), 100,		0,0,0,		0,0,1);	
	gluLookAt(CAMERA_RAD*cos(CAMERA_ANGLE), CAMERA_RAD*sin(CAMERA_ANGLE), CAMERA_HEIGHT, 0, 0, 0, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);

	DrawRoom();
	drawBed();
	//drawSalineStand(BED_X+ BED_LENGTH + 20, BED_Y + BED_WIDTH +15, 0);
	drawSalineStand(-50, 135, 0);
	drawWheelChair(WHEEL_X, WHEEL_Y, WHEEL_Z);
	drawTable(100, -100, 0);

	glutSwapBuffers();
}

void animate(){

	CAMERA_ANGLE += CAMERA_SPEED;
	glutPostRedisplay();
}

void init(){

	BED_SIDE_RELLING_LEN = 58;
	BED_END_RELLING_LEN = 90;

	BED_X = (-(ROOM_LENGTH / 2) + 40);
	BED_Y = (ROOM_WIDTH / 2 - 80) - BED_WIDTH;
	BED_Z = 40;

	CAMERA_HEIGHT = 100;
	CAMERA_RAD = 180;
	CAMERA_SPEED = .01;

	BED_SLIDING_ANGLE_1 = 0;
	BED_SLIDING_ANGLE_2 = 0;
	WHEEL_ROTATING_ANGLE = 0;


	WHEEL_X = 50;
	WHEEL_Y = 50;
	WHEEL_Z = 0;

	CAMERA_ANGLE = 0;

	glClearColor(BLACK, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, 1, 0.1, 10000.0);

}


int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("Hospital Cabin by Hasib Mohammed Muhtadi (0605033)");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)
	glutKeyboardFunc(keyboardListener);
	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
