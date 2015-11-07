//////////////////////////////////////////////////////////////////////////
//
// This header is a part of the Tutorial Tool Kit (TTK) library. 
// You may not use this header in your GDW games.
//
// This is the complete Quaternion class
//
// Michael Gharbharan 2015
//
//////////////////////////////////////////////////////////////////////////

#pragma once

#ifdef TTK_EXPORTS
#define TTK_API __declspec(dllexport)
#else
#define TTK_API __declspec(dllimport)
#endif

#include "TTK/TTK.h"

namespace TTK
{
	class TTK_API Quaternion
	{
	public:
		// Initialize to identity (1, 0, 0, 0)
		Quaternion();

		// Initialize from four values
		Quaternion(float _w, float _x, float _y, float _z);

		// Initialize from angle (radians) and axis
		Quaternion(float angleRad, TTK::Vector3 axis); 

		// Exact same as Vector3 functions, but in four dimensions
		static float magnitude(Quaternion a);
		static Quaternion normalize(Quaternion a);
		
		// Used to rotate Vector by Quaternion
		static TTK::Vector3 rotateVector(Quaternion q, const TTK::Vector3 b);

		// Converts quaternion to a rotation matrix that can be
		// plugged into a homogeneous transformation matrix
		Matrix3x3 toMatrix3x3();

		// Used to interpolate between two Quaternions
		static Quaternion slerp(Quaternion q0, Quaternion q1, float t);

		// Quaternion dot

		// Used to combine two quaternions
		Quaternion operator*(const Quaternion &b) const;

	private:
		float w;
		union
		{
			struct
			{
				float x, y, z;
			};
			struct
			{
				TTK::Vector3 v;
			};
		};
	};
}