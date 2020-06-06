#include "camera.h"
#include "draw.h"
#include <GL/glut.h>
#include <math.h>
#define M_PI 3.14159265358979323846
#define skybox_size 6000
#define sun_size 850
#define earth_size 200
#define moon_size 85


double degree_to_radian(double degree)
{
	return degree * M_PI / 180.0;
}



void init_camera(struct Camera* camera)
{
	camera->position.x = 3000;
	camera->position.y = 0;
	camera->position.z = 3000;

	camera->pose.x = 0;
	camera->pose.y = 0;
	camera->pose.z = 0;
}


void don_not_head_up_against_the_wall (struct Camera* camera, Move move){


	if (camera->position.x<-skybox_size || camera->position.x>skybox_size ||
		camera->position.y<-skybox_size || camera->position.y>skybox_size ||
		camera->position.z<-skybox_size || camera->position.z>skybox_size)
		init_camera (camera);

	if (camera->position.x<sun_size && camera->position.x>-sun_size &&
			camera->position.y<sun_size && camera->position.y>-sun_size &&
			camera->position.z<sun_size && camera->position.z>-sun_size)
			init_camera (camera);

	if (camera->position.x < move.earth.x+earth_size && camera->position.x>move.earth.x-earth_size &&
			camera->position.y<move.earth.y+earth_size && camera->position.y>move.earth.y-earth_size &&
			camera->position.z<move.earth.z+earth_size && camera->position.z>move.earth.z-earth_size)
			init_camera (camera);

	if (camera->position.x < move.earth.x+1000+moon_size && camera->position.x>move.earth.x+1000-moon_size &&
			camera->position.y<move.earth.y+1000+moon_size && camera->position.y>move.earth.y+1000-moon_size &&
			camera->position.z<move.earth.z-100+moon_size && camera->position.z>move.earth.z-100-moon_size)
			init_camera (camera);
}


void set_view_point(const struct Camera* camera)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(-(camera->pose.x + 90), 1.0, 0, 0);
	glRotatef(-(camera->pose.z - 90), 0, 0, 1.0);
	glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}



void rotate_camera(struct Camera* camera, double horizontal, double vertical)
{
	camera->pose.z += horizontal/CAMERA_SPEED;
	camera->pose.x += vertical/CAMERA_SPEED;

	if (camera->pose.z < 0) {
		camera->pose.z += 360.0;
	}

	if (camera->pose.z > 360.0) {
		camera->pose.z -= 360.0;
	}

	if (camera->pose.x < 0) {
		camera->pose.x += 360.0;
	}

	if (camera->pose.x > 360.0) {
		camera->pose.x -= 360.0;
	}

}


void rotate_camera_up(struct Camera* camera)
{
	rotate_camera(camera, 0, 5);

}



void rotate_camera_down(struct Camera* camera)
{
	rotate_camera(camera, 0, -5);
}



void move_camera_backward(struct Camera* camera)
{
	camera->prev_position = camera->position;
	double angle = degree_to_radian(camera->pose.z);

	camera->position.x -= cos(angle) * -2;
	camera->position.y -= sin(angle) * -2;


}


void move_camera_forward(struct Camera* camera)
{
	camera->prev_position = camera->position;
	double angle = degree_to_radian(camera->pose.z);


	camera->position.x += cos(angle) * 2;
	camera->position.y += sin(angle) * 2;

}


void rotate_camera_right(struct Camera* camera)
{
	rotate_camera(camera, -5, 0);
}


void rotate_camera_left(struct Camera* camera)
{
	rotate_camera(camera, 5, 0);
}