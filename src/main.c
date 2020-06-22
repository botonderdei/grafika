#include <GL/glut.h>
#include "SOIL/SOIL.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "model.h"
#include "draw.h"
#include "camera.h"
#include "load.h"
#include "transform.h"
#include "world.h"
#include <sys/time.h>

#define resolution 1   // 1: 1920*1080   0: 1366*768
#define fullscreen 1   // 1: fullscreen  0: windowed

GLfloat light_position[] = {1, 1, 0, 0};
GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 0 };
GLfloat light_diffuse[] = { 0.5, 0.5, 0, 0 };
GLfloat light_specular[] = { 1, 1, 1, 0 };


typedef GLubyte Pixel;
struct Camera camera;
struct Action action;

World world;
Rotate rotate;
Move move;

int WINDOW_WIDTH;
int WINDOW_HEIGHT;
int help, help_on = 0;
float angle = 135;
double degree = 0;
double distance_a = 4000;
double distance_b = 4000;
float speed = 30;
int previous_time;
int mouse_x, mouse_y;




void specialFunc(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1:
		if (help_on) {
			help_on = 0;

			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, light_ambient);
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);
		}else {
			help_on = 1;
			GLfloat ones[] = { 1, 1, 1, 1 };
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ones);
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ones);
		}
	}

}

void update_camera_position(struct Camera* camera, double elapsed_time)
{
	double distance;

	distance = 0.05 * MOVE_SPEED * speed;

	if (action.move_forward == TRUE) {
	move_camera_forward(camera, distance);
	}

	if (action.move_backward == TRUE) {
		move_camera_backward(camera, distance);
	}

	if (action.rotate_left == TRUE) {
		rotate_camera_left(camera, distance);
	}

	if (action.rotate_right == TRUE) {
		rotate_camera_right(camera, distance);
	}

	if (action.move_up == TRUE) {
		rotate_camera_up(camera, distance);
	}

	if (action.move_down == TRUE) {
		rotate_camera_down(camera, distance);
	}

	if (action.increase_light == TRUE) {
		if (light_ambient[0] < 1)
			light_ambient[0] = light_ambient[1] = light_ambient[2] += 0.01;
	}

	if (action.decrease_light == TRUE) {
		if (light_ambient[0] > -0.51)
			light_ambient[0] = light_ambient[1] = light_ambient[2] -= 0.01;
	}

	don_not_head_up_against_the_wall (camera, move);

}

void reshape(GLsizei width, GLsizei height) {
	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (!help_on)
		gluPerspective(50.0, (GLdouble)width / (GLdouble)height, 0.1, 20000.0);
	else
		gluOrtho2D(0, width, height, 0);
}

double calc_elapsed_time()
{
	int current_time;
	double elapsed_time;

	current_time = glutGet(GLUT_ELAPSED_TIME);
	elapsed_time = (double)(current_time - previous_time) / 1000.0;
	previous_time=current_time;

	return elapsed_time;
}



void draw_help() {

	GLfloat ones[] = { 1, 1, 1, 1 };
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ones);
				glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ones);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, help);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(WINDOW_WIDTH, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0, WINDOW_HEIGHT, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	reshape(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutSwapBuffers();
}



void rotation_of_objects(Rotate* rotate) {

	if (action.rotate_earth_in_galaxy == TRUE){
		rotate->earth_rotation+=0.5;

		rotate->sun_rotation+=0.05;
	
		rotate->moon_rotation+=0.5;
	}
	
	if (action.rotate_mars_in_galaxy == TRUE){
		rotate->earth_rotation+=0.5;

		rotate->sun_rotation+=0.05;
	
		rotate->moon_rotation+=0.5;
		
		rotate->mars_rotation+=0.5;
	}
}

void movement_of_objects (Move* move){

if (action.move_earth_in_galaxy == TRUE){
		degree+=0.1;
		double angle = degree_to_radian(degree);
		move->earth.x = cos(angle) * distance_a/1.8;
		move->earth.y = sin(angle) * distance_b/1.8;
		move->earth.z = 0;
		}
	else
		if (move->earth.x == 0){
		move->earth.x = 4000;
		move->earth.y = 0;
		move->earth.z = 0;
		}

if (action.move_mars_in_galaxy == TRUE){
		degree+=0.1;
		double angle = degree_to_radian(degree)-100;
		move->mars.x = (cos(angle)* distance_a)/1.3;
		move->mars.y = (sin(angle)* distance_b)/1.3;
		move->mars.z = 0;
		}
	else
		if (move->mars.x == 0){
		move->mars.x = 4000;
		move->mars.y = 0;
		move->mars.z = 0;
		}
		
if (action.move_mercury_in_galaxy == TRUE){
		degree+=0.1;
		double angle = degree_to_radian(degree)-200;
		move->mercury.x = (cos(angle)* distance_a)/2.8;
		move->mercury.y = (sin(angle)* distance_b)/2.8;
		move->mercury.z = 0;
		}
	else
		if (move->mercury.x == 0){
		move->mercury.x = 4000;
		move->mercury.y = 0;
		move->mercury.z = 0;
		}
		
if (action.move_venus_in_galaxy == TRUE){
		degree+=0.1;
		double angle = degree_to_radian(degree)-400;
		move->venus.x = (cos(angle)* distance_a)/2.3;
		move->venus.y = (sin(angle)* distance_b)/2.3;
		move->venus.z = 0;
		}
	else
		if (move->venus.x == 0){
		move->venus.x = 4000;
		move->venus.y = 0;
		move->venus.z = 0;
		}


if (action.move_jupiter_in_galaxy == TRUE){
		degree+=0.1;
		double angle = degree_to_radian(degree)+100;
		move->jupiter.x = (cos(angle)* distance_a)*1.2;
		move->jupiter.y = (sin(angle)* distance_b)*1.2;
		move->jupiter.z = 0;
		}
	else
		if (move->jupiter.x == 0){
		move->jupiter.x = 4000;
		move->jupiter.y = 0;
		move->jupiter.z = 0;
		}
		
if (action.move_saturn_in_galaxy == TRUE){
		degree+=0.1;
		double angle = degree_to_radian(degree)+300;
		move->saturn.x = (cos(angle)* distance_a)*1.6;
		move->saturn.y = (sin(angle)* distance_b)*1.6;
		move->saturn.z = 0;
		}
	else
		if (move->saturn.x == 0){
		move->saturn.x = 4000;
		move->saturn.y = 0;
		move->saturn.z = 0;
		}
		
if (action.move_uranus_in_galaxy == TRUE){
		degree+=0.1;
		double angle = degree_to_radian(degree)+550;
		move->uranus.x = (cos(angle)* distance_a)*2;
		move->uranus.y = (sin(angle)* distance_b)*2;
		move->uranus.z = 0;
		}
	else
		if (move->uranus.x == 0){
		move->uranus.x = 4000;
		move->uranus.y = 0;
		move->uranus.z = 0;
		}
		
if (action.move_neptune_in_galaxy == TRUE){
		degree+=0.1;
		double angle = degree_to_radian(degree)+700;
		move->neptune.x = (cos(angle)* distance_a)*2.3;
		move->neptune.y = (sin(angle)* distance_b)*2.3;
		move->neptune.z = 0;
		}
	else
		if (move->neptune.x == 0){
		move->neptune.x = 4;
		move->neptune.y = 0;
		move->neptune.z = 0;
		}
}


void display() {
	if (!help_on) {
		action.move_forward == TRUE;
		double elapsed_time;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		elapsed_time = calc_elapsed_time();
		update_camera_position(&camera, elapsed_time);
		set_view_point(&camera);


		glLightfv(GL_LIGHT1, GL_POSITION, light_position);
        glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, light_ambient);
		glEnable(GL_LIGHT1);


		draw_environment(world, &rotate, move);
		double pos[3] = {camera.position.x, camera.position.y, camera.position.z};
		double rotate[3] = {camera.pose.x, camera.pose.y, camera.pose.z};
		
		draw_ship(world, pos, rotate);
		movement_of_objects(&move);
		rotation_of_objects(&rotate);
		reshape(WINDOW_WIDTH, WINDOW_HEIGHT);
		glutSwapBuffers();

	}
	else {
		draw_help();
	}
}


