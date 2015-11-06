#include "ParticleEmitter.h"
#include "AnimationMath.h"

//Particle Constructor
ParticleEmitter::ParticleEmitter()
{
	// Initialize memory pointer to null
	particles = nullptr;
	numParticles = 0;
	drawCube = false;
	drawSpriteSmoke = false; 
	drawSpriteFire = false;
	drawSpriteTrail = false;

	initialSize = 1.0f;
	initialLife = 1.0f;
	initialMass = 1.0f;

		playing = false;
}

//Decontructor
ParticleEmitter::~ParticleEmitter()
{
	if (particles)
		delete[] particles;
}

void ParticleEmitter::Initialize(unsigned int _numParticles)
{
	if (!playing)
	{
		//clear memory
		//any non zero values will be true
		if (particles)
		{
			delete[] particles;
			particles = nullptr;
			numParticles = _numParticles;
		}

		if (_numParticles) //make sure new size is > 0
		{
			particles = new Particle[_numParticles]();
			numParticles = _numParticles;
		}
	}
}

void ParticleEmitter::update(float dt)
{
	//If particle memory has been initialized and if playing is true
	if (particles && playing)
	{
		for (int i = 0; i < numParticles; i++)
		{
			//Store pointer to current particle
			//Why is is a plus sign?
			Particle* p = particles + i; //doing math on a pointer
			//You could also do this
			// Particle* p = particles[i]; 
			//But is slower

			if (!p->isAlive())
			{
				//could put more logic here, ie if you didn't want it to reapawn
				// ...
				//if particle is dead, respawn it
				*p = respawnParticle();
			}

			if (lerpColour1)
				p->colour = lerp<TTK::Vector4>(colour0, colour1, 1.0 - p->life / p->initialLife);
			if (lerpColour2)
				p->colour = lerp<TTK::Vector4>(colour2, colour3, 1.0 - p->life / p->initialLife);
			//Update the particle 
			p->update(dt);
		}
	}
}

//Draw Particles 

void ParticleEmitter::draw()
{
	TTK::Graphics::DrawCube(initialPosition.values);

	//call each particles draw function
	for (int i = 0; i < numParticles; i++)
	{
		Particle* p = particles + i;

		if (p)
		{
			if (p->isAlive())
				p->draw();
		}
	}
}

Particle ParticleEmitter::respawnParticle()
{
	Particle p;

	//Initialize new particle 
	// different spawn location logic can go here
	p.position = initialPosition; // spawn particle at emitter position
	p.mass = initialMass * randomFloat01();
	p.velocity = initialVelocity + randomDirection();
	p.acceleration = initialForce / p.mass; //f = ma
	p.setInitialLife(initialLife * randomFloat01());
	p.colour = TTK::Vector4(1.0f);
	p.scale = initialSize;
	p.drawCube = drawCube;
	p.drawSpriteSmoke = drawSpriteSmoke;
	p.drawSpriteFire = drawSpriteFire;
	p.drawSpriteTrail = drawSpriteTrail;
	//check paritcle creation flags

	if (randomizeColour)
	{
		p.colour = colour0;
		colour0 = TTK::Vector4(randomColourRGB(), 1.0f);
		
	}

	if (randomizeVelocity)
	{
		p.velocity = randomDirection() * randomFloatRange(0.0f, 10.0f);
	}

	//if (randomSize)
	//{
	//	p.scale = randomSize() * randomFloatRange(0.0f, 10.0f)
	//}

	// 


	return p;
}