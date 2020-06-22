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


	
	world->moon.texture = load_texture("textures/moon.png");
	


	
	world->earth.texture = load_texture("textures/earth.png");

	


	world->mars.texture = load_texture("textures/mars.png");

	

	world->mercury.texture = load_texture("textures/mercury.png");
	
	
	
	world->venus.texture = load_texture("textures/venus.png");
	
	
	
	world->jupiter.texture = load_texture("textures/jupiter.png");
	
	
	
	world->saturn.texture = load_texture("textures/saturn.png");

	
	
	world->uranus.texture = load_texture("textures/uranus.png");
	
	
	
	world->neptune.texture = load_texture("textures/neptune.png");
	
	
	world->sun.material.ambient.red = 0.0;
    world->sun.material.ambient.green = 0.0;
    world->sun.material.ambient.blue = 0.0;

    world->sun.material.diffuse.red = 0.0;
    world->sun.material.diffuse.green = 0.0;
    world->sun.material.diffuse.blue = 0.0;

    world->sun.material.specular.red = 0.0;
    world->sun.material.specular.green = 0.0;
    world->sun.material.specular.blue = 0.0;

    world->sun.material.shininess = 0.0;
	
	
	world->earth.material.ambient.red = 0.0;
    world->earth.material.ambient.green = 0.0;
    world->earth.material.ambient.blue = 0.0;

    world->earth.material.diffuse.red = 0.0;
    world->earth.material.diffuse.green = 0.0;
    world->earth.material.diffuse.blue = 0.0;

    world->earth.material.specular.red = 0.0;
    world->earth.material.specular.green = 0.0;
    world->earth.material.specular.blue = 0.0;

    world->earth.material.shininess = 0.0;
	
	
	world->mars.material.ambient.red = 0.0;
    world->mars.material.ambient.green = 0.0;
    world->mars.material.ambient.blue = 0.0;

    world->mars.material.diffuse.red = 0.0;
    world->mars.material.diffuse.green = 0.0;
    world->mars.material.diffuse.blue = 0.0;

    world->mars.material.specular.red = 0.0;
    world->mars.material.specular.green = 0.0;
    world->mars.material.specular.blue = 0.0;

    world->mars.material.shininess = 0.0;
	
	
	world->mercury.material.ambient.red = 0.0;
    world->mercury.material.ambient.green = 0.0;
    world->mercury.material.ambient.blue = 0.0;

    world->mercury.material.diffuse.red = 0.0;
    world->mercury.material.diffuse.green = 0.0;
    world->mercury.material.diffuse.blue = 0.0;

    world->mercury.material.specular.red = 0.0;
    world->mercury.material.specular.green = 0.0;
    world->mercury.material.specular.blue = 0.0;

    world->mercury.material.shininess = 0.0;


	world->neptune.material.ambient.red = 0.0;
    world->neptune.material.ambient.green = 0.0;
    world->neptune.material.ambient.blue = 0.0;

    world->neptune.material.diffuse.red = 0.0;
    world->neptune.material.diffuse.green = 0.0;
    world->neptune.material.diffuse.blue = 0.0;

    world->neptune.material.specular.red = 0.0;
    world->neptune.material.specular.green = 0.0;
    world->neptune.material.specular.blue = 0.0;

    world->neptune.material.shininess = 0.0;




}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}
