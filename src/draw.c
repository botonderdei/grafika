#include "draw.h"
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "world.h"
#include "camera.h"
#include "transform.h"
float r=0;

void draw_model(const Model* model)
{
    draw_triangles(model);
}

void draw_triangles(const Model* model)
{
    int i, k;
    int vertex_index, texture_index, normal_index;
    float x, y, z, u, v;

    glBegin(GL_TRIANGLES);

    for (i = 0; i < model->n_triangles; ++i) {
        for (k = 0; k < 3; ++k) {

            normal_index = model->triangles[i].points[k].normal_index;
            x = model->normals[normal_index].x;
            y = model->normals[normal_index].y;
            z = model->normals[normal_index].z;
            glNormal3f(x, y, z);

            texture_index = model->triangles[i].points[k].texture_index;
            u = model->texture_vertices[texture_index].u;
            v = model->texture_vertices[texture_index].v;
            glTexCoord2f(u, v);

            vertex_index = model->triangles[i].points[k].vertex_index;
            x = model->vertices[vertex_index].x;
            y = model->vertices[vertex_index].y;
            z = model->vertices[vertex_index].z;
            glVertex3f(x, y, z);
        }
    }

    glEnd();
}

void draw_skybox_bottom(Entity skybox)
{
    double theta, phi1, phi2;
    double x1, y1, z1;
    double x2, y2, z2;
    double u, v1, v2;

    int n_slices, n_stacks;
    double radius;
    int i, k;

    n_slices = 12;
    n_stacks = 6;
    radius = SKYBOX_SIZE;

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, skybox.texture);
    glScaled(radius, radius, radius);

    glColor3f(1, 1, 1);

	glBegin(GL_TRIANGLE_STRIP);

    for (i = 0; i < n_stacks; ++i) {
        v1 = (double)i / n_stacks;
        v2 = (double)(i + 1) / n_stacks;
        phi1 = v1 * M_PI / 2.0;
        phi2 = v2 * M_PI / 2.0;
        for (k = 0; k <= n_slices; ++k) {
            u = (double)k / n_slices;
            theta = u * 2.0 * M_PI;
            x1 = cos(theta) * cos(phi1);
            y1 = sin(theta) * cos(phi1);
            z1 = sin(phi1);
            x2 = cos(theta) * cos(phi2);
            y2 = sin(theta) * cos(phi2);
            z2 = sin(phi2);
            glTexCoord2d(u, 1.0 - v1);
            glVertex3d(x1, y1, -z1);
            glTexCoord2d(u, 1.0 - v2);
            glVertex3d(x2, y2, -z2);
        }
    }

    glEnd();
    glPopMatrix();
}



void draw_skybox_top(Entity skybox)
{
    double theta, phi1, phi2;
    double x1, y1, z1;
    double x2, y2, z2;
    double u, v1, v2;

    int n_slices, n_stacks;
    double radius;
    int i, k;

    n_slices = 12;
    n_stacks = 6;
    radius = SKYBOX_SIZE;

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, skybox.texture);
    glScaled(radius, radius, radius);

    glColor3f(1, 1, 1);

	glBegin(GL_TRIANGLE_STRIP);

    for (i = 0; i < n_stacks; ++i) {
        v1 = (double)i / n_stacks;
        v2 = (double)(i + 1) / n_stacks;
        phi1 = v1 * M_PI / 2.0;
        phi2 = v2 * M_PI / 2.0;
        for (k = 0; k <= n_slices; ++k) {
            u = (double)k / n_slices;
            theta = u * 2.0 * M_PI;
            x1 = cos(theta) * cos(phi1);
            y1 = sin(theta) * cos(phi1);
            z1 = sin(phi1);
            x2 = cos(theta) * cos(phi2);
            y2 = sin(theta) * cos(phi2);
            z2 = sin(phi2);
            glTexCoord2d(u, 1.0 - v1);
            glVertex3d(x1, y1, z1);
            glTexCoord2d(u, 1.0 - v2);
            glVertex3d(x2, y2, z2);
        }
    }

    glEnd();
    glPopMatrix();
}

