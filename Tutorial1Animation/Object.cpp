#include "Object.h"

Object::Object()
{
	rotX = rotY = rotZ = 0.0f;
	localScale = 1.0f;
	parent = nullptr;

	colour.a = 1.0f;
}

void Object::Update()
{
	// Update rotation
	// Construct quats for each axis and plug in the corresponding euler angle
	TTK::Quaternion qX(rotX * degToRad, TTK::Vector3(1.0f, 0.0f, 0.0f));
	TTK::Quaternion qY(rotY * degToRad, TTK::Vector3(0.0f, 1.0f, 0.0f));
	TTK::Quaternion qZ(rotZ * degToRad, TTK::Vector3(0.0f, 0.0f, 1.0f));

	localRotation = qZ * qY * qX; // XYZ rotation order

	// Update local matrix
	localTranformationMatrix = TTK::Matrix4x4(localRotation.toMatrix3x3(), localPosition, localScale);

	
}

void Object::Draw()
{
	//TTK::Vector3 wPos = getWorldPosition();
	//TTK::Quaternion wRot = getWorldRotation();
	//
	//// Rotate unit axis
	//TTK::Vector3 rotatedLocalX = TTK::Quaternion::rotateVector(wRot, TTK::Vector3(1.0f, 0.0f, 0.0f));
	//TTK::Vector3 rotatedLocalY = TTK::Quaternion::rotateVector(wRot, TTK::Vector3(0.0f, 1.0f, 0.0f));
	//TTK::Vector3 rotatedLocalZ = TTK::Quaternion::rotateVector(wRot, TTK::Vector3(0.0f, 0.0f, 1.0f));
	//
	//// Colours
	//TTK::Vector3 red(1.0f, 0.0f, 0.0f);
	//TTK::Vector3 green(0.0f, 1.0f, 0.0f);
	//TTK::Vector3 blue(0.0f, 0.0f, 1.0f);
	//
	//// Draw the vectors to sceen
	//TTK::Graphics::DrawVector(wPos.values, rotatedLocalX.values, 2.0f, red.values);
	//TTK::Graphics::DrawVector(wPos.values, rotatedLocalY.values, 2.0f, green.values);
	//TTK::Graphics::DrawVector(wPos.values, rotatedLocalZ.values, 2.0f, blue.values);
	//
	//// Draw the joint
	//TTK::Graphics::DrawSphere(localToWorldTransformationMatrix, colour);
	//
	//if (parent)
	//{
	//	TTK::Vector3 parentWorldPosition = parent->getWorldPosition();
	//
	//	// Draw line expects positions in world space
	//	TTK::Graphics::DrawLine(wPos.values, parentWorldPosition.values, 5.0f);
	//}
	//
	//// Draw the children
	//for (int i = 0; i < children.size(); i++)
	//{
	//	children[i]->Draw();
	//}
}
