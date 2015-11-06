#ifndef OBJECT_H
#define OBJECT_H

#include "TTK/TTK.h"
#include <vector>

class Object
{
private:
	TTK::Matrix4x4 localTranformationMatrix; // transformation relative to parent
	TTK::Matrix4x4 localToWorldTransformationMatrix; // transform relative to world

	Object* parent;
	std::vector<Object*> children;

public:
	Object();
	//~GameObject(); // If wanted to handle removing children, put logic here

	void Draw(); // Draws a cube at the world position

	void Update(); // calculates the local and global matrices

	void addChild(Object* newChild);

	TTK::Matrix4x4 getLocalToWorldMatrix();
	TTK::Vector3 getWorldPosition();
	TTK::Quaternion getWorldRotation();

	TTK::Vector3 localPosition;
	TTK::Quaternion localRotation;

	TTK::Vector4 colour;


	float localScale;
	float rotX, rotY, rotZ; // local rotations as euler (degree)
	float degToRad = 3.14159f / 180.0f;

};

#endif // !GAMEOBJECT_H