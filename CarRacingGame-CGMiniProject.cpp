#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<random>
#include<iostream>
#include<GL/glut.h>
using namespace std;

bool gameStarted = false;
float car_x,road_y,speed=0;
float score = 0;
float obstacles[3][2] = { {-600,-100},
	{-600,100},
	{-600,300}
};
void draw_road(int x, int y) {
	glColor3f(0.2, 0.2, 0.2);
	//printf("Hello world");
	glBegin(GL_POLYGON);
	glVertex2f(-100.0+x, -300.0+y);
	glVertex2f(-100.0+x, 300.0+y);
	glVertex2f(100.0+x, 300.0+y);
	glVertex2f(100.0+x, -300.0+y);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	for (int i = -280; i < 280; i += 40) {
		glVertex2f(0.0+x, i+y);
		glVertex2f(0.0+x, i + 20+y);
	}
	glEnd();
}
void draw_car(int x, int y) {

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(-30.0+x, -50.0+y);
	glVertex2f(-30.0+x, 50.0+y);
	glVertex2f(30.0+x, 50.0+y);
	glVertex2f(30.0+x, -50.0+y);
	glEnd();

	//Front window(grey color)
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex2f(-20.0 + x, 30.0 + y);
	glVertex2f(-10.0 + x, 10.0 + y);
	glVertex2f(10.0 + x, 10.0 + y);
	glVertex2f(20.0 + x, 30.0 + y);
	glEnd();

	//Rear Window(grey color)
	glBegin(GL_POLYGON);
	glVertex2f(-20.0 + x, -40.0 + y);
	glVertex2f(-10.0 + x, -20.0 + y);
	glVertex2f(10.0 + x, -20.0 + y);
	glVertex2f(20.0 + x, -40.0 + y);
	glEnd();

	// Side mirrors
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON); // Left mirror
	glVertex2f(-32.0 + x, 7.0 + y);
	glVertex2f(-42.0 + x, 14.0 + y);
	glVertex2f(-32.0 + x, 27.0 + y);
	glEnd();

	glBegin(GL_POLYGON); // Right mirror
	glVertex2f(31.0 + x, 7.0 + y);
	glVertex2f(41.0 + x, 14.0 + y);
	glVertex2f(31.0 + x, 27.0 + y);
	glEnd();

	//Wheels
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);//Left rear wheel
	glVertex2f(-40.0 + x, -37.0 + y);
	glVertex2f(-30.0 + x, -37.0 + y);
	glVertex2f(-30.0 + x, -23.0 + y);
	glVertex2f(-40.0 + x, -23.0 + y);
	glEnd();

	glBegin(GL_POLYGON);//Right rear wheel
	glVertex2f(40.0 + x, -37.0 + y);
	glVertex2f(30.0 + x, -37.0 + y);
	glVertex2f(30.0 + x, -23.0 + y);
	glVertex2f(40.0 + x, -23.0 + y);
	glEnd();

	glBegin(GL_POLYGON);//Left front wheel
	glVertex2f(-40.0 + x, 37.0 + y);
	glVertex2f(-30.0 + x, 37.0 + y);
	glVertex2f(-30.0 + x, 23.0 + y);
	glVertex2f(-40.0 + x, 23.0 + y);
	glEnd();

	glBegin(GL_POLYGON);//Right front wheel
	glVertex2f(40.0 + x, 37.0 + y);
	glVertex2f(30.0 + x, 37.0 + y);
	glVertex2f(30.0 + x, 23.0 + y);
	glVertex2f(40.0 + x, 23.0 + y);
	glEnd();

	
	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_POLYGON); // Front left detail
	glVertex2f(-30.0 + x, 25.0 + y);
	glVertex2f(-30.0 + x, 50.0 + y);
	glVertex2f(-20.0 + x, 50.0 + y);
	glEnd();

	glBegin(GL_POLYGON); // Front right detail
	glVertex2f(30.0 + x, 25.0 + y);
	glVertex2f(30.0 + x, 50.0 + y);
	glVertex2f(20.0 + x, 50.0 + y);
	glEnd();

	glBegin(GL_POLYGON); // Rear left detail
	glVertex2f(-30.0 + x, 50.0 + y);
	glVertex2f(-20.0 + x, 40.0 + y);
	glVertex2f(-30.0 + x, 40.0 + y);
	glEnd();

	glBegin(GL_POLYGON); // Rear right detail
	glVertex2f(30.0 + x, 50.0 + y);
	glVertex2f(20.0 + x, 40.0 + y);
	glVertex2f(30.0 + x, 40.0 + y);
	glEnd();
}
void calculateObstacles() {
	float obstacle_x, obstacle_y;
	srand(static_cast<unsigned int>(time(0)));
	float x_coord_choices[] = { -50.0,50.0 };
	 // Choices for x-coordinates within road boundaries
	for (int i = 0; i < 3; i++) {
		obstacle_y = road_y - 300 + i * 200;
		if (obstacle_y < -300) {
			obstacle_y += 600;

		}
		obstacle_x = x_coord_choices[rand() % 2];
		obstacles[i][0] = obstacle_x;
		if (obstacle_y > 300) {
			obstacle_y -= 600;
		}
		obstacles[i][1] = obstacle_y;
	}
}
void draw_rectangle(int x, int y) {
	glColor3f(1, 1, 0); 
	glBegin(GL_QUADS);
	glVertex2f(x - 25, y - 15); 
	glVertex2f(x + 25, y - 15);
	glVertex2f(x + 25, y + 15);
	glVertex2f(x - 25, y + 15);
	glEnd();
}

