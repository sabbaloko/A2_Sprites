#pragma once

#include <math.h>
#include <random>

// Linear interpolation 

template <typename T>
T lerp(T d0, T d1, float t)
{
	return d0 * (1 - t) + d1 * t;
}

// Catmull-Rom interpolation

// Returns a point between p1 and p2
template <typename T>
T catmull(T p0, T p1, T p2, T p3, float t)
{
	return	((p1 * 2.0f) + (-p0 + p2) * t +
		((p0 * 2.0f) - (p1 * 5.0f) + (p2 * 4.0f) - p3) * (t * t) +
		(-p0 + (p1 * 3.0f) - (p2 * 3.0f) + p3) * (t * t * t)) * 0.5f;
}

// Bezier interpolation

// Bezier degree 0
template <typename T>
T bezier(T p0, float t)
{
	return p0;
}

// Bezier degree 1
// aka just LERP
template <typename T>
T bezier(T p0, T p1, float t)
{
	return lerp(bezier(p0, t), bezier(p1, t), t);
}

// Bezier degree 2
template <typename T>
T bezier(T p0, T p1, T p2, float t)
{
	return lerp(bezier(p0, p1, t), bezier(p1, p2, t), t);
}

// Bezier degree 3
template <typename T>
T bezier(T p0, T p1, T p2, T p3, float t)
{
	return lerp(bezier(p0, p1, p2, t), bezier(p1, p2, p3, t), t);
}
// Utility function for geting random numbers

//Return a random float between 0 and 1
inline float randomFloat01()
{
	return (float)rand() / (float)RAND_MAX;
}

inline float randomFloatRange(float min = -1.0f, float max = 1.0f)
{
	return min + ((max - min) * rand()) / (RAND_MAX + 1.0f);
}
//Direction
inline TTK::Vector3 randomDirection()
{
	return TTK::Vector3(randomFloatRange(), randomFloatRange(), randomFloatRange());
}
//Colour
inline TTK::Vector3 randomColourRGB()
{
	return TTK::Vector3(randomFloatRange(0.0f), randomFloatRange(0.0f), randomFloatRange(0.0f));
}

//Size
inline TTK::Vector3 randomizeSize()
{
	return TTK::Vector3(randomFloatRange(0.0f), randomFloatRange(0.0f), randomFloatRange(0.0f));
}