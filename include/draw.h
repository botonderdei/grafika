#ifndef OBJ_DRAW_H
#define OBJ_DRAW_H

#include "model.h"

#define SKYBOX_SIZE 10000.0

typedef struct Position
{
	double x;
	double y;
	double z;
}Position;

typedef struct {

	double earth_rotation;
	double sun_rotation;
	double moon_rotation;
	double mars_rotation;
	double mercury_rotation;
	double venus_rotation;
	double jupiter_rotation;
	double saturn_rotation;
	double uranus_rotation;
	double neptune_rotation;
	
}Rotate;

typedef struct{
	Position earth;
	Position sun;
	Position moon;
	Position mars;
	Position mercury;
	Position venus;
	Position jupiter;
	Position saturn;
	Position uranus;
	Position neptune;
	
	
}Move;

/**
 * Draw the model.
 */
void draw_model(const Model* model);

/**
 * Draw the triangles of the model.
 */
void draw_triangles(const Model* model);

void draw_skybox_top(Entity skybox);


//Draw the bottom skybox.
void draw_skybox_bottom(Entity skybox);


//Draw the entitys to the world.
void draw_environment(World world,Rotate* rotate, Move move);

//Draw the ship
void draw_ship(World world, double* pos, double* rotate);



#endif /* OBJ_DRAW_H */
