#ifndef CAMERA_H
#define CAMERA_H
#include "model.h"
#include "draw.h"

#define MOVE_SPEED 10.0  //BIGGER IS FASTER
#define CAMERA_SPEED 5.0 //BIGGER IS SLOWER

struct Camera
{
	struct Vertex position;
	struct Vertex pose;
	struct Vertex prev_position;
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
