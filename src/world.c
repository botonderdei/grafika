#include "world.h"
#include "transform.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_BUFFER_SIZE 1024

void init_entities(World* world){


	world->skybox.texture = load_texture("textures/sky.png");


    load_model(&world->ship.model, "objects/ship2.obj");
	world->ship.texture = load_texture("textures/ship.png");
	scale_model (&world->ship.model, 0.1, 0.1, 0.1);


	load_model(&world->sun.model, "objects/geoid.obj");
	world->sun.texture = load_texture("textures/sun.png");
	scale_model (&world->sun.model, 1, 1, 1);


	load_model(&world->moon.model, "objects/geoid.obj");
	world->moon.texture = load_texture("textures/moon.png");
	scale_model (&world->moon.model, 0.1, 0.1, 0.1);


	load_model(&world->earth.model, "objects/geoid.obj");
	world->earth.texture = load_texture("textures/earth.png");
	scale_model (&world->earth.model, 0.2, 0.2, 0.2);
	

	load_model(&world->mars.model, "objects/geoid.obj");
	world->mars.texture = load_texture("textures/mars.png");
	scale_model (&world->mars.model, 0.2, 0.2, 0.2);
	
	load_model(&world->mercury.model, "objects/geoid.obj");
	world->mercury.texture = load_texture("textures/mercury.png");
	scale_model (&world->mercury.model, 0.1, 0.1, 0.1);
	
	load_model(&world->venus.model, "objects/geoid.obj");
	world->venus.texture = load_texture("textures/venus.png");
	scale_model (&world->venus.model, 0.15, 0.15, 0.15);
	
	load_model(&world->jupiter.model, "objects/geoid.obj");
	world->jupiter.texture = load_texture("textures/jupiter.png");
	scale_model (&world->jupiter.model, 0.35, 0.35, 0.35);
	
	load_model(&world->saturn.model, "objects/geoid.obj");
	world->saturn.texture = load_texture("textures/saturn.png");
	scale_model (&world->saturn.model, 0.2, 0.2, 0.2);
	
	load_model(&world->uranus.model, "objects/geoid.obj");
	world->uranus.texture = load_texture("textures/uranus.png");
	scale_model (&world->uranus.model, 0.2, 0.2, 0.2);
	
	load_model(&world->neptune.model, "objects/geoid.obj");
	world->neptune.texture = load_texture("textures/neptune.png");
	scale_model (&world->neptune.model, 0.2, 0.2, 0.2);





}