void draw_obstacles() {
	for (int i = 0; i < 3; i++) {
		float x1 = obstacles[i][0];
		float y1 = obstacles[i][1];
		if (y1 >= -300 && y1 <= 300) { // Only draw obstacles within the screen
			draw_rectangle(x1, y1);
		}
	}
}

void init() {
	//glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-400.0, 400.0, -300.0, 300.0); 
	glMatrixMode(GL_MODELVIEW);
}
void reshape(int w, int h) {
	glViewport(0, 0, w, h); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 

	
	float aspect = (float)w / (float)h;

	
	if (w >= h) {
		gluOrtho2D(-400.0 * aspect, 400.0 * aspect, -300.0, 300.0);
	}
	else {
		gluOrtho2D(-400.0, 400.0, -300.0 / aspect, 300.0 / aspect);
	}

	glMatrixMode(GL_MODELVIEW); 
}

void drawString(float cx, float cy, const char* str) {
	glRasterPos2f(cx, cy);
	for (int i = 0; i < strlen(str); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	}
}

void frontPage() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	drawString(-200.0, 150.0, "Name: Harsh RG");
	drawString(-200.0, 100.0, "USN: 1RN21CS062");
	drawString(-200.0, 50.0, "Section: 6th sem CSE 'A' section");
	drawString(-240.0, 0.0, "Guide: Dr Sudhamani MJ, Associate Professor, CSE Dept");

	// Instructions of the game
	glColor3f(1.0, 1.0, 0.0);
	drawString(-100.0, -75.0, "Instructions");
	drawString(-235.0, -125.0, "1. Press 'u' or 'U' simulating forward movement of car.");
	drawString(-235.0, -150.0, "2. Press 'L' for car to move left.");
	drawString(-235.0, -175.0, "3. Press 'R' for car to move right.");
	drawString(-235.0, -200.0, "4. Press 'w' or 'W' simulating backward movement of car.");
	drawString(-235.0, -225.0, "5. Press '-' to decrease speed.");
	drawString(-235.0, -250.0, "6. Press '=' to increase speed.");
	drawString(-235.0, -275.0, "7. Press 's' or 'S' to start the game.");
	glutSwapBuffers();
}
void startGame() {
	gameStarted = true;
	//printf("Hello world\n");
	glutPostRedisplay();
}
void display() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	if (!gameStarted) {
		frontPage();
	}
	else {
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		//calculateObstacles();
		draw_road(0,road_y);
		draw_road(0,road_y-600);
		draw_road(0,road_y+600);
		draw_obstacles();
		draw_car(car_x, -150);
		char scoreText[20];
		sprintf_s(scoreText, "Score:%.2f", score);
		drawString(-370.0, 280.0, scoreText);
		glutSwapBuffers();
	}
}
void keyboard(unsigned char key, int x, int y) {
	if (key == 's' || key == 'S') {
		startGame();
	}
	else if (key == 'w' || key == 'W') {
		road_y += speed;
		if (road_y > 600) {
			road_y -= 600;
		}
		score = 0;
	}
	else if (key == 'u' || key == 'U') {
		road_y -= speed;
		if (road_y < 0) {
			road_y += 600;
		}
	}
	else if (key == 'l' || key == 'L') {
		car_x-=3;
		if (car_x < -70) {
			car_x = -70;
		}
	}
	else if (key == 'r' || key == 'R') {
		car_x+=3;
		if (car_x > 70) {
			car_x = 70;
		}
	}
	else if (key == '-') {
		speed--;
		if (speed < 0) {
			speed = 0;
		}
	}
	else if (key == '=') {
		speed++;
		if (speed > 100) {
			speed = 100;
		}
	}
	glutPostRedisplay();
}
void idle(int t) {
	if (speed > 0) { // Only move obstacles if the car is moving
		road_y -= speed / 10;
		if (road_y < 0) {
			road_y += 600;
		}
		calculateObstacles();
		score += speed / 10;
	}
	else {
		score = 0;
	}
	glutTimerFunc(50, idle, 0);
	glutPostRedisplay();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("2D Car Racing Game");

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(1000,idle,0);
	glutMainLoop();
	return 0;
}