void mouse_handler(int button, int state, int x, int y)
{
	mouse_x = x;
	mouse_y = y;
}


void motion_handler(int x, int y)
{
	double horizontal, vertical;

	horizontal = mouse_x - x;
	vertical = mouse_y - y;

	rotate_camera(&camera, horizontal, vertical);

	mouse_x = x;
	mouse_y = y;

	glutPostRedisplay();
}


void key_handler(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		action.move_forward = TRUE;
		break;
	case 's':
		action.move_backward = TRUE;
		break;
	case 'a':
		action.rotate_left = TRUE;
		break;
	case 'd':
		action.rotate_right = TRUE;
		break;
	case 'x':
		action.move_down = TRUE;
		break;
	case 32:
		action.move_up = TRUE;
		break;
	case '+':
		action.increase_light = TRUE;
		break;
	case '-':
		action.decrease_light = TRUE;
		break;
	case 27:
		exit(0);
	}

	glutPostRedisplay();
}


void key_up_handler(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		action.move_forward = FALSE;
		break;
	case 's':
		action.move_backward = FALSE;
		break;
	case 'a':
		action.rotate_left = FALSE;
		break;
	case 'd':
		action.rotate_right = FALSE;
		break;
	case 'x':
		action.move_down = FALSE;
		break;
	case 32:
		action.move_up = FALSE;
		break;
	case '+':
		action.increase_light = FALSE;
		break;
	case '-':
		action.decrease_light = FALSE;
		break;
	case 27:
		exit(0);
	}

	glutPostRedisplay();
}


void idle()
{
	glutPostRedisplay();
}


void set_callbacks() {
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key_handler);
	glutKeyboardUpFunc(key_up_handler);
	glutMouseFunc(mouse_handler);
	glutMotionFunc(motion_handler);
	glutIdleFunc(idle);
	glutSpecialFunc(specialFunc);
	if (fullscreen==1) glutFullScreen();
}


void initialize()
{
	set_callbacks();
	init_camera(&camera);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);
    glClearColor(0.1, 0.1, 0.1, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glClearDepth(1.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, light_ambient);
	glEnable(GL_LIGHTING);
    help = load_texture("textures//help.png");
    init_entities(&world);
    glEnable(GL_TEXTURE_2D);
}


int main(int argc, char** argv) {

	glutInit(&argc, argv);
	if (resolution==1){ glutInitWindowSize(1920, 1080);}
	else {glutInitWindowSize(1366, 768);}
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	int wnd = glutCreateWindow("solarsystem");
	glutSetWindow(wnd);
	initialize();

    action.move_forward = FALSE;
    action.move_backward = FALSE;
    action.rotate_left = FALSE;
    action.rotate_right = FALSE;
    action.rotate_earth_in_galaxy = TRUE;
	action.move_earth_in_galaxy = TRUE;
	action.move_mars_in_galaxy = TRUE;
	action.move_mercury_in_galaxy = TRUE;
	action.move_venus_in_galaxy = TRUE;
	action.move_jupiter_in_galaxy = TRUE;
	action.move_saturn_in_galaxy = TRUE;
	action.move_uranus_in_galaxy = TRUE;
	action.move_neptune_in_galaxy = TRUE;

	glutMainLoop();
	return 0;
}