void draw_environment(World world, Rotate* rotate, Move move ){
	glEnable(GL_TEXTURE_2D);


	//Draw the bottom skybox.
	draw_skybox_bottom(world.skybox);


	//Draw the top skybox.
	draw_skybox_top(world.skybox);

	//Draw the sun.
	glPushMatrix();

		glTranslatef(0,0,0);
		set_material(&(world.sun.material));
		glBindTexture(GL_TEXTURE_2D, world.sun.texture);
		glScalef(1.0f, 1.0f, 1.0f);
		glRotatef(rotate->sun_rotation, 1, 1, 1);
		draw_model(&world.sun.model);

    glPopMatrix();


    //Draw the earth.
    glPushMatrix();

    		glTranslatef (move.earth.x,move.earth.y,move.earth.z);
    		set_material(&(world.earth.material));
    		glBindTexture(GL_TEXTURE_2D, world.earth.texture);
    		glScalef(0.2f, 0.2f, 0.2f);
    		glRotatef(rotate->earth_rotation, 0, 0, 1);
    		draw_model(&world.sun.model);


   glPopMatrix();
   
   
     //Draw the mars.
   glPushMatrix();
			
    		glTranslatef (move.mars.x,move.mars.y,move.mars.z);
    		set_material(&(world.mars.material));
    		glBindTexture(GL_TEXTURE_2D, world.mars.texture);
    		glScalef(0.2f, 0.2f, 0.2f);
    		glRotatef(rotate->mars_rotation, 0, 0, 1);
    		draw_model(&world.sun.model);

   glPopMatrix();


     //Draw the moon.
    glPushMatrix();
			
			r=r+1;
    		glTranslatef (move.earth.x+cos(r*(3.14)/180) * 500,move.earth.y+sin(r*(3.14)/180) * 500,move.earth.z);
    		set_material(&(world.moon.material));
    		glBindTexture(GL_TEXTURE_2D, world.moon.texture);
    		glScalef(0.1f, 0.1f, 0.1f);
    		glRotatef(rotate->moon_rotation, 0, 0, 1);
    		draw_model(&world.sun.model);

   glPopMatrix();
   
   //Draw the mercury.
   glPushMatrix();
			
    		glTranslatef (move.mercury.x,move.mercury.y,move.mercury.z);
    		set_material(&(world.mercury.material));
    		glBindTexture(GL_TEXTURE_2D, world.mercury.texture);
    		glScalef(0.1f, 0.1f, 0.1f);
    		glRotatef(rotate->mercury_rotation, 0, 0, 1);
    		draw_model(&world.sun.model);

   glPopMatrix();
   
   //Draw the venus.
   glPushMatrix();
			
    		glTranslatef (move.venus.x,move.venus.y,move.venus.z);
    		set_material(&(world.venus.material));
    		glBindTexture(GL_TEXTURE_2D, world.venus.texture);
    		glScalef(0.15f, 0.15f, 0.15f);
    		glRotatef(rotate->venus_rotation, 0, 0, 1);
    		draw_model(&world.sun.model);

   glPopMatrix();
   
   //Draw the jupiter.
   glPushMatrix();
			
    		glTranslatef (move.jupiter.x,move.jupiter.y,move.jupiter.z);
    		set_material(&(world.jupiter.material));
    		glBindTexture(GL_TEXTURE_2D, world.jupiter.texture);
    		glScalef(0.35f, 0.35f, 0.35f);
    		glRotatef(rotate->jupiter_rotation, 0, 0, 1);
    		draw_model(&world.sun.model);

   glPopMatrix();
   
      //Draw the saturn.
   glPushMatrix();
			
    		glTranslatef (move.saturn.x,move.saturn.y,move.saturn.z);
    		set_material(&(world.saturn.material));
    		glBindTexture(GL_TEXTURE_2D, world.saturn.texture);
    		glScalef(0.2f, 0.2f, 0.2f);
    		glRotatef(rotate->saturn_rotation, 0, 0, 1);
    		draw_model(&world.sun.model);


   glPopMatrix();
   
      //Draw the uranus.
   glPushMatrix();
			
    		glTranslatef (move.uranus.x,move.uranus.y,move.uranus.z);
    		set_material(&(world.uranus.material));
    		glBindTexture(GL_TEXTURE_2D, world.uranus.texture);
    		glScalef(0.2f, 0.2f, 0.2f);
    		glRotatef(rotate->uranus_rotation, 0, 0, 1);
    		draw_model(&world.sun.model);



   glPopMatrix();
   
   
      //Draw the neptune.
   glPushMatrix();
			
    		glTranslatef (move.neptune.x,move.neptune.y,move.neptune.z);
    		set_material(&(world.neptune.material));
    		glBindTexture(GL_TEXTURE_2D, world.neptune.texture);
    		glScalef(0.2f, 0.2f, 0.2f);
    		glRotatef(rotate->neptune_rotation, 0, 0, 1);
    		draw_model(&world.sun.model);




   glPopMatrix();
   

}

void draw_ship(World world, double* pos, double* rotate){
    //Draw the ship.
	glPushMatrix();

        GLfloat a[4] = {0.5 , 0.5, 0.5, 1.0};
		set_material(&(world.ship.material));
		glBindTexture(GL_TEXTURE_2D, world.ship.texture);
	    glTranslated(pos[0], pos[1], pos[2]);
		glScalef(10.0f, 10.0f, 10.0f);
        glRotatef(180, 0, 0, 1);
		draw_model(&world.ship.model);
    glPopMatrix();
}
