#ifndef CAMERA_H
#define CAMERA_H
#include <GL/glut.h>
#include "model.h"
#include "draw.h"
#include "load.h"


#define MOVE_SPEED 10.0  //BIGGER IS FASTER
#define CAMERA_SPEED 5.0 //BIGGER IS SLOWER


struct Camera
{
	struct Vertex position;
	struct Vertex pose;
	struct Vertex prev_position;
};

struct Action
{
	int move_forward;
	int move_backward;
	int rotate_left;
	int rotate_right;
	int move_up;
	int move_down;
	int rotate_earth_in_galaxy;
	int move_earth_in_galaxy;
	int rotate_mars_in_galaxy;
	int move_mars_in_galaxy;
	int rotate_mercury_in_galaxy;
	int move_mercury_in_galaxy;
	int move_venus_in_galaxy;
	int move_jupiter_in_galaxy;
	int move_saturn_in_galaxy;
	int move_uranus_in_galaxy;
	int move_neptune_in_galaxy;
	int increase_light;
	int decrease_light;
};

//Converts degree to radian.
double degree_to_radian(double degree);


//Checks if the camera can move. If it can't, loads the starter position.
void don_not_head_up_against_the_wall (struct Camera* camera, Move move);


//Initialize the camera position and direction.
void init_camera(struct Camera* camera);


//Transform the models into the view point of the camera.
void set_view_point(const struct Camera* camera);


//Rotate the camera horizontally and vertically.
void rotate_camera(struct Camera* camera, double horizontal, double vertical);


//Move the camera forward.
void move_camera_forward(struct Camera* camera);

//Move the camera backward.
void move_camera_backward(struct Camera* camera);

//rotate the camera left.
void rotate_camera_left(struct Camera* camera);


//rotate the camera right.
void rotate_camera_right(struct Camera* camera);


//rotate the camera up.
void rotate_camera_up(struct Camera* camera);


//rotate the camera down.
void rotate_camera_down(struct Camera* camera);



#endif
