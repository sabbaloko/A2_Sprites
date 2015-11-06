#pragma once

#include "TTK/TTK.h"


//Each particle will have it's own set of parameters

class Particle
{
public:
	Particle();
	~Particle();
	TTK::SpriteSheetQuad *spriteFire;
	//TTK::SpriteSheetQuad *spriteSmoke;
	//TTK::SpriteSheetQuad *spriteTrail;

 	void update(float dt); //Moves the particle for physics
	void draw(); //draws particle onto screen

	void setInitialLife(float _life); // Sets how long they stay alive
	bool isAlive(); //Value of true tells us if particle is alive

	// Locomotion Properties

	TTK::Vector3 velocity; //12 bytes
	TTK::Vector3 position; //12 bytes
	TTK::Vector3 acceleration; //12 bytes
	float mass;
	float scale;
	bool drawCube;
	bool drawSpriteSmoke;
	bool drawSpriteFire;
	bool drawSpriteTrail;

	//Visual properties
	TTK::Vector4 colour; //16 bytes
	
	//Texture, geometry, normal map, displacement map...
	//Rigid body for collision
	float life; //Life remaining, in seconds
	float initialLife;
};