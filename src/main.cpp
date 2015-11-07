// Standard Library
#include <iostream>
#include <string>
#include <math.h>
#include <time.h>

// Libraries
#include "GLUT/glut.h"
#include "TTK/TTK.h"
#include <IL\ilut.h>
#pragma comment(lib, "TTK.lib")

// Project specific
#include "Particle.h"
#include "ParticleEmitter.h"

#define FRAMES_PER_SECOND 30
const int FRAME_DELAY_SPRITE = 1000 / FRAMES_PER_SECOND;

int windowWidth = 800;
int windowHeight = 600;

TTK::Vector3 mousePosition;
TTK::Vector3 position;

// Useful conversions
float degToRad = 3.14159f / 180.0f;
float radToDeg = 180.0f / 3.14159f;

float deltaTime = 0.0f;

float t = 0.0f; // interpolation param
float multiplier = 1.0f;

TTK::SpriteSheetQuad* ss;

TTK::Camera camera;

/* function DisplayCallbackFunction(void)
* Description:
*  - this is the openGL display routine
*  - this draws the sprites appropriately
*/

/* Create Game Objects */
//GameObject *obj;
//GameObject *other;

/* These are our texture handles */

GLuint backgroundTex;
GLuint floorTex;


void drawSceneObjects(void)
{
	//obj->Draw();
	//other->Draw();

	/* Create a floor */
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glScalef(10.f, 10.f, 10.f);
	glBindTexture(GL_TEXTURE_2D, floorTex);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, 0.0f, 1.0f);
	glEnd();

	glPopMatrix();
	
}


void DisplayCallbackFunction(void)
{
	TTK::Graphics::SetBackgroundColour(0.5f, 0.0f, 1.0f);
	TTK::Graphics::ClearScreen();
	drawSceneObjects();

	TTK::Graphics::SetCameraMode3D(windowWidth, windowHeight);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.updateView();
	//TTK::Graphics::DrawGrid();

	////First Particle Emitter////
	      ////Smoke////
	static ParticleEmitter emitterSmoke;
	static bool emitterIsInit = false;
	if (!emitterIsInit)
	{
		emitterIsInit = true;

		// Set emitter properties
		emitterSmoke.initialSize = 1.0f;
		emitterSmoke.initialMass = 5.0f;
		emitterSmoke.initialLife = 3.0f;
		emitterSmoke.initialVelocity = TTK::Vector3(2.0f, 2.0f, 0.0f);
		emitterSmoke.initialForce = TTK::Vector3(0.0f);
		//Set initial position of emitter 
		emitterSmoke.initialPosition = TTK::Vector3(0.0f, 0.0f, 0.0f);
		emitterSmoke.secondPosition = TTK::Vector3(1.0f, 1.0f, 1.0f);
		emitterSmoke.thirdPosition = TTK::Vector3(2.0f, 2.0f, 2.0f);
		emitterSmoke.finalPosition = TTK::Vector3(0.0f, 5.0f, 0.0f);
		emitterSmoke.deltaTime = 5.0f;

		emitterSmoke.colour0 = TTK::Vector4(0.2f);
		//Set color 0 for smoke = almost black to white
		emitterSmoke.colour1 = TTK::Vector4(0.9f);
	

		//set emitter flags

		emitterSmoke.drawCube = true;
		emitterSmoke.lerpColour1 = true;
		//emitterSmoke.doCatmull = true; //this breaks it 


		emitterSmoke.Initialize(25);
		emitterSmoke.play();
	}

	
	emitterSmoke.update(deltaTime);
	emitterSmoke.draw();

	////Second Particle Emitter////
	     ////Fire////
	static ParticleEmitter emitterFire;
	static bool erInit = false;
	if (!erInit)
	{
		erInit = true;

		//Properties 
		//Random Colour
		emitterFire.randomizeColour = true;
		//Random Velocity
		//emitterFire.randomizeVelocity = true;
		//Set Velocity
		emitterFire.initialVelocity = 25.0f;
		//Draw Sprite
		emitterFire.drawSpriteFire = true;
		//emitterFire.drawCube = true;
		emitterFire.initialMass = 10.0f;
		emitterFire.initialLife = 2.0f;
		//Emitter Initial Position
		emitterFire.initialPosition = TTK::Vector3(-6.0f, 5.0f, 0.0f);

		emitterFire.Initialize(5);
		emitterFire.play();
		
	}

	emitterFire.update(deltaTime);
	emitterFire.draw();
	


	////Third Particle Emitter////
	      ////Fireworks or Trail////
	static ParticleEmitter emitterTrail;
	static bool trailInit = false;
	if (!trailInit)
	{
		trailInit = true;

		//Properties 
		//Random Colour
		emitterTrail.randomizeColour = true;
		//Random Velocity
		emitterTrail.randomizeVelocity = true;
		//Draw Sprite
		emitterTrail.randomizeSize = true;
		emitterTrail.drawSpriteTrail = true;
		emitterTrail.drawCube = true;
		emitterTrail.initialMass = 5.0f;
		emitterTrail.initialLife = 5.0f;
		emitterTrail.initialPosition = TTK::Vector3(-5.0f, -2.6f,-5.0f);
		

		emitterTrail.Initialize(15);
		emitterTrail.play();
	}

	emitterTrail.update(deltaTime);
	emitterTrail.draw();

	
	glutSwapBuffers();
	
}


