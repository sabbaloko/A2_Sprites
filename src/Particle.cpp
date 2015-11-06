#include "Particle.h"
#include <Windows.h>
#include <gl/GL.h>

Particle::Particle()
{
	spriteFire = new TTK::SpriteSheetQuad("..//img//fire.png");
	//spriteSmoke = new TTK::SpriteSheetQuad("..//img//smoke.png");
	//spriteTrail = new TTK::SpriteSheetQuad("..//img//trail.png");
	mass = 1.0f;
	life = 0.0f;
	scale = 0.0f;
	drawCube = false;
	drawSpriteSmoke = false;
	drawSpriteFire = false;
	drawSpriteTrail = false;
	
}

Particle::~Particle()
{
	//delete sprite;
}

void Particle::update(float dt) //moves the particle around
{
	//Euler 

	//Store previous velocity
	TTK::Vector3 vPrev = velocity;

	//Calculate current position
	//position += velocity * dt + acceleration * 0.5f * (dt*dt);
	
	// Adams Bashforth

	//update velocity
	//velocity += acceleration * dt;

	velocity += acceleration * dt;

	position += (velocity * 3.0f - vPrev) * 0.5f * dt;

	life -= dt; //Decrement particle life
	//This is where you would update acceleration
}

//Specifies what particle to draw
//Sprite...
void Particle::draw()
{
	

	if (drawCube)
	{
	
	TTK::Graphics::DrawCube(position.values, scale, colour.values);
	}
	
	//Sprite for 1st Particle 
	if (drawSpriteSmoke)
	{
		glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();
		glPushMatrix();
		TTK::Matrix4x4 mat = TTK::Matrix4x4(TTK::Matrix3x3(), position, scale);

		glMultMatrixf(mat.values);

		//For Cube
		//TTK::Graphics::DrawCube(position.values, scale, colour.values);
		//spriteSmoke->draw();
		glPopMatrix();

	}

	//Sprite for Second Particle 
	if (drawSpriteFire)
	{
		glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();
		glPushMatrix();
		TTK::Matrix4x4 mat = TTK::Matrix4x4(TTK::Matrix3x3(), position, scale);

		glMultMatrixf(mat.values);

		//For Cube
		//TTK::Graphics::DrawCube(position.values, scale, colour.values);
		spriteFire->draw();
		glPopMatrix();

	}

	//Sprite for Third Particle 
	if (drawSpriteTrail)
	{
		glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();
		glPushMatrix();
		TTK::Matrix4x4 mat = TTK::Matrix4x4(TTK::Matrix3x3(), position, scale);

		glMultMatrixf(mat.values);

		//For Cube
		//TTK::Graphics::DrawCube(position.values, scale, colour.values);
		//spriteTrail->draw(); /////////////////////////make pointers<<<<<<<<<
		glPopMatrix();

	}
	

}



void Particle::setInitialLife(float _life)
{
	life = initialLife = _life;
}

bool Particle::isAlive()
{
	return life > 0.0f;
}