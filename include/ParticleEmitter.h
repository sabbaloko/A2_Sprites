#pragma once

#include "TTK/TTK.h"
#include "Particle.h"
#include <math.h>


class ParticleEmitter
{
public:
	ParticleEmitter();
   ~ParticleEmitter();

	//Initialize memory for particles
	void Initialize(unsigned int _numParticles);

	//Play back controls
	inline void play()
	{
		playing = true;

	}

	inline void pause()
	{
		playing = false;
	}

	//Updates each particle in system
	void update(float dt);

	//Draw all particles in system
	void draw();

	//Used to recycle particles
	Particle respawnParticle();

	// Emitter properties

	TTK::Vector3 initialPosition; //Emittter position in worldspace
	TTK::Vector3 initialVelocity; //Initial velocity for each particle
	TTK::Vector3 initialForce; //Initial force for each particle

	float initialLife;
	float initialMass;
	float initialSize;

	// Visual properties for the particles
	TTK::Vector4 colour0;
	TTK::Vector4 colour1;
	TTK::Vector4 colour2;
	TTK::Vector4 colour3;
	float initialize;
	// Textire, spritesheet etc...(whatever visual properties you want)

	bool catPosition;
	bool randomizeColour;
	bool randomizeVelocity;
	bool lerpColour1;
	bool lerpColour2;
	
	bool drawCube;
	//Smoke
	bool drawSpriteSmoke;
	//Fireworks
	bool drawSpriteFire;
	//Trail
	bool drawSpriteTrail;

	// ...add as many more as you like 
private:
	Particle* particles; //Pointer to the first element in array
	unsigned int numParticles; //

	bool playing;

};
	