/* function void KeyboardCallbackFunction(unsigned char, int,int)
* Description:
*   - this handles keyboard input when a button is pressed
*/
void KeyboardCallbackFunction(unsigned char key, int x, int y)
{
	switch (key)
	{
		// Camera
	case 'a':
	case 'A':
		camera.moveLeft();
		break;
	case 'd':
	case 'D':
		camera.moveRight();
		break;
	case 'w':
	case 'W':
		camera.moveForward();
		break;
	case 's':
	case 'S':
		camera.moveBackward();
		break;
	case 'q':
	case 'Q':
		camera.moveUp();
		break;
	case 'e':
	case 'E':
		camera.moveDown();
		break;
	default:
		break;
	}
}
/* function void KeyboardUpCallbackFunction(unsigned char, int,int)
* Description:
*   - this handles keyboard input when a button is lifted
*/
void KeyboardUpCallbackFunction(unsigned char key, int x, int y)
{

}

void SpecialInputCallbackFunction(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		position.z += 2.0f * deltaTime;
		break;
	case GLUT_KEY_DOWN:
		position.z -= 2.0f * deltaTime;
		break;
	case GLUT_KEY_LEFT:
		position.x += 2.0f * deltaTime;
		break;
	case GLUT_KEY_RIGHT:
		position.x -= 2.0f * deltaTime;
		break;
	}
}
/* function TimerCallbackFunction(int value)
* Description:
*  - this is called many times per second
*  - this enables you to animate things
*  - no drawing, just changing the state
*  - changes the frame number and calls for a redisplay
*  - FRAME_DELAY_SPRITE is the number of milliseconds to wait before calling the timer again
*/
void TimerCallbackFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(FRAME_DELAY_SPRITE, TimerCallbackFunction, 0);

	// Calculate new deltaT for potential updates and physics calculations
	static int elapsedTimeAtLastTick = 0;
	int totalElapsedTime = glutGet(GLUT_ELAPSED_TIME);

	deltaTime = totalElapsedTime - elapsedTimeAtLastTick;
	deltaTime /= 1000.0f;
	elapsedTimeAtLastTick = totalElapsedTime;
}

/* function WindowReshapeCallbackFunction()
* Description:
*  - this is called whenever the window is resized
*  - and sets up the projection matrix properly
*  - currently set up for an orthographic view (2D only)
*/
void WindowReshapeCallbackFunction(int w, int h)
{
	windowWidth = w;
	windowHeight = h;
	TTK::Graphics::SetCameraMode2D(w, h);
}

void MouseClickCallbackFunction(int button, int state, int x, int y)
{
	mousePosition.x = x;
	mousePosition.y = y;

	camera.setMousePosition(mousePosition);

	switch (state)
	{
	case GLUT_DOWN:
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			// left button input goes here
			break;
		default:
			break;
		}

	default:
		break;
	}
}


/* function MouseMotionCallbackFunction()
* Description:
*   - this is called when the mouse is clicked and moves
*/
void MouseMotionCallbackFunction(int x, int y)
{
	mousePosition.x = x;
	mousePosition.y = y;

	camera.rotateXY(x, y);
}

/* function MousePassiveMotionCallbackFunction()
* Description:
*   - this is called when the mouse is moved in the window
*/
void MousePassiveMotionCallbackFunction(int x, int y)
{

}

/* function main()
* Description:
*  - this is the main function
*  - does initialization and then calls glutMainLoop() to start the event handler
*/
int main(int argc, char **argv)
{
	/* initialize the window and OpenGL properly */
	glutInit(&argc, argv);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Particles");

	/* set up our function callbacks */
	glutDisplayFunc(DisplayCallbackFunction);
	glutKeyboardFunc(KeyboardCallbackFunction);
	glutKeyboardUpFunc(KeyboardUpCallbackFunction);
	glutReshapeFunc(WindowReshapeCallbackFunction);
	glutMouseFunc(MouseClickCallbackFunction);
	glutMotionFunc(MouseMotionCallbackFunction);
	glutPassiveMotionFunc(MousePassiveMotionCallbackFunction);
	glutSpecialFunc(SpecialInputCallbackFunction);
	glutTimerFunc(1, TimerCallbackFunction, 0);

	TTK::Graphics::SetBackgroundColour(0.0f, 0.0f, 1.0f);
	TTK::Graphics::ClearScreen();

	/* initialize TTK */
	TTK::InitializeTTK();

	///* Init Image Library */
	glEnable(GL_TEXTURE_2D);
	//ilInit();
	//iluInit();
	//ilutRenderer(ILUT_OPENGL);

	/* Load scene Textures */
	//linker error needs fix, Ilut 
	//floorTex = ilutGLLoadImage("..//img//earth.png");

	// Set random seed
	// if this is uncommented, then every time you run your program 
	// you will get different random numbers. Otherwise you will get the
	// same random numbers everytime.
	//srand((unsigned)time(0));

	/* start the event handler */
	glutMainLoop();
	return 0;
}